#include "SwitchScript.h"
#include "extern.h"

void SwitchScript::init() {

}

void SwitchScript::update(float dt) {
	if (ECS.getComponentFromEntity<Collider>(owner_).colliding) {
		mps->shouldPlatformMove = true;
	}
	else {
		mps->shouldPlatformMove = false;
	}

}