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

	Enemyheap<MaxEnemyCount> ActiveEnemies[NoOfRegions]; //heap of Active Enemies in REGIONs ABCD

	Enemyqueue<MaxEnemyCount> tobeTested[NoOfRegions];   //all the elements that have been attacked to test if they are dead
														//if not dead they would be passed to the Active list again
														//else they would be passed to killed enemies
	
	
	Enemyqueue<MaxEnemyCount> InactiveEnemies; //queue of Inactive Enemies*
	Enemyqueue<MaxEnemyCount> KilledEnemies;   //queue of kileed Enemies*

public:
	
	Battle();
	Castle * GetCastle();
	void RunSimulation();
	void AddEnemy_InputFile();	//Loading data from input file into enemies queues
	void ActivatedEnemies(double t);    //Add Recent Active enemies from Inactive list to Active list
	void Simulation();			//just to show a demo and should be removed in phase1 1 & 2
	void DecrementClocks();
	void DecrementDistanceAll();
	void checkDead();
	//
	// TODO: Add More Member Functions As Needed
	//
};

