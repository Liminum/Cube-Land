#pragma once
#ifndef _PLAYER_H__
#define _PLAYER_H__
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include<iostream>
#include <map>
#include <list>
#include<fstream>
#include "AudioManager.h"
#include "TextureMaster.h"
#include "Projectile.h"
#include "Staff.h"
#include "ParticleSystem.h"


class Player
{
public:
	Player(sf::RenderWindow* _renderWindow, b2World& _world, const float& _scale, AudioManager* _audiomanager, TextureMaster* _texturemaster);
	~Player();

	void Start();
	void Update(sf::Vector2f _mousepos);
	void Render(sf::Shader* _defaultshader = NULL);
	void PollMovement(sf::Event& _event);
	void Movement();
	void AddItemToInventory(Item* _item, bool _bCanStack = true);
	void AddItemToInventory(Item* _item, int _amount, bool _bCanStack = true);
	bool IsItemInInventory(Item* _item);
	bool IsItemInInventory(Item* _item, int _amount);
	void RemoveItemFromInventory(int _pos);
	void CreateBody(float _posX, float _posY, b2BodyType _type, bool _sensor = false);
	void DestroyBody();
	b2Body* GetBody();

	void TogglebInventoryOpen();
	void SetCurrentMana(float _mana);
	float GetCurrentMana();
	void TakeDamage(float _damage);
	void SetCurrentHealth(float _health);
	float GetCurrentHealth();
	void Attack(Projectile::PROJECTILETYPE _type);
	sf::Sprite GetShape();

	std::map<int, Item> m_InventoryMap;
	float m_iMovementSpeed = 50;
	std::list<Projectile> m_Projectiles;
	std::map<int, int> m_InventoryStackValues;
	int m_CurrentItemIndex = 0;
	bool m_bInventoryOpen = false;

private:
	
	sf::RenderWindow* m_RenderWindow;
	TextureMaster* m_TextureMaster;
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
	ParticleSystem* m_ParticleSystem;
	sf::Clock m_ParticleClock;
	b2Vec2 m_Velocity;
	sf::Texture m_PlayerTexture;
	sf::Sprite m_Shape;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_b2pShape;
	b2FixtureDef m_FixtureDef;
	b2Body* m_Body;
	b2World* m_World;
	AudioManager* m_AudioManager;
	Projectile* m_Projectile;
	Staff* m_Staff;
	sf::Clock m_AttackTimer;
	sf::Vector2f m_MousePos;

	float m_Scale;
};

#endif