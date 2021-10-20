//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CDebugWindow.cpp
// Description : CDebugWindow Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "CDebugWindow.h"

/// <summary>
/// CDebugWindow Contructor
/// </summary>
/// <param name="_textureMaster"></param>
/// <param name="_worldManager"></param>
/// <param name="_player"></param>
/// <param name="_spawners"></param>
/// <param name="_bChangeScenes"></param>
/// <param name="_sceneValue"></param>
/// <param name="_numberOfLeakes"></param>
CDebugWindow::CDebugWindow(TextureMaster* _textureMaster, WorldManager* _worldManager, Player* _player)
{
	m_WorldManager = _worldManager;
	m_Player = _player;
	m_TextureMaster = _textureMaster;

	// Texture
	m_PlayerPreviewTexture.loadFromFile("Images/PlayerIconRight.png");
	m_PlayerPreview.setTexture(m_PlayerPreviewTexture, true);

	// Player Stuff
	m_PlayerBackGround = sf::RectangleShape(sf::Vector2f(400, 600));
	m_PlayerBackGround.setFillColor(sf::Color::Green);
	m_PlayerStatsBackGround = sf::RectangleShape(sf::Vector2f(350, 275));
	m_PlayerStatsBackGround.setFillColor(sf::Color::Yellow);
	m_PlayerStatsBackGround.setPosition(25, 300);
	m_PlayerImageIconBackGround = sf::RectangleShape(sf::Vector2f(125, 125));
	m_PlayerImageIconBackGround.setFillColor(sf::Color::Magenta);
	m_PlayerImageIconBackGround.setPosition(50, 325);
	m_PlayerPreview.setPosition(50 + 12.5f, 325 + 12.5f);

	// Enemy Stuff
	m_EnemiesBackGround = sf::RectangleShape(sf::Vector2f(200, 300));
	m_EnemiesBackGround.setFillColor(sf::Color::Red);
	m_EnemiesBackGround.setPosition(400, 0);
	// World Stuff
	m_WorldBackGround = sf::RectangleShape(sf::Vector2f(200, 300));
	m_WorldBackGround.setFillColor(sf::Color::Blue);
	m_WorldBackGround.setPosition(400, 300);

	// Render Window Creation
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(600, 600), "DEBUG CONTROLS", (sf::Style::Titlebar));
}

/// <summary>
/// CDebugWindow Destructor
/// </summary>
CDebugWindow::~CDebugWindow()
{
	m_PlayerButtons.clear();
	m_EnemyButtons.clear();
	m_WorldButtons.clear();

	DeletePointer(m_RenderWindow);
	m_RenderWindow = nullptr;
}

/// <summary>
/// CDebugWindow Start
/// </summary>
void CDebugWindow::Start()
{
	CreateEnemyControlButtons();
	CreatePlayerControlButtons();
	CreateWorldControlButtons();

	m_MousePositionPointerTexture.loadFromFile("Images/Cursor.png");
	m_MousePositionPointer.setTexture(m_MousePositionPointerTexture, true);
}

/// <summary>
/// CDebugWindow Update
/// </summary>
void CDebugWindow::Update()
{
	m_MousePos = m_RenderWindow->mapPixelToCoords((sf::Mouse::getPosition(*m_RenderWindow)));
	m_MousePositionPointer.setPosition(static_cast<sf::Vector2f>(m_MousePos)); // Set position

	// Buttons (Polled Update)
	while (m_RenderWindow->pollEvent(m_Event))
	{
		for (int i = 0; i < m_EnemyButtons.size(); i++)
		{
		}

		for (int i = 0; i < m_PlayerButtons.size(); i++)
		{
			if (i == 2 && m_Player != nullptr)
			{
				int x = m_Player->GetShape()->getPosition().x;
				int y = m_Player->GetShape()->getPosition().y;
				std::string positionstring = "Position: ";
				positionstring += std::to_string(x);
				positionstring += ", ";
				positionstring += std::to_string(y);

				m_PlayerButtons[i].SetLabel(positionstring, 40.0f);
			}
			m_PlayerButtons[i].Update();

			if (m_Event.type == sf::Event::MouseButtonPressed && m_PlayerButtons[i].bIsinBounds(m_MousePos))
			{
				if (i == 0)
				{
					KillPlayer();
				}
				else if (i == 1)
				{
					m_PlayerButtons[i].SetState("Click");
					m_PlayerButtons[i].m_bIsPressed = !m_PlayerButtons[i].m_bIsPressed;
				}
				break;
			}
		}
	}
}

/// <summary>
/// CDebugWindow Render
/// </summary>
void CDebugWindow::Render()
{
	// Clear Render Window
	m_RenderWindow->clear();

	m_RenderWindow->draw(m_PlayerBackGround);
	m_RenderWindow->draw(m_EnemiesBackGround);
	m_RenderWindow->draw(m_WorldBackGround);
	m_RenderWindow->draw(m_PlayerStatsBackGround);
	m_RenderWindow->draw(m_PlayerImageIconBackGround);
	m_RenderWindow->draw(m_PlayerPreview);

	// Item Buttons

	for (int i = 0; i < m_EnemyButtons.size(); i++)
	{
		m_RenderWindow->draw(m_EnemyButtons[i].Sprite);
	}

	for (int i = 0; i < m_WorldButtons.size(); i++)
	{
		if (i == 4)
		{
			m_WorldButtons[i].RenderOnlyLabel();
		}
		else
		{
			m_RenderWindow->draw(m_WorldButtons[i].Sprite);

		}
	}

	for (int i = 0; i < m_PlayerButtons.size(); i++)
	{
		if (i == 2)
		{
			m_PlayerButtons[i].RenderOnlyLabel();
		}
		else
		{
			m_RenderWindow->draw(m_PlayerButtons[i].Sprite);
		}
		
	}

	m_RenderWindow->draw(m_MousePositionPointer);

	// Display
	m_RenderWindow->display();
}

/// <summary>
/// Sets m_Player to _player
/// </summary>
/// <param name="_player"></param>
void CDebugWindow::SetPlayer(Player* _player)
{
	m_Player = _player;
}

/// <summary>
/// Creates enemy control buttons
/// </summary>
void CDebugWindow::CreateEnemyControlButtons()
{
	
}

/// <summary>
/// Creates world control buttons 
/// </summary>
void CDebugWindow::CreateWorldControlButtons()
{
	// Force Plains Biome
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(20 + (13 * 30), (11 * 30) - 20);
		tempbutton->SetLabel("Force Plains");

		sf::Texture Hover;
		Hover.loadFromFile("Images/ForcePlainsButton-Hover.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/ForcePlainsButton.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/ForcePlainsButton.png");
		tempbutton->SetIdleTex(Idle);

		m_WorldButtons.insert_or_assign(0, *tempbutton);
		tempbutton = nullptr;
	}
	// Force Sand Biome
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(20 + (14 * 30), (11 * 30) - 20);
		tempbutton->SetLabel("Force Sand");

		sf::Texture Hover;
		Hover.loadFromFile("Images/ForceSandButton-Hover.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/ForceSandButton.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/ForceSandButton.png");
		tempbutton->SetIdleTex(Idle);

		m_WorldButtons.insert_or_assign(1, *tempbutton);
		tempbutton = nullptr;
	}
	// Force Ice Biome
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(20 + (15 * 30), (11 * 30) - 20);
		tempbutton->SetLabel("Force Ice");

		sf::Texture Hover;
		Hover.loadFromFile("Images/ForceIceButton-Hover.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/ForceIceButton.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/ForceIceButton.png");
		tempbutton->SetIdleTex(Idle);

		m_WorldButtons.insert_or_assign(2, *tempbutton);
		tempbutton = nullptr;
	}
	// Force Hell Biome
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(20 + (16 * 30), (11 * 30) - 20);
		tempbutton->SetLabel("Force Hell");

		sf::Texture Hover;
		Hover.loadFromFile("Images/ForceHellButton-Hover.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/ForceHellButton.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/ForceHellButton.png");
		tempbutton->SetIdleTex(Idle);

		m_WorldButtons.insert_or_assign(3, *tempbutton);
		tempbutton = nullptr;
	}
}

/// <summary>
/// Created Player control buttons
/// </summary>
void CDebugWindow::CreatePlayerControlButtons()
{
	// Kill Player Button
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(10 + (0 * 30), (9 * 30) - 20);
		tempbutton->SetLabel("Kill Player");

		sf::Texture Hover;
		Hover.loadFromFile("Images/KillPlayerButton-Hover.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/KillPlayerButton.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/KillPlayerButton.png");
		tempbutton->SetIdleTex(Idle);

		m_PlayerButtons.insert_or_assign(0, *tempbutton);
		tempbutton = nullptr;
	}

	// GodMode Bool Button
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(10 + (1 * 30), (9 * 30) - 20);

		sf::Texture Hover;
		Hover.loadFromFile("Images/GodMode.png");
		tempbutton->SetHoverTex(Hover);

		sf::Texture Pressed;
		Pressed.loadFromFile("Images/GodModeToggled.png");
		tempbutton->SetClickTex(Pressed);

		sf::Texture Idle;
		Idle.loadFromFile("Images/GodMode.png");
		tempbutton->SetIdleTex(Idle);

		m_PlayerButtons.insert_or_assign(1, *tempbutton);
		tempbutton = nullptr;
	}

	// Position Label
	if (true)
	{
		CButtons* tempbutton = new CButtons(m_RenderWindow);
		tempbutton->SetPosition(75 + 12.5f, 445 + 12.5f);

		if (m_Player != nullptr)
		{
			int x = m_Player->GetShape()->getPosition().x;
			int y = m_Player->GetShape()->getPosition().y;
			std::string positionstring = "Position: ";
			positionstring += std::to_string(x);
			positionstring += ", ";
			positionstring += std::to_string(y);

			tempbutton->SetLabel(positionstring, 40.0f);
		}

		m_PlayerButtons.insert_or_assign(2, *tempbutton);
		tempbutton = nullptr;
	}
}

/// <summary>
/// Close the debugwindow renderwindow
/// </summary>
void CDebugWindow::Close()
{
	m_RenderWindow->close();
}

/// <summary>
/// Resets all button bools to false
/// </summary>
void CDebugWindow::ResetAllButtons()
{

	for (int i = 0; i < m_EnemyButtons.size(); i++)
	{
		m_EnemyButtons[i].m_bIsPressed = false;
	}

	for (int i = 0; i < m_PlayerButtons.size(); i++)
	{
		m_PlayerButtons[i].m_bIsPressed = false;
	}
}

/// <summary>
/// Kill player
/// </summary>
void CDebugWindow::KillPlayer()
{
	if (m_Player != nullptr)
	{
		m_Player->SetCurrentHealth(0);
	}
}