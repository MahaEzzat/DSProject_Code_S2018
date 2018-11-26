#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "Defs.h"

using namespace std;
void InputGenerator()
{
	ofstream output;
	output.open("input.txt");
	srand(time(0));
	int maxNo = 50 + rand() % (30 - 10 + 1);
	double startPower = 100 + rand() % (60 - 10 + 1);
	output << to_string(MaxEnemyCount) << "\t" << maxNo << "\t" << startPower << endl;
	//<=20% are healers
	//>=80% are fighters
	//there are 300 enemies
	int noHealers = 0;
	int noFighters = 0;
	vector<int> randomRoles;
	vector<char> randomPlace;
	vector<int> randomPower;
	vector<int> randomHealth;
	vector<int> randomReload;
	vector<int> randomTime;
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = 1 + rand() % (MaxEnemyCount);
		if (x <= 60)
		{
			noHealers++;
			randomRoles.push_back(2);
		}
		else
		{
			noFighters++;
			randomRoles.push_back(1);
		}
	}
	//now we have our randomized list of enemies
	//now we need to spread them in between different regions evenly -but not so evenly- :")) for each region
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = 1 + rand() % (100);
		if (x <= 29)
		{
			randomPlace.push_back('A');          //Region A
		}
		if (29 < x <= 43)
		{
			randomPlace.push_back('B');          //Region B
		}
		if (41 < x <= 71)
		{
			randomPlace.push_back('C');         //Region C
		}
		if (71 < x <= 92)
		{
			randomPlace.push_back('D');         //Region D
		}
	}
	//now we have almost randomized list of the enemies places
	//now we need to give them almost randomized health with at least initial health of 65 and maximum health of 100
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = 1 + rand() % (35);
		randomHealth.push_back(65 + x);

	}
	//now we need to do the same to the power of the enemies with at least power of 70 and maximum power of 100
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = 1 + rand() % (30);
		randomPower.push_back(70 + x);
	}
	//randomized reload time with at least 1 time step reload time and 4 as maximum
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = 1 + rand() % 4;
		randomReload.push_back(x);
	}
	//randomized arrival time with at maximum value as MaxTimeStep(defined in Defs.h)
	//that means that at time step 25 all enemies are spawned
	for (int i = 1; i <= MaxEnemyCount; i++)
	{
		int x = rand() % (MaxTimeStep);
		randomTime.push_back(x);
	}
	sort(randomTime.begin(), randomTime.end());
	for (int i = 1; i <= MaxEnemyCount; i++)
	{

		output << i << "\t" << randomRoles[i - 1] << "\t" << randomTime[i - 1] << "\t" << randomHealth[i - 1] << "\t" << randomPower[i - 1] << "\t" << randomReload[i - 1] << "\t" << randomPlace[i - 1] << endl;

	}

	output << -1 << endl;
	output.close();
}