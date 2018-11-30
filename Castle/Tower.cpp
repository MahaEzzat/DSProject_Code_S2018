#include "Tower.h"
#include <cstdlib>
#include <ctime>

Tower::Tower()
{
	EnemiesNumber = 0;
	KilledEnemiesNumber = 0;
}


void Tower::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}
void Tower::SetPower(double power)
{
	Power = power;
}
double Tower::GetPower() const
{
	return Power;
}
void Tower::SetEnemiesNumber(int enemiesNumber)
{
	EnemiesNumber = enemiesNumber;
}
int Tower::GetEnemiesNumber() const
{
	return EnemiesNumber;
}
void Tower::IncrementKilledEnemies()
{
	KilledEnemiesNumber++;
}
int Tower::GetKilledEnemiesNumber() const
{
	return KilledEnemiesNumber;
}

int Tower::GetState()
{
	return (int)state;
}

void Tower::Icing(double h)
{
	freezed = freezed + h;
	if (freezed >= Health * 0.2) //tower is weak so it gets frozen fast
	{
		state = Freezed;
	}
}
void Tower::Damaged(double h)
{
	Health = Health - h;
	if (Health <= 0)
	{
		state = Killed;
	}
}

void Tower::SetRegion(int x)
{
	regioon = (REGION)x;
}

//randomize the fires to make 20% of it as ice

void Tower::attack(Enemy* e)
{
	srand(time(0));
	int x = 1 + rand() % 99;
	int distance = e->GetDistance();
	double bulletHealer = (Power * (1 / distance)) / 2;
	double bulletFire = (Power * (1 / distance));

	if (x >= 20) // the tower shoots fire
	{

		if ((e->GetType() == FIGHTER) || (e->GetType() == FREEZER))
		{
			e->Damage(bulletFire);
		}
		else if (e->GetType() == HEALER)
		{
			e->Damage(bulletHealer);
		}
	}
	//in case the tower shoots ice on enemies 
	else
	{
		e->frozen();   
	}
}


Tower::~Tower()
{

}