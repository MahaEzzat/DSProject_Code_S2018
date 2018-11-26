#pragma once
#include "Enemy.h"

class EnemyHealer : public Enemy

{

public:
	EnemyHealer(REGION r_region, int d = MaxDistance);
	~EnemyHealer();
	virtual void Act();
	virtual void Move();

};