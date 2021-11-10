#include "GUI.h"


GUI::GUI(sf::RenderWindow* _renderwindow, TextureMaster* _texturemaster, sf::Font& _font)
{
	m_RenderWindow = _renderwindow;
	m_TextureMaster = _texturemaster;
	m_Font = _font;
	m_Timer = sf::Clock();
	m_DisplayText = sf::Text();
	m_DisplayText.setFont(m_Font);
}

GUI::~GUI()
{
	CleanupBattleSceneButtons();
	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
}

void GUI::Start()
{
	InitHealthAndManaUI();
}

void GUI::Render(Player* _player, sf::Shader* _defaultshader, sf::Vector2f _mousePos)
{
	sf::Vector2f mousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow));
	
	m_RenderWindow->draw(m_HealthBorderSprite, _defaultshader);
	m_RenderWindow->draw(m_HealthSprite, _defaultshader);
	m_RenderWindow->draw(m_ManaBorderSprite, _defaultshader);
	m_RenderWindow->draw(m_ManaSprite, _defaultshader);
}

sf::Vector2f GUI::UIMousePointer(sf::View& _uiview)
{
	sf::Shader* defaultShader = NULL;
	sf::Vector2f mousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow), _uiview);
	return mousePos;
}

void GUI::InitHealthAndManaUI()
{
	m_ManaTexture.loadFromFile("Resources/Images/ManaBar.png");
	m_ManaBorderTexture.loadFromFile("Resources/Images/ManaBarBorder.png");
	m_ManaSprite.setTexture(m_ManaTexture, true);
	m_ManaBorderSprite.setTexture(m_ManaBorderTexture, true);
	m_ManaSprite.setOrigin(-3, -3);
	m_ManaSprite.scale(1.51, 1.5);
	m_ManaBorderSprite.scale(1.5, 1.5);

	m_HealthTexture.loadFromFile("Resources/Images/HealthBar.png");
	m_HealthBorderTexture.loadFromFile("Resources/Images/HealthBarBorder.png");
	m_HealthSprite.setTexture(m_HealthTexture, true);
	m_HealthBorderSprite.setTexture(m_HealthBorderTexture, true);
	m_HealthSprite.setOrigin(-3, -3);
	m_HealthSprite.scale(1.51, 1.5);
	m_HealthBorderSprite.scale(1.5, 1.5);
}

void GUI::HealthAndManaUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player)
{
	m_RenderWindow->mapCoordsToPixel(m_HealthSprite.getPosition());
	m_RenderWindow->mapCoordsToPixel(m_HealthBorderSprite.getPosition());
	m_HealthSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 80);
	m_HealthBorderSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 80);
	
	if (_player->GetCurrentHealth() > 0)
	{
		m_HealthSprite.setTextureRect(sf::IntRect(0, 0, (int) _player->GetCurrentHealth(), m_HealthTexture.getSize().y));
	}
	else
	{
		m_HealthSprite.setTextureRect(sf::IntRect(0, 0, 0, m_HealthTexture.getSize().y));
	}

	m_RenderWindow->mapCoordsToPixel(m_ManaSprite.getPosition());
	m_RenderWindow->mapCoordsToPixel(m_ManaBorderSprite.getPosition());
	m_ManaSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 100);
	m_ManaBorderSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 100);
	if (_player->GetCurrentMana() > 0)
	{
		m_ManaSprite.setTextureRect(sf::IntRect(0, 0, _player->GetCurrentMana(), m_ManaTexture.getSize().y));
	}
	else
	{
		m_ManaSprite.setTextureRect(sf::IntRect(0, 0, 0, m_ManaTexture.getSize().y));
	}
}

void GUI::TimerUI()
{
	std::string string = std::to_string((int)std::round(m_Timer.getElapsedTime().asSeconds()));
	m_DisplayText.setString(string);
	m_DisplayText.setFillColor(sf::Color::White);
	m_DisplayText.setOutlineThickness(0.75f);
	m_DisplayText.setOutlineColor(sf::Color::Black);
	m_DisplayText.setOrigin(m_DisplayText.getGlobalBounds().width / 2, m_DisplayText.getGlobalBounds().height / 2);
	m_DisplayText.setCharacterSize(50);
	m_RenderWindow->mapCoordsToPixel(m_DisplayText.getPosition());
	m_DisplayText.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 110, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 15);
	m_RenderWindow->draw(m_DisplayText);
}

void GUI::InitBattleUI()
{
	InitCubeBoyUI();
}

void GUI::BattleUI(sf::View& _uiView, sf::View& _worldView)
{
	m_RenderWindow->setView(_uiView);
	for (auto& item : m_BattleSceneMenuShapes)
	{
		m_RenderWindow->draw(item);
	}
	for (auto& item : m_BattleSceneAttackShapes)
	{
		if (item.getTexture() == &m_FireDeminishAttack)
		{
			if (m_BattleSceneAttackButtons[0]->m_bIsHovering)
			{
				m_RenderWindow->draw(item);
			}
		}
		else if (item.getTexture() == &m_FireBurnAttack)
		{
			if (m_BattleSceneAttackButtons[1]->m_bIsHovering)
			{
				m_RenderWindow->draw(item);
			}
		}
		else if (item.getTexture() == &m_FireEmberAttack)
		{
			if (m_BattleSceneAttackButtons[2]->m_bIsHovering)
			{
				m_RenderWindow->draw(item);
			}
		}
		else if (item.getTexture() == &m_FireIncinerateAttack)
		{
			if (m_BattleSceneAttackButtons[3]->m_bIsHovering)
			{
				m_RenderWindow->draw(item);
			}
		}
		else
		{
			m_RenderWindow->draw(item);
		}
	}
	for (auto& item : m_BattleSceneButtons)
	{
		item->Update();
		m_RenderWindow->draw(item->Sprite);
	}
	for (auto& item : m_BattleSceneAttackButtons)
	{
		item->Update();
		m_RenderWindow->draw(item->Sprite);
	}
	

	m_RenderWindow->setView(_worldView);
}

void GUI::InitButton(CButtons* _button, sf::Texture* _idleTexture, sf::Texture* _hoverTexture)
{
	_button->SetClickTex(_hoverTexture);
	_button->SetHoverTex(_hoverTexture);
	_button->SetIdleTex(_idleTexture);
}

void GUI::CleanupBattleSceneButtons()
{
	for (auto& item : m_BattleSceneButtons)
	{
		DeletePointer(item);
		item = nullptr;
	}
	for (auto& item : m_BattleSceneAttackButtons)
	{
		DeletePointer(item);
		item = nullptr;
	}
	m_BattleSceneAttackButtons.erase(std::remove(m_BattleSceneAttackButtons.begin(), m_BattleSceneAttackButtons.end(), nullptr), m_BattleSceneAttackButtons.end());
}

void GUI::InitCubeBoyUI()
{
	//m_CurrentlyHeldCubemons = Player::ReturnCubemonData();
	InitTextures();
	InitCubeBoyMenuButtons();

	sf::RectangleShape CubeBoyBackgrounds;
	CubeBoyBackgrounds.setSize(sf::Vector2f(800, 300));
	CubeBoyBackgrounds.setFillColor(sf::Color(128,128,128));
	CubeBoyBackgrounds.setOrigin(400, 150);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y + 370);
	m_BattleSceneMenuShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(470, 275));
	CubeBoyBackgrounds.setFillColor(sf::Color(100, 100, 100));
	CubeBoyBackgrounds.setOrigin(100, 275/2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y + 370);
	m_BattleSceneMenuShapes.push_back(CubeBoyBackgrounds);

	InitCubeBoyAttackUI();
}

void GUI::InitCubeBoyMenuButtons()
{
	m_BattleSceneButtons.push_back(new CButtons(m_RenderWindow));
	sf::Vector2f pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 5 - 120, m_RenderWindow->getView().getCenter().y + m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 8.5);
	sf::Vector2f scale = sf::Vector2f(0.9f, 0.9f);
	InitButtonPosScaleTexture(pos, scale, &m_AttackButton, &m_AttackButton_Hover, m_BattleSceneButtons);

	m_BattleSceneButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 5 - 120, m_RenderWindow->getView().getCenter().y + m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 10.91666666666667);
	scale = sf::Vector2f(0.9f, 0.9f);
	InitButtonPosScaleTexture(pos, scale, &m_BackpackButton, &m_BackpackButton_Hover, m_BattleSceneButtons);

	m_BattleSceneButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 5 - 120, m_RenderWindow->getView().getCenter().y + m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 13.36066666666667);
	scale = sf::Vector2f(0.9f, 0.9f);
	InitButtonPosScaleTexture(pos, scale, &m_CubeboyButton, &m_CubeboyButton_Hover, m_BattleSceneButtons);

	m_BattleSceneButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 5 - 120, m_RenderWindow->getView().getCenter().y + m_BattleSceneButtons.back()->Sprite.getGlobalBounds().width * 15.75);
	scale = sf::Vector2f(0.9f, 0.9f);
	InitButtonPosScaleTexture(pos, scale, &m_FleeButton, &m_FleeButton_Hover, m_BattleSceneButtons);
}

void GUI::InitCubeBoyAttackUI()
{
	InitCubeBoyAttackButtons();

	sf::RectangleShape CubeBoyBackgrounds;
	CubeBoyBackgrounds.setSize(sf::Vector2f(315, 255));
	CubeBoyBackgrounds.setFillColor(sf::Color(90, 90, 90));
	CubeBoyBackgrounds.setOrigin(200, 255/2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x + 240, m_RenderWindow->getView().getCenter().y + 370);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(110, 110));
	CubeBoyBackgrounds.setFillColor(sf::Color::Magenta);
	CubeBoyBackgrounds.setOrigin(55, 55);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x - 30, m_RenderWindow->getView().getCenter().y + 300);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(100, 100));
	CubeBoyBackgrounds.setFillColor(sf::Color::White);
	CubeBoyBackgrounds.setOrigin(50, 50);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x - 30, m_RenderWindow->getView().getCenter().y + 300);
	CubeBoyBackgrounds.setTexture(&m_FireElement);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	// Attacks

	CubeBoyBackgrounds.setSize(sf::Vector2f(315, 255));
	CubeBoyBackgrounds.setFillColor(sf::Color::White);
	CubeBoyBackgrounds.setOrigin(200, 255 / 2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x + 240, m_RenderWindow->getView().getCenter().y + 380);
	CubeBoyBackgrounds.setTexture(&m_FireDeminishAttack);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(315, 255));
	CubeBoyBackgrounds.setFillColor(sf::Color::White);
	CubeBoyBackgrounds.setOrigin(200, 255 / 2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x + 240, m_RenderWindow->getView().getCenter().y + 380);
	CubeBoyBackgrounds.setTexture(&m_FireBurnAttack);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(315, 255));
	CubeBoyBackgrounds.setFillColor(sf::Color::White);
	CubeBoyBackgrounds.setOrigin(200, 255 / 2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x + 240, m_RenderWindow->getView().getCenter().y + 380);
	CubeBoyBackgrounds.setTexture(&m_FireEmberAttack);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);

	CubeBoyBackgrounds.setSize(sf::Vector2f(315, 255));
	CubeBoyBackgrounds.setFillColor(sf::Color::White);
	CubeBoyBackgrounds.setOrigin(200, 255 / 2);
	CubeBoyBackgrounds.setPosition(m_RenderWindow->getView().getCenter().x + 240, m_RenderWindow->getView().getCenter().y + 380);
	CubeBoyBackgrounds.setTexture(&m_FireIncinerateAttack);
	m_BattleSceneAttackShapes.push_back(CubeBoyBackgrounds);
}

void GUI::InitCubeBoyAttackButtons()
{
	m_BattleSceneAttackButtons.push_back(new CButtons(m_RenderWindow));
	sf::Vector2f pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 5 + 85, m_RenderWindow->getView().getCenter().y + m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 12.25);
	sf::Vector2f scale = sf::Vector2f(0.4f, 0.4f);
	InitButtonPosScaleTexture(pos, scale, &m_AttackFire, &m_AttackFire_Hover, m_BattleSceneAttackButtons);

	m_BattleSceneAttackButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 5 + 85, m_RenderWindow->getView().getCenter().y + m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 13.41);
	scale = sf::Vector2f(0.4f, 0.4f);
	InitButtonPosScaleTexture(pos, scale, &m_AttackFire, &m_AttackFire_Hover, m_BattleSceneAttackButtons);

	m_BattleSceneAttackButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 5 + 85, m_RenderWindow->getView().getCenter().y + m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 14.58);
	scale = sf::Vector2f(0.4f, 0.4f);
	InitButtonPosScaleTexture(pos, scale, &m_AttackFire, &m_AttackFire_Hover, m_BattleSceneAttackButtons);

	m_BattleSceneAttackButtons.push_back(new CButtons(m_RenderWindow));
	pos = sf::Vector2f(m_RenderWindow->getView().getCenter().x - m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 5 + 85, m_RenderWindow->getView().getCenter().y + m_BattleSceneAttackButtons.back()->Sprite.getGlobalBounds().width * 15.75);
	scale = sf::Vector2f(0.4f, 0.4f);
	InitButtonPosScaleTexture(pos, scale, &m_AttackFire, &m_AttackFire_Hover, m_BattleSceneAttackButtons);
}

void GUI::InitTextures()
{
	LoadTexture(&m_AttackButton, "GUI/Attack.png", false);
	LoadTexture(&m_BackpackButton, "GUI/Backpack.png", false);
	LoadTexture(&m_CubeboyButton, "GUI/CubeBoy.png", false);
	LoadTexture(&m_FleeButton, "GUI/Flee.png", false);

	LoadTexture(&m_AttackButton_Hover, "GUI/Attack_Hover.png", false);
	LoadTexture(&m_BackpackButton_Hover, "GUI/Backpack_Hover.png", false);
	LoadTexture(&m_CubeboyButton_Hover, "GUI/CubeBoy_Hover.png", false);
	LoadTexture(&m_FleeButton_Hover, "GUI/Flee_Hover.png", false);

	LoadTexture(&m_FireElement, "GUI/Fire.png", false);
	LoadTexture(&m_WaterElement, "GUI/Water.png", false);
	LoadTexture(&m_EarthElement, "GUI/Earth.png", false);
	LoadTexture(&m_AirElement, "GUI/Air.png", false);

	LoadTexture(&m_AttackFire, "GUI/FireAttack.png", false);
	LoadTexture(&m_AttackWater, "GUI/WaterAttack.png", false);
	LoadTexture(&m_AttackEarth, "GUI/EarthAttack.png", false);
	LoadTexture(&m_AttackAir, "GUI/AirAttack.png", false);

	LoadTexture(&m_AttackFire_Hover, "GUI/FireAttack_Hover.png", false);
	LoadTexture(&m_AttackWater_Hover, "GUI/WaterAttack_Hover.png", false);
	LoadTexture(&m_AttackEarth_Hover, "GUI/EarthAttack_Hover.png", false);
	LoadTexture(&m_AttackAir_Hover, "GUI/AirAttack_Hover.png", false);

	LoadTexture(&m_FireDeminishAttack, "GUI/Attacks/FireDeminish2.png", false);
	LoadTexture(&m_FireBurnAttack, "GUI/Attacks/FireBurn.png", false);
	LoadTexture(&m_FireEmberAttack, "GUI/Attacks/FireEmber.png", false);
	LoadTexture(&m_FireIncinerateAttack, "GUI/Attacks/FireIncinerate.png", false);
}

void GUI::SetAllButtonScaling(float _newScale)
{
	for (auto& button : m_BattleSceneButtons)
	{
		button->Sprite.setScale(_newScale, _newScale);
		button->Sprite.setOrigin(button->Sprite.getGlobalBounds().height / 2, button->Sprite.getGlobalBounds().width / 2);
	}
}

void GUI::InitButtonPosScaleTexture(sf::Vector2f _position, sf::Vector2f _scale, sf::Texture* _idleTexture, sf::Texture* _hoverTexture, std::vector<CButtons*> _vector)
{
	_vector.back()->SetPosition(_position.x, _position.y);
	_vector.back()->SetIdleTex(_idleTexture);
	_vector.back()->SetHoverTex(_hoverTexture);
	_vector.back()->SetClickTex(_hoverTexture);
	_vector.back()->Sprite.setScale(_scale.x, _scale.y);
}
