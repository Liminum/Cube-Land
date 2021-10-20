#pragma once
#ifndef _NumptyBehavior__
#define _NumptyBehavior__

// Non-Local Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <box2d/box2d.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <utils-master/stringutils.h>

class NumptyBehavior
{
public:
	template <typename T>
	static inline void DeletePointer(T* _pointer)
	{
		if (_pointer != nullptr)
		{
			delete _pointer;
		}
	}

	static inline sf::Texture* LoadTexture(sf::Texture* _texture, std::string _filePath, bool _repeated = true)
	{
		if (_texture != nullptr)
		{
			_texture->loadFromFile("Resources/Images/" + _filePath);
			_texture->setRepeated(_repeated);
		}
		return _texture;
	}

	static inline sf::Sprite* LoadSpriteTexture(sf::Texture* _texture, sf::Sprite* _sprite, bool _resetTextRect = true, bool _setOriginCentre = true)
	{
		if (_sprite != nullptr)
		{
			_sprite->setTexture(*_texture, _resetTextRect);

			if (_setOriginCentre)
			{
				_sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height / 2);
			}
		}
		return _sprite;
	}

	static inline void RenderSpritePointer(sf::RenderWindow* _renderWindow, sf::Sprite* _sprite)
	{
		if (_renderWindow != nullptr)
		{
			if (_sprite != nullptr)
			{
				_renderWindow->draw(*_sprite);
			}
		}
	}

protected:
	virtual void Start() {}
	virtual void Update() {}
	virtual void PolledUpdate() {}
	virtual void Render() {}

	float m_Scale = 45.0f;
};
#endif

