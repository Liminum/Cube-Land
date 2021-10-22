#pragma once
#ifndef _WORLDMANAGER_H__
#define _WORLDMANAGER_H__

#define INISIZE 40

#include "NumptyBehavior.h"

// Local Includes
#include "TextureMaster.h"
#include "Player.h"
#include "Tile.h"

class WorldManager : public NumptyBehavior
{
public:
	WorldManager(sf::RenderWindow* _renderWindow, b2World& _world, TextureMaster* _texturemaste);
	virtual ~WorldManager();

	virtual void Start(AudioManager* _audioManager);
	virtual void Update();
	virtual void Render(sf::Shader* _defaultshader = NULL);

	void InitBackground(sf::Texture& _texture); 

	void ImportWorldFromINI();
	void CleanupTiles();

private:
	void GrabTileTypes(std::vector<char>& _tileTypes);
	void ProcessTileTypes(std::vector<char>& _tileTypes);

	std::vector<Tile*> m_Tiles = {};
	Tile* m_Tile = nullptr;

	TextureMaster* m_TextureMaster = nullptr;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::Sprite* m_background = nullptr;
	b2World* m_World = nullptr;
};
#endif