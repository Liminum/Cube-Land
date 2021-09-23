#pragma once
#ifndef _ITEM_H__
#define _ITEM_H__
#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>
#include<iostream>
class Item
{

public:

	enum ITEMTYPE
	{
		DEFAULT,
		LUMBERPILE,
		STONEPILE,
		STAFF,
	};

	ITEMTYPE m_Type = ITEMTYPE::DEFAULT;

	Item();

	Item(sf::Texture* _texture, ITEMTYPE _type);

	virtual ~Item();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	
	b2Body* GetBody();
	void CreateBody(float _posX, float _posY, b2Vec2(_position),b2BodyType _type, bool _sensor);
	void DestroyBody();

	void SetPosition(float _x, float _y);
	sf::Vector2f GetPosition();
	sf::Sprite& GetShape();
	int m_PositionInInventory = 0;
	sf::Texture* m_Texture;
	bool m_bIsItemSelected = false;
	bool m_bItemIsMovingInInventory = false;

protected:

	
	float m_Scale = 50;
	b2World* m_World;
	sf::Sprite m_Shape;
	sf::RenderWindow* m_RenderWindow;
	b2Body* m_Body;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
};
#endif