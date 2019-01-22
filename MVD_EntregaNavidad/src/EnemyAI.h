#pragma once
#include "includes.h"
#include "ScriptSystem.h"

class EnemyAI : public Script
{
public:
	EnemyAI(int owner) : Script(owner) {};
	
	int state = 0, currWeightpoint = -1;
	float speed = 4;
	float rotationSpeed = 0.5f;
	Transform* transform;
//	Transform* forwardRay;
	Transform* targetTrans, *playerTrans;
	lm::vec3 forwardCam, forwardWeghtPoint;
	std::vector<int> weightPoints;
	float timer = 0;

	void init();
	void update(float dt);
};
