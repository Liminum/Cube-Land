#include "WorldManager.h"

WorldManager::WorldManager(sf::RenderWindow* _renderWindow, b2World &_world, TextureMaster* _texturemaster)
{
	m_RenderWindow = _renderWindow;
	m_TextureMaster = _texturemaster;
	m_World = &_world;
}

WorldManager::~WorldManager()
{
	std::cout << "World Destroyed" << std::endl;

	CleanupTiles();
	DeletePointer(m_background);
	DeletePointer(m_Tile);
	DeletePointer(m_World);
	m_background = nullptr;
	m_Tile = nullptr;
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_TextureMaster = nullptr;
}

void WorldManager::Start(AudioManager* _audioManager)
{
	InitBackground(*m_TextureMaster->m_BackgroundTexture);

	ImportWorldFromINI();
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

void WorldManager::CleanupTiles()
{
	for (auto& pointer : m_Tiles)
	{
		DeletePointer(pointer);
		pointer = nullptr;
	}
	m_Tiles.erase(std::remove(m_Tiles.begin(), m_Tiles.end(), nullptr), m_Tiles.end());
}

void WorldManager::GrabTileTypes(std::vector<char>& _tileTypes)
{
	char m_Type = 0;
	std::ifstream file;
	std::string currentLine;
	file.open("Resources/Output/World.ini");
	if (file.is_open())
	{
		while (file.get(m_Type))
		{
			if (m_Type == ',')
			{
			}
			else
			{
				_tileTypes.push_back(m_Type);
			}
		}
		file.close();
	}
}

void WorldManager::ProcessTileTypes(std::vector<char>& _tileTypes)
{
	int iteratorX = -INISIZE;
	int iteratorY = -INISIZE;
	std::vector<char>::iterator it = _tileTypes.begin();
	while (it != _tileTypes.end())
	{
		if (*it == '0')
		{

		}
		else if (*it == 'o')
		{
			m_Tiles.push_back(new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_DirtBlock_BG, sf::Vector2f((float)iteratorX * 100.0f, (float)iteratorY * 100.0f), sf::Vector2f(100, 100), "Background"));
		}
		else if (*it == '1')
		{
			m_Tiles.push_back(new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_DirtBlock, sf::Vector2f((float)iteratorX * 100.0f, (float)iteratorY * 100.0f), sf::Vector2f(100, 100), "Wall"));
		}
		else if (*it == '2')
		{
			m_Tiles.push_back(new Tile(m_RenderWindow, *m_World, m_TextureMaster->m_Grass, sf::Vector2f((float)iteratorX * 100.0f, (float)iteratorY * 100.0f), sf::Vector2f(100, 100), "Event"));
		}

		if (iteratorX == INISIZE)
		{
			iteratorX = -INISIZE;
			iteratorY++;
		}
		else
		{
			iteratorX++;
		}

		it++;
	}
}

void WorldManager::ImportWorldFromINI()
{
	CleanupTiles();

	std::vector<char> m_TileTypes;
	GrabTileTypes(m_TileTypes);

	ProcessTileTypes(m_TileTypes);
}
