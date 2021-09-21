#pragma once
#ifndef _PROJECTILE_H__
#define _PROJECTILE_H__
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Projectile
{

public:

	enum class PROJECTILETYPE
	{
		DEFAULT = 0,
		PLAYERBASICATTACK,
		ENEMYMAGEATTACK,

	};


	Projectile(Projectile::PROJECTILETYPE _type, sf::Vector2f _position, b2World &_world, sf::Vector2f _mousepos);

	~Projectile();


	void Start();
	void Update();
	void Render();
	void CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _bullet = true ,bool _sensor = false);
	void DestroyBody();
	b2Body* GetBody();
	bool m_MARKASDESTROY = false;
	sf::Sprite m_Shape;
	PROJECTILETYPE m_Type;
	float m_ManaCost = 0;


protected:

	b2World* m_World;
	float m_Scale = 50.0f;
	sf::Texture* m_Texture;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;
};

#endif