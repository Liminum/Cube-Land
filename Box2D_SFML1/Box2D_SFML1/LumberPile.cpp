#include "LumberPile.h"

LumberPile::LumberPile()
{
	m_Scale = 50.0f;
	Item::m_Type = ITEMTYPE::LUMBERPILE;
	m_Texture = new sf::Texture;
	m_Texture->loadFromFile("Resources/Sprites/LumberPile.png");
	m_Shape.setTexture(*m_Texture, true);
}

LumberPile::LumberPile(sf::RenderWindow* _renderwindow, b2World& _world, float _posX, float _posY)
{
	m_RenderWindow = _renderwindow;
	m_World = &_world;
	m_Type = ITEMTYPE::LUMBERPILE;
	m_Texture = new sf::Texture();
	m_Texture->loadFromFile("Resources/Sprites/LumberPile.png");
	m_Shape.setTexture(*m_Texture, true);
	CreateBody(_posX, _posY, b2Vec2(100,60), b2_dynamicBody, false);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

LumberPile::~LumberPile()
{
	DestroyBody();
	delete m_Texture;

}

void LumberPile::Start()
{

}

void LumberPile::Update()
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

void LumberPile::SetLumberPileAmount(int _lumberamount)
{
	LumberAmount = _lumberamount;
}

int LumberPile::GetLumberPileAmount()
{
	return LumberAmount;
}




