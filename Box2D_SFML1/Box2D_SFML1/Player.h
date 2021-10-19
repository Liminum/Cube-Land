#pragma once
#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "CEntity.h"
#include "AudioManager.h"
#include "TextureMaster.h"
#include "Projectile.h"
#include "Staff.h"
#include "ParticleSystem.h"

class Player : public CEntity
{
public:
	Player(sf::RenderWindow* _renderWindow, b2World& _world, AudioManager* _audiomanager, TextureMaster* _texturemaster);
	virtual ~Player();

	virtual void Start();
	virtual void Update(sf::Vector2f _mousepos);
	virtual void Render(sf::Shader* _defaultshader = NULL);

	void PollMovement(sf::Event& _event);
	void Movement();
	void AddItemToInventory(Item* _item, bool _bCanStack = true);
	void AddItemToInventory(Item* _item, int _amount, bool _bCanStack = true);
	bool IsItemInInventory(Item* _item);
	bool IsItemInInventory(Item* _item, int _amount);
	void RemoveItemFromInventory(int _pos);

	b2Body* GetBody();
	sf::Sprite GetShape();
	Staff* GetStaff();

	void TogglebInventoryOpen();
	void SetCurrentMana(float _mana);
	float GetCurrentMana();
	void TakeDamage(float _damage);
	void SetCurrentHealth(float _health);
	float GetCurrentHealth();
	void Attack(Projectile::PROJECTILETYPE _type);

	std::map<int, Item> m_InventoryMap;
	float m_iMovementSpeed = 50;
	std::list<Projectile> m_Projectiles;
	std::map<int, int> m_InventoryStackValues;
	int m_CurrentItemIndex = 0;
	bool m_bInventoryOpen = false;

private:
	sf::Clock m_DamageTakenTimer;
	sf::Clock m_ManaRegen;
	float m_ManaRegenFrequency = 1.f;
	float m_CurrentMana = 100.f;
	float m_MaxMana = 100.f;
	float m_CurrentHealth = 100.f;
	float m_MaxHealth = 100.f;
	float m_JumpForce = 500.0f;
	int m_InventorySize = -1;
	bool m_bCanJump = false;
	sf::Clock m_ParticleClock;
	b2Vec2 m_Velocity;
	sf::Texture m_PlayerTexture;
	Projectile* m_Projectile = nullptr;
	Staff* m_Staff = nullptr;
	sf::Clock m_AttackTimer;
	sf::Vector2f m_MousePos;
};

#endif