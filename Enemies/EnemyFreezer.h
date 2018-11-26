#pragma once
#include "Enemy.h"

class EnemyFreezer : public Enemy

{

public:
	EnemyFreezer(REGION r_region, int d = MaxDistance);
	~EnemyFreezer();
	virtual void Act();
	virtual void Move();

};