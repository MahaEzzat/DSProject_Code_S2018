#pragma once
#include "..\Defs.h"


class Tower
{
private:
	double Health;			   //Tower Health
	double Power;			   //Tower Power
	TOWER_STATE state;		   //Tower state(Active,Freezed,Killed)
	int EnemiesNumber;		   //active enemies number	
	int KilledEnemiesNumber;   //killed enemies number



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

