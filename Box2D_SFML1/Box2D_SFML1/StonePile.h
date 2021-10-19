#pragma once
#ifndef _STONEPILE_H__
#define _STONEPILE_H__

#include "Item.h"

class StonePile : public Item
{
public:
	StonePile();
	StonePile(sf::RenderWindow* _renderwindow, b2World& _world, int _amount, float _posX, float _posY);
	virtual ~StonePile();

	virtual void Update();

	void SetStonePileAmount(int _stoneamount);
	int GetStonePileAmount();

private:
	int StoneAmount = 5;
};

#endif