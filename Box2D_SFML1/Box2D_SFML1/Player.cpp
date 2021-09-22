#include "Player.h"

Player::Player(sf::RenderWindow* _renderWindow, b2World& _world, const float& _scale, AudioManager* _audiomanager)
{
	m_RenderWindow = _renderWindow;
	m_Scale = _scale;
	m_World = &_world;
	m_AudioManager = _audiomanager;

	m_Projectile = nullptr;
	m_Staff = nullptr;

	m_ParticleSystem = new ParticleSystem(200, sf::seconds(.4f), sf::Color(126, 232, 228, 255));

	//falling object
	
	m_PlayerTexture.loadFromFile("Resources/Sprites/Player.png");
	m_Shape.setTexture(m_PlayerTexture, true);
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);

	CreateBody(0, -100, b2_dynamicBody);
}

Player::~Player()
{
	m_Projectiles.clear();
	DestroyBody();
	m_AudioManager = nullptr;
	m_RenderWindow = nullptr;
	m_World = nullptr;
	m_Projectile = nullptr;
	if (m_Staff != nullptr)
	{
		delete m_Staff;
	}
	m_Staff = nullptr;
	delete m_ParticleSystem;
	m_ParticleSystem = nullptr;
}

void Player::Start()
{
	// Resetting output txt doc
	std::ofstream out_file;
	out_file.open("Resources/Output/FirstEmptyInventorySlot.txt");

	if (out_file.is_open())
	{
		out_file.clear();
		out_file << 0 << std::endl;
		out_file.close();
	}
	else
	{
		std::cout << "OutPut File Not Open!" << std::endl;
	}

	for (int i = 0; i < 9; i++)
	{
		m_Inventory[i];
	}

	

	m_Staff = new Staff();
	AddItemToInventory(m_Staff, false);
	m_Staff = nullptr;
}

void Player::Update(sf::Vector2f _mousepos)
{
	m_MousePos = _mousepos;

	Movement();
	// Set SFML Shape Transform To Box 2D Body Transform
	m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);

	if (m_Staff != nullptr)
	{
		Attack(Projectile::PROJECTILETYPE::PLAYERBASICATTACK);
		m_Staff->Update();
		m_Staff->FlipSprite(m_Shape.getPosition(), m_Shape);
	}

	// Items
	for (std::map<int, Item>::iterator iit = m_Inventory.begin(); iit != m_Inventory.end(); iit++)
	{
		// Player Selects Bow
		if (iit->second.m_bIsItemSelected == true && iit->second.m_Type == Item::ITEMTYPE::STAFF)
		{
			std::cout << "New Bow Created!" << std::endl;
			m_Staff = new Staff(m_RenderWindow, m_Scale, m_Shape.getPosition().x, m_Shape.getPosition().y);
			iit->second.m_bIsItemSelected = false;
		}

		// Player Unselects Bow
		else if ((m_Staff != nullptr && m_CurrentItemIndex != iit->first && iit->second.m_Type == Item::ITEMTYPE::STAFF))
		{
			delete m_Staff;
			m_Staff = nullptr;
		}

	}

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

	for (Projectile& projectile : m_Projectiles)
	{
		projectile.Update();
	}

	std::list<Projectile>::iterator pit = m_Projectiles.begin();
	while (pit != m_Projectiles.end())
	{
		if (pit->m_MARKASDESTROY)
		{
			pit->m_MARKASDESTROY = false;
			pit = m_Projectiles.erase(pit);
			break;
		}
		pit++;
	}

	sf::Time elapsedtime = m_ParticleClock.getElapsedTime();
	m_ParticleSystem->Update(elapsedtime);

	if (m_ManaRegen.getElapsedTime().asSeconds() >= m_ManaRegenFrequency)
	{
		if (GetCurrentMana() < m_MaxMana)
		{
			SetCurrentMana(GetCurrentMana() + 1);
			m_ManaRegen.restart();
		}

	}
}

void Player::Render()
{
	m_RenderWindow->draw(m_Shape);
	
	for (Projectile& projectile : m_Projectiles)
	{
		m_RenderWindow->draw(projectile.m_Shape);
	}
	
	if (m_Staff != nullptr)
	{
		m_Staff->Render();
	}

	m_RenderWindow->draw(*m_ParticleSystem);
}

void Player::PollMovement(sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Key::W && m_bCanJump)
	{
		m_Body->ApplyLinearImpulseToCenter(b2Vec2(0,-m_JumpForce), true);
	}

	

}

void Player::Movement()
{
	float x = 0.f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Shape.setScale(-1, 1);
		x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Shape.setScale(1, 1);
		x = 1.f;
	}
	m_Velocity = b2Vec2(x, 0);
	m_Body->ApplyLinearImpulseToCenter(m_iMovementSpeed/2 * m_Velocity, true);
	b2Vec2 worldposition = { m_Shape.getPosition().x, m_Shape.getPosition().y };
	float Mag = sqrt((m_Body->GetLinearVelocityFromWorldPoint(worldposition).x * m_Body->GetLinearVelocityFromWorldPoint(worldposition).x));
	if(Mag > m_iMovementSpeed)
	{
		m_Body->ApplyLinearImpulseToCenter(-1 *(m_iMovementSpeed * m_Velocity), true);
	}
}

void Player::Attack(Projectile::PROJECTILETYPE _type)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_AttackTimer.getElapsedTime().asSeconds() >= 0.5f)
	{
		
		switch (_type)
		{
		case Projectile::PROJECTILETYPE::PLAYERBASICATTACK:
		{
			if (GetCurrentMana() >= 4.f)
			{
				m_Projectile = new Projectile(Projectile::PROJECTILETYPE::PLAYERBASICATTACK, sf::Vector2f(m_Shape.getPosition().x, m_Shape.getPosition().y - 50), *m_World, m_MousePos);
				SetCurrentMana(GetCurrentMana() - m_Projectile->m_ManaCost);
				m_Projectiles.push_back(*m_Projectile);
				m_Projectile = nullptr;
				m_AttackTimer.restart();
				m_ParticleClock.restart();
				m_AudioManager->FireBow();

				// if player is facing left then create the particle emitter on the left
				if (m_Shape.getScale().x < 0)
				{
					m_ParticleSystem->SetEmitter(sf::Vector2f(m_Shape.getPosition().x - 85, m_Shape.getPosition().y - 10));
				}
				// else the player is facing right so create the particle emitter on the right
				else
				{
					m_ParticleSystem->SetEmitter(sf::Vector2f(m_Shape.getPosition().x + 85, m_Shape.getPosition().y - 10));
				}
			}
			break;
		}

		
		
		
		
		default:
		{
			break;
		}
			
		}

	}
}

void Player::AddItemToInventory(Item* _item, bool _bCanStack)
{
	if (_bCanStack)
	{
		if (IsItemInInventory(_item))
		{

		}
		else
		{
			// Reading From File??
			//
			std::string line;
			std::ifstream myfile("Resources/Output/FirstEmptyInventorySlot.txt");
			myfile.is_open();
			int firstEmpty;
			myfile >> firstEmpty;

			m_RenderWindow->mapCoordsToPixel(_item->GetShape().getPosition());
			if (m_InventorySize < 9)
			{
				m_InventorySize++;
				// increase number of that type
				m_InventoryStackValues[firstEmpty]++;
				_item->m_PositionInInventory = firstEmpty;
				m_Inventory.insert_or_assign(firstEmpty, *_item);
			}
			else
			{
				std::cout << "Inventory Full! : " << m_InventorySize << std::endl;
			}

			myfile.close();
		}
	}
	else
	{
		// Reading From File??

		std::string line;
		std::ifstream myfile("Resources/Output/FirstEmptyInventorySlot.txt");
		myfile.is_open();
		int firstEmpty;
		myfile >> firstEmpty;

		m_RenderWindow->mapCoordsToPixel(_item->GetShape().getPosition());
		if (m_InventorySize < 9)
		{
			m_InventorySize++;
			// increase number of that type
			m_InventoryStackValues[firstEmpty]++;
			_item->m_PositionInInventory = firstEmpty;
			m_Inventory.insert_or_assign(firstEmpty, *_item);
		}
		else
		{
			std::cout << "Inventory Full! : " << m_InventorySize << std::endl;
		}
		myfile.close();

		
	}
	_item = nullptr;

}

void Player::AddItemToInventory(Item* _item, int _amount, bool _bCanStack)
{
	if (_bCanStack)
	{
		if (IsItemInInventory(_item, _amount))
		{
			
		}
		else
		{
			// Reading From File??
			//
			std::string line;
			std::ifstream myfile("Resources/Output/FirstEmptyInventorySlot.txt");
			myfile.is_open();
			int firstEmpty;
			myfile >> firstEmpty;

			m_RenderWindow->mapCoordsToPixel(_item->GetShape().getPosition());
			
			if (m_InventorySize < 9)
			{
				m_InventorySize++;
				// increase number of that type
				for (int i = 0; i < _amount; i++)
				{
					++m_InventoryStackValues[firstEmpty];
				}
				_item->m_PositionInInventory = firstEmpty;
				m_Inventory.insert_or_assign(firstEmpty, *_item);
			}
			else
			{
				std::cout << "Inventory Full! : " << m_InventorySize << std::endl;
			}
			myfile.close();
		}
	}
	else
	{
		// Reading From File??

		std::string line;
		std::ifstream myfile("Resources/Output/FirstEmptyInventorySlot.txt");
		myfile.is_open();
		int firstEmpty;
		myfile >> firstEmpty;

		m_RenderWindow->mapCoordsToPixel(_item->GetShape().getPosition());
		for (int i = 0; i < _amount; i++)
		{
			if (m_InventorySize < 9)
			{
				m_InventorySize++;
				// increase number of that type
				m_InventoryStackValues[firstEmpty + i]++;
				_item->m_PositionInInventory = firstEmpty + i;
				m_Inventory.insert_or_assign(firstEmpty + i, *_item);
			}
			else
			{
				std::cout << "Inventory Full! : " << m_InventorySize << std::endl;
			}

		}
		myfile.close();
	}
	_item = nullptr;
}

bool Player::IsItemInInventory(Item* _item)
{
	std::map<int, Item>::iterator it;
	for (it = m_Inventory.begin(); it != m_Inventory.end(); it++)
	{
		if (it->second.m_Type == _item->m_Type)
		{
			// increase number of that type
			m_InventoryStackValues[it->first]++;
			delete _item;
			_item = nullptr;
			return true;

		}
	}
	
	return false;

}

bool Player::IsItemInInventory(Item* _item, int _amount)
{
	std::map<int, Item>::iterator it;
	for (it = m_Inventory.begin(); it != m_Inventory.end(); it++)
	{
		if (it->second.m_Type == _item->m_Type)
		{
			// increase number of that type
			for (int i = 0; i < _amount; i++)
			{
				++m_InventoryStackValues[it->first];
			}
			delete _item;
			_item = nullptr;
			return true;

		}
	}

	return false;
}

void Player::RemoveItemFromInventory(int _pos)
{
	std::map<int, Item>::iterator it = m_Inventory.begin();

	while (it != m_Inventory.end())
	{
		if (it->first == _pos)
		{
			it->second.m_PositionInInventory = -1;
			it = m_Inventory.erase(it);

			return;
		}
		it++;
	}
}

void Player::CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor)
{

	//falling object physics
	m_BodyDef.position = b2Vec2(_posX / m_Scale, _posY / m_Scale);
	m_BodyDef.type = _type;
	m_BodyDef.fixedRotation = 1;
	m_BodyDef.linearDamping = 0.4f;
	m_BodyDef.gravityScale = 10;
	m_Body = m_World->CreateBody(&m_BodyDef);
	m_b2pShape.SetAsBox((100.f / 2) / m_Scale, (100.f / 2) / m_Scale);
	if (_sensor)
	{
		m_FixtureDef.isSensor = true;
	}
	m_FixtureDef.density = 2.0f;
	m_FixtureDef.friction = 1.0f;
	m_FixtureDef.restitution = 0.2f;
	m_FixtureDef.shape = &m_b2pShape;
	m_FixtureDef.filter.categoryBits = 0x0002;
	m_Body->CreateFixture(&m_FixtureDef);
}

void Player::DestroyBody()
{
	if (m_World != nullptr && m_Body != nullptr)
	{
		m_World->DestroyBody(m_Body);
		m_Body = nullptr;
	}
}

b2Body* Player::GetBody()
{
	return m_Body;
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
		SetCurrentHealth(GetCurrentHealth() - _damage);
		std::cout << "Damage Taken : " << _damage << std::endl;
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

sf::Sprite Player::GetShape()
{
	return m_Shape;
}