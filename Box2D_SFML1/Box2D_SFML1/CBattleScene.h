#pragma once

#include "IScene.h"

class CBattleScene : public IScene
{
public:
	CBattleScene(sf::RenderWindow* _renderWindow, TextureMaster* _textureMaster, sf::Event& _event);
	virtual ~CBattleScene();

	virtual void Start()override;
	virtual void Update()override;
	virtual void PolledUpdate() override;
	virtual void Render() override;
	virtual void CheckForMARKASDESTROY()override;

private:
	void CreateAudioManager();
	virtual void CleanupAllPointers()override;

	void InitUIView();
	void InitWorldView();

	sf::Event* m_Event = nullptr;
	sf::View m_UIView;
	sf::View m_WorldView;
};

