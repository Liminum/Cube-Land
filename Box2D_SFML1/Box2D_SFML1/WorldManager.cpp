#include "WorldManager.h"

WorldManager::WorldManager(sf::RenderWindow* _renderWindow, b2World &_world, TextureMaster* _texturemaster, LEVELTYPE _type)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _texturemaster;
	m_World = &_world;
	m_Type = _type;
}

WorldManager::~WorldManager()
{
	std::cout << "World Destroyed" << std::endl;

	CleanupBlocks();
	DeletePointer(m_background);
	DeletePointer(m_Tile);
	m_background = nullptr;
	m_Tile = nullptr;
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_TextureMaster = nullptr;
}

void WorldManager::Start(AudioManager* _audioManager)
{
	switch (m_Type)
	{
	case WorldManager::LEVELTYPE::DEFAULT:
	{
		InitBackground(*m_TextureMaster->m_BackgroundTexture);
		
		CreateBasicBlocks();

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
		break;
	}
	}
}

void WorldManager::Update()
{
	for (Tile* tile : m_Tiles)
	{
		tile->Update();
	}

	// World Step
	m_World->Step(1 / 60.f, 60, 60);
}

void WorldManager::Render(sf::Shader* _defaultshader)
{
	m_RenderWindow->draw(*m_background, _defaultshader);

	// Blocks
	std::vector<Tile*>::iterator it;
	for (it = m_Tiles.begin(); it != m_Tiles.end(); it++)
	{
		float Mag1 = sqrt((((*it)->GetShape()->getPosition().x - m_RenderWindow->getView().getCenter().x) * ((*it)->GetShape()->getPosition().x - m_RenderWindow->getView().getCenter().x)) + (((*it)->GetShape()->getPosition().y - m_RenderWindow->getView().getCenter().y) * ((*it)->GetShape()->getPosition().y - m_RenderWindow->getView().getCenter().y)));
		if (Mag1 < 1920 * 2.8f)
		{
			m_RenderWindow->draw(*(*it)->GetShape(), _defaultshader);
		}
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

void WorldManager::CleanupBlocks()
{
	for (auto& pointer : m_Tiles)
	{
		DeletePointer(pointer);
		pointer = nullptr;
	}
	m_Tiles.erase(std::remove(m_Tiles.begin(), m_Tiles.end(), nullptr), m_Tiles.end());
}

void WorldManager::CreateBasicBlocks()
{
	CleanupBlocks();
	// Ground Creation
	for (int i = -20000; i < 20000; i += 100)
	{
		m_Tiles.push_back(new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_GrassTexture, sf::Vector2f(i, 0), sf::Vector2f(100, 100)));
	}

	m_Tiles.push_back(new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_GrassTexture, sf::Vector2f(250, -600), sf::Vector2f(100, 100)));
}