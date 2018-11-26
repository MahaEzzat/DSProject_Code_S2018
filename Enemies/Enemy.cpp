#include "Enemy.h"


Enemy::Enemy(int id, double t, double h, double Pow, double rld, REGION r_region, int d)
{
	Region = r_region;
	ID = id;
	T = t;
	Health = h;
	RLD = rld;
	power = Pow;
	SetDistance(d);
}

Enemy::~Enemy()
{
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}
void Enemy::SetKD(double kd)
{
	KD = kd;
}
double Enemy::GetKD() const
{
	return KD;
}
void Enemy::SetFD(double fd)
{
	FD = fd;
}
double Enemy::GetFD() const
{
	return FD;
}

double Enemy::GetPriority() const
{
	return priority;
}

void Enemy::CalPriority()
{
	priority = Health + power + 1 / Distance;
}

double Enemy::GetArrivalTime() const
{
	return T;
}