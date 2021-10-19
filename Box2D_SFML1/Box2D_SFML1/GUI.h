#pragma once
#ifndef _GUI_H__
#define _GUI_H__

// Local Includes
#include "Player.h"

class GUI : public MonoBehavior
{
public:
	GUI(sf::RenderWindow* _renderwindow, TextureMaster* _texturemaster, sf::Font &_font);
	virtual ~GUI();

	virtual void Start();
	virtual void Render(Player* _player, sf::Shader* _defaultshader = NULL ,sf::Vector2f _mousePos = sf::Vector2f(0, 0));

	sf::Vector2f UIMousePointer(sf::View& _uiview);
	void InitInventoryUI(Player* _player);
	void InitHealthAndManaUI();
	void HealthAndManaUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player);
	void InventoryUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player);
	void TimerUI();
	int FindFirstEmptyInventorySlot(Player* _player);
	void HotBarScrolling(sf::Event& _event, Player* _player);
	void InitHotBarScrolling(sf::Event& _event, Player* _player);
	void ItemClicked(sf::Event& _event, Player* _player);
	void ItemDroppedInInventory(sf::RenderWindow* _renderwindow, sf::View& _uiview, sf::View& _worldview, sf::Event& _event, Player* _player);
	void HoldItemInInventory(Player* _player);
	bool bPlayerIsMovingItem(Player* _player, int _it);
	bool bPlayerIsMovingItem(Player* _player);
	int bGetPositionOfMovingItem(Player* _player);

	sf::Font m_Font;

private:
	std::map<int, sf::Text> m_InventoryStackCounters;
	sf::Clock m_FirstEmptySlotTimer;
	std::map<int, sf::Sprite> m_InventorySlotMap;
	sf::RenderWindow* m_RenderWindow = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	sf::Clock m_Timer;
	sf::Text m_DisplayText;

	sf::Sprite m_MousePointer;

	sf::Texture m_ManaTexture;
	sf::Texture m_ManaBorderTexture;
	sf::Sprite m_ManaSprite;
	sf::Sprite m_ManaBorderSprite;

	sf::Texture m_HealthTexture;
	sf::Texture m_HealthBorderTexture;
	sf::Sprite m_HealthSprite;
	sf::Sprite m_HealthBorderSprite;

	sf::Sprite m_Shape;
};
#endif