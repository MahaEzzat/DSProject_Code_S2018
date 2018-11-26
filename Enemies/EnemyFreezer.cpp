#include "EnemyFreezer.h"
#include <iostream>

EnemyFreezer::EnemyFreezer(REGION r_region, int d ) : Enemy(r_region, d)
{
	Clr = DARKOLIVEGREEN;
}

void EnemyFreezer::Act()
{
	std::cout << "ok" << endl;
}

void EnemyFreezer::Move()
{
	std::cout << "ok" << endl;
}

EnemyFreezer::~EnemyFreezer()
{

}