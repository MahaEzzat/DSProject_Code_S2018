#include "Enemy.h"


Enemy::Enemy(int id, double t, double h, double Pow, double rld, REGION r_region, ENEMY_TYPE typee)
{
	Region = r_region;
	ID = id;
	T = t;
	FST = INFINITE;
	Health = h;
	RLD = rld;
	power = Pow;
	type = typee;
	CalPriority();
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
	if (distance > MinDistance && clockIce > 0)
	{
		if (this->Health >= 50)
		{
			distance--;
		}
		else if (this->Health<50) //less than half ... only move one step every two time steps
		{
			if (steps % 2 == 0)
			{
				distance--;
			}
		}
		steps++;
	}
	CalPriority();
}

int Enemy::GetDistance() const
{
	
	return distance;
}


void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		distance = d;
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
void Enemy::SetFST(double Time)
{
	if (FST > Time)
	{
		FST = Time;
		SetFD(FST - T);
	}
}
double Enemy::GetFST() const
{
	return FST;
}
double Enemy::GetFD() const
{
	return FD;
}

double Enemy::GetPriority() const
{
	return priority;
}

void Enemy::CalPriority() //Calculating Priority with Normilized Parameters with equal weignts
{
	priority = (Health / 100.0)*(1.0/3) + (power / 100.0)*(1.0/3) + (float(MinDistance) /distance)*(1.0/3);
}

double Enemy::GetArrivalTime() const
{
	return T;
}

ENEMY_TYPE Enemy::GetType() const
{
	return type;
}


double Enemy::GetHealth() const
{
	return Health;
}

void Enemy::frozen()
{
	if (this->Health <= 50)
	{
		clockIce = 2;
	}
	else if (this->Health > 50)
	{
		clockIce = 1;
	}
}

void Enemy::Reloading()
{
	if (steps % 5 == 0)
	{
		clockReload = RLD;
	}
}


void Enemy::Clocks()
{
	if (clockIce >= 0)
	{
		clockIce--;
	}
	if (clockReload >= 0)
	{
		clockReload--;
	}
}

bool Enemy::isKilled()
{
	if (Health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Enemy::Damage(double bullet)
{
	Health = Health - bullet;
}

int Enemy::GetId() const
{
	return ID;
}

void Enemy::SetArrivalTime(double t)
{
	T = t;
}

double Enemy::GetKTS() const
{
	return KTS;
}
void Enemy::SetKTS(double Time)
{
	KTS = Time;
	SetKD(KTS-FST);
	SetLT(KTS-T);
}
double Enemy::GetLT() const
{
	return LT;
}
void Enemy::SetLT(double Time)
{
	LT = Time;
}
void Enemy::setRegion(REGION reg)
{
	Region = reg;
}