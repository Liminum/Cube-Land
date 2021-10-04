#pragma once
#ifndef _SLIME_H__
#define _SLIME_H__
#include "Enemy.h"
#include "Player.h"

class Slime : public Enemy
{
public:

	enum class SLIMETYPE
	{
		GREEN,
		BOSS
	};

	Slime(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _textureMaster, AudioManager& _audimanager, const float& _scale, float _posX, float _posY);

	virtual ~Slime();

	virtual void Start();
	virtual void Update();
	virtual void Movement();
	virtual void Attack();
	virtual void CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor = false);
	void SetPlayer(Player* _player);
	void LosePlayer();
	bool bHasPlayer();
	void TakeDamage(float _damage);


private:

	AudioManager* m_AudioManager;
	Player* m_Player;
	bool m_bIsBoss = false;
	bool m_bApplyFallDamage;
	SLIMETYPE m_SlimeType = SLIMETYPE::GREEN;
	sf::Clock* m_DamageTimer;


};
#endif