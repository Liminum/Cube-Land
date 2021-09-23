#pragma once
#ifndef _TEXTUREMASTER_H__
#define _TEXTUREMASTER_H__
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureMaster
{

public:

	TextureMaster();

	~TextureMaster();

	sf::Texture* m_LumberPile;
	sf::Texture* m_StonePile;
	sf::Texture* m_BackgroundTexture;
	sf::Texture* m_GrassTexture;
	
	// Projectile Textures
	sf::Texture* m_PlayerBasicAttackTexture;
	sf::Texture* m_EnemyMageAttackTexture;
	sf::Texture* m_CoinTexture;

	sf::Texture* m_MousePosTex;
	sf::Texture* m_CIITexture;
	sf::Texture* m_ItemSlot;
	sf::Texture* m_ItemSelectedTex;

private:


};

#endif