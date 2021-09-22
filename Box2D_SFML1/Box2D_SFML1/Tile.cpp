#include "Tile.h"

Tile::Tile()
{
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_Body = nullptr;
	m_Texture = nullptr;
}

Tile::Tile(sf::RenderWindow* _renderWindow, b2World& _world, sf::Texture* _texture, const float& _scale, sf::Vector2f _position, sf::Vector2f _size)
{
	m_World = &_world;
	m_RenderWindow = _renderWindow;
	m_Scale = _scale;
	m_Texture = _texture;

	m_Shape.setTexture(*m_Texture, true);
	m_Shape.setTextureRect(sf::IntRect(0, 0, _size.x, _size.y));

	CreateBody(_size.x,_size.y,_position.x,_position.y,b2_staticBody);
}

Tile::~Tile()
{
	DestroyBody();
	m_RenderWindow = nullptr;
	m_Body = nullptr;
	m_World = nullptr;
	m_Texture = nullptr;
}

void Tile::Start()
{
}

void Tile::Update()
{	// Set SFML Shape Transform To Box 2D Body Transform
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void Tile::Render()
{
	m_RenderWindow->draw(m_Shape);
}

void Tile::CreateBody(float _posX, float _posY, b2BodyType _type, bool _collision, bool _sensor)
{
	m_bHasCollision = _collision;
	//falling object physics
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, _posY / m_Scale);
	m_Body = m_World->CreateBody(&m_BodyDef);
	m_FixtureDef.density = 1.0f;
	m_FixtureDef.shape = &m_b2pShape;
	m_FixtureDef.filter.categoryBits = 0x0002;
	m_FixtureDef.filter.maskBits = 0x0004;
	m_Body->CreateFixture(&m_FixtureDef);
}

void Tile::CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _sensor)
{
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, _posY / m_Scale);
	m_Body = m_World->CreateBody(&m_BodyDef);
	m_b2pShape.SetAsBox((_sizeX / 2) / m_Scale, (_sizeY / 2) / m_Scale);
	m_FixtureDef.density = 1.0f;
	m_FixtureDef.shape = &m_b2pShape;
	m_FixtureDef.filter.categoryBits = 0x0004;
	m_Body->CreateFixture(&m_FixtureDef);
}

sf::Sprite Tile::GetShape()
{
	return m_Shape;
}

void Tile::DestroyBody()
{
	if (m_World != nullptr && m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
	}
}


