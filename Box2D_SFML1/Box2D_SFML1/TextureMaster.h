#pragma once
#ifndef _TEXTUREMASTER_H__
#define _TEXTUREMASTER_H__

#include "NumptyBehavior.h"

class TextureMaster : public NumptyBehavior
{
public:
	TextureMaster();
	virtual ~TextureMaster();

	sf::Texture* m_BackgroundTexture = nullptr;
	sf::Texture* m_GrassTexture = nullptr;
	sf::Texture* m_DirtBlock = nullptr;
	sf::Texture* m_DirtBlock_BG = nullptr;
	sf::Texture* m_Grass = nullptr;
};

#endif