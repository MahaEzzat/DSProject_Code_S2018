#pragma once
#include "..\Defs.h"
#include "Enemyheap.h"
#include "Enemyqueue.h"
#include "..\Enemies\Enemy.h"

class Tower
{
private:

	double Health;			   //Tower Health
	double Power;			   //Tower Power
	TOWER_STATE state = Active;		   //Tower state(Active,Freezed,Killed)
	int EnemiesNumber;		   //active enemies number	
	int KilledEnemiesNumber;   //killed enemies number
	double freezed = 0;
	REGION regioon;
	int attackCapacity;          //the number of enemies the tower could attack every time step

public:

	Tower();
	~Tower();
	//setter and getters
	void SetHealth(double h);
	double GetHealth() const;
	void SetPower(double Power);
	void SetRegion(int x);
	double GetPower() const;
	void SetEnemiesNumber(int EnemiesNumber);
	int GetEnemiesNumber() const;
	void IncrementKilledEnemies();
	int GetKilledEnemiesNumber() const;
	void Icing(double h);
	void Damaged(double h);
	int GetState();
	void SetattackCapacity(int attack_number);
	int GetattackCapacity() const;
	//action methods
	void attack(Enemy* e);
	//void freeze();
	//
	

};

