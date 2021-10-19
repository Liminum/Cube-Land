#include "TextureMaster.h"

TextureMaster::TextureMaster()
{
	// Tile Textures
	m_BackgroundTexture = new sf::Texture();
	m_BackgroundTexture->setSmooth(true);
	m_BackgroundTexture->setRepeated(true);
	m_GrassTexture = new sf::Texture();

	if (m_BackgroundTexture->loadFromFile("Resources/Images/OriBG.jpg"))
	{
		std::cout << "Background Texture Loaded!" << std::endl;
	}

	if (m_GrassTexture->loadFromFile("Resources/Images/GrassBlock.png"))
	{
		std::cout << "Grass Texture Loaded!" << std::endl;
	}
	m_GrassTexture->setRepeated(true);

	// Item Textures
	m_LumberPile = new sf::Texture();
	m_StonePile = new sf::Texture();

	if (m_LumberPile->loadFromFile("Resources/Images/LumberPile.png"))
	{
		std::cout << "LumberPile Texture Loaded!" << std::endl;
	}
	if (m_StonePile->loadFromFile("Resources/Images/StonePile.png"))
	{
		std::cout << "StonePile Texture Loaded!" << std::endl;
	}


	//Projectile Textures
	m_PlayerBasicAttackTexture = new sf::Texture();
	m_EnemyMageAttackTexture = new sf::Texture();
	m_CoinTexture = new sf::Texture();

	if (m_PlayerBasicAttackTexture->loadFromFile("Resources/Images/PlayerBasicAttack.png"))
	{
		std::cout << "Player Basic Attack Texture Loaded!" << std::endl;
	}
	if (m_EnemyMageAttackTexture->loadFromFile("Resources/Images/EnemyMageAttack.png"))
	{
		std::cout << "Enemy Make Attack Texture Loaded!" << std::endl;
	}
	if (m_CoinTexture->loadFromFile("Resources/Images/Coin.png"))
	{
		std::cout << "Coin Texture Loaded!" << std::endl;
	}

	// GUI Textures
	m_CIITexture = new sf::Texture();
	m_ItemSlot = new sf::Texture();
	m_MousePosTex = new sf::Texture();
	m_ItemSelectedTex = new sf::Texture();

	if (m_MousePosTex->loadFromFile("Resources/Images/Cursor.png"))
	{
		std::cout << "Mouse Pointer Texture Loaded!" << std::endl;
	}
	if (m_CIITexture->loadFromFile("Resources/Images/CurrentlySelectedItem.png"))
	{
		std::cout << "Currently Selected Item Texture Loaded!" << std::endl;
	}
	if (m_ItemSlot->loadFromFile("Resources/Images/ItemSlot.png"))
	{
		std::cout << "Item Slot Texture Loaded!" << std::endl;
	}
}

TextureMaster::~TextureMaster()
{
	DeletePointer(m_BackgroundTexture);
	m_BackgroundTexture = nullptr;
	DeletePointer(m_LumberPile);
	m_LumberPile = nullptr;
	DeletePointer(m_StonePile);
	m_StonePile = nullptr;
	DeletePointer(m_GrassTexture);
	m_GrassTexture = nullptr;
	DeletePointer(m_ItemSelectedTex);
	m_ItemSelectedTex = nullptr;
	DeletePointer(m_CIITexture);
	m_CIITexture = nullptr;
	DeletePointer(m_ItemSlot);
	m_ItemSlot = nullptr;
	DeletePointer(m_MousePosTex);
	m_MousePosTex = nullptr;
	DeletePointer(m_PlayerBasicAttackTexture);
	m_PlayerBasicAttackTexture = nullptr;
	DeletePointer(m_EnemyMageAttackTexture);
	m_EnemyMageAttackTexture = nullptr;
	DeletePointer(m_CoinTexture);
	m_CoinTexture = nullptr;
}
