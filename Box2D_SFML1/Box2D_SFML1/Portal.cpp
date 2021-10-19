#include "Portal.h"

Portal::Portal(sf::RenderWindow* _renderwindow, b2World& _world, float _posX, float _posY)
{
	m_RenderWindow = _renderwindow;
	m_World = &_world;

	Start(_posX, _posY);
}

Portal::~Portal()
{
	m_RenderWindow = nullptr;
}

void Portal::Start(float _posX, float _posY)
{
	CreateBody(_posX, _posY, b2_staticBody);
	m_Texture = new sf::Texture;
	if (m_Texture->loadFromFile("Resources/Images/PortalClosed.png"))
	{
		std::cout << "Portal Texture Loaded" << std::endl;
	}
	m_Shape.setTexture(*m_Texture, true);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(_posX, _posY);
}

void Portal::Update()
{
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
}

void Portal::Render(sf::Shader* _defaultshader)
{
	m_RenderWindow->draw(m_Shape, _defaultshader);
	_defaultshader = nullptr;
}

void Portal::CreateBody(float _posX, float _posY, b2BodyType _type, bool _collision, bool _sensor)
{
	//falling object physics
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, _posY / m_Scale);
	m_Body = m_World->CreateBody(&m_BodyDef);
	m_FixtureDef.density = 1.0f;
	m_b2pShape.SetAsBox((180 / 2) / m_Scale, (320 / 2) / m_Scale);
	m_FixtureDef.shape = &m_b2pShape;
	if (_collision)
	{
		m_FixtureDef.filter.categoryBits = 0x0002;
		m_FixtureDef.filter.maskBits = 0x0004;
	}
	else
	{
		m_FixtureDef.filter.categoryBits = 0x0004;
	}
	m_Body->CreateFixture(&m_FixtureDef);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}
