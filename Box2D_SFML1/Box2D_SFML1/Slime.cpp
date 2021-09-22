#include "Slime.h"

Slime::Slime(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _textureMaster, AudioManager& _audiomanager, const float& _scale, float _posX, float _posY)
{
    m_RenderWindow = _renderWindow;
    m_Texture = new sf::Texture();
    m_DamageTimer = nullptr;
    m_AudioManager = &_audiomanager;

    srand((unsigned)time(NULL));

    // Random Slime Type
    if (rand() % 2 == 0)
    {
        m_SlimeType = SLIMETYPE::GREEN;
    }
    else if (rand() % 2 == 1)
    {
        m_SlimeType = SLIMETYPE::BOSS;
    }
    else
    {
        m_SlimeType = SLIMETYPE::GREEN;
    }

    // Set Appropriate Texture
    switch (m_SlimeType)
    {
    case Slime::SLIMETYPE::GREEN:
    {
        m_Texture->loadFromFile("Resources/Sprites/Slime.png");
        break;
    }
    case Slime::SLIMETYPE::BOSS:
    {
        m_Texture->loadFromFile("Resources/Sprites/BossSlime.png");
        m_bIsBoss = true;
        break;
    }
    default:
    {
        //m_Texture->loadFromFile("Resources/Sprites/Slime.png");
        break;
    }
    }

    m_World = &_world;
    m_Shape.setTexture(*m_Texture, true);
    m_Player = nullptr;

    CreateBody(_posX, _posY, b2_dynamicBody);
}

Slime::~Slime()
{
    LosePlayer();
    
    if (m_DamageTimer != nullptr)
    {
        delete m_DamageTimer;
    }
    m_DamageTimer = nullptr;
    delete  m_Texture;
    m_AudioManager = nullptr;
    
}

void Slime::Start()
{
    m_DamageTimer = new sf::Clock();
}

void Slime::Update()
{
    Movement();
    Attack();
    
    m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
    m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);



    b2Contact* contact;
    for (contact = m_World->GetContactList(); contact; contact = contact->GetNext())
    {
        b2Fixture* a = contact->GetFixtureA();
        b2Fixture* b = contact->GetFixtureB();
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);

        b2Vec2 vel1 = m_Body->GetLinearVelocityFromWorldPoint(m_Body->GetPosition());
        b2Vec2 vel2 = b->GetBody()->GetLinearVelocityFromWorldPoint(worldManifold.points[0]);
        b2Vec2 impactVelocity = vel1 - vel2;
        b2Vec2 worldposition = { m_Shape.getPosition().x, m_Shape.getPosition().y };

        if (a->GetBody() == m_Body || b->GetBody() == m_Body)
        {
            if (a->GetBody()->GetFixtureList()->IsSensor() || b->GetBody()->GetFixtureList()->IsSensor())
            {
                TakeDamage(2.5f);
            }
        }



        a = nullptr;
        b = nullptr;
    }
    contact = nullptr;
}

void Slime::Render()
{
    m_RenderWindow->draw(m_Shape);
}

void Slime::Movement()
{
    b2Vec2 worldposition = { m_Shape.getPosition().x, m_Shape.getPosition().y };
    b2Vec2 velocity = m_Body->GetLinearVelocityFromWorldPoint(worldposition);

    float DistanceToPlayer;
    float DirectionToPlayer;
    if (bHasPlayer())
    {
        DistanceToPlayer = sqrt(((m_Player->GetShape().getPosition().x - m_Shape.getPosition().x) * (m_Player->GetShape().getPosition().x - m_Shape.getPosition().x)) + ((m_Player->GetShape().getPosition().y - m_Shape.getPosition().y) * (m_Player->GetShape().getPosition().y - m_Shape.getPosition().y)));
        DirectionToPlayer = m_Player->GetShape().getPosition().x - m_Shape.getPosition().x;
    }
    else
    {
        DistanceToPlayer = 0.0f;
        DirectionToPlayer = 0;
    }

    // Movement
    if (DistanceToPlayer > 100.0f && DistanceToPlayer < 2000.0f)
    {
        if (velocity.x < 1.0f && velocity.x > -1.0f && DirectionToPlayer < 0.f)
        {
            // Face Left
            m_Shape.setScale(1, 1);

            switch (m_SlimeType)
            {
            case Slime::SLIMETYPE::GREEN:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(-100.f - rand() % 300, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -100.f - rand() % 300), true);
                break;
            }
            case Slime::SLIMETYPE::BOSS:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(-100.f - rand() % 2400, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -100.f - rand() % 2400), true);
                break;
            }
            default:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(-100.f - rand() % 300, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -100.f - rand() % 300), true);
                break;
            }
            }
        }
        else if (velocity.x < 1.0f && velocity.x > -1.0f && DirectionToPlayer > 0.f)
        {
            // Face Right
            m_Shape.setScale(-1, 1);

            // Move Right
            switch (m_SlimeType)
            {
            case Slime::SLIMETYPE::GREEN:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(100.f + rand() % 300, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 100.f + rand() % 300), true);
                break;
            }
            case Slime::SLIMETYPE::BOSS:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(100.f + rand() % 2400, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 100.f + rand() % 2400), true);
                break;
            }
            default:
            {
                // Move Left
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(100.f + rand() % 300, 0.0f), true);
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 100.f + rand() % 300), true);
                break;
            }
            }
        }
    }
}

void Slime::Attack()
{
    float DistanceToPlayer;
    float DirectionToPlayer;

    if (bHasPlayer())
    {
        DistanceToPlayer = sqrt(((m_Player->GetShape().getPosition().x - m_Shape.getPosition().x) * (m_Player->GetShape().getPosition().x - m_Shape.getPosition().x)) + ((m_Player->GetShape().getPosition().y - m_Shape.getPosition().y) * (m_Player->GetShape().getPosition().y - m_Shape.getPosition().y)));
        DirectionToPlayer = m_Player->GetShape().getPosition().x - m_Shape.getPosition().x;

        switch (m_SlimeType)
        {

        case Slime::SLIMETYPE::GREEN:
        {
            if (DistanceToPlayer <= 110.0f)
            {
                m_Body->SetLinearVelocity(b2Vec2(DirectionToPlayer * -4, 0));
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * -5, -200), true);
                m_Player->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * 1 / 2, 0), true);
                m_Player->TakeDamage(12.25f);
            }
            break;
        }

        case Slime::SLIMETYPE::BOSS:
        {
            if (DistanceToPlayer <= 300.0f)
            {
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * -5, -200), true);
                m_Player->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * 1 / 2, 0), true);
                m_Player->TakeDamage(35.0f);
            }
            break;
        }

        default:
        {
            if (DistanceToPlayer <= 110.0f)
            {
                m_Body->SetLinearVelocity(b2Vec2(DirectionToPlayer * -4, 0));
                m_Body->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * -5, -200), true);
                m_Player->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(DirectionToPlayer * 1 / 2, 0), true);
                m_Player->TakeDamage(1.f);
            }
            break;
        }
        }
    }
}

void Slime::TakeDamage(float _damage)
{
    if (m_DamageTimer->getElapsedTime().asSeconds() >= 0.5f)
    {
        m_AudioManager->SlimeDamage(10);
        m_Health -= _damage;
        m_DamageTimer->restart();
    }
}

void Slime::CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor)
{
    //ground physics
    m_BodyDef.type = _type;
    m_BodyDef.fixedRotation = true;
    m_BodyDef.linearDamping = 0.6f;

    if (m_bIsBoss)
    {
        m_BodyDef.gravityScale = 3.0f;
    }
    else
    {
        m_BodyDef.gravityScale = 10.0f;
    }

    m_BodyDef.position = b2Vec2(_posX / m_Scale, (_posY / m_Scale));
    m_Body = m_World->CreateBody(&m_BodyDef);

    if (m_bIsBoss)
    {
        m_b2pShape.SetAsBox((300 / 2) / m_Scale, (300 / 2) / m_Scale);
    }
    else
    {
        m_b2pShape.SetAsBox((100 / 2) / m_Scale, (100 / 2) / m_Scale);
    }

    if (_sensor)
    {
        m_FixtureDef.isSensor = true;
    }
    m_FixtureDef.density = 2.0f;
    m_FixtureDef.shape = &m_b2pShape;
    m_FixtureDef.friction = 1.0f;
    m_FixtureDef.restitution = 0.1f;
    m_FixtureDef.filter.categoryBits = 0x0004;
    m_Body->CreateFixture(&m_FixtureDef);

    m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
    m_Shape.setPosition(m_Body->GetPosition().x * m_Scale, m_Body->GetPosition().y * m_Scale);
    m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}

void Slime::SetPlayer(Player* _player)
{
	m_Player = _player;
}

void Slime::LosePlayer()
{
	m_Player = nullptr;
}

bool Slime::bHasPlayer()
{
	if (m_Player != nullptr)
	{
		return true;
	}

	return false;
}
