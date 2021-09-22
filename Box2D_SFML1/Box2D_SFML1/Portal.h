#pragma once
#ifndef _PORTAL_H__
#define _PORTAL_H__
#include "Tile.h"
#include "AudioManager.h"

class Portal : public Tile
{

public:

	Portal(sf::RenderWindow* _renderWindow, b2World& _world, const float& _scale, float _posX, float _posY);

	virtual ~Portal();

	void Start(float _posX, float _posY);
	void Update();
	void Render();

	void CreateBody(float _posX, float _posY, b2BodyType _type, bool _collision = false, bool _sensor = false);

private:

	bool m_bIsPortalOpen = false;
};

#endif