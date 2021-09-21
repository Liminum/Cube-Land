#pragma once
#ifndef _AUDIOMANAGER_H__
#define _AUDIOMANAGER_H__
#include <sfml/audio.hpp>
class AudioManager
{
public:

	AudioManager();


	~AudioManager();

	void PlayerDeath();
	void FireBow();
	void SlimeDeath(float _volume);
	void SlimeDamage(float _volume);
	void PlayMusic();

	sf::Music m_Music;

private:

	
	sf::SoundBuffer m_SlimeDeathBuffer;
	sf::SoundBuffer m_SlimeHurt1;
	sf::SoundBuffer m_SlimeHurt2;
	sf::SoundBuffer SlimeHurtBuffers[2];
	sf::Sound m_SlimeDeathSound;
	sf::Sound m_SlimeDamageSound;

	sf::SoundBuffer m_PlayerDeathBuffer;
	sf::Sound m_PlayerDeathSound;


	sf::SoundBuffer m_BowBuffer;
	sf::Sound m_BowShotSound;


};
#endif