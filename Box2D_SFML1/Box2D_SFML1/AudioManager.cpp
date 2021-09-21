#include "AudioManager.h"

AudioManager::AudioManager()
{
    srand(time(NULL));

    m_SlimeHurt1.loadFromFile("Resources/Audio/SlimeHit.wav");
    m_SlimeHurt2.loadFromFile("Resources/Audio/SlimeHit2.wav");

    m_PlayerDeathBuffer.loadFromFile("Resources/Audio/Death.wav");
    m_SlimeDeathBuffer.loadFromFile("Resources/Audio/SlimeDeath.wav");

    m_BowBuffer.loadFromFile("Resources/Audio/FireBow.wav");

    SlimeHurtBuffers[0] = m_SlimeHurt1;
    SlimeHurtBuffers[1] = m_SlimeHurt2;
}

AudioManager::~AudioManager()
{

}

void AudioManager::PlayerDeath()
{
    m_PlayerDeathSound.setBuffer(m_PlayerDeathBuffer);
    m_PlayerDeathSound.setVolume(25.0f);
    m_PlayerDeathSound.play();
}

void AudioManager::FireBow()
{
    m_BowShotSound.setBuffer(m_BowBuffer);
    m_BowShotSound.setVolume(25.0f);
    m_BowShotSound.play();
}

void AudioManager::SlimeDeath(float _volume)
{
    m_SlimeDeathSound.setBuffer(m_SlimeDeathBuffer);
    m_SlimeDeathSound.setVolume(25.0f);
    m_SlimeDeathSound.play();
}

void AudioManager::SlimeDamage(float _volume)
{
    m_SlimeDamageSound.setBuffer(SlimeHurtBuffers[0]);
    m_SlimeDamageSound.setVolume(_volume);
    m_SlimeDamageSound.play();
}

void AudioManager::PlayMusic()
{
	m_Music.openFromFile("Resources/Audio/BackgroundMusic.wav");
	m_Music.setLoop(true);
	m_Music.setVolume(10.0f);
	m_Music.play();
}
