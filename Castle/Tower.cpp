#include "Tower.h"


Tower::Tower()
{
	SetHealth(TowerInitHealth);
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
void Tower::SetKilledEnemiesNumber(int killedEnemiesNumber)
{
	KilledEnemiesNumber = killedEnemiesNumber;
}
int Tower::GetKilledEnemiesNumber() const
{
	return KilledEnemiesNumber;
}

Tower::~Tower()
{

}