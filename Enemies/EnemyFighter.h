#pragma once
#include "Enemy.h"

class EnemyFighter : public Enemy

{

public:
	EnemyFighter(REGION r_region, int d = MaxDistance);
	~EnemyFighter();
	virtual void Act();
	virtual void Move();

};