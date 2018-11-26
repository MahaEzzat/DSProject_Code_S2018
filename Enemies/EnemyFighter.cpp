#include "EnemyFighter.h"
#include <iostream>

EnemyFighter::EnemyFighter(int id, double t, double h, double Pow, double rld, REGION r_region, int d) : Enemy(id, t,h, Pow, rld, r_region, d)
{
	Clr = FIGHTER_CLR;
}

void EnemyFighter::Act()
{
	std::cout << "ok" << endl;
}

void EnemyFighter::Move()
{
	std::cout << "ok" << endl;
}

EnemyFighter::~EnemyFighter()
{
	
}