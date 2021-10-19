#pragma once
#ifndef _ITEM_H__
#define _ITEM_H__

#include "MonoBehavior.h"

class Item : public MonoBehavior
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
	virtual void Render(sf::Shader* _defaultshader = NULL);
	
	b2Body* GetBody();
	void CreateBody(float _posX, float _posY, b2Vec2 _position,b2BodyType _type, bool _sensor);
	void DestroyBody();

	void SetPosition(float _x, float _y);
	sf::Vector2f GetPosition();
	sf::Sprite& GetShape();
	int m_PositionInInventory = 0;
	sf::Texture* m_Texture;
	bool m_bIsItemSelected = false;
	bool m_bItemIsMovingInInventory = false;

protected:
	b2World* m_World = nullptr;
	sf::Sprite m_Shape;
	sf::RenderWindow* m_RenderWindow = nullptr;
	b2Body* m_Body = nullptr;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
};
#endif