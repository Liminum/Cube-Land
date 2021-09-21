#include "StonePile.h"

StonePile::StonePile()
{
	m_Scale = 50.0f;
	m_Body = nullptr;
	Item::m_Type = ITEMTYPE::STONEPILE;
	m_Texture = new sf::Texture;
	m_Texture->loadFromFile("Resources/Sprites/StonePile.png");
	m_Shape.setTexture(*m_Texture, true);
}

StonePile::StonePile(sf::RenderWindow* _renderwindow, b2World& _world, float _posX, float _posY)
{
	m_RenderWindow = _renderwindow;
	m_World = &_world;
	m_Type = ITEMTYPE::STONEPILE;
	m_Texture = new sf::Texture();
	m_Texture->loadFromFile("Resources/Sprites/StonePile.png");
	m_Shape.setTexture(*m_Texture, true);
	CreateBody(_posX, _posY, b2Vec2(100, 60), b2_dynamicBody, false);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

StonePile::~StonePile()
{
	DestroyBody();
	delete m_Texture;
}

void StonePile::Start()
{
}

void StonePile::Update()
{
	if (!m_Body->IsAwake() && m_FixtureDef.isSensor == false)
	{
		DestroyBody();
		CreateBody(m_Shape.getPosition().x, m_Shape.getPosition().y, b2Vec2(100, 60), b2_staticBody, true);
	}

	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void StonePile::SetStonePileAmount(int _stoneamount)
{
	StoneAmount = _stoneamount;
}

int StonePile::GetStonePileAmount()
{
	return StoneAmount;
}
