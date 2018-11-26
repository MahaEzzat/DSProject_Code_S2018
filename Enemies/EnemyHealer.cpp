#include "EnemyHealer.h"
#include <iostream>

EnemyHealer::EnemyHealer(REGION r_region, int d ) : Enemy(r_region, d)
{
	Clr = ORANGERED;
}

void EnemyHealer::Act()
{
	std::cout << "ok" << endl;
}

void EnemyHealer::Move()
{
	std::cout << "ok" << endl;
}

EnemyHealer::~EnemyHealer()
{

}