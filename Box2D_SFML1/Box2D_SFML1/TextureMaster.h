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

	sf::Texture* m_CIITexture;
	sf::Texture* m_ItemSlot;

private:


};

#endif