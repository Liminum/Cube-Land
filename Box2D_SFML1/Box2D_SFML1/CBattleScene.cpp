#include "CBattleScene.h"

CBattleScene::CBattleScene(sf::RenderWindow* _renderWindow, TextureMaster* _textureMaster, sf::Event& _event)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _textureMaster;
	m_Event = &_event;
	m_Font.loadFromFile("Resources/Fonts/ANDYB.TTF");
}

CBattleScene::~CBattleScene()
{
	CleanupAllPointers();
}

void CBattleScene::Start()
{
	InitUIView();
	InitWorldView();

	CreateAudioManager();
	m_AudioManager->PlayMusic(-1);

	DeletePointer(m_GUI);
	m_GUI = nullptr;
	m_GUI = new GUI(m_RenderWindow, m_TextureMaster, m_Font);
	m_GUI->InitBattleUI();
}

void CBattleScene::Update()
{
	
}

void CBattleScene::PolledUpdate()
{
	while (m_RenderWindow->pollEvent(*m_Event))
	{

	}
}

void CBattleScene::Render()
{
	if (m_GUI != nullptr)
	{
		m_GUI->BattleUI(m_UIView, m_WorldView);
	}
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
	DeletePointer(m_AudioManager);
	DeletePointer(m_GUI);
	m_GUI = nullptr;
	m_AudioManager = nullptr;
	m_TextureMaster = nullptr;
	m_Event = nullptr;
	m_RenderWindow = nullptr;
}

void CBattleScene::InitUIView()
{
	m_UIView.setSize((sf::Vector2f)m_RenderWindow->getSize());
	m_UIView.setCenter(m_RenderWindow->getView().getCenter());
}

void CBattleScene::InitWorldView()
{
	m_WorldView.setSize((sf::Vector2f)m_RenderWindow->getSize());
	m_WorldView.setCenter(m_RenderWindow->getView().getCenter());
}
