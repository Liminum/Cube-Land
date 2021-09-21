#include "WorldManager.h"

WorldManager::WorldManager(sf::RenderWindow* _renderWindow, b2World &_world, TextureMaster* _texturemaster, Player* _player)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _texturemaster;
	m_World = &_world;
	m_Tile = nullptr;
	m_LumberPile = nullptr;
	m_StonePile = nullptr;
	m_Player = _player;
}

WorldManager::~WorldManager()
{
	m_Tiles.clear();

	m_LumberPiles.clear();
	m_LumberPile = nullptr;
	m_StonePiles.clear();
	m_StonePile = nullptr;

	m_RenderWindow = nullptr;
	m_Tile = nullptr;
	m_World = nullptr;
	m_TextureMaster = nullptr;
	m_Player = nullptr;
}

void WorldManager::Start()
{
	InitBackground();
	
	m_Tile = new Tile(m_RenderWindow, *m_World, 50.0f, sf::Vector2f(0, 0), sf::Vector2f(25000, 100));
	m_Tiles.push_back(*m_Tile);
	m_Tile = nullptr;
	m_Tile = new Tile(m_RenderWindow, *m_World, 50.0f, sf::Vector2f(250, -600), sf::Vector2f(500, 100));
	m_Tiles.push_back(*m_Tile);
	m_Tile = nullptr;


	m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 200, -100);
	m_LumberPiles.push_back(*m_LumberPile);
	m_LumberPile = nullptr;
	m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 400, -100);
	m_LumberPiles.push_back(*m_LumberPile);
	m_LumberPile = nullptr;
	m_LumberPile = new LumberPile(m_RenderWindow, *m_World, 300, -100);
	m_LumberPiles.push_back(*m_LumberPile);
	m_LumberPile = nullptr;

	m_StonePile = new StonePile(m_RenderWindow, *m_World, -200, -100);
	m_StonePiles.push_back(*m_StonePile);
	m_StonePile = nullptr;

}

void WorldManager::Update()
{
	for (Tile& tile : m_Tiles)
	{
		tile.Update();
	}

	for (LumberPile& LumberPile : m_LumberPiles)
	{
		LumberPile.Update();
	}
	for (StonePile& StonePile : m_StonePiles)
	{
		StonePile.Update();
	}

	PickupItemOnGround();

	// World Step
	m_World->Step(1 / 60.f, 10, 30);
}

void WorldManager::Render()
{
	m_RenderWindow->draw(m_background);
	for (Tile& tile : m_Tiles)
	{
		tile.Render();
	}
	for (LumberPile& LumberPile : m_LumberPiles)
	{
		LumberPile.Render();
	}
	for (StonePile& StonePile : m_StonePiles)
	{
		StonePile.Render();
	}
}

void WorldManager::InitBackground()
{
	
	m_background = sf::Sprite();
	m_background.setTexture(*m_TextureMaster->m_BackgroundTexture, true);
	m_background.setTextureRect(sf::IntRect(0,0,10000,10000));

	m_background.setOrigin(m_background.getGlobalBounds().width / 2, m_background.getGlobalBounds().height / 2);
	m_background.setScale(7, 7);
	m_background.setPosition(m_RenderWindow->getView().getCenter() + sf::Vector2f(0, 2000));
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