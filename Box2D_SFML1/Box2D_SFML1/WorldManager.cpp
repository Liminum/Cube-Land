#include "WorldManager.h"

WorldManager::WorldManager(sf::RenderWindow* _renderWindow, b2World &_world, TextureMaster* _texturemaster, Player* _player, LEVELTYPE _type)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _texturemaster;
	m_World = &_world;
	m_Player = _player;
	m_Type = _type;
}

WorldManager::~WorldManager()
{
	std::cout << "World Destroyed" << std::endl;
	m_Tiles.clear();
	if (m_Portal != nullptr)
	{
		delete m_Portal;
	}
	m_Portal = nullptr;

	m_LumberPiles.clear();
	m_LumberPile = nullptr;
	m_StonePiles.clear();
	m_StonePile = nullptr;

	delete m_background;
	m_background = nullptr;
	m_RenderWindow = nullptr;
	m_Tile = nullptr;
	m_World = nullptr;
	m_TextureMaster = nullptr;
	m_Player = nullptr;
}

void WorldManager::Start(AudioManager* _audioManager)
{
	switch (m_Type)
	{
	case WorldManager::LEVELTYPE::DEFAULT:
	{
		InitBackground(*m_TextureMaster->m_BackgroundTexture);
		
		// Ground Creation
		
		for (int i = -20000; i < 20000; i += 100)
		{
			m_Tile = new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_GrassTexture, sf::Vector2f(i, 0), sf::Vector2f(100, 100));
			m_Tiles.push_back(*m_Tile);
			m_Tile = nullptr;
		}

		m_Tile = new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_GrassTexture, sf::Vector2f(250, -600), sf::Vector2f(100, 100));
		m_Tiles.push_back(*m_Tile);
		m_Tile = nullptr;

		// Other Tile Creation
		m_Portal = new Portal(m_RenderWindow, *m_World, - 1000.f, -225.f);

		// Dropped Item Creation
		m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 5, 200, -100);
		m_LumberPiles.push_back(*m_LumberPile);
		m_LumberPile = nullptr;
		m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 5, 400, -100);
		m_LumberPiles.push_back(*m_LumberPile);
		m_LumberPile = nullptr;
		m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 5, 300, -100);
		m_LumberPiles.push_back(*m_LumberPile);
		m_LumberPile = nullptr;

		m_StonePile = new StonePile(m_RenderWindow, *m_World, 5, -200, -100);
		m_StonePiles.push_back(*m_StonePile);
		m_StonePile = nullptr;


		break;
	}
	case WorldManager::LEVELTYPE::FOREST:
	{
		break;
	}
		
	case WorldManager::LEVELTYPE::SNOW:
	{
		break;
	}
		
	default:
	{
		m_Tile = new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_GrassTexture, sf::Vector2f(0, 0), sf::Vector2f(100, 100));
		m_Tiles.push_back(*m_Tile);
		m_Tile = nullptr;
		break;
	}
	}
}

void WorldManager::Update()
{
	for (Tile& tile : m_Tiles)
	{
		tile.Update();
	}
	if (m_Portal != nullptr)
	{
		m_Portal->Update();
	}
	for (LumberPile& LumberPile : m_LumberPiles)
	{
		LumberPile.Update();
	}
	for (StonePile& StonePile : m_StonePiles)
	{
		StonePile.Update();
	}

	if (m_Player != nullptr && !m_Player->m_MARKASDESTROY)
	{
		PickupItemOnGround();
	}

	// World Step
	m_World->Step(1 / 60.f, 60, 60);
}

void WorldManager::Render(sf::Shader* _defaultshader)
{
	m_RenderWindow->draw(*m_background, _defaultshader);
	// Blocks
	std::list<Tile>::iterator it;
	for (it = m_Tiles.begin(); it != m_Tiles.end(); it++)
	{
		float Mag1 = sqrt(((it->GetShape().getPosition().x - m_RenderWindow->getView().getCenter().x) * (it->GetShape().getPosition().x - m_RenderWindow->getView().getCenter().x)) + ((it->GetShape().getPosition().y - m_RenderWindow->getView().getCenter().y) * (it->GetShape().getPosition().y - m_RenderWindow->getView().getCenter().y)));
		if (Mag1 < 1920 * 2.8f)
		{
			m_RenderWindow->draw(it->GetShape(), _defaultshader);
		}
	}
	if (m_Portal != nullptr)
	{
		m_Portal->Render(_defaultshader);
	}
	for (LumberPile& LumberPile : m_LumberPiles)
	{
		LumberPile.Render(_defaultshader);
	}
	for (StonePile& StonePile : m_StonePiles)
	{
		StonePile.Render(_defaultshader);
	}
}

void WorldManager::InitBackground(sf::Texture& _texture)
{
	std::cout << "Background Created" << std::endl;
	m_background = new sf::Sprite();
	m_background->setTexture(_texture, true);
	m_background->setTextureRect(sf::IntRect(0,0,10000,10000));

	m_background->setOrigin(m_background->getGlobalBounds().width / 2, m_background->getGlobalBounds().height / 2);
	m_background->setScale(7, 7);
	m_background->setPosition(sf::Vector2f(0, 2000));
}

bool WorldManager::PickupItemOnGround()
{
	b2Contact* contact;
	bool sensorA;
	bool sensorB;
	for (contact = m_World->GetContactList(); contact; contact = contact->GetNext())
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		//make sure only one of the fixtures was a sensor
		sensorA = fixtureA->IsSensor();
		sensorB = fixtureB->IsSensor();
		if ((sensorA || sensorB) && (fixtureA->GetBody() == m_Player->GetBody() || fixtureB->GetBody() == m_Player->GetBody()))
		{
			if (IsItemListBody(m_LumberPiles, fixtureA) || IsItemListBody(m_LumberPiles, fixtureB))
			{
				std::list<LumberPile>::iterator it;
				for (it = m_LumberPiles.begin(); it != m_LumberPiles.end(); it++)
				{
					if (it->GetBody() == fixtureA->GetBody() || it->GetBody() == fixtureB->GetBody())
					{
						Item* temp = new Item(m_TextureMaster->m_LumberPile, Item::ITEMTYPE::LUMBERPILE);
						m_Player->AddItemToInventory(temp, it->GetLumberPileAmount());
						temp = nullptr;
						it = m_LumberPiles.erase(it);
						break;
					}
				}
			}
			else if (IsItemListBody(m_StonePiles, fixtureA) || IsItemListBody(m_StonePiles, fixtureB))
			{
				std::list<StonePile>::iterator it;
				for (it = m_StonePiles.begin(); it != m_StonePiles.end(); it++)
				{
					if (it->GetBody() == fixtureA->GetBody() || it->GetBody() == fixtureB->GetBody())
					{
						Item* temp = new Item(m_TextureMaster->m_StonePile, Item::ITEMTYPE::STONEPILE);
						m_Player->AddItemToInventory(temp, it->GetStonePileAmount());
						temp = nullptr;
						it = m_StonePiles.erase(it);
						break;
					}
				}
			}
			fixtureA = nullptr;
			fixtureB = nullptr;
			contact = nullptr;
			return true;
		}

		fixtureA = nullptr;
		fixtureB = nullptr;
	}
	contact = nullptr;

	return false;
}

void WorldManager::SetPlayer(Player* _player)
{
	m_Player = _player;
}

void WorldManager::LosePlayer()
{
	m_Player = nullptr;
}