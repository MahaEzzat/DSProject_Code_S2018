#include "Battle.h"
#include "InputGenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

Battle::Battle()
{
	EnemyCount = 0;
	BCastle.SetBattlePtr(this);
}

Enemyheap<MaxEnemyCount>* Battle::GetActiveList(int index)
{
	return &(ActiveEnemies[index]);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::AddEnemy_InputFile()
{
	string loadfilename = "input.txt";
	fstream loadfile;
	loadfile.open(loadfilename, ios::in);
	//specifying the tower regions

	if (loadfile)
	{
		int id;
		double t, h, Pow, rld;
		REGION reg;
		string Type;
		ENEMY_TYPE type;
		string word;
		//Reading Tower Health
		loadfile >> word;
		int TowerInitHealth = stoi(word, 0, 10);

		//Reading Tower Enemies Number
		loadfile >> word;
		int TowerAttackCount = stoi(word, 0, 10);

		//Reading Tower Power
		loadfile >> word;
		int TowerInitPower = stoi(word, 0, 10);

		//setting Towers parameters
		Tower *Towers = BCastle.getTowers();

		for (int j = 0; j < NoOfRegions; j++)
		{
			Towers[j].SetHealth(TowerInitHealth);
			Towers[j].SetPower(TowerInitPower);
			Towers[j].SetattackCapacity(TowerAttackCount);
		}

		srand(time(NULL)); // Random generator for picking 20% of Fighters as Freezers

		//Reading the Sequence number
		loadfile >> word;
		id = stoi(word, 0, 10);
		do
		{
			//Reading Enemy Type
			loadfile >> word;
			int x = rand() % (100);
			switch (stoi(word, 0, 10))
			{
			case 1:
				if (0 <= x && x < 20)
					type = FREEZER;          
				
				if (20 <= x && x< 30)
					type = COLLECTOR;      

				if (30 <= x && x < 40)
					type = WEAKEN;    

				if (40 <= x && x < 100)
					type = FIGHTER;         

				break;
			case 2:
				type = HEALER;
				break;
			default:
				break;
			}

			//Arrival Time
			loadfile >> word;
			t = stod(word);

			//Health
			loadfile >> word;
			h = stod(word);

			//Reading Power
			loadfile >> word;
			Pow = stod(word);

			//Reading RLD
			loadfile >> word;
			rld = stod(word);

			//Reading Region
			loadfile >> word;
			if (word == "A")
				reg = A_REG;
			else if (word == "B")
				reg = B_REG;
			else if (word == "C")
				reg = C_REG;
			else
				reg = D_REG;

			Tower* ptr = &((BCastle.getTowers())[reg]);
			Enemy *e;
			switch (type)
			{
			case FREEZER:
				e = new EnemyFreezer(id, t, h, Pow, rld, reg, type, ptr);
				break;
			case HEALER:
				e = new EnemyHealer(id, t, h, Pow, rld, reg, type, ptr);
				break;
			case WEAKEN:
				e = new EnemyWeaken(id, t, h, Pow, rld, reg, type, ptr);
				break;
			case COLLECTOR:
				e = new EnemyCollector(id, t, h, Pow, rld, reg, type, ptr);
				break;
			case FIGHTER:
				e = new EnemyFighter(id, t, h, Pow, rld, reg, type, ptr);

			}
			InactiveEnemies.Enqueue(e);
			//Reading the Sequence number
			loadfile >> word;
			id = stoi(word, 0, 10);
		} while (id != -1);
	}
}

void Battle::ActivatedEnemies(double t)
{
	Enemy* e = NULL;
	if (!InactiveEnemies.IsEmpty())
	{
		InactiveEnemies.PeekFront(e);
		while (e->GetArrivalTime() <= t && !InactiveEnemies.IsEmpty())
		{	
			if (EnemyCount < MaxEnemyCount)
				BEnemiesForDraw[EnemyCount++] = e;

			REGION h = e->GetRegion();
			InactiveEnemies.Dequeue(e);
			ActiveEnemies[h].Enqueue(e);
			InactiveEnemies.PeekFront(e);
		}
	}

}


void Battle::DecrementClocks()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		BEnemiesForDraw[i]->Clocks();
	}
}

void Battle::DecrementDistanceAll()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		BEnemiesForDraw[i]->Act();
		BEnemiesForDraw[i]->DecrementDist();
	}

}

void Battle::checkDead(double Time)   //test all the "tobeTested" queues and if the enemy is dead, it moves to dead queues. else the enemy is back to Active elements
{
	Tower *Towers = BCastle.getTowers();
	for (int j = 0; j < NoOfRegions;j++)
	{
		while (!tobeTested[j].IsEmpty())
		{
			Enemy* e; 
			tobeTested[j].Dequeue(e);
			e->SetFST(Time);
			if (e->isKilled())
			{
				e->SetKTS(Time);
				KilledEnemies.Enqueue(e);
				Towers[j].IncrementKilledEnemies();
				DecrementEnemiesCount(e);
			}
			else
			{
				ActiveEnemies[j].Enqueue(e);
				
			}
			Towers[j].SetEnemiesNumber(ActiveEnemies[j].GetSize() + 1);
		}
	
	}
}

void Battle::DecrementEnemiesCount(Enemy* e)
{
	//swapping the deleted enemy to the very last of the array and decrement the number by one
	for (int i = 0; i < EnemyCount; i++)
	{
		if (BEnemiesForDraw[i]->GetId() == e->GetId())
		{
			EnemyCount--;
			BEnemiesForDraw[i] = BEnemiesForDraw[EnemyCount];
			BEnemiesForDraw[EnemyCount] = nullptr;
			break;
		}
	}

}

void Battle::towerDeath()
{
	Tower* towers = BCastle.getTowers();

	for (int i = 0; i < NoOfRegions; i++)
	{	
		if (towers[i].GetState() == Killed)
		{	
			Enemy *e = ActiveEnemies[i].Dequeue();
			REGION current;
			if (e != NULL)
			{
				while (e != NULL)
				{
					moveAdjacent(e);
					current = e->GetRegion();
					ActiveEnemies[int(current)].Enqueue(e);
					e = ActiveEnemies[i].Dequeue();
				}
				towers[current].SetEnemiesNumber(towers[current].GetEnemiesNumber() + towers[i].GetEnemiesNumber());
				towers[i].SetEnemiesNumber(0);
			}

		}
	}
}

void Battle::moveAdjacent(Enemy* e)
{
	if (e->GetRegion() == A_REG)
		e->setRegion(B_REG);

	else if (e->GetRegion() == B_REG)
			e->setRegion(C_REG);

		else if (e->GetRegion() == C_REG)
				e->setRegion(D_REG);
			
			else if (e->GetRegion() == D_REG)
					e->setRegion(A_REG);
				
}

/*
    We would loop over the towers and if any is dead and any of towers has a health over 35% it will give the dead tower 10% of their health 
	else the tower is not revived
*/
void Battle::revive()
{
	Tower* towers = BCastle.getTowers();
	int Number_of_cont = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		if (towers[i].GetState() == Killed)
		{
			for (int k = 0; k < NoOfRegions; k++)
			{
				if (towers[k].GetHealth() >= 0.35 * TowerInitHealth)
				{
					Number_of_cont++;
					double tobeAdded = towers[k].GetHealth();
					towers[k].SetHealth(tobeAdded - tobeAdded*0.1);
					towers[i].SetHealth(towers[i].GetHealth() + tobeAdded*0.1);
					towers[i].setState(Active);
				}
			}
		}
	}
	if (Number_of_cont == 0)
		towerDeath();
}


void Battle::RunSimulation()
{
	InputGenerator(); //Generate Input file
	int x;
	cout << "Please Enter 0 for interactive mode or 1 for silent mode: ";
	cin >> x;
	if (x == INTERACTIVE)
		Simulation();
	else
		Silent();
}

void Battle::OutPut()
{

}

void Battle::Simulation()
{
	GUI* pGUI = new GUI;
	pGUI->PrintMessage("Press Mouse Click To start");
	Tower *Towers = BCastle.getTowers();

	AddEnemy_InputFile();

	Point p;
	pGUI->GetPointClicked(p);
	
	pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);
	bool IsEnd = false;
	string GameResult = "DRAW";

	double x = 0;
	do
	{
		ActivatedEnemies(x);
		DecrementClocks();
		//Tower Attack
		int enemies_counter;
	
		for (int j = 0; j < NoOfRegions; j++)
		{
			if (ActiveEnemies[j].GetSize() + 1 > Towers[j].GetattackCapacity())
				enemies_counter = Towers[j].GetattackCapacity();
			else
				enemies_counter = ActiveEnemies[j].GetSize() + 1;

			for (int i = 0; i < enemies_counter; i++)
			{
				Enemy* tobeAttacked = ActiveEnemies[j].Dequeue();
				if (tobeAttacked != NULL)
				{
					Towers[j].attack(tobeAttacked);
					tobeTested[j].Enqueue(tobeAttacked);
				}
			}
		}

		checkDead(x); //Remove ememies from Active list to killed list if it's dead

		revive(); 
		       
		pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);
		DecrementDistanceAll();

		int ActiveEnemiesNumber = 0;
		int KilledEnemiesNumber = 0;
		int healthoftower = 0;
		int Poweroftower = 0;
		string msg = "This is Interactive Mode, Number of Active enemies is: ";
		for (int j = 0; j < NoOfRegions; j++)
		{
			ActiveEnemiesNumber = Towers[j].GetEnemiesNumber();
			msg += to_string(ActiveEnemiesNumber) + " ";

		}
		msg += ", Number of Killed enemies is: ";
		for (int j = 0; j < NoOfRegions; j++)
		{
			KilledEnemiesNumber = Towers[j].GetKilledEnemiesNumber();
			msg += to_string(KilledEnemiesNumber) + " ";
		}
		msg += ", Health of towers are :";
		for (int j = 0; j < NoOfRegions; j++)
		{
			healthoftower = Towers[j].GetHealth();
			msg += to_string(healthoftower) + " ";
		}

		msg += ", Power of towers are :";
		for (int j = 0; j < NoOfRegions; j++)
		{
			Poweroftower = Towers[j].GetPower();
			msg += to_string(Poweroftower) + " ";
		}
		
		pGUI->PrintMessage(msg);
		pGUI->GetPointClicked(p);
		KilledEnemies.SortFD();

		x++;
		if (Towers[0].GetState() == Killed && Towers[1].GetState() == Killed && Towers[2].GetState() == Killed && Towers[3].GetState() == Killed)
		{
			IsEnd = true;
			GameResult = "LOSE";
		}
		else if (Towers[0].GetState() == NoPower && Towers[1].GetState() == NoPower && Towers[2].GetState() == NoPower && Towers[3].GetState() == NoPower)
		{
			IsEnd = true;
			GameResult = "LOSE";
		}
		else if (ActiveEnemies[0].GetSize() == -1 && ActiveEnemies[1].GetSize() == -1 && ActiveEnemies[2].GetSize() == -1 && ActiveEnemies[3].GetSize() == -1)
		{
			IsEnd = true;
			GameResult = "WIN";
		}

	} while ((x != 3 * MaxTimeStep) && !IsEnd);
	string msg = "This is the end of the game, and the result is: " + GameResult + " Press Mouse Click To exit";
	pGUI->PrintMessage(msg);
	pGUI->GetPointClicked(p);
}

void Battle::Silent()
{
	Tower *Towers = BCastle.getTowers();

	AddEnemy_InputFile();

	int x = 0;
	do
	{
		ActivatedEnemies(x);
		DecrementClocks();
		//Tower Attack
		int enemies_counter;

		for (int j = 0; j < NoOfRegions; j++)
		{
			if (ActiveEnemies[j].GetSize() + 1 > Towers[j].GetattackCapacity())
				enemies_counter = Towers[j].GetattackCapacity();
			else
				enemies_counter = ActiveEnemies[j].GetSize() + 1;

			for (int i = 0; i < enemies_counter; i++)
			{
				Enemy* tobeAttacked = ActiveEnemies[j].Dequeue();
				if (tobeAttacked != NULL)
				{
					Towers[j].attack(tobeAttacked);
					tobeTested[j].Enqueue(tobeAttacked);
				}
			}
		}

		checkDead(x); //Remove ememies from Active list to killed list if it's dead
		revive();
		DecrementDistanceAll();
		
		KilledEnemies.SortFD();
		x++;
	} while (x != 3*MaxTimeStep);
	OutPut();
}