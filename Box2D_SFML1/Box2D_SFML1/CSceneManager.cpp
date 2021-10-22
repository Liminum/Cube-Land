#include "CSceneManager.h"

CSceneManager::CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster)
{
	m_RenderWindow = _renderWindow;
	m_Event = &_event;
	m_TextureMaster = _textureMaster;
	m_GameScene = false;

	m_MainMenuSceneVector.push_back(new CMainMenuScene(m_RenderWindow, *m_Event));
}

CSceneManager::~CSceneManager()
{
	CleanupGameScenes();
	CleanupMainMenuScenes();

	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_Event = nullptr;
}

void CSceneManager::Start()
{
	if (!m_GameScene)
	{
		m_MainMenuSceneVector.back()->Start();
	}
	else
	{
		m_GameSceneVector.back()->Start();
	}
}

void CSceneManager::Update()
{
	if (!m_GameScene)
	{
		m_MainMenuSceneVector.back()->Update();
	}
	else
	{
		m_GameSceneVector.back()->Update();
	}
}

void CSceneManager::PolledUpdate()
{
	if (!m_GameScene)
	{
		m_MainMenuSceneVector.back()->PolledUpdate();
	}
	else
	{
		m_GameSceneVector.back()->PolledUpdate();
	}

	ChangeScenes();
}

void CSceneManager::Render()
{
	if (!m_GameScene)
	{
		m_MainMenuSceneVector.back()->Render();
	}
	else
	{
		m_GameSceneVector.back()->Render();
	}
}

void CSceneManager::ChangeScenes()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && m_SceneTimer.getElapsedTime().asSeconds() >= m_SceneChangeDelay)
	{
		m_GameScene = !m_GameScene;

		if (m_GameScene == true)
		{
			CleanupMainMenuScenes();
			m_GameSceneVector.push_back(new CGameScene(m_RenderWindow, m_TextureMaster, *m_Event));
		}
		else if (m_GameScene == false)
		{
			CleanupGameScenes();
			m_MainMenuSceneVector.push_back(new CMainMenuScene(m_RenderWindow, *m_Event));
		}


		Start();

		m_SceneTimer.restart();
	}
}

void CSceneManager::CheckForMARKASDESTROY()
{
	if (m_GameScene == true)
	{
		m_GameSceneVector.back()->CheckForMARKASDESTROY();
	}
	else if (m_GameScene == false)
	{
		m_MainMenuSceneVector.back()->CheckForMARKASDESTROY();
	}
}

void CSceneManager::CleanupGameScenes()
{
	for (auto& pointer : m_GameSceneVector)
	{
		DeletePointer(pointer);
		pointer = nullptr;
	}
	m_GameSceneVector.erase(std::remove(m_GameSceneVector.begin(), m_GameSceneVector.end(), nullptr), m_GameSceneVector.end());

}

void CSceneManager::CleanupMainMenuScenes()
{
	for (auto& pointer : m_MainMenuSceneVector)
	{
		DeletePointer(pointer);
		pointer = nullptr;
	}
	m_MainMenuSceneVector.erase(std::remove(m_MainMenuSceneVector.begin(), m_MainMenuSceneVector.end(), nullptr), m_MainMenuSceneVector.end());

}
