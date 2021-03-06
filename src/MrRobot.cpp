/*
PROJECT: Ludum Dare
CREATED: 12th December 2015
AUTHORS: Oliver Hirschfield
*/

#include "MrRobot.h"
#include "Resources.h"
#include "Lasers.h"
#include "Player.h"
#include "Effects.h"

#include "Engine\Texture.h"
#include "Engine\Audio.h"


std::vector<Robot> MrRobot::entities;

int directionBob = 0;

void MrRobot::add(int posX) {

	Robot temp;

	temp.health = 20;
	temp.damage = 1;

	temp.posX = posX;
	temp.posY = 450;


	entities.push_back(temp);
}


void MrRobot::render(int distance) {
	
	for (int i = 0; i < entities.size(); i++){

		if (entities[i].health > 0 && entities[i].posX - distance < 1300){
			Texture::draw(Resources::enemyRobot, entities[i].posX - distance, entities[i].posY, 1.0);
		}
	}
}

void MrRobot::run(int distance) {
	
	for (int i = 0; i < entities.size(); i++){

		if (entities[i].health > 0 && entities[i].posX > - 100){
			entities[i].posX -= 1.0;
			
			if (entities[i].posY > 440 && directionBob == 0){
				entities[i].posY -= 1.0;
			} else{
				directionBob = 1;
			}

			if (entities[i].posY < 460 && directionBob == 1){
				entities[i].posY += 1.0;
			} else{
				directionBob = 0;
			}

		}

		for (int l = 0; l < Lasers::getTotal(); l++){
			if (Lasers::getBulletLocation(l) > entities[i].posX - distance && Lasers::getBulletLocation(l) < entities[i].posX - distance + 50 && entities[i].health > 0){
				Audio::playEffect("Assets/Sounds/RobotExplode.wav");
				Effects::add(entities[i].posX - distance, entities[i].posY);
				entities[i].health = 0;
				Lasers::destroy(l);
			}
		}

		if (entities[i].health > 0 && entities[i].posX < 110 + distance  && Player::getHealth() > 0){
			Player::damageHealth();
			Audio::playEffect("Assets/Sounds/PlayerHit.wav");
			Effects::setHurtTimer();
			Player::setDeath(2);
			entities[i].health = 0;
			
		}

	}
}

void MrRobot::killAll() {
	entities.clear();
}