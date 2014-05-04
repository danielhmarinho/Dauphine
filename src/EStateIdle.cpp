#include "EStateIdle.h"
#include "Logger.h"
#include <cmath>
#include "SDLWrapper.h"

void EStateIdle::enter(){
	Logger::verbose("enter enemy idle");	
}

void EStateIdle::exit(){

}

void EStateIdle::update(){
	// Aerial
	if(!this->enemy->isGrounded){
		this->enemy->changeState(Enemy::EStates::AERIAL);
		return;
	}

	/// @todo Make the range be only in the direciton the enemy is facing.
	if(abs(this->enemy->x - Enemy::px) < Enemy::alertRange){
		this->enemy->changeState(Enemy::EStates::ALERT);
		return;
	}
}

EStateIdle::EStateIdle(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
