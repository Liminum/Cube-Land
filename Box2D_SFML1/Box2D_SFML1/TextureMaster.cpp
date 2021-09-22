#include "TextureMaster.h"

TextureMaster::TextureMaster()
{
	m_BackgroundTexture = new sf::Texture();
	if (m_BackgroundTexture->loadFromFile("Resources/Sprites/gameBackground.png"))
	{
		std::cout << "Background Texture Loaded" << std::endl;
	}
	m_BackgroundTexture->setSmooth(true);
	m_BackgroundTexture->setRepeated(true);

	m_LumberPile = new sf::Texture();
	m_LumberPile->loadFromFile("Resources/Sprites/LumberPile.png");

	m_StonePile = new sf::Texture();
	if (m_StonePile->loadFromFile("Resources/Sprites/StonePile.png"))
	{
		std::cout << "StonePile Texture Loaded" << std::endl;
	}

	m_GrassTexture = new sf::Texture();
	if (m_GrassTexture->loadFromFile("Resources/Sprites/Grass.png"))
	{
		std::cout << "Grass Texture Loaded" << std::endl;
	}
	m_GrassTexture->setRepeated(true);

	m_CIITexture = new sf::Texture();
	m_CIITexture->loadFromFile("Resources/Sprites/CurrentlySelectedItem.png");

	m_ItemSlot = new sf::Texture();
	m_ItemSlot->loadFromFile("Resources/Sprites/ItemSlot.png");
}

TextureMaster::~TextureMaster()
{
	delete m_BackgroundTexture;
	m_BackgroundTexture = nullptr;
	delete m_LumberPile;
	m_LumberPile = nullptr;
	delete m_StonePile;
	m_StonePile = nullptr;
	delete m_GrassTexture;
	m_GrassTexture = nullptr;
	delete m_CIITexture;
	m_CIITexture = nullptr;
	delete m_ItemSlot;
	m_ItemSlot = nullptr;
}
