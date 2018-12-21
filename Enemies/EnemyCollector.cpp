#include "EnemyCollector.h"
#include "..\Castle\Tower.h"
#include "..\Battle.h"
#include <iostream>

EnemyCollector::EnemyCollector(int id, double t, double h, double Pow, double rld, REGION r_region, ENEMY_TYPE typee, Tower* ptr) : Enemy(id, t, h, Pow, rld, r_region, typee, ptr)
{
	Clr = COLLECTOR_CLR;
}

void EnemyCollector::Act()
{
	double distance_of_collector = GetDistance();
	int const Array_size = 100;
	int k = 0;

	Enemyheap<MaxEnemyCount> *ActiveEnemies_copy = Tower_Ptr->GetCastlePtr()->GetBattlePtr()->GetActiveList(GetRegion());
	Enemy* eaten_enemy = ActiveEnemies_copy->Dequeue();
	Enemy *Enemy_Array[Array_size];

	while (eaten_enemy != nullptr)
	{
		double distance_of_enemyE = eaten_enemy->GetDistance();
		double relative_distanceE = abs(distance_of_enemyE - distance_of_collector);    // distance relative to healer
		double currenthealth_of_enemyE = eaten_enemy->GetHealth();
		double originalhealth_of_enemyE = eaten_enemy->GetOriginalHealth();
		if (relative_distanceE <= 4 && currenthealth_of_enemyE <= (originalhealth_of_enemyE * (1.0 / 4.0)) && GetId() != eaten_enemy->GetId())
		{
			double newhealth_of_enemyE = (GetHealth() + eaten_enemy->GetHealth());
			SetHealth(newhealth_of_enemyE);
			eaten_enemy->SetHealth(0);
		}

		Enemy_Array[k] = eaten_enemy;
		k++;
		eaten_enemy = ActiveEnemies_copy->Dequeue();
	}

	for (int i = 0; i < k; i++)
		ActiveEnemies_copy->Enqueue(Enemy_Array[i]);
}


EnemyCollector::~EnemyCollector()
{
	
}