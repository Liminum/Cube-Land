#include "CSceneManager.h"

CSceneManager::CSceneManager(sf::RenderWindow* _renderWindow, sf::Event& _event, TextureMaster* _textureMaster)
{
	m_RenderWindow = _renderWindow;
	m_Event = &_event;
	m_TextureMaster = _textureMaster;
}

CSceneManager::~CSceneManager()
{
	while (m_Scenes.size() > 0)
	{
		m_Scenes.pop();
	}
	std::queue<CGameScene>().swap(m_Scenes);

	NumptyBehavior::DeletePointer(m_Scene);
	m_Scene = nullptr;

	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_Event = nullptr;
}

void CSceneManager::Start()
{
	m_Scene = new CGameScene(m_RenderWindow, m_TextureMaster, *m_Event);
	m_Scenes.push(*m_Scene);
	m_Scenes.front().Start();
}

void CSceneManager::Update()
{
	m_Scenes.front().Update();
}

void CSceneManager::PolledUpdate()
{
	m_Scenes.front().PolledUpdate();
}

void CSceneManager::Render()
{
	m_Scenes.front().Render();
}

void CSceneManager::CheckForPlayerMARKASDESTROY()
{

	m_Scenes.front().CheckForPlayerMARKASDESTROY();

}
