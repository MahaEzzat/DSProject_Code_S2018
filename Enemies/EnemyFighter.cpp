#include "EnemyFighter.h"
#include <iostream>

EnemyFighter::EnemyFighter(int id, double t, double h, double Pow, double rld, REGION r_region, ENEMY_TYPE typee) : Enemy (id, t,h, Pow, rld, r_region, typee )
{
	Clr = FIGHTER_CLR;
}

void EnemyFighter::Act()
{
	
}

void EnemyFighter::Move()
{
	std::cout << "ok" << endl;
}

EnemyFighter::~EnemyFighter()
{
	
}