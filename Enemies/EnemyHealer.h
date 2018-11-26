#pragma once
#include "Enemy.h"

class EnemyHealer : public Enemy

{

public:
	EnemyHealer(int id, double t, double h, double Pow, double rld, REGION r_region, int d = MaxDistance);
	~EnemyHealer();
	virtual void Act();
	virtual void Move();

};