#pragma once
#ifndef _TEXTUREMASTER_H__
#define _TEXTUREMASTER_H__

#include "MonoBehavior.h"

class TextureMaster : public MonoBehavior
{
public:
	TextureMaster();
	virtual ~TextureMaster();

	// Item Textures
	sf::Texture* m_LumberPile = nullptr;
	sf::Texture* m_StonePile = nullptr;
	sf::Texture* m_BackgroundTexture = nullptr;
	sf::Texture* m_GrassTexture = nullptr;
	
	// Projectile Textures
	sf::Texture* m_PlayerBasicAttackTexture = nullptr;
	sf::Texture* m_EnemyMageAttackTexture = nullptr;
	sf::Texture* m_CoinTexture = nullptr;

	sf::Texture* m_MousePosTex = nullptr;
	sf::Texture* m_CIITexture = nullptr;
	sf::Texture* m_ItemSlot = nullptr;
	sf::Texture* m_ItemSelectedTex = nullptr;
};

#endif