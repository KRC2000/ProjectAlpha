#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>



#include "IEC.h"
#include "ScenesEnum.h"
#include "ResourcesEnum.h"
#include "PointersEnum.h"
#include "ItemsEnum.h"
#include "PlayerStateIndicatorsEnum.h"
//#include "PlayerConditionTypesEnum.h"
#include "Colors.h"

//#include "GUIelement.h"
//#include "Button.h"




using namespace std;
using namespace sf;
//using namespace tgui;

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)\

static ifstream readFileObj;


//static const Color GroundColor{ 87, 0, 127, 255 };