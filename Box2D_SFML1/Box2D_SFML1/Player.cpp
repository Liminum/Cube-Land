#include "Player.h"

Player::Player(sf::RenderWindow* _renderWindow, b2World& _world, AudioManager* _audiomanager, TextureMaster* _texturemaster)
{
	m_RenderWindow = _renderWindow;
	m_World = &_world;
	m_AudioManager = _audiomanager;
	m_TextureMaster = _texturemaster;
}

Player::~Player()
{
	CleanupCubemon();
	DestoryShape();
	DestroyBody();
	DeletePointer(m_ParticleSystem);
	m_ParticleSystem = nullptr;
	m_AudioManager = nullptr;
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_TextureMaster = nullptr; 
}

void Player::Start()
{
	CreateShape();
	LoadSpriteTexture(LoadTexture(&m_SpriteSheet, "Player/Player_SpriteSheett.png", false), m_Shape, true, false);
	m_Shape->setScale(10, 10);

	CreateBody(0, -100, b2_dynamicBody);

	AddCubemon(new CThallic(m_RenderWindow, m_World, sf::Vector2f(0, -400)));
}

void Player::Update(sf::Vector2f _mousepos)
{
	m_MousePos = _mousepos;

	Movement();

	SetShapeToB2Body();

	for (b2Contact* contact = m_World->GetContactList(); contact; contact = contact->GetNext())
	{
		b2Fixture* a = contact->GetFixtureA();
		b2Fixture* b = contact->GetFixtureB();
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		b2Vec2 vel1 = m_Body->GetLinearVelocityFromWorldPoint(m_Body->GetPosition());

		if ((vel1.y <= 1.f && vel1.y >= -1.f) && (a->GetBody() == m_Body || b->GetBody() == m_Body))
		{
			m_bCanJump = true;
		}
		else if(vel1.y < -2.0f || vel1.y > 2.0f)
		{
			m_bCanJump = false;
		}

		a = nullptr;
		b = nullptr;
	}

	if (m_ManaRegen.getElapsedTime().asSeconds() >= m_ManaRegenFrequency)
	{
		if (GetCurrentMana() < m_MaxMana)
		{
			SetCurrentMana(GetCurrentMana() + 1);
			m_ManaRegen.restart();
		}
	}

	UpdateCubemon();
}

void Player::Render(sf::Shader* _defaultshader)
{
	RenderCubemon();

	RenderSpritePointer(m_RenderWindow, m_Shape);
}

void Player::PollMovement(sf::Event& _event)
{
	/*if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Key::W && m_bCanJump)
	{
		m_Body->ApplyLinearImpulseToCenter(b2Vec2(0,-m_JumpForce), true);
	}*/
}

void Player::Movement()
{
	float x = 0.f;
	float y = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (m_Shape != nullptr)
		{
			m_Shape->setScale(-1, 1);
		}
		y = -1.f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (m_Shape != nullptr)
		{
			m_Shape->setScale(-1, 1);
		}
		x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (m_Shape != nullptr)
		{
			m_Shape->setScale(-1, 1);
		}
		y = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (m_Shape != nullptr)
		{
			m_Shape->setScale(1, 1);
		}
		x = 1.f;
	}
	m_Velocity = b2Vec2(x , y);

	m_Body->SetLinearVelocity((float)m_iMovementSpeed * m_Velocity);

	Animation(m_Velocity);
}

void Player::SetCurrentMana(float _mana)
{
	m_CurrentMana = _mana;
}

float Player::GetCurrentMana()
{
	return m_CurrentMana;
}

void Player::TakeDamage(float _damage)
{
	if (m_DamageTakenTimer.getElapsedTime().asSeconds() >= 0.3f)
	{
		for (int i = 0; i < _damage; i++)
		{
			if (m_CurrentHealth > 1)
			{
				m_CurrentHealth--;
			}
			else
			{
				m_MARKASDESTROY = true;
				break;
			}
		}
		std::cout << "Damage Taken : " << _damage << std::endl;
		std::cout << "Current Health : " << GetCurrentHealth() << std::endl;
		m_DamageTakenTimer.restart();
	}
}

void Player::Heal(float _amount)
{
	if (m_DamageTakenTimer.getElapsedTime().asSeconds() >= 0.3f)
	{
		for (int i = 0; i < _amount; i++)
		{
			if (m_CurrentHealth < m_MaxHealth && m_CurrentHealth > 0)
			{
				m_CurrentHealth++;
			}
			else
			{
				break;
			}
		}
		std::cout << "Player Healed!" << std::endl;
		std::cout << "Current Health : " << GetCurrentHealth() << std::endl;
		m_DamageTakenTimer.restart();
	}
}

void Player::SetCurrentHealth(float _health)
{
	m_CurrentHealth = _health;
}

float Player::GetCurrentHealth()
{
	return m_CurrentHealth;
}

void Player::AddCubemon(ICubemon* _cubeMon)
{
	m_CubemonVector.push_back(_cubeMon);
	_cubeMon = nullptr;
}

void Player::UpdateCubemon()
{
	for (auto& cubemon : m_CubemonVector)
	{
		cubemon->Update();
	}
}

void Player::RenderCubemon()
{
	for (auto& cubemon : m_CubemonVector)
	{
		cubemon->Render();
	}
}

void Player::Animation(b2Vec2 _movementVector)
{
	bool _ignoreScale = false;
	if (_movementVector.x > 0.1f)
	{
		if (m_Shape->getTextureRect().left != 0 && m_Shape->getTextureRect().left != 14)
		{
			m_Shape->setTextureRect(sf::IntRect(0, 0, 14, 16));
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left != 14)
		{
			m_Shape->setTextureRect(sf::IntRect(m_Shape->getTextureRect().left + 14, 0, 14, 16));
			m_AnimationClock.restart();
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left == 14)
		{
			m_Shape->setTextureRect(sf::IntRect(0, 0, 14, 16));
			m_AnimationClock.restart();
		}
	}
	else if (_movementVector.x < -0.1f)
	{
		_ignoreScale = true;
		m_Shape->setScale(-m_SheetScale, m_SheetScale);
		if (m_Shape->getTextureRect().left != 0 && m_Shape->getTextureRect().left != 14)
		{
			m_Shape->setTextureRect(sf::IntRect(0, 0, 14, 16));
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left != 14)
		{
			m_Shape->setTextureRect(sf::IntRect(m_Shape->getTextureRect().left + 14, 0, 14, 16));
			m_AnimationClock.restart();
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left == 14)
		{
			m_Shape->setTextureRect(sf::IntRect(0, 0, 14, 16));
			m_AnimationClock.restart();
		}
	}
	else if (_movementVector.y < -0.1f)
	{
		if (m_Shape->getTextureRect().left != 28 && m_Shape->getTextureRect().left != 42)
		{
			m_Shape->setTextureRect(sf::IntRect(28, 0, 14, 16));
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left != 42)
		{
			m_Shape->setTextureRect(sf::IntRect(m_Shape->getTextureRect().left + 14, 0, 14, 16));
			m_AnimationClock.restart();
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left == 42)
		{
			m_Shape->setTextureRect(sf::IntRect(28, 0, 14, 16));
			m_AnimationClock.restart();
		}
	}
	else if (_movementVector.y > 0.1f)
	{
		if (m_Shape->getTextureRect().left != 56 && m_Shape->getTextureRect().left != 70)
		{
			m_Shape->setTextureRect(sf::IntRect(56, 0, 14, 16));
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left != 70)
		{
			m_Shape->setTextureRect(sf::IntRect(m_Shape->getTextureRect().left + 14, 0, 14, 16));
			m_AnimationClock.restart();
		}
		else if (m_AnimationClock.getElapsedTime().asSeconds() > 0.5f && m_Shape->getTextureRect().left == 70)
		{
			m_Shape->setTextureRect(sf::IntRect(56, 0, 14, 16));
			m_AnimationClock.restart();
		}
	}
	else
	{
		m_Shape->setTextureRect(sf::IntRect(84, 0, 14, 16));
	}

	if (!_ignoreScale)
	{
		m_Shape->setOrigin(7, 8);
		m_Shape->setScale(m_SheetScale, m_SheetScale);
	}
}

void Player::CleanupCubemon()
{
	for (auto& pointer : m_CubemonVector)
	{
		DeletePointer(pointer);
		pointer = nullptr;
	}
	m_CubemonVector.erase(std::remove(m_CubemonVector.begin(), m_CubemonVector.end(), nullptr), m_CubemonVector.end());

}
