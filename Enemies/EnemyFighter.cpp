#include "EnemyFighter.h"
#include <iostream>

EnemyFighter::EnemyFighter(REGION r_region, int d) : Enemy(r_region, d )
{
	Clr = DARKBLUE;
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