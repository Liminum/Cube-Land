#pragma once
#ifndef _SPAWNER_H__
#define _SPAWNER_H__
#include <SFML/Graphics.hpp> 
#include <list> 
#include "Slime.h"


class Spawner
{
public:
	Spawner(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _textureMaster, AudioManager* _audiomanager, const float& _scale, float _posX, float _posY, float _spawnfrequency, Player* _player, Enemy::ENEMYTYPE _type);

	~Spawner();

	void Start();
	void Update();
	void Render();
	void LosePlayer();
	void SetPlayer(Player* _player);
	void ToggleSpawning();
	void SetSpawnCount(int _spawncount);
	int GetSpawnCount();
	

	std::list<Slime> m_Slimes;

private:


	Enemy::ENEMYTYPE m_Type;

	bool m_bSpawn = false;
	int m_SpawnCount = 0;
	float m_SpawnFrequency;
	AudioManager* m_AudioManager;
	sf::RenderWindow* m_RenderWindow;
	b2World* m_World;
	TextureMaster* m_TextureMaster;
	Player* m_Player;

	float m_Scale = 50.0f;

	sf::Clock* m_SpawnTimer;

	Slime* m_Slimeptr;

};

#endif