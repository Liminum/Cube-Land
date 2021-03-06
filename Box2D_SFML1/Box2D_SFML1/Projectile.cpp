#include "Projectile.h"

Projectile::Projectile(Projectile::PROJECTILETYPE _type, sf::Vector2f _position, b2World &_world, sf::Vector2f _mousepos, TextureMaster* _texturemaster, const float _scale)
{

	m_World = &_world;
	m_TextureMaster = _texturemaster;
	m_Scale = _scale;
	m_MousePos = _mousepos;

	m_Body = nullptr;
	
	switch (_type)
	{
	case Projectile::PROJECTILETYPE::DEFAULT:
		m_Shape.setTexture(*m_TextureMaster->m_PlayerBasicAttackTexture, true);
		CreateBody(10, 10, 0, 0, b2_dynamicBody, true, true);
		m_Type = Projectile::PROJECTILETYPE::DEFAULT;
		break;
	case Projectile::PROJECTILETYPE::PLAYERBASICATTACK:
		m_Shape.setTexture(*m_TextureMaster->m_PlayerBasicAttackTexture, true);
		CreateBody(50, 50, _position.x, _position.y, b2_dynamicBody, true, true);
		m_Type = Projectile::PROJECTILETYPE::PLAYERBASICATTACK;
		m_ManaCost = 4.f;
		break;
	case Projectile::PROJECTILETYPE::ENEMYMAGEATTACK:
		m_Shape.setTexture(*m_TextureMaster->m_EnemyMageAttackTexture, true);
		CreateBody(5, 5, _position.x, _position.y, b2_dynamicBody, true, true);
		m_Type = Projectile::PROJECTILETYPE::ENEMYMAGEATTACK;
		break;

	case Projectile::PROJECTILETYPE::COIN:
		m_Shape.setTexture(*m_TextureMaster->m_CoinTexture, true);
		CreateBody(10, 10, _position.x, _position.y, b2_dynamicBody, false, true);
		m_Type = Projectile::PROJECTILETYPE::COIN;
		break;
	default:
		m_Shape.setTexture(*m_TextureMaster->m_PlayerBasicAttackTexture, true);
		CreateBody(5, 5, 0, 0, b2_dynamicBody, true, true);
		m_Type = Projectile::PROJECTILETYPE::DEFAULT;
		break;
	}

	float d = _mousepos.x - m_Shape.getPosition().x;
	float dy = _mousepos.y - m_Shape.getPosition().y;

	m_Body->SetLinearVelocity(b2Vec2(d, dy));
}

Projectile::~Projectile()
{
	DestroyBody();

	m_TextureMaster = nullptr;
	m_World = nullptr;
}

void Projectile::Start()
{
}

void Projectile::Update()
{
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);

	b2Contact* contact;
	for (contact = m_World->GetContactList(); contact; contact = contact->GetNext())
	{
		b2Fixture* a = contact->GetFixtureA();
		b2Fixture* b = contact->GetFixtureB();

		if (a->GetBody() == m_Body || b->GetBody() == m_Body)
		{
			m_MARKASDESTROY = true;
		}

		a = nullptr;
		b = nullptr;
	}
	contact = nullptr;



}

void Projectile::Render()
{
}

void Projectile::CreateBody(float _sizeX, float _sizeY, float _posX, float _posY, b2BodyType _type, bool _bullet, bool _sensor)
{
	//ground physics
	m_BodyDef.type = _type;
	m_BodyDef.position = b2Vec2(_posX / m_Scale, (_posY / m_Scale));
	m_BodyDef.allowSleep = false;
	m_BodyDef.gravityScale = 0;
	
	if (_bullet)
	{
		m_BodyDef.bullet = true;
	}
	m_Body = m_World->CreateBody(&m_BodyDef);
	m_b2pShape.SetAsBox((_sizeX / 2) / m_Scale, (_sizeY / 2) / m_Scale);

	if (_sensor)
	{
		m_FixtureDef.isSensor = true;
	}

	m_FixtureDef.density = 100.0f;
	m_FixtureDef.shape = &m_b2pShape;
	m_FixtureDef.filter.categoryBits = 0x0002;
	m_FixtureDef.filter.maskBits = 0x0004;
	m_Body->CreateFixture(&m_FixtureDef);

	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Body->SetTransform(m_Body->GetPosition(), atan2(m_MousePos.y - m_Shape.getPosition().y, m_MousePos.x - m_Shape.getPosition().x));
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void Projectile::DestroyBody()
{
	if (m_World != nullptr && m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}

b2Body* Projectile::GetBody()
{
	return m_Body;
}
