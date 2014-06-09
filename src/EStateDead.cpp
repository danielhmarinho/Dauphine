#include "EStateDead.h"
#include "Logger.h"

double deadTime;

void EStateDead::enter(){
	Log(DEBUG) << "ENTER DEAD";
	this->enemy->getAnimation()->changeAnimation(1, 1, 1, false, 0);
}

void EStateDead::exit(){

}

void EStateDead::update(const double dt_){
	deadTime += dt_;
	if(deadTime >= 2){
		this->enemy->setDead(true);
	}
	this->enemy->vx = 0;
}

EStateDead::EStateDead(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
