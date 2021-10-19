#include "CEntity.h"

void CEntity::SetShapeToB2Body()
{
	// Set SFML Shape Transform To Box 2D Body Transform
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void CEntity::CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor)
{
	// Body
	m_BodyDef.position = b2Vec2(_posX / m_Scale, _posY / m_Scale);
	m_BodyDef.type = _type;
	m_BodyDef.fixedRotation = 1;
	m_BodyDef.linearDamping = 0.4f;
	m_BodyDef.gravityScale = 10;
	m_Body = m_World->CreateBody(&m_BodyDef);

	// Shape
	m_b2pShape.SetAsBox((100.f / 2) / m_Scale, (100.f / 2) / m_Scale);

	// Fixture
	if (_sensor)
	{
		m_FixtureDef.isSensor = true;
	}
	m_FixtureDef.density = 2.0f;
	m_FixtureDef.friction = 1.0f;
	m_FixtureDef.restitution = 0.2f;
	m_FixtureDef.shape = &m_b2pShape;
	m_FixtureDef.filter.categoryBits = 0x0004;
	m_FixtureDef.filter.groupIndex = -1;
	m_Body->CreateFixture(&m_FixtureDef);
}

void CEntity::DestroyBody()
{
	if (m_World != nullptr && m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}
