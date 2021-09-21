#pragma once
#ifndef _TILE_H__
#define _TILE_H__
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
class Tile
	
{
public:
	Tile(sf::RenderWindow* _renderWindow, b2World& _world, const float& _scale, sf::Vector2f _position, sf::Vector2f _size);
	~Tile();

	void Start();
	void Update();
	void Render();
	void CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor = false);
	void DestroyBody();
	void CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _sensor = false );

	sf::RectangleShape GetShape();

private:
	sf::RenderWindow* m_RenderWindow;
	

	sf::RectangleShape m_Shape;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;
	b2World* m_World;

	float m_Scale = 50.0f;
};
#endif