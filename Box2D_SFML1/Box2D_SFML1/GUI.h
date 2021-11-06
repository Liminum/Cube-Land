#pragma once
#ifndef _GUI_H__
#define _GUI_H__

// Local Includes
#include "Player.h"
#include "CButtons.h"

class GUI : public NumptyBehavior
{
public:
	GUI(sf::RenderWindow* _renderwindow, TextureMaster* _texturemaster, sf::Font &_font);
	virtual ~GUI();

	virtual void Start();
	virtual void Render(Player* _player, sf::Shader* _defaultshader = NULL ,sf::Vector2f _mousePos = sf::Vector2f(0, 0));

	sf::Vector2f UIMousePointer(sf::View& _uiview);
	void InitHealthAndManaUI();
	void HealthAndManaUI(sf::RenderWindow* _renderWindow, sf::View& _uiView, Player* _player);
	void TimerUI();

	void InitBattleUI();
	void BattleUI(sf::View& _uiView, sf::View& _worldView);

	void InitButton(CButtons* _button, sf::Texture* _idleTexture, sf::Texture* _hoverTexture);

	sf::Font m_Font;

private:
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

	std::vector<CButtons*> m_BattleSceneButtons{};
	std::vector<sf::RectangleShape> m_BattleSceneMenuShapes{};

	sf::Texture m_PlayerPreview;

	void CleanupBattleSceneButtons();
	void InitCubeBoyUI();
	void InitBackpackUI();
	void InitDialogueUI();
};
#endif