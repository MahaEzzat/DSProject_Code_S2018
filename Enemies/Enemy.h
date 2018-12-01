#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <iostream>


//Enemies colors for next phases
//You can choose whatever colors you like for your enemies
const color FIGHTER_CLR = ORANGERED;
const color FEEZER_CLR = CYAN;
const color HEALER_CLR = LIGHTGREEN;


// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int distance = MaxDistance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)
	double priority;//priority of the enemy
	double Health;	//Enemy health
	double power;   //Enemy attack power
	double LT = 0;      //Enemy Life time 
	double KD;      //Enemy Killed time
	double FD;      //Enemy First-shot delay
	double T;       //Enemy Arrival time
	double RLD;     //Enemy reload period
	                //We Would Make The Enemy Reload Every 5 steps
	ENEMY_TYPE type;
	ENEMY_STATE state;          //Enemy State (Frozen,Inaction,Reloading)
	int clockIce;				//Clock for freezed time
	int clockReload;             //Clock for reload time
	int steps = 0;              //Counting the Enemy Steps 
public:
	Enemy(int id, double t, double h, double Pow, double rld, REGION r_region, ENEMY_TYPE typee);
	 ~Enemy();
	color GetColor() const;
	REGION GetRegion() const;
	void DecrementDist();
	void SetDistance(int d);
	int GetDistance() const;
	double GetHealth() const;
	void SetKD(double kd);
	ENEMY_TYPE GetType() const;
	double GetKD() const;
	void SetFD(double fd);
	double GetFD() const;
	double GetPriority() const;
	double GetArrivalTime() const;
	void CalPriority();
	void Damage(double bullet);
	void frozen();                 //the enemy would be freezed for 2 time step
	void Clocks();      
	void Reloading();
	bool isKilled();
	int GetId() const;
	virtual void Act() = 0;	

	//


};

