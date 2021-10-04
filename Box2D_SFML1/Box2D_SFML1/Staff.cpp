#include "Staff.h"

Staff::Staff()
{
	m_Scale = 50.0f;
	m_Type = ITEMTYPE::STAFF;
	m_Texture = new sf::Texture();
	m_Texture->loadFromFile("Resources/Sprites/Staff.png");
	//m_StaffSprite.setTexture(*m_Texture, true);
	//m_StaffSprite.setScale(0.3f, 0.3f);
	//m_StaffSprite.setOrigin(m_StaffSprite.getGlobalBounds().width / 2, m_StaffSprite.getGlobalBounds().height / 2);

	m_Shape.setTexture(*m_Texture, true);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setScale(0.4f, 0.4f);
}

Staff::Staff(sf::RenderWindow* _renderwindow, const float& _scale, float _posX, float _posY)
{
	m_RenderWindow = _renderwindow;
	m_Scale = _scale;
	m_Type = ITEMTYPE::STAFF;
	m_Texture = new sf::Texture();
	m_Texture->loadFromFile("Resources/Sprites/Staff.png");
	m_StaffSprite.setTexture(*m_Texture, true);
	m_StaffSprite.setOrigin(m_StaffSprite.getGlobalBounds().width / 2, m_StaffSprite.getGlobalBounds().height / 2);
	m_StaffSprite.setScale(0.3f, 0.3f);
	m_StaffSprite.setPosition(-1000000, -1000000);
}

Staff::~Staff()
{
	delete m_Texture;
}

void Staff::Start()
{

}

void Staff::Update()
{
	Item::Update();
}

void Staff::Render(sf::Shader* _defaultshader)
{
	m_RenderWindow->draw(m_StaffSprite, _defaultshader);
	_defaultshader = nullptr;
}

void Staff::FlipSprite(sf::Vector2f _playerpos, sf::Sprite& _playersprite)
{
	// Player left
	if (_playersprite.getScale().x < 0)
	{
		m_StaffSprite.setScale(-1, 1);
		m_StaffSprite.setPosition(_playerpos.x - 60, _playerpos.y + 15);
	}
	// Player right
	else
	{
		m_StaffSprite.setScale(1, 1);
		m_StaffSprite.setPosition(_playerpos.x + 60, _playerpos.y + 15);
	}
}
