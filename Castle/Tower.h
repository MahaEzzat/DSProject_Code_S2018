#pragma once
#include "..\Defs.h"
#include "Enemyqueue.h"
#include "Heap.h"

class Tower
{
private:
	double Health;			   //Tower Health
	double Power;			   //Tower Power
	TOWER_STATE state;		   //Tower state(Active,Freezed,Killed)
	int EnemiesNumber;		   //active enemies number	
	int KilledEnemiesNumber;   //killed enemies number

	Heap<MaxEnemyCount/4 +1> ActiveEnemies;			   //heap of Active Enemies*
	Enemyqueue<MaxEnemyCount / 4 + 1> InactiveEnemies; //queue of Inactive Enemies*
	Enemyqueue<MaxEnemyCount / 4 + 1> KilledEnemies;   //queue of kileed Enemies*

public:

	Tower();
	~Tower();

	//setter and getters
	void SetHealth(double h);
	double GetHealth() const;
	void SetPower(double Power);
	double GetPower() const;
	void SetEnemiesNumber(int EnemiesNumber);
	int GetEnemiesNumber() const;
	void SetKilledEnemiesNumber(int KilledEnemiesNumber);
	int GetKilledEnemiesNumber() const;
	//

	//action methods
	//void attack();
	//void freeze();
	//
	

};

