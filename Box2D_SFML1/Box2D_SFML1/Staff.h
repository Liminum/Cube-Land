#pragma once
#ifndef _STAFF_H__
#define _STAFF_H__
#include "Item.h"
class Staff : public Item
{
public:

	Staff();
	Staff(sf::RenderWindow* _renderwindow, const float& _scale, float _posX, float _posY);

	~Staff();

	void Start();
	void Update();
	void Render(sf::Shader* _defaultshader = NULL);
	void FlipSprite(sf::Vector2f _playerpos, sf::Sprite& _playersprite);


	sf::Sprite m_StaffSprite;

private:




};

#endif