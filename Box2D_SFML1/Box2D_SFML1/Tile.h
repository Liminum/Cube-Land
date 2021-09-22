#pragma once
#ifndef _TILE_H__
#define _TILE_H__
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

class Tile
	
{
public:
	Tile();
	Tile(sf::RenderWindow* _renderWindow, b2World& _world, sf::Texture* _texture, const float& _scale, sf::Vector2f _position, sf::Vector2f _size);
	virtual ~Tile();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void CreateBody(float _posX, float _posY, b2BodyType _type, bool _collision, bool _sensor = false);
	void DestroyBody();
	virtual void CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _sensor = false );

	sf::Sprite GetShape();

protected:
	
	bool m_bHasCollision = false;
	sf::RenderWindow* m_RenderWindow;
	
	sf::Texture* m_Texture;
	sf::Sprite m_Shape;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;
	b2World* m_World;

	float m_Scale;
};
#endif