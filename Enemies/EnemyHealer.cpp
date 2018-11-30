#include "EnemyHealer.h"
#include <iostream>

EnemyHealer::EnemyHealer(int id, double t, double h, double Pow, double rld, REGION r_region,ENEMY_TYPE typpe) : Enemy(id, t, h, Pow, rld, r_region,typpe)
{
	Clr = HEALER_CLR;
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