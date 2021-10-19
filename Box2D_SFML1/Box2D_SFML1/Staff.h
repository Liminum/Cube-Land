#pragma once
#ifndef _STAFF_H__
#define _STAFF_H__

#include "Item.h"

class Staff : public Item
{
public:
	Staff();
	Staff(sf::RenderWindow* _renderwindow, float _posX, float _posY);

	virtual ~Staff();

	virtual void Update();
	virtual void Render(sf::Shader* _defaultshader = NULL);
	void FlipSprite(sf::Vector2f _playerpos, sf::Sprite& _playersprite);

	sf::Sprite m_StaffSprite;
};

#endif