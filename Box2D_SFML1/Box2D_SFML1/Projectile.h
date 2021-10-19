#pragma once
#ifndef _PROJECTILE_H__
#define _PROJECTILE_H__

#include "TextureMaster.h"

class Projectile : public MonoBehavior
{
public:
	enum class PROJECTILETYPE
	{
		DEFAULT = 0,
		PLAYERBASICATTACK,
		ENEMYMAGEATTACK,
		COIN,

	};

	Projectile(Projectile::PROJECTILETYPE _type, sf::Vector2f _position, b2World &_world, sf::Vector2f _mousepos, TextureMaster* _texturemaster);
	virtual ~Projectile();

	virtual void Start();
	virtual void Update();
	virtual void Render();

	void CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _bullet = true ,bool _sensor = false);
	void DestroyBody();
	b2Body* GetBody();
	bool m_MARKASDESTROY = false;
	sf::Sprite m_Shape;
	PROJECTILETYPE m_Type;
	float m_ManaCost = 0;

protected:
	b2World* m_World = nullptr;
	
	TextureMaster* m_TextureMaster = nullptr;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body = nullptr;
	sf::Vector2f m_MousePos;
};

#endif