#include "MovePlatformScript.h"
#include "extern.h"

void MovePlatformScript::init() {
	transform = &ECS.getComponentFromEntity<Transform>(owner_);
}

void MovePlatformScript::update(float dt) {

	if (input_->GetKey(GLFW_KEY_J))
	{
		shouldPlatformMove = true;
	}

	if (input_->GetKey(GLFW_KEY_K)) {
		shouldPlatformMove = false;
	}

	std::cout << shouldPlatformMove << "\n";

	if (shouldPlatformMove)
		transform->translate(0, dt, 0);
}