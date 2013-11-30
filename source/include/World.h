#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "Sprite.h"
#include "tmxloader/MapLoader.h"
#include "Movable.h"
#include "Player.h"
#include "Sprite.h"
#include "Tile.h"
#include "Collectable.h"
#include "ActionHandler.h"
#include "Enemy.h"

class World : ActionHandler {

	public:

	World(Player *player);
	void update(float interval);
	void draw(sf::RenderWindow *screen);
	void cleanup();
	void setMap(std::string level);

	void increaseLife(); 
	void growPlayer();
	void addCoin();
	void addMedallion();
	void addCollectable(Collectable *collectable);

	private: 
	#define MAX_INVENCIBILITY_TIME 5 

	tmx::MapLoader *map;
	Player *player;
	sf::Sprite *bg;
	std::vector<Collectable *> collectables;
	std::vector<Enemy *> enemies;
	std::string level;
	float invencibilityTime;

	void checkCollisions();
	void checkMarkers(Movable *actor);
	void checkCollisionsOnX(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	void checkCollisionsOnY(Movable *actor, std::vector<Tile *> &tiles, sf::Rect<float> &movement);
	Tile* getTile(int row, int col, Layer layer_index);
	void getTilesOnPath(sf::Rect<float> movement, std::vector<Tile*> &tiles);
	void checkCollectables();
	void checkPlayerEnemies();
	void restart();

	void loadCollectables();
	Collectable* makeCollectable(tmx::MapObject *obj);
	
};

#endif
