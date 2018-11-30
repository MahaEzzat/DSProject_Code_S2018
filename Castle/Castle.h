#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include <vector>
#include "Tower.h"

class Castle
{

	Tower Towers[NoOfRegions];
	
public:

	Castle();
	void SetTowerHealth(REGION TowerRegion, double h);
	Tower* getTowers();
	
};
