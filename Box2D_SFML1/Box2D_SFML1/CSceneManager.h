#pragma once

#include "CGameScene.h"
#include "CMainMenuScene.h"

class CSceneManager : NumptyBehavior
{
public:
	CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster);
	virtual ~CSceneManager();

	virtual void Start();
	virtual void Update();
	virtual void PolledUpdate();
	virtual void Render();

	void ChangeScenes();

	void CheckForMARKASDESTROY();

	void CleanupGameScenes();
	void CleanupMainMenuScenes();
private:

	std::queue<CGameScene> m_GameSceneQueue = {};
	std::queue<CMainMenuScene> m_MainMenuSceneQueue = {};

	sf::RenderWindow* m_RenderWindow = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	sf::Event* m_Event = nullptr;

	bool m_ChangeScenes;
};

