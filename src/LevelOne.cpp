#include "LevelOne.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"

LevelOne::LevelOne() :
	Level()
{

}

LevelOne::~LevelOne(){

}

void LevelOne::load(){
	Log(DEBUG) << "Loading level 1...";

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("res/maps/level1.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("res/images/lv1_background.png");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string pathPlayerSpriteSheet = luaLevel1.unlua_get<std::string>(
		"level.player.spriteSheet");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathTempEnemy = luaLevel1.unlua_get<std::string>("level.dummyEnemy");

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the player and the camera.
	Player* lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	Camera* lCamera = new Camera(lPlayer); 
	
	const std::string lPaths[] = {"res/images/hud/player_bar.png", "res/images/hud/player_hp_background.png",
	 "res/images/hud/player_alert1.png"};
	this->hud = new HUD(0, 0, "res/images/hud/player_bar.png", 3);
	this->hud->setSprites(lPaths);

	Enemy* enemy = new Enemy(704.0, 0.0, pathTempEnemy, true, 0.0);
	enemy->setLevelWH(this->width, this->height);
	addEntity(enemy);
	
	// Test text.
	// Text* text = new Text(200.0, 900.0, "res/fonts/KGFeeling22.ttf", 50, "dauphine");
	// addEntity(text);

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);
	setCamera(lCamera);
}

void LevelOne::unload(){
	Log(DEBUG) << "\tUnloading level 1...";
	cleanEntities();
}

void LevelOne::update(const double dt_){
	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// // Updating the entities, using the QuadTree.
	std::vector<CollisionRect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}

	/// @todo Refactor this static Enemy::px, Enemy::py.
	Enemy::px = 4000;//this->player->x;
	Enemy::py = 4000;//this->player->y;

	this->camera->update();

	// Set next level if end is reached.
	if(this->player->reachedLevelEnd){
		Game::instance().setState(Game::GStates::LEVEL_ONE);
	}

}

void LevelOne::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	this->hud->render(this->player->x - cameraX, this->player->y - cameraY);

	// Render all the entities in the list.
	for(auto entity : entities){
        entity->render(cameraX, cameraY);
	}
}

