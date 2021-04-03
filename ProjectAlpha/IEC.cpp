#include "IEC.h"




IEC::IEC()
{
	
}

void IEC::receiveKeyboardInput(Keyboard::Key keyCode, IEC::KeyState state)
{
	keyboardKeysArr[keyCode] = state;
}

void IEC::receiveMouseInput(Mouse::Button buttonCode, IEC::KeyState state)
{
	mouseButtonsArr[buttonCode] = state;
}

IEC::KeyState IEC::getKeyboardKeyState(Keyboard::Key keyCode)
{
	return keyboardKeysArr[keyCode];
}

IEC::KeyState IEC::getMouseButtonState(Mouse::Button buttonCode)
{
	return mouseButtonsArr[buttonCode];
}

void IEC::eventExpire(Keyboard::Key keyCode)
{
	if (keyboardKeysArr[keyCode] == KeyState::JUSTPRESSED)
		keyboardKeysArr[keyCode] = KeyState::PRESSED;
	if (keyboardKeysArr[keyCode] == KeyState::JUSTRELEASED)
		keyboardKeysArr[keyCode] = KeyState::RELEASED;
}

void IEC::eventExpire(Mouse::Button buttonCode)
{
	if (mouseButtonsArr[buttonCode] == KeyState::JUSTPRESSED)
		mouseButtonsArr[buttonCode] = KeyState::PRESSED;
	if (mouseButtonsArr[buttonCode] == KeyState::JUSTRELEASED)
		mouseButtonsArr[buttonCode] = KeyState::RELEASED;
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

void IEC::receiveMouseWheelInput(int delta)
{
	mouseWheelDelta = delta;
}

void IEC::moveMouse(int x, int y)
{
	mouse.setPosition({mouse.getPosition().x + x, mouse.getPosition().y + y});
}


void IEC::eventUpdate()
{
	for (unsigned int i = 0; i < Keyboard::KeyCount; i++)
	{
		if (keyboardKeysArr[i] == KeyState::JUSTPRESSED)
			keyboardKeysArr[i] = KeyState::PRESSED;
		if (keyboardKeysArr[i] == KeyState::JUSTRELEASED)
			keyboardKeysArr[i] = KeyState::RELEASED;
	}
	for (unsigned int i = 0; i < Mouse::ButtonCount; i++)
	{
		if (mouseButtonsArr[i] == KeyState::JUSTPRESSED)
			mouseButtonsArr[i] = KeyState::PRESSED;
		if (mouseButtonsArr[i] == KeyState::JUSTRELEASED)
			mouseButtonsArr[i] = KeyState::RELEASED;
	}

	mouseWheelDelta = 0;
	cycleTime = timer.restart();
}

