#pragma once
#include "Loader.h"
#include <vector>
#include <string>
class Animation
{
public:
	Animation(void);
	Animation(std::vector<std::string> path_);
	void ShowAnimation();
	void EnableTexture(int animboom);
	~Animation();
	std::vector<std::string> path;
	int animateCount;
	int speedTextureChange;
	Loader*loader;
};

