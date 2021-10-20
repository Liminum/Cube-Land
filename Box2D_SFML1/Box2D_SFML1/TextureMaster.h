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
};

#endif