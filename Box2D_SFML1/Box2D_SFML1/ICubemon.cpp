#include "ICubemon.h"

int ICubemon::TakeDamage(float _amount)
{
	if (m_DamageTimer.getElapsedTime().asSeconds() >= 0.1f)
	{
		for (int i = 0; i < _amount; i++)
		{
			if (m_CurrentHealth > 1)
			{
				m_CurrentHealth--;
			}
			else
			{
				m_MARKASDESTROY = true;
				break;
			}
		}

		m_DamageTimer.restart();
		return _amount;
	}
	else
	{
		return 0;
	}
}

int ICubemon::Heal(float _amount)
{
	if (m_DamageTimer.getElapsedTime().asSeconds() >= 0.1f)
	{
		for (int i = 0; i < _amount; i++)
		{
			if (m_CurrentHealth < m_MaxHealth && m_CurrentHealth > 0)
			{
				m_CurrentHealth++;
			}
			else
			{
				break;
			}
		}

		m_DamageTimer.restart();
		return _amount;
	}
	else
	{
		return 0;
	}
}
