#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
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
public:
	enum KeyState
	{
		RELEASED,
		JUSTPRESSED,
		JUSTRELEASED,
		PRESSED,
		AMOUNT
	};
private:
	Mouse mouse;
	Clock timer;
	KeyState keyboardKeysArr[Keyboard::KeyCount]{KeyState::RELEASED};
	KeyState mouseButtonsArr[Mouse::ButtonCount]{KeyState::RELEASED};

	Time cycleTime;
	int mouseWheelDelta;
	//Time timePerFrame = seconds(1.f / 60.f);
	//
public:

	Event event;

	IEC();

	/////////////////////
	///These methods must be called in while(window.pollEvent()) loop
	//
	void receiveKeyboardInput(Keyboard::Key keyCode, IEC::KeyState state);
	void receiveMouseInput(Mouse::Button buttonCode, IEC::KeyState state);
	void receiveMouseWheelInput(int delta);
	//
	/////////////////////


	/////////////////////
	///These methods are used to get input status of a key or button
	//
	IEC::KeyState getKeyboardKeyState(Keyboard::Key keyCode);
	IEC::KeyState getMouseButtonState(Mouse::Button buttonCode);
	int getMouseWheelDelta() { return mouseWheelDelta; };
	//
	/////////////////////


	void eventExpire(Keyboard::Key keyCode);
	void eventExpire(Mouse::Button buttonCode);
	void expireMouseWheelDelta() { mouseWheelDelta = 0; };


	Time getCycleTime() { return cycleTime; };

	//Gets global position of mouse basics on view in the world
	Vector2f getMousePos(RenderWindow& window, View view);

	//Gets local screen position
	Vector2f getMousePos(RenderWindow& window);


	/// <summary>
	/// Moves computer cursor 
	/// </summary>
	/// <param name="x">offset x</param>
	/// <param name="y">offset y</param>
	void moveMouse(int x, int y);

	/// <summary>
	/// Must be called last in every loop
	/// </summary>
	void eventUpdate();
};


