#include "Item.h"

Item::Item()
{
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_Body = nullptr;
	m_Texture = nullptr;
}

Item::Item(sf::Texture* _texture, ITEMTYPE _type)
{
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_Body = nullptr;

	m_Texture = _texture;
	m_Type = _type;
	m_Shape.setTexture(*_texture,true);

	m_Shape.setOrigin((m_Shape.getGlobalBounds().width / 2), (m_Shape.getGlobalBounds().height / 2));
	m_Shape.setScale(0.4f, 0.4f);
}

Item::~Item()
{
	m_Body = nullptr;
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_Texture = nullptr;
}

void Item::Start()
{

}

void Item::Update()
{
	// Set SFML Shape Transform To Box 2D Body Transform
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	if (m_Body != nullptr)
	{
		m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, (m_Body->GetPosition().y * m_Scale));
		m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
	}
}

void Item::Render()
{
	m_RenderWindow->draw(m_Shape);
}

b2Body* Item::GetBody()
{
	return m_Body;
}

void Item::CreateBody(float _posX, float _posY, b2Vec2(_size), b2BodyType _type, bool _sensor)
{
	//ground physics
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, (_posY / m_Scale));
	m_BodyDef.allowSleep = true;


	m_Body = m_World->CreateBody(&m_BodyDef);
	m_b2pShape.SetAsBox((_size.x / 2) / m_Scale, (_size.y / 2) / m_Scale);

	if (_sensor)
	{
		m_FixtureDef.isSensor = true;
	}

	m_FixtureDef.density = 5.0f;
	m_FixtureDef.friction = 1.5f;
	m_FixtureDef.shape = &m_b2pShape;
	m_Body->CreateFixture(&m_FixtureDef);

	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void Item::DestroyBody()
{
	if (m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
	}
}

void Item::SetPosition(float _x, float _y)
{
	m_Shape.setPosition(_x, _y);
}

sf::Vector2f Item::GetPosition()
{
	return m_Shape.getPosition();
}

sf::Sprite& Item::GetShape()
{
	return m_Shape;
}
