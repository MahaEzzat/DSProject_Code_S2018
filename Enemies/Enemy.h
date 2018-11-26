#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

//Enemies colors for next phases
//You can choose whatever colors you like for your enemies
const color FIGHTER_CLR = DARKBLUE;
const color HEALER_CLR = ORANGERED;


// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr = FIGHTER_CLR;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
						//Always positive (ranges from 2 to 60)

	double priority;//priority of the enemy
	double Health;	//Enemy health
	double power;   //Enemy attack power
	double LT;      //Enemy Life time 
	double KD;      //Enemy Killed time
	double FD;      //Enemy First-shot delay
	double T;       //Enemy Arrival time
	double RLD;     //Enemy reload period
	ENEMY_STATE state;    //Enemy State (Frozen,Inaction,Reloading)


public:
	Enemy(REGION r_region, int d = MaxDistance);
	 ~Enemy();

	color GetColor() const;
	REGION GetRegion() const;


	void DecrementDist();
	void SetDistance(int d);
	int GetDistance() const;
	void Damage();

	// Getter and Setter
	void SetKD(double kd);
	double GetKD() const;
	void SetFD(double fd);
	double GetFD() const;
	double GetPriority() const;
	void CalPriority();

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	//All enemies can move color based
	//virtual void Act() = 0;	//Acting means fighting or healing

	//


};
