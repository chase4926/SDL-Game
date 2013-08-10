//
// map.cpp
//

#include "map.h"
#include "lib_sdl.h"
#include "lib_misc.h"
#include <iostream>

// Tile class functions
Tile::Tile(SDL_Surface* new_image_pointer, int x_coord, int y_coord, float z_coord) {
  image_pointer = new_image_pointer;
  box.x = x_coord;
  box.y = y_coord - ((*image_pointer).h - 32);
  box.w = (*image_pointer).w;
  box.h = (*image_pointer).h;
  z = z_coord + y_coord; // Makes the tiles below be on top of the tiles above
}

void Tile::draw() {
  if ((image_pointer != NULL) and (check_collision(camera_rect, box))) {
    //zoip = Z_Ordered_Image_Pointer
    Z_Ordered_Image_Pointer temp_zoip;
    temp_zoip.x = box.x - camera_rect.x;
    temp_zoip.y = box.y - camera_rect.y;
    temp_zoip.z = z;
    temp_zoip.image_pointer = image_pointer;
    z_order_pq.push(temp_zoip);
  }
}


//Player class functions
void Player::draw() {
  if (image_pointer != NULL) {
    Z_Ordered_Image_Pointer temp_zoip;
    temp_zoip.x = box.x - camera_rect.x;
    temp_zoip.y = box.y - camera_rect.y;
    temp_zoip.z = box.y + 32;
    temp_zoip.image_pointer = image_pointer;
    z_order_pq.push(temp_zoip);
  }
}


// Map class functions
Map::Map() {
  player.box.x = 0;
  player.box.y = 0;
  player.image_pointer = image_loader.get_image("../images/character/character.png");
  player.box.w = (*player.image_pointer).w;
  player.box.h = (*player.image_pointer).h;
  center_camera();
}

void Map::move_player(int rel_x, int rel_y) {
  player.box.x += rel_x;
  player.box.y += rel_y;
  center_camera();
}

void Map::center_camera() {
  camera_rect.x = player.box.x - ((SCREEN_WIDTH / 2) - (player.box.w / 2));
  camera_rect.y = player.box.y - ((SCREEN_HEIGHT / 2) - (player.box.h / 2));
}

void Map::load_map(std::string filename) {
  std::ifstream infile(filename);
  // Initialize some variable to hold information as the file is read
  int x = 0, y = 0;
  float z = 0;
  std::string imagename = "";
  std::string line;
  while (std::getline(infile, line)) {
    // Reset the imagename variable
    imagename = "../images/";
    std::vector<std::string> string_parts = split_string(line, ',');
    imagename.append(string_parts[0]);
    x = atoi(string_parts[1].c_str());
    y = atoi(string_parts[2].c_str());
    z = (float)(atoi(string_parts[3].c_str()));
    z *= 32;
    tiles_vector.push_back(Tile(image_loader.get_image(imagename), x, y, z));
    //for (std::string &part : string_parts) {
      //std::cout << "\"" << part << "\"\n";
    //}
  }
}

void Map::draw() {
  for (Tile &tile : tiles_vector) {
    tile.draw();
  }
  player.draw();
}

