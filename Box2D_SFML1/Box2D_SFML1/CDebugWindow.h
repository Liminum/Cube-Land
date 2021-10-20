//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CDebugWindow.h
// Description : CDebugWindow Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#ifndef _DEBUGWINDOW_H__
#define _DEBUGWINDOW_H__

// Local Includes
#include "GUI.h"
#include "WorldManager.h"
#include "AudioManager.h"
#include "CInputField.h"
#include "CButtons.h"

class CDebugWindow : NumptyBehavior
{
public:
	CDebugWindow(TextureMaster* _textureMaster, WorldManager* _worldManager, Player* _player);
	~CDebugWindow();

	virtual void Start();
	virtual void Update();
	virtual void Render();

	void Close();

	void SetPlayer(Player* _player);

	bool m_InFocus = true;

private:
	void CreateEnemyControlButtons();
	void CreateWorldControlButtons();
	void CreatePlayerControlButtons();

	void ResetAllButtons();

	void KillPlayer();

	sf::Event m_Event;

	sf::Vector2f m_MousePos;

	sf::RenderWindow* m_RenderWindow = nullptr;
	WorldManager* m_WorldManager = nullptr;
	Player* m_Player = nullptr;
	TextureMaster* m_TextureMaster = nullptr;

	std::map<int, CButtons> m_PlayerButtons;
	std::map<int, CButtons> m_EnemyButtons;
	std::map<int, CButtons> m_WorldButtons;

	sf::RectangleShape m_PlayerBackGround;
	sf::RectangleShape m_PlayerStatsBackGround;
	sf::RectangleShape m_PlayerImageIconBackGround;

	sf::RectangleShape m_EnemiesBackGround;

	sf::RectangleShape m_WorldBackGround;

	sf::Sprite m_PlayerPreview;
	sf::Texture m_PlayerPreviewTexture;

	bool m_bGodMode = false;

	sf::Sprite m_MousePositionPointer;
	sf::Texture m_MousePositionPointerTexture;
};
#endif

