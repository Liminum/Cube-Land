//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CMainMenu.h
// Description : CMainMenu Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#ifndef _MAINMENU_H__
#define _MAINMENU_H__

// Local Includes
#include "CButtons.h"

class CMainMenu : public sf::Drawable, sf::Transformable, MonoBehavior
{
public:
	CMainMenu(sf::RenderWindow* _renderWindow, sf::Font& _font, std::string _bgPath);
	virtual ~CMainMenu();

	virtual void Start() = 0;
	virtual void Update(sf::Event& _event, int* _gameState);
	virtual void Render() = 0;

	CButtons* m_Play;
	CButtons* m_Options;
	CButtons* m_Exit;

private:
	void Start(std::string _bgPath);

	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	void LoadImageOntoSprite(sf::Sprite& _sprite, sf::Texture& _texture, std::string _filePath);

	void CreateBackGroundImage(std::string _bgPath);
	void CreateTitle();

	void RainbowTitle();
	void ParralaxBackground();

	void CreateButtons();

	void ButtonUpdates(int* _gameState);

	void RenderButtons(sf::RenderTarget& _target, sf::RenderStates _states) const;

	void InitButtonTextures(std::string _texture1, std::string _texture2);

	bool IsMouseLeftPressed();

	sf::Text m_Title;
	sf::Text m_Credit;

	sf::RenderWindow* m_RenderWindow = nullptr;

	sf::Texture m_MainMenuTexture;
	sf::Texture m_MainMenuButtonTexture;
	sf::Texture m_MainMenuButtonTexture_Hover;

	sf::Sprite m_MainMenuImage;

	sf::Font* m_Font = nullptr;

	std::string m_TitleString;

	sf::Clock m_RainbowClock;
	sf::Clock m_ParralaxClock;
	sf::Clock m_ButtonTimer;

	sf::Vector2f m_MousePos;

	bool m_bClose = false;
};
#endif 

