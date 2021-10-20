#pragma once

#include "CGameScene.h"

class CSceneManager : NumptyBehavior
{
public:
	CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster);
	virtual ~CSceneManager();

	virtual void Start();
	virtual void Update();
	virtual void PolledUpdate();
	virtual void Render();

	void CheckForPlayerMARKASDESTROY();

private:
	std::queue<CGameScene> m_Scenes = {};
	CGameScene* m_Scene = nullptr;

	sf::RenderWindow* m_RenderWindow = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	sf::Event* m_Event = nullptr;
};

