#pragma once
#ifndef _MONOBEHAVIOR__
#define _MONOBEHAVIOR__

// Non-Local Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <box2d/box2d.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <utils-master/stringutils.h>

class MonoBehavior
{
public:
	static inline void DeletePointer(void* _pointer)
	{
		if (_pointer != nullptr)
		{
			std::cout << "Cleanup Successful : " << (int) ctime_s << std::endl;
			delete _pointer;
		}
	}

protected:
	virtual inline void Start() {}
	virtual inline void Update() {}
	virtual inline void Render() {}

	float m_Scale = 45.0f;
};
#endif

