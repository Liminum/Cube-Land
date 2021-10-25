#include "CBattleScene.h"

CBattleScene::CBattleScene(sf::RenderWindow* _renderWindow, TextureMaster* _textureMaster, sf::Event& _event)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _textureMaster;
	m_Event = &_event;
}

CBattleScene::~CBattleScene()
{
	CleanupAllPointers();
}

void CBattleScene::Start()
{
	CreateAudioManager();
	m_AudioManager->PlayMusic(-1);
}

void CBattleScene::Update()
{
}

void CBattleScene::PolledUpdate()
{
}

void CBattleScene::Render()
{
}

void CBattleScene::CheckForMARKASDESTROY()
{
}

void CBattleScene::CreateAudioManager()
{
	NumptyBehavior::DeletePointer(m_AudioManager);
	m_AudioManager = nullptr;
	m_AudioManager = new AudioManager;
}

void CBattleScene::CleanupAllPointers()
{
	NumptyBehavior::DeletePointer(m_AudioManager);
	m_AudioManager = nullptr;
	m_TextureMaster = nullptr;
	m_Event = nullptr;
	m_RenderWindow = nullptr;
}
