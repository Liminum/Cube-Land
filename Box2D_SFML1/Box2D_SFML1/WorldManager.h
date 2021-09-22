#pragma once
#ifndef _WORLDMANAGER_H__
#define _WORLDMANAGER_H__

#include <list>
#include "TextureMaster.h"
#include "Player.h"
#include "Tile.h"
#include "LumberPile.h"
#include "StonePile.h"
#include "Portal.h"


class WorldManager
{

public:

	enum class LEVELTYPE
	{
		DEFAULT = 0,
		FOREST,
		SNOW,

	};


	WorldManager(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _texturemaster, Player* _player, const float _scale, LEVELTYPE _type = LEVELTYPE::DEFAULT);
	~WorldManager();

	template <typename T> 
	bool IsItemListBody(std::list<T>& _itemlist, b2Fixture* _bodyfixture);

	void Start();
	void Update();
	void Render();
	void SetPlayer(Player* _player);
	void LosePlayer();
	void InitBackground(sf::Texture& _texture);
	bool PickupItemOnGround();  

private:

	LEVELTYPE m_Type;

	LumberPile* m_LumberPile;
	StonePile* m_StonePile;
	Portal* m_Portal;
	TextureMaster* m_TextureMaster;

	std::list<Tile> m_Tiles = {}; // Tiles includes all Tile instances, including tile sub classes

	std::list<LumberPile> m_LumberPiles = {};
	std::list<StonePile> m_StonePiles = {};

	sf::RenderWindow* m_RenderWindow;
	Tile* m_Tile;
	sf::Sprite* m_background;
	b2World* m_World;
	Player* m_Player;
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
