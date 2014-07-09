#include "LevelTwo.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"
#include "Collision.h"
#include "Crosshair.h"

LevelTwo::LevelTwo() :
	Level(),
	items{{3500, 8000,4900, 10000},{2950, 1950,1950, 2912}},
	caughtItems{false,false,true,false}
{
	this->changeCheckpoints(2, {4090,7870}, {2776,1700});
}

LevelTwo::~LevelTwo(){

}

void LevelTwo::load(){
	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("res/audio/lv1.wav");

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/level2.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("res/images/lv1_background.png");
	for(int i = 0; i < this->NUMBER_OF_CHECKPOINTS; ++i){
		this->checkpoints.push_back(Game::instance().getResources().get("res/images/checkpoint.png"));
	}
	this->image = Game::instance().getResources().get("res/images/potion.png");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string pathPlayerSpriteSheet = luaLevel1.unlua_get<std::string>(
		"level.player.spriteSheet");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathEnemy = luaLevel1.unlua_get<std::string>("level.enemy");

	// Changing the music.
	// Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the player and the camera.
	Player* lPlayer = nullptr;
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2){
		double savedPX = 0.0;
		double savedPY = 0.0;

		Game::instance().getSaves().getPlayerPosition(savedPX, savedPY, Game::instance().currentSlot);

		lPlayer = new Player(savedPX, savedPY, pathPlayerSpriteSheet);
	}
	else{
		lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	}
	
	Camera* lCamera = new Camera(lPlayer); 
	
	this->playerHud = new PlayerHUD(lPlayer);

	// Loading the refill of potion.
	this->image = Game::instance().getResources().get("res/images/potion.png");
	
	this->playerHud = new PlayerHUD(lPlayer);
	

	Enemy* lEnemy1 = new Enemy(1840.0, 4720.0, pathEnemy, false, 200.0);
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(0, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy1->setDead(true);
	}

	lEnemy1->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy1);

	Enemy* lEnemy2 = new Enemy(4840.0, 4400.0, pathEnemy, false, 0.0);
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(1, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy2->setDead(true);
	}

	lEnemy2->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy2);

	Enemy* lEnemy3 = new Enemy(4500.0, 3650.0, pathEnemy, true, 0.0);
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(2, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy3->setDead(true);
	}

	lEnemy3->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy3);

	Enemy* lEnemy4 = new Enemy(3160.0, 3600.0, pathEnemy, true, 0.0);
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(3, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy4->setDead(true);
	}

	lEnemy4->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy4);

	Enemy* lEnemy5 = new Enemy(3600.0, 2700.0, pathEnemy, true, 0.0);
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(4, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy5->setDead(true);
	}

	lEnemy5->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy5);

	Enemy* lEnemy6 = new Enemy(7300.0, 1600.0, pathEnemy, false, 0.0);
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(5, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy6->setDead(true);
	}

	lEnemy6->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy6);

	Enemy* lEnemy7 = new Enemy(8900.0, 1500.0, pathEnemy, false, 0.0);
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(6, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy7->setDead(true);
	}

	lEnemy7->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy7);

	Enemy* lEnemy8 = new Enemy(10600.0, 2700.0, pathEnemy, false, 0.0);
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(7, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy8->setDead(true);
	}

	lEnemy8->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy8);

		Enemy* lEnemy9 = new Enemy(5400.0, 1700.0, pathEnemy, false, 400.0);
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
		if(Game::instance().getSaves().isEnemyDead(7, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2)
			lEnemy9->setDead(true);
	}

	lEnemy9->setLevelWH(this->width, this->height);
	this->enemies.push_back(lEnemy9);

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);
	Enemy::pLife = this->player->life;

	setCamera(lCamera);

	Game::instance().getFade().fadeOut(0, 0.002);
}

void LevelTwo::unload(){
	Log(DEBUG) << "\tUnloading level 1...";
	cleanEntities();
	clearEnemies();
	//this->checkpointVisited = false;	
}

void LevelTwo::update(const double dt_){
	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// Updating the entities, using the QuadTree.
	std::vector<CollisionRect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}

	// Updating the enemies.
	for(auto enemy : this->enemies){
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, enemy->getBoundingBox());
		enemy->setCollisionRects(returnObjects);
		enemy->update(dt_);
	}

	// Set to GameOver if the player is dead.
	if(this->player->isDead()){
		Game::instance().setState(Game::GStates::GAMEOVER);
		return;
	}

	// Updating the potions.
	for(auto potion : this->player->potions){
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, potion->getBoundingBox());
		potion->setCollisionRects(returnObjects);
	}

	/// @todo Maybe refactor this static Enemy::px, Enemy::py.
	// Updating player info for the enemies.
	Enemy::px = this->player->x;
	Enemy::py = this->player->y;
	Enemy::pVulnerable = this->player->isVulnerable;

	for (int i = 0; i < NUMBER_ITEMS; ++i){	
		if(Collision::rectsCollided(this->player->getBoundingBox(), {items[0][i], items[1][i], 192, 192}) && caughtItems[i] == false){
			this->player->addPotions(3);
			caughtItems[i]=true;
		}
	}

	if(this->player->life != Enemy::pLife){
		if(this->player->isVulnerable){
			this->player->life--;
			Enemy::pLife = this->player->life;
			this->player->changeState(Player::PStates::HITED);
			this->player->isVulnerable = false;
		}
		else{

		}
	}

	// Updating the HUD.
	this->playerHud->update();

	// Updating the camera.
	this->camera->update();

	// Set next level if end is reached.
	if(this->player->reachedLevelEnd){
		Game::instance().transitionTo = Game::GStates::LEVEL_THREE;
		Game::instance().setState(Game::GStates::TRANSITION);
		return;
	}

	// Updating the potion/enemy collision.
	for(auto potion : this->player->potions){
		for(auto enemy : this->enemies){
			if(Collision::rectsCollided(potion->getBoundingBox(), enemy->getBoundingBox())){
				if(potion->activated){
					
					if(enemy->life > 0 && this->player->canAttack){
						enemy->life -= 100;
						potion->activated = false;
					}
					// Log(DEBUG) << "Enemy Life = " << enemy->life;

					if(enemy->life <= 0)
						enemy->changeState(Enemy::EStates::DEAD);
				}
			}
		}
	}

	// Updating the player attack/enemy collision.
	for(auto enemy : this->enemies){
		if(Collision::rectsCollided(this->player->getBoundingBox(), enemy->getBoundingBox())){
			if(this->player->isRight != enemy->isRight)
				if(this->player->isCurrentState(Player::PStates::ATTACK) || this->player->isCurrentState(Player::PStates::ATTACKMOVING)){
					
					if(enemy->life > 0 && this->player->canAttack){
						enemy->life -= this->player->attackStrength;
						this->player->canAttack = false;
					}
					// Log(DEBUG) << "Enemy Life = " << enemy->life;

					if(enemy->life <= 0)
						enemy->changeState(Enemy::EStates::DEAD);
				}
		}
	}

	//Saving the game state
	for(int j = 0; j < this->NUMBER_OF_CHECKPOINTS; ++j){
		if(!this->checkpointsVisited[j] && this->player->getBoundingBox().x >= checkpointsX[j] 
				&& this->player->getBoundingBox().x <= checkpointsX[j] + 100 && this->player->getBoundingBox().y >= checkpointsY[j]
				&& this->player->getBoundingBox().y <= checkpointsY[j] + 200){
			this->checkpoints[j] = Game::instance().getResources().get("res/images/checkpoint_visited.png");
			Game::instance().getSaves().saveLevel(2, this->player, this->enemies, Game::instance().currentSlot);
			this->checkpointsVisited[j] = true;
		}	
	}
}

void LevelTwo::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	for(int j = 0; j < this->NUMBER_OF_CHECKPOINTS; ++j){
		this->checkpoints[j]->render(this->checkpointsX[j] - cameraX, this->checkpointsY[j] - cameraY);
	}

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	this->playerHud->render();

	for(auto enemy : this->enemies){
		enemy->render(cameraX, cameraY);
	}

	// Render all the entities in the list.
	for(auto entity : this->entities){
        entity->render(cameraX, cameraY);
	}

	for (unsigned int i = 0; i < NUMBER_ITEMS; i++){
		if(this->image != nullptr && caughtItems[i] == false){
			
			this->image->Sprite::render((items[0][i]+60) - cameraX, ((items[1][i]) - cameraY));
		
		}
	}
}

