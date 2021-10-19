#pragma once

#include "MonoBehavior.h"
#include "TextureMaster.h"
#include "AudioManager.h"
#include "ParticleSystem.h"

class CEntity :	public MonoBehavior
{
public:
	bool m_MARKASDESTROY = false;

protected:
	void SetShapeToB2Body();

	void CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor = false);
	void DestroyBody();

	sf::RenderWindow* m_RenderWindow = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	AudioManager* m_AudioManager = nullptr;
	ParticleSystem* m_ParticleSystem = nullptr;

	sf::Sprite m_Shape;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body = nullptr;
	b2World* m_World = nullptr;
};

