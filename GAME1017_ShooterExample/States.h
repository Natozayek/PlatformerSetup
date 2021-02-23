#pragma once
#ifndef _STATES_
#define  _STATES_

#include "TiledLevel.h"

class State // THis is the base abstract base class for all states
{

public:
	virtual void Enter() = 0;// = 0 means Pure virtual - must be defined in subclass
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
	virtual ~State() = default; // Modern alternative to = {};

protected:// Private but inherited... Prevents instantiation outside the class
	State() {}
	map<std::string, GameObject*> m_objects;
			
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	
};
class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	//virtual void HandleEvents();
	//virtual void CheckCollision();
	//bool KeyDown(SDL_Scancode c);
	virtual void Render();
	virtual void Resume();
	virtual void Exit();
};
#endif
