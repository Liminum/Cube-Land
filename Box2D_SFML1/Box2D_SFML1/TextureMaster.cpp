#include "TextureMaster.h"

TextureMaster::TextureMaster()
{
	// Textures
	m_BackgroundTexture = new sf::Texture();
	m_BackgroundTexture->setSmooth(true);
	m_BackgroundTexture->setRepeated(true);

	m_GrassTexture = new sf::Texture();
	m_GrassTexture->setRepeated(true);

	if (m_BackgroundTexture->loadFromFile("Resources/Images/OriBG.jpg"))
	{
		std::cout << "Background Texture Loaded!" << std::endl;
	}
	if (m_GrassTexture->loadFromFile("Resources/Images/GrassBlock.png"))
	{
		std::cout << "Grass Texture Loaded!" << std::endl;
	}
}

TextureMaster::~TextureMaster()
{
	DeletePointer(m_BackgroundTexture);
	m_BackgroundTexture = nullptr;
	DeletePointer(m_GrassTexture);
	m_GrassTexture = nullptr;
}
