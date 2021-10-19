#include "CSceneManager.h"

CSceneManager::CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster)
{
	m_RenderWindow = _renderWindow;
	m_Event = &_event;
	m_TextureMaster = _textureMaster;
}

CSceneManager::~CSceneManager()
{
	delete m_Scene;
	m_Scene = nullptr;
}

void CSceneManager::Start()
{
	m_Scene = new CGameScene(m_RenderWindow, m_TextureMaster, *m_Event);
	m_Scene->Start();
}

void CSceneManager::Update()
{
	m_Scene->Update();
}

void CSceneManager::PolledUpdate()
{
	m_Scene->PolledUpdate();
}

void CSceneManager::Render()
{
	m_Scene->Render();
}

void CSceneManager::CheckForPlayerMARKASDESTROY()
{
	if (m_Scene != nullptr)
	{
		m_Scene->CheckForPlayerMARKASDESTROY();
	}
}
