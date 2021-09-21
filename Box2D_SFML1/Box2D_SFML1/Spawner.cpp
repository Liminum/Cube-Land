#include "Spawner.h"

Spawner::Spawner(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _textureMaster, AudioManager* _audiomanager,const float& _scale, float _posX, float _posY, float _spawnfrequency, Player* _player, Enemy::ENEMYTYPE _type)
{
    m_AudioManager = _audiomanager;
    m_SpawnFrequency = _spawnfrequency;
	m_World = &_world;     
	m_RenderWindow = _renderWindow;     
	m_TextureMaster = _textureMaster;    
	m_Player = _player;     
	m_Slimeptr = nullptr;      
	m_Scale = _scale;     
	m_Type = _type; 
    Start();
}


Spawner::~Spawner()
{
	m_Slimes.clear();

	m_Player = nullptr;
	m_World = nullptr;
	m_RenderWindow = nullptr;
	m_TextureMaster = nullptr;
	m_Slimeptr = nullptr;
    delete m_SpawnTimer;
    m_SpawnTimer = nullptr;
    m_AudioManager = nullptr;
}

void Spawner::Start()
{
	m_SpawnTimer = new sf::Clock();
}

void Spawner::Update()
{
    switch (m_Type)
    {
    case Enemy::ENEMYTYPE::DEFAULT:
        break;
    case Enemy::ENEMYTYPE::SLIME:
    {
        if (m_bSpawn && m_Slimes.size() < m_SpawnCount)
        {
            if (m_SpawnTimer->getElapsedTime().asSeconds() >= m_SpawnFrequency)
            {
                m_Slimeptr = new Slime(m_RenderWindow, *m_World, m_TextureMaster, *m_AudioManager, m_Scale, 10000, -100);
                
                m_Slimes.push_front(*m_Slimeptr);
                m_Slimes.front().SetPlayer(m_Player);
                m_Slimes.front().Start();
                m_Slimeptr = nullptr;
                std::cout << "Slime Spawned!" << "(" << m_Slimes.size() << ")" << std::endl;
                m_SpawnTimer->restart();
            }
        }


        break;
    }

    default:
    {
        break;
    }

    }
    if (m_Slimes.size() > 0)
    {
        for (Slime& slime : m_Slimes)
        {
            // Slime Dies
            if (slime.GetHealth() <= 0.0f && m_Player != nullptr)
            {
                m_AudioManager->SlimeDeath(10);
                slime.m_MARKASDESTROY = true;

                slime.LosePlayer();

                //m_bClose = true;
            }
            // Slime Spawns When Player Dead
            else if (!slime.bHasPlayer() && m_Player != nullptr)
            {
                slime.SetPlayer(m_Player);
            }

            // Update
            slime.Update();
        }

        // Cleanup
        std::list<Slime>::iterator sit;
        for (sit = m_Slimes.begin(); sit != m_Slimes.end(); sit++)
        {
            if (sit->m_MARKASDESTROY)
            {
                sit->m_MARKASDESTROY = false;
                sit = m_Slimes.erase(sit);
            }
        }
    }

}


void Spawner::Render()
{
    switch (m_Type)
    {
    case Enemy::ENEMYTYPE::DEFAULT:
        break;
    case Enemy::ENEMYTYPE::SLIME:
    {
        for (Slime& slime : m_Slimes)
        {
            slime.Render();
        }
        break;
    }
    default:
        break;
    }

}

void Spawner::LosePlayer()
{
    m_Player = nullptr;

    // Enemies Lose The Player Pointer
    for (Slime& slime : m_Slimes)
    {
        slime.SetPlayer(nullptr);
    }
}

void Spawner::SetPlayer(Player* _player)
{
    m_Player = _player;

    for (Slime& slime : m_Slimes)
    {
        slime.SetPlayer(m_Player);
    }
}

void Spawner::ToggleSpawning()
{
    m_bSpawn = !m_bSpawn;
}

void Spawner::SetSpawnCount(int _spawncount)
{
    m_SpawnCount = _spawncount;
}

int Spawner::GetSpawnCount()
{
    return m_SpawnCount;
}
