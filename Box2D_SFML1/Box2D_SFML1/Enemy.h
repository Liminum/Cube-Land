#pragma once
#ifndef _ENEMY_H__
#define _ENEMY_H__
#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>
#include<iostream>
#include <list> 
#include"TextureMaster.h"

class Enemy
{

public:

	enum class ENEMYTYPE
	{
		DEFAULT = 0,
		SLIME,

	};
	
	
	Enemy();

	virtual ~Enemy();

	virtual void Start();
	virtual void Update();
	virtual void Render(sf::Shader* _defaultshader = NULL);
	virtual void Movement();
	virtual void Attack();
	virtual void CreateBody(float _posX,float _posY,b2BodyType _type,bool _sensor = false);
	void DestroyBody();
	void SetHealth(float _health);
	float GetHealth();
	virtual void SetMaxHealth(float _health);

	ENEMYTYPE m_Type = ENEMYTYPE::DEFAULT;
	bool m_MARKASDESTROY = false;


protected:


	sf::RenderWindow* m_RenderWindow;
	TextureMaster* m_TextureMaster;
	b2World* m_World;
	float m_Scale = 50.0f;
	sf::Sprite m_Shape;
	sf::Texture* m_Texture;

	float m_Health = 5.f;
	float m_MaxHealth = 5.f;
	float m_MovementSpeed = 35;

	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;

};

#endif