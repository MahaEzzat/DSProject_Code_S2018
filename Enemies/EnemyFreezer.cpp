#include "EnemyFreezer.h"
#include <iostream>

EnemyFreezer::EnemyFreezer(int id, double t, double h, double Pow, double rld, REGION r_region, int d) : Enemy(id, t, h, Pow, rld, r_region, d)
{
	Clr = FEEZER_CLR;
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