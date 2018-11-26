#pragma once

#include "Enemies\EnemyFighter.h"
#include "Enemies\/EnemyFreezer.h"
#include "Enemies\EnemyHealer.h"
#include "Enemies\Enemy.h"
#include "Castle\Enemyqueue.h"
#include "Castle\Enemyheap.h"
#include <fstream>
#include "Castle\Castle.h"

// it is the controller of the project
class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy* BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Enemyheap<MaxEnemyCount> ActiveEnemies;		//heap of Active Enemies*
	Enemyqueue<MaxEnemyCount> InactiveEnemies; //queue of Inactive Enemies*
	Enemyqueue<MaxEnemyCount> KilledEnemies;   //queue of kileed Enemies*

public:
	
	Battle();
	Castle * GetCastle();
	void RunSimulation();
	void AddEnemy_InputFile();	//Loading data from input file into enemies queues
	void DecrementDistALL();	//Decrement distance for all active enemies
	void ActicvateEnemies(double t);    //Add Recent Active enemies from Inactive list to Active list
	void Just_A_Demo();			//just to show a demo and should be removed in phase1 1 & 2

	//
	// TODO: Add More Member Functions As Needed
	//
};

