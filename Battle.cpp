#include "Battle.h"
#include "InputGenerator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Battle::Battle()
{
	EnemyCount = 0;
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
			int a = rand() % (100);

			switch (stoi(word, 0, 10))
			{
			case 1:
				if (a >= 20)
					type = FIGHTER;
				else
					type = FREEZER;
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

			Enemy *e;
			switch (type)
			{
			case FREEZER:
				e = new EnemyFreezer(id, t, h, Pow, rld, reg , type);
				break;
			case HEALER:
				e = new EnemyHealer(id, t, h, Pow, rld, reg , type);
				break;
			default :
				e = new EnemyFighter(id, t, h, Pow, rld, reg , type);

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
			InactiveEnemies.Dequeue(e);
			if (EnemyCount < MaxEnemyCount)
				BEnemiesForDraw[EnemyCount++] = e;

			REGION h = e->GetRegion();
			//cout << endl << InactiveEnemies.GetSize();
			ActiveEnemies[h].Enqueue(e);
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
		BEnemiesForDraw[i]->DecrementDist();
	}
}

void Battle::checkDead()   //test all the "tobeTested" queues and if the enemy is dead, it moves to dead queues. else the enemy is back to Active elements
{
	Tower *Towers = BCastle.getTowers();
	for (int j = 0; j < NoOfRegions;j++)
	{
		while (!tobeTested[j].IsEmpty())
		{
			Enemy* x; 
			tobeTested[j].Dequeue(x);
			if (x->isKilled())
			{
				KilledEnemies.Enqueue(x);
				Towers[j].IncrementKilledEnemies();
				DecrementEnemiesCount(x);
			}
			else
			{
				ActiveEnemies[j].Enqueue(x);
				Towers[j].SetEnemiesNumber(ActiveEnemies[j].GetSize());
				
			}
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


void Battle::RunSimulation()
{
	InputGenerator(); //Generate Input file
	Simulation();
}


void Battle::Simulation()
{

	int clock;
	cout << "Enter the time of the Simulation" << endl;
	cin >> clock;

	GUI* pGUI = new GUI;
	pGUI->PrintMessage("Press Mouse Click To start");
	Tower *Towers = BCastle.getTowers();

	AddEnemy_InputFile();
	ActivatedEnemies(0);

	Point p;
	pGUI->GetPointClicked(p);
	
	pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

	int x = 0;
	do
	{
		DecrementClocks();
		//Tower Attack
		int enemies_counter;
	
		for (int j = 0; j < NoOfRegions; j++)
		{
			if (ActiveEnemies[j].GetSize() > Towers[j].GetattackCapacity())
				enemies_counter = Towers[j].GetattackCapacity();
			else
				enemies_counter = ActiveEnemies[j].GetSize();

			for (int i = 0; i < enemies_counter; i++)
			{
				if (ActiveEnemies[j].GetSize() != 0)
				{
					Enemy* tobeAttacked = ActiveEnemies[j].Dequeue();
					Towers[j].attack(tobeAttacked);
					tobeTested[j].Enqueue(tobeAttacked);
				}
			}
		}

		checkDead(); //Remove ememies from Active list to killed list if it's dead
		/*fighting*/
		pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

		ActivatedEnemies(x);
		DecrementDistanceAll();

		int ActiveEnemiesNumber = 0;
		int KilledEnemiesNumber = 0;
		int healthoftower = 0;
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

		pGUI->PrintMessage(msg);
		pGUI->GetPointClicked(p);
		x++;
	} while (x != clock);
}

