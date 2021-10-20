#pragma once
#include "ICubemon.h"

class CThallic : public ICubemon
{
public:
	CThallic(sf::RenderWindow* _renderWindow, b2World* _world, sf::Vector2f _pos = sf::Vector2f(0, 0));
	virtual ~CThallic();

	virtual void Start();
	virtual void Update();
	virtual void Render();

protected:
	virtual void Movement();
	virtual void Attack();
};

