#pragma once
#include "IEntity.h"
class ICubemon : public IEntity
{
public:
	enum class CUBEMONSTATE
	{
		UNASSIGNED,

		ASLEEP = 1,
		WORLD = 2,
		COMBAT = 3,
		DEAD = 4
	};

	enum class CUBEMONTYPE
	{
		UNASSIGNED,

		THALLIC = 1,
	};

	virtual ~ICubemon() { };

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Movement() = 0;
	virtual void Attack() = 0;

	virtual int TakeDamage(float _amount);
	inline void SetCurrentHealth(float _amount) { m_CurrentHealth = _amount; }
	inline float GetCurrentHealth() { return m_CurrentHealth; }
	virtual int Heal(float _amount);

	CUBEMONTYPE m_CubeType = CUBEMONTYPE::UNASSIGNED;

protected:
	CUBEMONSTATE m_CubeState = CUBEMONSTATE::UNASSIGNED;

	float m_CurrentHealth = 100.0f;
	float m_MaxHealth = 100.0f;

	sf::Texture* m_SpriteTexture = nullptr;
private:
	sf::Clock m_DamageTimer;
};

