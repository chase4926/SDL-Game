//
// lib_sdl.cpp
//

#include "lib_sdl.h"

//The surface that will be used for a screen
SDL_Surface *screen = NULL;
SDL_Rect camera_rect = {0, 0, (Uint16)SCREEN_WIDTH, (Uint16)SCREEN_HEIGHT};
//Priority queue that will be used for z ordering
std::priority_queue<Z_Ordered_Image_Pointer, std::vector<Z_Ordered_Image_Pointer>, CompareZOrderedImagePointer> z_order_pq;
//Image loader that will be used for loading all the images
Image_loader image_loader;

SDL_Surface *load_image( std::string filename ) {
  //Temporary storage for the image that's loaded
  SDL_Surface* loadedImage = NULL;
  //The optimized image that will be used
  SDL_Surface* optimizedImage = NULL;
  
  //Load the image
  loadedImage = IMG_Load( filename.c_str() );
  
  //If nothing went wrong in loading the image
  if ( loadedImage != NULL ) {
    //Create an optimized image
    optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
    //Free the old image
    SDL_FreeSurface( loadedImage );
  }
  //Return the optimized image
  return optimizedImage;
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) {
  //Make a temporary rectangle to hold the offsets
  SDL_Rect offset;
  //Give the offsets to the rectangle
  offset.x = x;
  offset.y = y;
  //Blit the surface
  SDL_BlitSurface( source, NULL, destination, &offset );
}


bool check_collision(SDL_Rect A, SDL_Rect B) {
  if (bounding_box_test(A.x, A.y, A.w, A.h, B.x, B.y, B.w, B.h)) {
    return true;
  } else {
    return false;
  }
}

// CompareZOrderedImagePointer class functions
bool CompareZOrderedImagePointer::operator()(Z_Ordered_Image_Pointer& z1, Z_Ordered_Image_Pointer& z2) { // Returns true if z1 should be drawn before z2
  if (z1.z > z2.z) {
    return true;
  } else {
    return false;
  }
}

// Image_loader class functions
Image_loader::~Image_loader() {
  for(std::vector<int>::size_type i = 0; i != image_pointer_vector.size(); i++) {
    SDL_FreeSurface(image_pointer_vector[i]);
  }
}

void Image_loader::add_image(std::string filename) {
  // Only load the image if it isn't already loaded
  // Not doing this could cause a memory leak
  if (image_index_map.find(filename) == image_index_map.end()) {
    image_pointer_vector.push_back(load_image(filename));
    image_index_map[filename] = image_pointer_vector.size() - 1;
  }
}

SDL_Surface* Image_loader::get_image(std::string filename) {
  add_image(filename); // Load the image if it isn't already loaded
  return image_pointer_vector[image_index_map[filename]];
}

// Music class functions
Music::Music(std::string filename) {
  music_pointer = Mix_LoadMUS(filename.c_str());
}

void Music::play(int loop) {
  //If there is no music playing
  if( Mix_PlayingMusic() == 0 ) {
    //Play the music
    Mix_PlayMusic( music_pointer, loop );
  }
}

void Music::stop() {
  //Stop the music
  if( Mix_PlayingMusic() == 0 ) {
    Mix_HaltMusic();
  }
}

// Timer class functions
Timer::Timer() {
  starting_tick = 0;
  paused_tick = 0;
  started = false;
  paused = false;
}

void Timer::start() {
  started = true;
  starting_tick = SDL_GetTicks();
}

void Timer::pause() {
  paused = true;
  paused_tick = SDL_GetTicks();
}

void Timer::unpause() {
  paused = false;
  starting_tick = SDL_GetTicks() - (paused_tick - starting_tick);
}

int Timer::get_ticks() {
  // Return -1 if stopped, -2 if paused
  if (!started) {
    return -1;
  } else if (paused) {
    return -2;
  } else {
    return SDL_GetTicks() - starting_tick;
  }
}

