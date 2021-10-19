#pragma once

#include "CGameScene.h"

class CSceneManager
{
public:
	CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster);
	~CSceneManager();

	void Start();
	void Update();
	void PolledUpdate();
	void Render();

	void CheckForPlayerMARKASDESTROY();

private:
	CGameScene* m_Scene = nullptr;

	sf::RenderWindow* m_RenderWindow = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	sf::Event* m_Event = nullptr;
};

