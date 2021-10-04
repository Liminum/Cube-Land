#include "Enemy.h"

Enemy::Enemy()
{
	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_World = nullptr;
	m_Body = nullptr;
	m_Texture = nullptr;
}

Enemy::~Enemy()
{

	DestroyBody();

	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_World = nullptr;
	m_Body = nullptr;
	m_Texture = nullptr;



}

void Enemy::Start()
{
}

void Enemy::Update()
{
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);

}

void Enemy::Render(sf::Shader* _defaultshader)
{
	m_RenderWindow->draw(m_Shape, _defaultshader);
}

void Enemy::Movement()
{
}

void Enemy::Attack()
{
}

void Enemy::CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor)
{
	//ground physics
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, (_posY / m_Scale));
	m_BodyDef.allowSleep = true;


	m_Body = m_World->CreateBody(&m_BodyDef);
	m_b2pShape.SetAsBox((100 / 2) / m_Scale, (100 / 2) / m_Scale);

	if (_sensor)
	{
		m_FixtureDef.isSensor = true;
	}

	m_FixtureDef.density = 1.0f;
	m_FixtureDef.shape = &m_b2pShape;
	m_Body->CreateFixture(&m_FixtureDef);

	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void Enemy::DestroyBody()
{
	if (m_World != nullptr && m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}

void Enemy::SetHealth(float _health)
{
	m_Health = _health;
}

float Enemy::GetHealth()
{
	return m_Health;
}

void Enemy::SetMaxHealth(float _health)
{
	m_MaxHealth = _health;
}


