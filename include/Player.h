#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "DynamicEntity.h"
#include "Sprite.h"
#include "InputKeys.h"
#include "PlayerState.h"

class PlayerState;

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public DynamicEntity {

	public:
		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Player(double x_, double y_, Sprite* sprite_);

		/**
		* The destructor.
		* Deletes the sprite.
		* @todo See if just the entity deleting the sprite is enough.
		*/
		virtual ~Player();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(double dt_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(unsigned int width_, unsigned int height_);

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		static void initializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		static void destroyStates();

		/**
		* Sets the current game state.
		* @see PlayerState::load
		* @see PlayerState::unload
		* @param state_ : The state you want to be changed into. All states are inside Player.
		*/
		static void changeState(PlayerState& state_);

		static PlayerState* actionIdle; /**< The action of stand. First state of the player. */
		static PlayerState* actionAerial; /**< The action of */
		static PlayerState* actionMoving; /**< The action of */
		static PlayerState* actionRolling; /**< The action of */
		static PlayerState* actionCrouching; /**< The action of */

	private:
		
		static PlayerState* currentAction; /**< The current action, which the player is in. */

		
		
};

#endif //INCLUDE_PLAYER_H
