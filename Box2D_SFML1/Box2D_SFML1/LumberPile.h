#pragma once
#ifndef _LUMBERPILE_H__
#define _LUMBERPILE_H__
#include "Item.h"
class LumberPile : public Item
{
public:

	LumberPile();

	LumberPile(sf::RenderWindow* _renderwindow, b2World& _world, int _amount, float _posX, float _posY);

	void Start();
	void Update();
	void SetLumberPileAmount(int _lumberamount);
	int GetLumberPileAmount();


	~LumberPile();

private:

	
	int LumberAmount = 2;

};
#endif