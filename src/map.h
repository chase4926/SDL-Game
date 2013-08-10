//
// map.h
//

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <fstream>
#include "SDL/SDL.h"
#include "constants.h"

class Tile {
  public:
    SDL_Surface * image_pointer;
    //int x, y;
    SDL_Rect box;
    float z;
    
    Tile(SDL_Surface*, int, int, float);
    
    void draw();
};

class Player {
  public:
    SDL_Rect box;
    SDL_Surface * image_pointer;
    
    void draw();
};

class Map {
  private:
    std::vector<Tile> tiles_vector;
    Player player;
  public:
    Map();
    
    void move_player(int, int);
    
    void center_camera();
    
    void load_map(std::string);
    
    void draw();
};

#endif

