#pragma once
#include "Enemy.h"

class EnemyFighter : public Enemy

{

public:
	EnemyFighter(int id, double t, double h, double Pow, double rld, REGION r_region, int d = MaxDistance);
	~EnemyFighter();
	virtual void Act();
	virtual void Move();

};