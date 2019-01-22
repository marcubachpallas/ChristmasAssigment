#pragma once
#include "includes.h"
#include "ScriptSystem.h"


class MovePlatformScript : public Script
{
public:
	MovePlatformScript(int owner) : Script(owner) {};

	void init();
	void update(float dt);

	bool shouldPlatformMove = false;
	Transform* transform;
};