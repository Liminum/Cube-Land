#pragma once
#ifndef _WORLDMANAGER_H__
#define _WORLDMANAGER_H__

#include "NumptyBehavior.h"

// Local Includes
#include "TextureMaster.h"
#include "Player.h"
#include "Tile.h"

class WorldManager : public NumptyBehavior
{
public:
	enum class LEVELTYPE
	{
		DEFAULT = 0,
		FOREST,
		SNOW,
	};

	WorldManager(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _texturemaster, LEVELTYPE _type = LEVELTYPE::DEFAULT);
	virtual ~WorldManager();

	template <typename T> 
	bool IsItemListBody(std::vector<T*>& _itemlist, b2Fixture* _bodyfixture);

	virtual void Start(AudioManager* _audioManager);
	virtual void Update();
	virtual void Render(sf::Shader* _defaultshader = NULL);

	void InitBackground(sf::Texture& _texture); 

	void CleanupBlocks();
	void CreateBasicBlocks();

	std::vector<Tile*> m_Tiles = {}; // Tiles includes all Tile instances, including tile sub classes
private:
	LEVELTYPE m_Type;
	TextureMaster* m_TextureMaster = nullptr;

	sf::RenderWindow* m_RenderWindow = nullptr;
	Tile* m_Tile = nullptr;
	sf::Sprite* m_background = nullptr;
	b2World* m_World = nullptr;
};
#endif

template<typename T>
inline bool WorldManager::IsItemListBody(std::vector<T*>& _itemlist, b2Fixture* _bodyfixture)
{
	typename std::vector<T*>::iterator it;
	for (it = _itemlist.begin(); it != _itemlist.end(); it++)
	{
		if ((*it)->GetBody() == _bodyfixture->GetBody())
		{
			return true;
		}

	}
	return false;
}