#include "IEC.h"



IEC::IEC()
{
}

void IEC::LMBclick()
{
	_LMB = true;
	LMB = true;
}

void IEC::LMBrelease()
{
	LMB_ = true;
	LMB = false;
}

void IEC::RMBclick()
{
	_RMB = true;
	RMB = true;
}

void IEC::RMBrelease()
{
	RMB_ = true;
	RMB = false;
}

void IEC::pressUp()
{
	if (!Up) _Up = true;
	Up = true;
}

void IEC::releaseUp()
{
	Up_ = true;
	Up = false;
}

void IEC::pressDown()
{
	if (!Down) _Down = true;
	Down = true;
}

void IEC::releaseDown()
{
	Down_ = true;
	Down = false;
}

void IEC::pressLeft()
{
	if (!Left) _Left = true;
	Left = true;
}

void IEC::releaseLeft()
{
	Left_ = true;
	Left = false;
}

void IEC::pressRight()
{
	if (!Right) _Right = true;
	Right = true;
}

void IEC::releaseRight()
{
	Right_ = true;
	Right = false;
}

void IEC::pressEscape()
{
	if (!Esc) _Esc= true;
	Esc = true;
}

void IEC::releaseEscape()
{
	Esc_ = true;
	Esc = false;
}

void IEC::pressW()
{
	if (!W) _W = true;
	W = true;
}

void IEC::releaseW()
{
	W_ = true;
	W = false;
}

void IEC::pressA()
{
	if (!A) _A = true;
	A = true;
}

void IEC::releaseA()
{
	A_ = true;
	A = false;
}

void IEC::pressS()
{
	if (!S) _S = true;
	S = true;
}

void IEC::releaseS()
{
	S_ = true;
	S = false;
}

void IEC::pressD()
{
	if (!D) _D = true;
	D = true;
}

void IEC::releaseD()
{
	D_ = true;
	D = false;
}

void IEC::pressR()
{
	if (!R) _R = true;
	R = true;
}

void IEC::releaseR()
{
	R_ = true;
	R = false;
}

void IEC::pressK()
{
	if (!K) _K = true;
	K = true;
}

void IEC::releaseK()
{
	K_ = true;
	K = false;
}

void IEC::pressX()
{
	if (!X) _X = true;
	X = true;
}

void IEC::releaseX()
{
	X_ = true;
	X = false;
}

void IEC::pressSpace()
{
	if (!Space) _Space = true;
	Space = true;
}

void IEC::releaseSpace()
{
	Space_ = true;
	Space = false;
}

void IEC::pressF5()
{
	if (!F5) _F5 = true;
	F5 = true;
}

void IEC::releaseF5()
{
	F5_ = true;
	F5 = false;
}

void IEC::pressF6()
{
	if (!F6) _F6 = true;
	F6 = true;
}

void IEC::releaseF6()
{
	F6_ = true;
	F6 = false;
}

void IEC::pressF12()
{
	if (!F12) _F12 = true;
	F12 = true;
}

void IEC::releaseF12()
{
	F12_ = true;
	F12 = false;
}

void IEC::pressF11()
{
	if (!F11) _F11 = true;
	F11 = true;
}

void IEC::releaseF11()
{
	F11_ = true;
	F11 = false;
}

void IEC::pressLShift()
{
	if (!LShift) _LShift = true;
	LShift = true;
}

void IEC::releaseLShift()
{
	LShift_ = true;
	LShift = false;
}

void IEC::pressEqual()
{
	if (!equal) _equal = true;
	equal = true;
}

void IEC::releaseEqual()
{
	equal_ = true;
	equal = false;
}

void IEC::pressDash()
{
	if (!dash) _dash = true;
	dash = true;
}

void IEC::releaseDash()
{
	dash_ = true;
	dash = false;
}

// Возвращает глобальные координаты курсора в мире с данным видом(камерой)
Vector2f IEC::getMousePos(RenderWindow& window, View view)
{
	View tempView = window.getView();
	window.setView(view);
	Vector2f pos = window.mapPixelToCoords(mouse.getPosition(window));
	window.setView(tempView);
	return pos;
}

// Возвращает локальные координаты курсора по отношение к матрице монитора 
//  его верхнему левому пикселю
Vector2f IEC::getMousePos(RenderWindow& window)
{
	View tempView = window.getView();
	window.setView(window.getDefaultView());
	Vector2f pos = window.mapPixelToCoords(mouse.getPosition(window));
	window.setView(tempView);
	return pos;
}

void IEC::mouseWheelScrolling(int delta)
{
	mouseWheelDelta = delta;
}

void IEC::moveMouse(int x, int y)
{
	mouse.setPosition({mouse.getPosition().x + x, mouse.getPosition().y + y});
}


void IEC::eventUpdate()
{
	mouseWheelDelta = 0;
	_LMB = false;
	LMB_ = false;
	_RMB = false;
	RMB_ = false;
	_Up = false;
	Up_ = false;
	_Down = false;
	Down_ = false;
	_Left = false;
	Left_ = false;
	_Right = false;
	Right_ = false;

	_Esc = false;
	Esc_ = false;

	_W = false;
	W_ = false;
	_A = false;
	A_ = false;
	_S = false;
	S_ = false;
	_D = false;
	D_ = false;
	_R = false;
	R_ = false;
	_K = false;
	K_ = false;
	_X = false;
	X_ = false;
	_F5 = false;
	F5_ = false;
	_F6 = false;
	F6_ = false;
	_F12 = false;
	F12_ = false;
	_F11 = false;
	F11_ = false;
	_Space = false;
	Space_ = false;
	_LShift = false;
	LShift_ = false;
	_equal = false;
	equal_ = false;
	_dash = false;
	dash_ = false;
	cycleTime = timer.restart();
}

