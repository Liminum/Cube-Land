#include "TextureMaster.h"

TextureMaster::TextureMaster()
{
	// Tile Textures
	m_BackgroundTexture = new sf::Texture();
	m_BackgroundTexture->setSmooth(true);
	m_BackgroundTexture->setRepeated(true);
	m_GrassTexture = new sf::Texture();

	if (m_BackgroundTexture->loadFromFile("Resources/Sprites/gameBackground.png"))
	{
		std::cout << "Background Texture Loaded!" << std::endl;
	}

	if (m_GrassTexture->loadFromFile("Resources/Sprites/GrassBlock.png"))
	{
		std::cout << "Grass Texture Loaded!" << std::endl;
	}
	m_GrassTexture->setRepeated(true);


	// Item Textures
	m_LumberPile = new sf::Texture();
	m_StonePile = new sf::Texture();

	if (m_LumberPile->loadFromFile("Resources/Sprites/LumberPile.png"))
	{
		std::cout << "LumberPile Texture Loaded!" << std::endl;
	}
	if (m_StonePile->loadFromFile("Resources/Sprites/StonePile.png"))
	{
		std::cout << "StonePile Texture Loaded!" << std::endl;
	}


	//Projectile Textures
	m_PlayerBasicAttackTexture = new sf::Texture();
	m_EnemyMageAttackTexture = new sf::Texture();
	m_CoinTexture = new sf::Texture();

	if (m_PlayerBasicAttackTexture->loadFromFile("Resources/Sprites/PlayerBasicAttack.png"))
	{
		std::cout << "Player Basic Attack Texture Loaded!" << std::endl;
	}
	if (m_EnemyMageAttackTexture->loadFromFile("Resources/Sprites/EnemyMageAttack.png"))
	{
		std::cout << "Enemy Make Attack Texture Loaded!" << std::endl;
	}
	if (m_CoinTexture->loadFromFile("Resources/Sprites/Coin.png"))
	{
		std::cout << "Coin Texture Loaded!" << std::endl;
	}


	// GUI Textures
	m_CIITexture = new sf::Texture();
	m_ItemSlot = new sf::Texture();
	m_MousePosTex = new sf::Texture();
	m_ItemSelectedTex = new sf::Texture();

	//if (m_MousePosTex->loadFromFile("Resources/Sprites/ItemSelected.png"))
	//{
		//std::cout << "Item Selected Texture Loaded!" << std::endl;
	//}
	if (m_MousePosTex->loadFromFile("Resources/Sprites/PlayerBasicAttack.png"))
	{
		std::cout << "Mouse Pointer Texture Loaded!" << std::endl;
	}
	if (m_CIITexture->loadFromFile("Resources/Sprites/CurrentlySelectedItem.png"))
	{
		std::cout << "Currently Selected Item Texture Loaded!" << std::endl;
	}
	if (m_ItemSlot->loadFromFile("Resources/Sprites/ItemSlot.png"))
	{
		std::cout << "Item Slot Texture Loaded!" << std::endl;
	}
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
	delete m_ItemSelectedTex;
	m_ItemSelectedTex = nullptr;
	delete m_CIITexture;
	m_CIITexture = nullptr;
	delete m_ItemSlot;
	m_ItemSlot = nullptr;
	delete m_MousePosTex;
	m_MousePosTex = nullptr;
	delete m_PlayerBasicAttackTexture;
	m_PlayerBasicAttackTexture = nullptr;
	delete m_EnemyMageAttackTexture;
	m_EnemyMageAttackTexture = nullptr;
	delete m_CoinTexture;
	m_CoinTexture = nullptr;

}
