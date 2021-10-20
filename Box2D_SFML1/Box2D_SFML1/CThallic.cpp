#include "CThallic.h"

CThallic::CThallic(sf::RenderWindow* _renderWindow, b2World* _world, sf::Vector2f _pos)
{
	m_RenderWindow = _renderWindow;
	m_World = _world;

	m_SpriteTexture = new sf::Texture();

	CreateBody(_pos.x, _pos.y, b2_dynamicBody);

	Start();
}

CThallic::~CThallic()
{
	DestoryShape();
	DestroyBody();

	DeletePointer(m_SpriteTexture);
	m_SpriteTexture = nullptr;
	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_AudioManager = nullptr;
	m_ParticleSystem = nullptr;
	m_Shape = nullptr;
	m_Body = nullptr;
	m_World = nullptr;
}

void CThallic::Start()
{
	CreateShape();
	LoadSpriteTexture(LoadTexture(m_SpriteTexture, "Cubemon/Thallic.png", false), m_Shape);
}

void CThallic::Update()
{
	SetShapeToB2Body();
	Render();
}

void CThallic::Render()
{
	RenderSpritePointer(m_RenderWindow, m_Shape);
}

void CThallic::Movement()
{
}

void CThallic::Attack()
{
}
