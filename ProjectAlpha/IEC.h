#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

/*
Class for handling input events. 
test _BUTTON for event on press
test BUTTON_ for event on release
test BUTTON for pressed
Call eventUpdate() at the end of every cycle
*/
class IEC
{
	Mouse mouse;
	Clock timer;
	
public:
	Time cycleTime;
	Time timePerFrame = seconds(1.f / 60.f);
	int mouseWheelDelta;

	bool _LMB = false;
	bool LMB = false;
	bool LMB_ = false;
	bool _RMB = false;
	bool RMB = false;
	bool RMB_ = false;

	bool Up = false;
	bool _Up = false;
	bool Up_ = false;
	bool Down = false;
	bool _Down = false;
	bool Down_ = false;
	bool Left = false;
	bool _Left = false;
	bool Left_ = false;
	bool Right = false;
	bool _Right = false;
	bool Right_ = false;

	bool Esc = false;
	bool _Esc = false;
	bool Esc_ = false;

	bool W = false;
	bool _W = false;
	bool W_ = false;
	bool A = false;
	bool _A = false;
	bool A_ = false;
	bool S = false;
	bool _S = false;
	bool S_ = false;
	bool D = false;
	bool _D = false;
	bool D_ = false;
	bool R = false;
	bool _R = false;
	bool R_ = false;
	bool K = false;
	bool _K = false;
	bool K_ = false;
	bool X = false;
	bool _X = false;
	bool X_ = false;
	bool Space = false;
	bool _Space = false;
	bool Space_ = false;
	bool LShift = false;
	bool _LShift = false;
	bool LShift_ = false;

	bool _F5 = false;
	bool F5 = false;
	bool F5_ = false;
	bool _F6 = false;
	bool F6 = false;
	bool F6_ = false;
	bool _F11 = false;
	bool F11 = false;
	bool F11_ = false;
	bool _F12 = false;
	bool F12 = false;
	bool F12_ = false;

	bool equal_ = false;
	bool equal = false;
	bool _equal = false;

	bool dash_ = false;
	bool dash = false;
	bool _dash = false;


	IEC();
	void LMBclick();
	void LMBrelease();
	void RMBclick();
	void RMBrelease();

	void pressUp();
	void releaseUp();
	void pressDown();
	void releaseDown();
	void pressLeft();
	void releaseLeft(); 
	void pressRight();
	void releaseRight();

	void pressEscape();
	void releaseEscape();

	void pressW();
	void releaseW();
	void pressA();
	void releaseA();
	void pressS();
	void releaseS();
	void pressD();
	void releaseD();
	void pressR();
	void releaseR();
	void pressK();
	void releaseK();
	void pressX();
	void releaseX();
	void pressSpace();
	void releaseSpace();
	void pressF5();
	void releaseF5();
	void pressF6();
	void releaseF6();
	void pressF12();
	void releaseF12();
	void pressF11();
	void releaseF11();
	void pressLShift();
	void releaseLShift();
	void pressEqual();
	void releaseEqual();
	void pressDash();
	void releaseDash();

	//Gets global position of mouse basics on view in the world
	Vector2f getMousePos(RenderWindow& window, View view);

	//Gets local screen position
	Vector2f getMousePos(RenderWindow& window);

	void mouseWheelScrolling(int delta);

	void moveMouse(int x, int y);
	//каждый цикл сбрасывает флаги нажатия и отпускания мыши
	void eventUpdate();
};


