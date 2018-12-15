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
	{
		Health = 0; // killed
		state = Killed;
	}
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

TOWER_STATE Tower::GetState()
{
	return state;
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
	if (state == Active)
	{
		srand(time(0));
		int x =  rand() % 100;
		int distance = e->GetDistance();
		double bulletHealer = (Power * (1.0 / distance)) / 2.0;
		double bulletFire = (Power * (1.0 / distance));

		if (20<= x < 100) // the tower shoots fire
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
		if (0 <= x < 20)
		{
			e->frozen();
		}
	}

}
void Tower::SetattackCapacity(int attack_number)
{
	attackCapacity = attack_number;
}
int Tower::GetattackCapacity() const
{
	return attackCapacity;
}

Tower::~Tower()
{

}

REGION Tower::getRegion()
{
	return regioon;
}

void Tower::setState(TOWER_STATE statte)
{
	state = statte;
}