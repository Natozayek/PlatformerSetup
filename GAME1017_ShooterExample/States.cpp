#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include "Utilities.h"
#include "TextureManager.h"
#include "EventManager.h"
#include <iostream>
#include "PlatformPlayer.h"

using namespace std;
void State::Render()
{
	SDL_RenderPresent(Engine::Instace().GetRenderer());
}

void State::Resume(){}
//Begin Title State --------------------------------------------------------------------
TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering Title State... " << endl;
}

void TitleState::Update()
{
	//Change to a new GameState
	if (EVMA::KeyPressed(SDL_SCANCODE_G))
	STMA::ChangeState(new GameState());// Change to new GameState
	

}

void TitleState::Render()
{
	cout << "Rendering Title State... " << endl;
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 255, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting Title State... " << endl;
	
}//End of Title State ------------------------------------------------------------------------ //End of Title State

//Begin of Pause state ----------------------------------------------------------------------- // Begin of pause state
PauseState::PauseState()
{
	
}

void PauseState::Enter()
{
	cout << "Entering Pause State... " << endl;
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
	
}

void PauseState::Render()
{
	cout << "Rendering Pause State... " << endl;
	//First render the Gamestate
	STMA::GetStates().front()->Render();//invoke render of GameState
	
	//Now render rest of Pause state
	SDL_SetRenderDrawBlendMode(Engine::Instace().GetRenderer(),SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 0, 128);
	SDL_Rect rect = { 256, 128, 512,512 };
	SDL_RenderFillRect(Engine::Instace().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting Pause State... " << endl;
}
//End of Pause State ------------------------------------------------------------------------ //End of Pause State

//Begin GameState
GameState::GameState() {}

void GameState::Enter()
{
	cout << "Entering GameState... " << endl;
	TEMA::Load("Img/Tiles.png", "tiles"); 
	m_objects.emplace("level", new TiledLevel(24, 32, 32, 32, "Dat/Tiledata.txt", "Dat/Level1.txt", "tiles"));
	//m_objects.emplace("player", new PlatformPlayer({ 0,0,128,128 }, { 288,480,64,64 }));
}

void GameState::Update()
{
	//m_bRunning = true;
	
	if (EVMA::KeyPressed(SDL_SCANCODE_X))
		STMA::ChangeState(new TitleState());//Change to new TitleState
	else if (EVMA::KeyPressed(SDL_SCANCODE_P))
		STMA::PushState(new PauseState()); // Push/ Add new pause state
	
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)// a iterator is a position in the list somewhere
		i->second->Update(); //this referst to a place holder of X element.. LEVEL, PLAYER, ENEMY
}


//bool GameState::KeyDown(SDL_Scancode c)
//{
//	/*if (m_iKeystates != nullptr)
//	{
//		if (m_iKeystates[c] == 1)
//			return true;
//		else
//			return false;
//	}
//	return false;*/
//}

void GameState::Render()
{
	cout << "Rendering Game State... " << endl;
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instace().GetRenderer());
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)// a iterator is a position in the list somewhere
		i->second->Render(); //this referst to a place holder of X element.. LEVEL, PLAYER, ENEMY
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))//check to see if current state is of type GameState
	{
		State::Render();
	}
	//
	//SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	//SDL_RenderClear(m_pRenderer); // Clear the screen with the draw color.
	//// Render stuff. Background first.
	//for (int i = 0; i < 2; i++)
	//	SDL_RenderCopy(m_pRenderer, m_pBGText, bgArray[i].GetSrcP(), bgArray[i].GetDstP());
	//// Player.
	//SDL_RenderCopyEx(m_pRenderer, m_pSprText, m_player->GetSrcP(), m_player->GetDstP(), m_player->GetAngle(), &m_pivot, SDL_FLIP_NONE);
	///*SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 128);
	//SDL_RenderFillRect(m_pRenderer, m_player->GetDstP());*/
	//// Player bullets.	
	//for (int i = 0; i < (int)m_vPBullets.size(); i++)
	//{
	//	SDL_RenderCopyEx(m_pRenderer, m_pSprText, m_vPBullets[i]->GetSrcP(), m_vPBullets[i]->GetDstP(), 90, &m_pivot, SDL_FLIP_NONE);
	//	/*SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 128);
	//	SDL_RenderFillRect(m_pRenderer, m_vPBullets[i]->GetDstP());*/
	//}
	//// Enemies.
	//for (int i = 0; i < (int)m_vEnemies.size(); i++)
	//{
	//	SDL_RenderCopyEx(m_pRenderer, m_pSprText, m_vEnemies[i]->GetSrcP(), m_vEnemies[i]->GetDstP(), -90, &m_pivot, SDL_FLIP_NONE);
	//	/*SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 128);
	//	SDL_RenderFillRect(m_pRenderer, m_vEnemies[i]->GetDstP());*/
	//}
	//// Enemy bullets.
	//for (int i = 0; i < (int)m_vEBullets.size(); i++)
	//	SDL_RenderCopy(m_pRenderer, m_pSprText, m_vEBullets[i]->GetSrcP(), m_vEBullets[i]->GetDstP());
	//SDL_RenderPresent(m_pRenderer);
}

void GameState::Resume()
{
	cout << "Pausing GameState... " << endl;
}

void GameState::Exit()
{
	cout << "Exiting GameState... " << endl;
	TEMA::UnLoad("tiles");
	for (map<std::string, GameObject*>::iterator i = m_objects.begin()/*counter */; i != m_objects.end()/*Limit */; i++ /*Increas*/)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
	
}//End of Game state ------------------------------------------------------------------------ //End of GameState
