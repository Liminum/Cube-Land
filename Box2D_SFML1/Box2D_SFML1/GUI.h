#pragma once
#ifndef _GUI_H__
#define _GUI_H__
#include<SFML/Graphics.hpp>
#include<fstream>
#include "Player.h"


class GUI
{
public:

	GUI(sf::RenderWindow* _renderwindow, TextureMaster* _texturemaster);

	~GUI();

	void Start();
	void Update();
	void Render(Player* _player);

	void InitInventoryUI(Player* _player);
	void InitHealthAndManaUI();
	void HealthAndManaUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player);
	void InventoryUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player);
	void TimerUI();
	int FindFirstEmptyInventorySlot(Player* _player);
	void HotBarScrolling(sf::Event& _event, Player* _player);
	void InitHotBarScrolling(sf::Event& _event, Player* _player);

private:


	std::map<int, sf::Text> m_InventoryStackCounters;
	sf::Clock m_FirstEmptySlotTimer;
	std::map<int, sf::Sprite> m_InventorySlotMap;
	sf::Font m_Font;
	sf::RenderWindow* m_RenderWindow;
	TextureMaster* m_TextureMaster;
	sf::Clock m_Timer;
	sf::Text m_DisplayText;



	sf::Texture m_ManaTexture;
	sf::Texture m_ManaBorderTexture;
	sf::Sprite m_ManaSprite;
	sf::Sprite m_ManaBorderSprite;

	sf::Texture m_HealthTexture;
	sf::Texture m_HealthBorderTexture;
	sf::Sprite m_HealthSprite;
	sf::Sprite m_HealthBorderSprite;

	sf::Texture m_Texture;

	sf::Sprite m_Shape;
};

#endif