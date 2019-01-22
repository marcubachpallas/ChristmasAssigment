#include "EnemyAI.h"
#include "extern.h"
#include "linmath.h"




void EnemyAI::init() {
	//int max = ;
	for (int i = 0; i != ECS.entities.size(); i++)
	{
		if (ECS.entities[i].name.find("weightPoint") != std::string::npos) {
			weightPoints.push_back(i);
			cout << ECS.getComponentID<Transform>(i) << "\n";
			cout << ECS.entities[i].name << "\n";
		}
	}
}

void EnemyAI::update(float dt) {
	//_sleep(100);

//	forwardRay = &ECS.getComponentFromEntity<Transform>(ECS.getEntity("ForwardRay"));
	Camera& camera = ECS.getComponentInArray<Camera>(ECS.main_camera);
	transform = &ECS.getComponentFromEntity<Transform>(owner_);
	//forwardCam = camera.forward;
	float dist, dist2Player;
	lm::vec3 pos2go;

	float yaw, rotation;
	lm::vec3 dv, lAt;

	//float maxRotate;

	cout << state << " ENEMY IA\n";
	switch (state)
	{
	case(0):
		cout << "idle";
		currWeightpoint = weightPoints[rand() % weightPoints.size()];
		state = 1;

		//look for other weightPoint
		break;
	case(1):
		cout << "patrol";
		targetTrans = &ECS.getComponentFromEntity<Transform>(currWeightpoint);
		playerTrans = &ECS.getComponentFromEntity<Transform>(camera.owner);
		forwardCam = playerTrans->position() - transform->position();
		forwardWeghtPoint = targetTrans->position() - transform->position();
		rotation = (transform->front().dot(forwardWeghtPoint));
		transform->rotateLocal(rotation* rotationSpeed*dt, lm::vec3(0, 1, 0));

		pos2go = (targetTrans->position() - transform->position());

		//cout << targetTrans->position().x << " " << targetTrans->position().y << " " << targetTrans->position().z << " \n";
		//cout << transform->position().x << " " << transform->position().y << " " << transform->position().z << " \n";
		//cout << pos2go.x << " " << pos2go.y << " " << pos2go.z;
		cout << "rotation: " << rotation << "\n";
		
		dist = sqrt(pow(abs(transform->position().x) - abs(targetTrans->position().x), 2) + pow(abs(transform->position().y) - abs(targetTrans->position().y), 2));
		dist2Player = sqrt(pow(abs(transform->position().x) - abs(playerTrans->position().x), 2) + pow(abs(transform->position().y) - abs(playerTrans->position().y), 2));

		cout << "rotation2player: " << cos((transform->front().normalize().x * forwardCam.normalize().x + transform->front().normalize().y * forwardCam.normalize().y) / (sqrt(pow(transform->front().normalize().x + transform->front().normalize().y, 2))*sqrt(pow(forwardCam.normalize().x + forwardCam.normalize().y, 2)))) << "\n";
		if (dist2Player < 20.0f) {
			//if (cos((transform->front().x * forwardCam.x + transform->front().y * forwardCam.y) / (sqrt(pow(transform->front().x + transform->front().y, 2))*sqrt(pow(forwardCam.x + forwardCam.y, 2)))) < 20)
			//if(rotation < 20)
			state = 2;
		}
		else if (dist < 2.0f) {
			state = 0;
		}
		transform->translateLocal(speed*dt, 0, 0);
		break;
	case(2):
		cout << "goToPlayer" << "\n";
		playerTrans = &ECS.getComponentFromEntity<Transform>(camera.owner);

		forwardCam = playerTrans->position() - transform->position();
		rotation = (transform->front().dot(forwardCam)) ;
		//rotation = cos((transform->front().x * forwardCam.x + transform->front().y * forwardCam.y) / (sqrt(pow(transform->front().x + transform->front().y, 2))*sqrt(pow(forwardCam.x + forwardCam.y, 2))));
		//maxRotate = (rotation * rotationSpeed*dt);
		/*if (maxRotate < -0.5f) maxRotate = -0.5f;
		else if (maxRotate > 0.5f) maxRotate = 0.5f;*/
		transform->rotateLocal(rotation* rotationSpeed*dt, lm::vec3(0, 1, 0));
		
		//position to move
		pos2go = (playerTrans->position()-transform->position());
		
		//cout << pos2go.x << " " << pos2go.y << " " << pos2go.z;
		//cout << "rotation: " << rotation << "\n";

		dist = sqrt(pow(abs(transform->position().x) - abs(playerTrans->position().x), 2) + pow(abs(transform->position().y) - abs(playerTrans->position().y), 2));

		if (dist < 2.0f) {
			state = 3;
		}else if (dist > 20.0f) {
			state = 0;
		}
		transform->translateLocal(speed*dt, 0, 0);
		//cout << "dist: " << dist << "\n";

		break;
	case(3):
		cout << "atack";
		playerTrans = &ECS.getComponentFromEntity<Transform>(camera.owner);

		dist = sqrt(pow(abs(transform->position().x) - abs(playerTrans->position().x), 2) + pow(abs(transform->position().y) - abs(playerTrans->position().y), 2));

		if (dist > 2.0f) {
			state = 2;
		}
		break;
	default:
		break;
	}
	cout << "\n";


}