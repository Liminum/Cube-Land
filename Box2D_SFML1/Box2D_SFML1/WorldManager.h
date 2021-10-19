#pragma once
#ifndef _WORLDMANAGER_H__
#define _WORLDMANAGER_H__

#include "MonoBehavior.h"

// Local Includes
#include "TextureMaster.h"
#include "Player.h"
#include "Tile.h"
#include "LumberPile.h"
#include "StonePile.h"
#include "Portal.h"

class WorldManager : public MonoBehavior
{
public:
	enum class LEVELTYPE
	{
		DEFAULT = 0,
		FOREST,
		SNOW,

	};

	WorldManager(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _texturemaster, Player* _player, LEVELTYPE _type = LEVELTYPE::DEFAULT);
	virtual ~WorldManager();

	template <typename T> 
	bool IsItemListBody(std::list<T>& _itemlist, b2Fixture* _bodyfixture);

	virtual void Start(AudioManager* _audioManager);
	virtual void Update();
	virtual void Render(sf::Shader* _defaultshader = NULL);

	void SetPlayer(Player* _player);
	void LosePlayer();
	void InitBackground(sf::Texture& _texture);
	bool PickupItemOnGround();  

	std::list<Tile> m_Tiles = {}; // Tiles includes all Tile instances, including tile sub classes
	std::list<LumberPile> m_LumberPiles = {};
	std::list<StonePile> m_StonePiles = {};
private:
	LEVELTYPE m_Type;

	LumberPile* m_LumberPile = nullptr;
	StonePile* m_StonePile = nullptr;
	Portal* m_Portal = nullptr;
	TextureMaster* m_TextureMaster = nullptr;

	sf::RenderWindow* m_RenderWindow = nullptr;
	Tile* m_Tile = nullptr;
	sf::Sprite* m_background = nullptr;
	b2World* m_World = nullptr;
	Player* m_Player = nullptr;
	float m_Scale;
};
#endif

template<typename T>
inline bool WorldManager::IsItemListBody(std::list<T>& _itemlist, b2Fixture* _bodyfixture)
{
	typename std::list<T>::iterator it;
	for (it = _itemlist.begin(); it != _itemlist.end(); it++)
	{
		if (it->GetBody() == _bodyfixture->GetBody())
		{
			return true;
		}

	}
	return false;
}
