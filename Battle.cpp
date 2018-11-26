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

	if (loadfile)
	{
		int id, dist;
		double t, h, Pow, rld;
		REGION reg;
		string Type;
		ENEMY_TYPE type;

		string word;

		//Reading Tower Health
		loadfile >> word; 
		TowerInitHealth = stoi(word, 0, 10);

		//Reading Tower Enemies Number
		loadfile >> word; 
		TowerAttackCount = stoi(word, 0, 10);

		//Reading Tower Power
		loadfile >> word; 
		TowerInitPower = stoi(word, 0, 10);

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
				if (a >= 15)
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
				e = new EnemyFreezer(id, t, h, Pow, rld, reg);
				break;
			case HEALER:
				e = new EnemyHealer(id, t, h, Pow, rld, reg);
				break;
			default :
				e = new EnemyFighter(id, t, h, Pow, rld, reg);

			} 
		InactiveEnemies.Enqueue(e);

		//Reading the Sequence number
		loadfile >> word; 
		id = stoi(word, 0, 10);
		} while (id != -1);
	}
}

void Battle::ActicvateEnemies(double t)
{
	Enemy* e = NULL;
	if (!InactiveEnemies.IsEmpty())
	{
		InactiveEnemies.PeekFront(e);
		while (e->GetArrivalTime() < t)
		{
			InactiveEnemies.Dequeue(e);
			if (EnemyCount < MaxEnemyCount)
				BEnemiesForDraw[EnemyCount++] = e;
			ActiveEnemies.Enqueue(e);
		}
	}

}

void Battle::DecrementDistALL()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		BEnemiesForDraw[i]->DecrementDist();
	}
}


void Battle::RunSimulation()
{
	InputGenerator(); //Generate Input file
	Just_A_Demo();
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{
	
	std::cout<<"\nWelcome to Castle Battle:\n";
	std::cout<<"\nIn phase2, you will be asked to select game mode\n";
	std::cout<<"\nFor now just press ENTER key to continue...";
	
	char tmp[10];
	std::cin.getline(tmp,10);
	//
	// THIS IS JUST A DEMO
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//
	
	GUI * pGUI = new GUI;

	pGUI->PrintMessage("This is Just a Demo. It should be changed ib phase1 & phase2. Click to move to next step");

	
	 
	// Declare some enemies and fill their data
	// In the game, enemies should be loaded from an input file
	// and should be dynamically allocated


	// Adding the enemies to the battle
	AddEnemy_InputFile();
	ActicvateEnemies(0);

	// Drawing the battle
	pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

	Point p;
	pGUI->GetPointClicked(p);

	// Now a demo to move enemies some time steps
	// TimeStep is a normal integer that is incremented each time by 1
	for(int TimeStep = 1 ; TimeStep <= MaxTimeStep ; TimeStep++)
	{
		//Add Recent Active enemies from Inactive list to Active list
		ActicvateEnemies(TimeStep);

		// Decrement the distance of each enemy. Just for the sake of demo

		DecrementDistALL();

		// Redraw the enemies
		pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

		pGUI->GetPointClicked(p);
	}

	delete pGUI;
}