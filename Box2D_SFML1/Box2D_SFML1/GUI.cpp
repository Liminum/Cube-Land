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
	m_InventorySlotMap.clear();
	m_InventoryStackCounters.clear();
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

	for (int i = 0; i < m_InventorySlotMap.size(); i++)
	{
		m_RenderWindow->draw(m_InventorySlotMap[i], _defaultshader);
		m_RenderWindow->draw(_player->m_InventoryMap[i].GetShape(), _defaultshader);
		m_RenderWindow->draw(m_InventoryStackCounters[i], _defaultshader);
	}
	
	m_RenderWindow->draw(m_HealthBorderSprite, _defaultshader);
	m_RenderWindow->draw(m_HealthSprite, _defaultshader);
	m_RenderWindow->draw(m_ManaBorderSprite, _defaultshader);
	m_RenderWindow->draw(m_ManaSprite, _defaultshader);
	
	if (_player->m_bInventoryOpen)
	{
		// Render Moving Item On Top Always
		if (bPlayerIsMovingItem(_player))
		{
			m_RenderWindow->draw(_player->m_InventoryMap[bGetPositionOfMovingItem(_player)].GetShape(), _defaultshader);
			m_RenderWindow->draw(m_InventoryStackCounters[bGetPositionOfMovingItem(_player)], _defaultshader);
		}
		
		m_MousePointer.setPosition(mousePos);
		m_RenderWindow->draw(m_MousePointer, _defaultshader);
	}
	else if (_player->GetStaff() != nullptr)
	{
		m_MousePointer.setPosition(mousePos);
		m_RenderWindow->draw(m_MousePointer, _defaultshader);
	}
	_defaultshader = nullptr;
}

sf::Vector2f GUI::UIMousePointer(sf::View& _uiview)
{
	sf::Shader* defaultShader = NULL;
	sf::Vector2f mousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow), _uiview);
	return mousePos;
}

void GUI::InitInventoryUI(Player* _player)
{
	m_MousePointer.setTexture(*m_TextureMaster->m_MousePosTex, true);
	m_MousePointer.setScale(2, 2);
	m_MousePointer.setOrigin(m_MousePointer.getGlobalBounds().width / 2 , m_MousePointer.getGlobalBounds().height / 2);

	for (int i = 0 ; i < 9 ; i++)
	{
		m_Shape = sf::Sprite();
		m_Shape.setTexture(*m_TextureMaster->m_ItemSlot, true);
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
		m_HealthSprite.setTextureRect(sf::IntRect(0, 0, _player->GetCurrentHealth(), m_HealthTexture.getSize().y));
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

void GUI::InventoryUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player)
{
	_renderWindow->setView(_uiView);

	UIMousePointer(_uiView);

	if (m_FirstEmptySlotTimer.getElapsedTime().asSeconds() >= 0.01f)
	{
		FindFirstEmptyInventorySlot(_player);
		m_FirstEmptySlotTimer.restart();
	}
	for (int i = 0; i < m_InventorySlotMap.size(); i++)
	{

		m_InventorySlotMap[i].setPosition(m_RenderWindow->getView().getCenter().x - (m_RenderWindow->getView().getSize().x / 2) + 55 + (i * 80), m_RenderWindow->getView().getCenter().y - (m_RenderWindow->getView().getSize().y / 2) + 50);
		
		if (bPlayerIsMovingItem(_player))
		{
			_renderWindow->mapCoordsToPixel(_player->m_InventoryMap[i].GetPosition(), _uiView);
			HoldItemInInventory(_player);
		}
		else
		{
			_renderWindow->mapCoordsToPixel(_player->m_InventoryMap[i].GetPosition(), _uiView);
			_player->m_InventoryMap[i].SetPosition(m_InventorySlotMap[i].getPosition().x, m_InventorySlotMap[i].getPosition().y);
			m_InventoryStackCounters[i].setPosition(m_InventorySlotMap[i].getPosition().x + 16, m_InventorySlotMap[i].getPosition().y + 10);
		}
		
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
	
	
	// m_CIITexture is the texture for the Current Item Index
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
		for (std::map<int, Item>::iterator iit = _player->m_InventoryMap.begin(); iit != _player->m_InventoryMap.end(); iit++)
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
	for (std::map<int, Item>::iterator iit = _player->m_InventoryMap.begin(); iit != _player->m_InventoryMap.end(); iit++)
	{
		if (_player->m_CurrentItemIndex == iit->first && iit->second.m_Type == Item::ITEMTYPE::STAFF)
		{
			std::cout << "Staff Selected!" << std::endl;
			iit->second.m_bIsItemSelected = true;
		}
	}
}

void GUI::ItemClicked(sf::Event& _event, Player* _player)
{
	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < _player->m_InventoryMap.size(); i++)
		{
			if (_player->m_bInventoryOpen && _player->m_InventoryMap[i].GetShape().getGlobalBounds().intersects(m_MousePointer.getGlobalBounds()))
			{
				_player->m_InventoryMap[i].m_bItemIsMovingInInventory = true;
				break;
			}
		}
	}
}

void GUI::ItemDroppedInInventory(sf::RenderWindow* _renderwindow, sf::View& _uiview, sf::View& _worldview, sf::Event& _event, Player* _player)
{
	_renderwindow->setView(_uiview);
	for (int i1 = 0; i1 < m_InventorySlotMap.size(); i1++)
	{
		if (bPlayerIsMovingItem(_player, i1) && _player->m_bInventoryOpen)
		{
			for (std::map<int, sf::Sprite>::iterator smit = m_InventorySlotMap.begin(); smit != m_InventorySlotMap.end(); smit++)
			{
				if (smit->second.getGlobalBounds().contains(m_MousePointer.getPosition()) && _event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
				{
					_player->m_InventoryMap[smit->first];
					_player->m_InventoryStackValues[smit->first];

					std::map<int, Item>::iterator itit = _player->m_InventoryMap.find(i1);
					std::map<int, int>::iterator stit = _player->m_InventoryStackValues.find(i1);

					if (smit->first != itit->first)
					{
						_player->m_InventoryMap[i1].m_PositionInInventory = smit->first;
						_player->m_InventoryMap[smit->first].m_PositionInInventory = i1;

						std::swap(_player->m_InventoryMap[smit->first], itit->second);
						std::swap(_player->m_InventoryStackValues[smit->first], stit->second);

						// Moved Item Into Currently Selected Slot?
						for (std::map<int, Item>::iterator iit = _player->m_InventoryMap.begin(); iit != _player->m_InventoryMap.end(); ++iit)
						{
							if (_player->m_CurrentItemIndex == iit->first && iit->second.m_Type == Item::ITEMTYPE::STAFF && iit->second.m_bIsItemSelected == false)
							{
								std::cout << "Staff Selected!" << std::endl;
								iit->second.m_bIsItemSelected = true;
								iit->second.m_bItemIsMovingInInventory = false;
								break;
							}
						}

						for (int i = 0; i < 9; i++)
						{
							_player->m_InventoryMap[i].m_bItemIsMovingInInventory = false;
						}
						break;

					}
					else if (smit->first == itit->first)
					{
					}
					for (int i = 0; i < 9; i++)
					{
						_player->m_InventoryMap[i].m_bItemIsMovingInInventory = false;
					}
				}
				else if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 9; i++)
					{
						_player->m_InventoryMap[i].m_bItemIsMovingInInventory = false;
					}
				}
			}
		}
	}
	_renderwindow->setView(_worldview);
}

void GUI::HoldItemInInventory(Player* _player)
{
	int itemOffset = -25;
	for (int i = 0; i < m_InventorySlotMap.size(); i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->m_bInventoryOpen && bPlayerIsMovingItem(_player, i))
		{
			_player->m_InventoryMap[i].GetShape().setPosition(m_MousePointer.getPosition() + sf::Vector2f(itemOffset, itemOffset));
			m_InventoryStackCounters[i].setPosition(m_MousePointer.getPosition().x + 16 + itemOffset, m_MousePointer.getPosition().y + 10 + itemOffset);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->m_bInventoryOpen && !bPlayerIsMovingItem(_player, i))
		{
			_player->m_InventoryMap[i].GetShape().setPosition(m_InventorySlotMap[i].getPosition());
			m_InventoryStackCounters[i].setPosition(m_InventorySlotMap[i].getPosition().x + 16, m_InventorySlotMap[i].getPosition().y + 10);
		}
	}
}

bool GUI::bPlayerIsMovingItem(Player* _player, int _it)
{
	if (_player->m_InventoryMap[_it].m_bItemIsMovingInInventory)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GUI::bPlayerIsMovingItem(Player* _player)
{
	int i = 0;
	for (i = 0; i < _player->m_InventoryMap.size(); i++)
	{
		if (_player->m_InventoryMap[i].m_bItemIsMovingInInventory)
		{
			return true;
		}
	}
	return false;
}

int GUI::bGetPositionOfMovingItem(Player* _player)
{
	if (bPlayerIsMovingItem(_player))
	{
		int i = 0;
		for (i = 0; i < _player->m_InventoryMap.size(); i++)
		{
			if (_player->m_InventoryMap[i].m_bItemIsMovingInInventory)
			{
				return i;
			}
		}
	}
	else
	{
		return -1;
	}
}