#include "CSceneManager.h"

CSceneManager::CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster)
{
	m_RenderWindow = _renderWindow;
	m_Event = &_event;
	m_TextureMaster = _textureMaster;
	m_ChangeScenes = false;

	m_GameSceneQueue.push(*new CGameScene(m_RenderWindow, m_TextureMaster, *m_Event));

	//m_MainMenuSceneQueue.push(*new CMainMenuScene(m_RenderWindow, *m_Event));
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
	if (m_MainMenuSceneQueue.size() > 0)
	{
		m_MainMenuSceneQueue.front().Start();
	}
	else
	{
		m_GameSceneQueue.front().Start();
	}
}

void CSceneManager::Update()
{
	if (m_MainMenuSceneQueue.size() > 0)
	{
		m_MainMenuSceneQueue.front().Update();
	}
	else
	{
		m_GameSceneQueue.front().Update();
	}
}

void CSceneManager::PolledUpdate()
{
	if (m_MainMenuSceneQueue.size() > 0)
	{
		m_MainMenuSceneQueue.front().PolledUpdate();
	}
	else
	{
		m_GameSceneQueue.front().PolledUpdate();
	}
}

void CSceneManager::Render()
{
	if (m_MainMenuSceneQueue.size() > 0)
	{
		m_MainMenuSceneQueue.front().Render();
	}
	else
	{
		m_GameSceneQueue.front().Render();
	}
}

void CSceneManager::ChangeScenes()
{
	if (m_ChangeScenes)
	{
		m_ChangeScenes = false;

		if (m_MainMenuSceneQueue.size() > 0)
		{
			m_MainMenuSceneQueue.pop();
			m_MainMenuSceneQueue.front().Start();
		}
		else
		{
			m_GameSceneQueue.pop();
			m_GameSceneQueue.front().Start();
		}
	}
}

void CSceneManager::CheckForMARKASDESTROY()
{
	m_MainMenuSceneQueue.front().CheckForMARKASDESTROY();
	m_GameSceneQueue.front().CheckForMARKASDESTROY();
}

void CSceneManager::CleanupGameScenes()
{
	while (m_GameSceneQueue.size() > 0)
	{
		m_GameSceneQueue.pop();
	}
	std::queue<CGameScene>().swap(m_GameSceneQueue);
}

void CSceneManager::CleanupMainMenuScenes()
{
	while (m_MainMenuSceneQueue.size() > 0)
	{
		m_MainMenuSceneQueue.pop();
	}
	std::queue<CMainMenuScene>().swap(m_MainMenuSceneQueue);
}
