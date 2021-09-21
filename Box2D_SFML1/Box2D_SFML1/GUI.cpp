#include "GUI.h"


GUI::GUI(sf::RenderWindow* _renderwindow, TextureMaster* _texturemaster)
{
	m_RenderWindow = _renderwindow;
	m_TextureMaster = _texturemaster;
	m_Timer = sf::Clock();
	m_Font = sf::Font();
	m_Font.loadFromFile("Resources/Fonts/ANDYB.TTF");
	m_DisplayText = sf::Text();
	m_DisplayText.setFont(m_Font);
}

GUI::~GUI()
{
	m_InventorySlotMap.clear();
	m_InventoryStackCounters.clear();
	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
}

void GUI::Start()
{
	InitHealthAndManaUI();
}

void GUI::Update()
{
	
}

void GUI::Render(Player* _player)
{
	for (int i = 0; i < m_InventorySlotMap.size(); i++)
	{
		m_RenderWindow->draw(m_InventorySlotMap[i]);
		m_RenderWindow->draw(_player->m_Inventory[i].GetShape());
		m_RenderWindow->draw(m_InventoryStackCounters[i]);
	}
	m_RenderWindow->draw(m_HealthBorderSprite);
	m_RenderWindow->draw(m_HealthSprite);
	m_RenderWindow->draw(m_ManaBorderSprite);
	m_RenderWindow->draw(m_ManaSprite);
}

void GUI::InitInventoryUI(Player* _player)
{
	if (m_Texture.loadFromFile("Resources/Sprites/ItemSlot.png"))
	{
		std::cout << "Item Slot Textures Loaded!" << std::endl;
	}
	
	for (int i = 0 ; i < 9 ; i++)
	{
		m_Shape = sf::Sprite();
		m_Shape.setTexture(m_Texture, true);
		m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
		m_Shape.setScale(0.4f, 0.4f);
		m_InventorySlotMap.emplace(i, m_Shape);

		sf::Text stackcounter = sf::Text();
		stackcounter.setFont(m_Font);
		stackcounter.setCharacterSize(18);
		stackcounter.setFillColor(sf::Color::White);
		stackcounter.setOutlineThickness(0.75f);
		stackcounter.setOutlineColor(sf::Color::Black);
		stackcounter.setString("");
		m_RenderWindow->mapCoordsToPixel(stackcounter.getPosition());
		m_InventoryStackCounters.insert({ i, stackcounter });;
		m_InventoryStackCounters[i].setOrigin(m_InventoryStackCounters[i].getGlobalBounds().width / 2, m_InventoryStackCounters[i].getGlobalBounds().height / 2);

		_player->m_InventoryStackValues.emplace(i, 0);
	}
}

void GUI::InitHealthAndManaUI()
{
	m_ManaTexture.loadFromFile("Resources/Sprites/ManaBar.png");
	m_ManaBorderTexture.loadFromFile("Resources/Sprites/ManaBarBorder.png");
	m_ManaSprite.setTexture(m_ManaTexture, true);
	m_ManaBorderSprite.setTexture(m_ManaBorderTexture, true);
	m_ManaSprite.setOrigin(-3, -3);
	m_ManaSprite.scale(1.51, 1.5);
	m_ManaBorderSprite.scale(1.5, 1.5);

	m_HealthTexture.loadFromFile("Resources/Sprites/Bar.png");
	m_HealthBorderTexture.loadFromFile("Resources/Sprites/HealthBarBorder.png");
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
	if (_player->GetHealth() > 0)
	{
		m_HealthSprite.setTextureRect(sf::IntRect(0, 0, _player->GetHealth(), m_HealthTexture.getSize().y));
	}
	else
	{
		m_HealthSprite.setTextureRect(sf::IntRect(0, 0, 0, m_HealthTexture.getSize().y));
	}

	m_RenderWindow->mapCoordsToPixel(m_ManaSprite.getPosition());
	m_RenderWindow->mapCoordsToPixel(m_ManaBorderSprite.getPosition());
	m_ManaSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 100);
	m_ManaBorderSprite.setPosition(m_RenderWindow->getView().getCenter().x + (m_RenderWindow->getView().getSize().x / 2) - 200, m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 100);
	if (_player->GetMana() > 0)
	{
		m_ManaSprite.setTextureRect(sf::IntRect(0, 0, _player->GetMana(), m_ManaTexture.getSize().y));
	}
	else
	{
		m_ManaSprite.setTextureRect(sf::IntRect(0, 0, 0, m_ManaTexture.getSize().y));
	}
}

void GUI::InventoryUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player)
{
	if (m_FirstEmptySlotTimer.getElapsedTime().asSeconds() >= 0.01f)
	{
		FindFirstEmptyInventorySlot(_player);
		m_FirstEmptySlotTimer.restart();
	}
	_renderWindow->setView(_uiView);
	for (int i = 0; i < m_InventorySlotMap.size(); i++)
	{
		m_InventorySlotMap[i].setPosition(m_RenderWindow->getView().getCenter().x - (m_RenderWindow->getView().getSize().x / 2) + 55 + (i * 80), m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 50);
		
		m_RenderWindow->mapCoordsToPixel(_player->m_Inventory[i].GetPosition());
		_player->m_Inventory[i].GetShape().setPosition(m_InventorySlotMap[i].getPosition());

		m_InventoryStackCounters[i].setPosition(m_InventorySlotMap[i].getPosition().x + 16, m_InventorySlotMap[i].getPosition().y + 10);
		
		m_InventorySlotMap[i].setTexture(*m_TextureMaster->m_ItemSlot);
		if (_player->m_InventoryStackValues[i] <= 1)
		{
			m_InventoryStackCounters[i].setString("");
		}
		else
		{
			m_InventoryStackCounters[i].setString(std::to_string(_player->m_InventoryStackValues[i]));
		}
	}
	
	
	// m_CIITexture is the texture for the currently selected slot
	m_InventorySlotMap[_player->m_CurrentItemIndex].setTexture(*m_TextureMaster->m_CIITexture);

}

int GUI::FindFirstEmptyInventorySlot(Player* _player)
{
	int i = 0;
	//
	// ofstream
	// x Pos
	std::ofstream out_file;

	out_file.open("Resources/Output/FirstEmptyInventorySlot.txt");
	if (out_file.is_open())
	{
		for (i = 0; i < m_InventorySlotMap.size(); i++)
		{
			if (_player->m_InventoryStackValues[i] == 0)
			{
				out_file << i << std::endl;
				break;
			}

		}
		out_file.close();
	}
	else
	{
		std::cout << "OutPut File Not Open!" << std::endl;
	}

	//
	return i;
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

void GUI::HotBarScrolling(sf::Event& _event, Player* _player)
{
	// Canvas Zooming
	if (_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
	{
		if (_event.mouseWheelScroll.delta >= 1)
		{

			if (_player->m_CurrentItemIndex < 9 && _player->m_CurrentItemIndex >= 0)
			{
				_player->m_CurrentItemIndex--;
			}
			if (_player->m_CurrentItemIndex < 0)
			{
				_player->m_CurrentItemIndex = 8;
			}
			std::cout << "zoom In" << std::endl;


		}
		else if (_event.mouseWheelScroll.delta <= -1)
		{
			if (_player->m_CurrentItemIndex < 9)
			{
				_player->m_CurrentItemIndex++;
			}
			if (_player->m_CurrentItemIndex > 8)
			{
				_player->m_CurrentItemIndex = 0;
			}
			std::cout << "zoom out" << std::endl;
		}

		// Items
		for (std::map<int, Item>::iterator iit = _player->m_Inventory.begin(); iit != _player->m_Inventory.end(); iit++)
		{
			if (_player->m_CurrentItemIndex == iit->first && iit->second.m_Type == Item::ITEMTYPE::STAFF)
			{
				std::cout << "Staff Selected!" << std::endl;
				iit->second.m_bIsItemSelected = true;
			}
		}
	}
}

void GUI::InitHotBarScrolling(sf::Event& _event, Player* _player)
{
	// Items
	for (std::map<int, Item>::iterator iit = _player->m_Inventory.begin(); iit != _player->m_Inventory.end(); iit++)
	{
		if (_player->m_CurrentItemIndex == iit->first && iit->second.m_Type == Item::ITEMTYPE::STAFF)
		{
			std::cout << "Staff Selected!" << std::endl;
			iit->second.m_bIsItemSelected = true;
		}
	}
}