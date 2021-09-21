// Non-Local Includes
#include <iostream>

// Local Includes
#include "WorldManager.h"
#include"AudioManager.h"
#include "GUI.h"
#include "Spawner.h"
namespace Utils
{
	const int WINDOWWIDTH = 1920;
	const int WINDOWHEIGHT = 1080;
	const float m_Scale = 50.0f;

};

// Forward Declaration
void Start();

void Update();

void Render();

void InitUIView();
void InitView();

void CenterViewTo(sf::Sprite _object);


WorldManager* m_WorldManager;
sf::Vector2f m_MousePos;

// Main Render Window
sf::RenderWindow* m_RenderWindow;

AudioManager* m_AudioManager;

// Main View / Camera
sf::View m_View;
sf::View m_UIView;

// b2World
b2Vec2 m_Gravity(0.0f, 10.0f);
b2World m_World(m_Gravity);
TextureMaster* m_TextureMaster;
GUI* m_GUI;
Player* m_Player;
Spawner* m_SlimeSpawner;
sf::Clock m_DeathTimer;

sf::Event m_Event;

int main()
{
	// Render Window Settings
	sf::ContextSettings m_Settings;
	m_Settings.antialiasingLevel = 8;

	// Render Window Creation
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "Cube Land", sf::Style::Default, m_Settings);
	m_RenderWindow->setFramerateLimit(60);
	m_RenderWindow->setKeyRepeatEnabled(false);

	Start();
	Update();

	// Cleanup
	delete m_Player;
	m_Player = nullptr;
	delete m_GUI;
	m_GUI = nullptr;
	delete m_SlimeSpawner;
	m_SlimeSpawner = nullptr;
	delete m_WorldManager;
	m_WorldManager = nullptr;
	delete m_AudioManager;
	m_AudioManager = nullptr;
	delete m_TextureMaster;
	m_TextureMaster = nullptr;

	// Render Window is always last
	delete m_RenderWindow;
	m_RenderWindow = nullptr;

	return 0;
}

void Start()
{
	InitUIView();
	InitView();
	
	

	m_Event = sf::Event();
	m_TextureMaster = new TextureMaster();

	m_AudioManager = new AudioManager();
	m_AudioManager->PlayMusic();

	m_Player = new Player(m_RenderWindow, m_World, Utils::m_Scale, m_AudioManager);
	m_Player->Start();

	m_WorldManager = new WorldManager(m_RenderWindow, m_World, m_TextureMaster, m_Player);
	m_WorldManager->Start();

	m_GUI = new GUI(m_RenderWindow, m_TextureMaster);
	m_GUI->Start();
	m_GUI->InitInventoryUI(m_Player);
	m_GUI->InitHotBarScrolling(m_Event, m_Player);

	// Monster spawners, given a place to spawn at and what type of enemy to spawn
	m_SlimeSpawner = new Spawner(m_RenderWindow, m_World, m_TextureMaster, m_AudioManager, Utils::m_Scale, 0,0, 5, m_Player,Enemy::ENEMYTYPE::SLIME);
	m_SlimeSpawner->SetPlayer(m_Player);
	m_SlimeSpawner->ToggleSpawning();
	m_SlimeSpawner->SetSpawnCount(30);

}

void Update()
{
	while (m_RenderWindow->isOpen())
	{

		m_MousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow),m_View);
		
		while (m_RenderWindow->pollEvent(m_Event))
		{
			if (m_Event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
				break;
			}
			if (m_Event.type == sf::Event::KeyPressed)
			{
				if (m_Player != nullptr)
				{
					m_Player->PollMovement(m_Event);
				}
			}
			if (m_Event.type == sf::Event::MouseButtonPressed)
			{

			}
			if (m_Event.type == sf::Event::MouseWheelScrolled)
			{
				if (m_Player != nullptr)
				{
					m_GUI->HotBarScrolling(m_Event, m_Player);
				}
			}

		}


		m_SlimeSpawner->Update();

		if (m_Player != nullptr)
		{
			CenterViewTo(m_Player->GetShape());

			m_GUI->Update();
			m_Player->Update(m_MousePos);
			
			m_WorldManager->Update();

			if (m_Player->GetHealth() <= 0 && m_Player != nullptr)
			{
				m_AudioManager->PlayerDeath();
				m_DeathTimer.restart();
				delete m_Player;
				m_Player = nullptr;
				m_WorldManager->LosePlayer();
				m_SlimeSpawner->LosePlayer();
			}
			// Render
			Render();
		}
		else if (m_Player == nullptr)
		{
			if (m_DeathTimer.getElapsedTime().asSeconds() >= 3)
			{
				m_Player = new Player(m_RenderWindow, m_World, Utils::m_Scale, m_AudioManager);
				m_Player->Start();
				m_GUI->InitHotBarScrolling(m_Event, m_Player);
				m_WorldManager->SetPlayer(m_Player);
				m_SlimeSpawner->SetPlayer(m_Player);
			}

		}



	}
}

void Render()
{
	m_RenderWindow->clear();
	m_RenderWindow->setView(m_View);

	m_WorldManager->Render();
	if (m_Player != nullptr)
	{
		m_SlimeSpawner->Render();
		m_Player->Render();

		m_RenderWindow->setView(m_UIView);
		m_GUI->InventoryUI(m_RenderWindow, m_UIView, m_Player);
		m_GUI->TimerUI();
		m_GUI->HealthAndManaUI(m_RenderWindow, m_UIView, m_Player);
		m_GUI->Render(m_Player);
	}
	m_RenderWindow->display();
}

void InitUIView()
{
	m_UIView = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));
}

void InitView()
{
	m_View = sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));
	m_View.zoom(4.0f);
}

void CenterViewTo(sf::Sprite _object)
{
	m_View.setCenter(_object.getPosition());
	m_RenderWindow->setView(m_View);
}

