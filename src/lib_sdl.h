//
// lib_sdl.h
//

#ifndef LIB_SDL_H
#define LIB_SDL_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

#include "lib_misc.h"
#include "constants.h"

SDL_Surface *load_image( std::string );

void apply_surface( int, int, SDL_Surface*, SDL_Surface* );

bool check_collision(SDL_Rect A, SDL_Rect B);

struct Z_Ordered_Image_Pointer {
  float z;
  int x, y;
  SDL_Surface* image_pointer;
};

class CompareZOrderedImagePointer {
  public:
    bool operator()(Z_Ordered_Image_Pointer&, Z_Ordered_Image_Pointer&);
};

class Image_loader {
  private:
    std::vector<SDL_Surface*> image_pointer_vector;
    std::map<std::string, int> image_index_map;
  public:
    ~Image_loader();
    
    void add_image(std::string);
    
    SDL_Surface* get_image(std::string);
};

class Music {
    Mix_Music *music_pointer;
  public:
    Music(std::string);
    
    void play(int);
    
    void stop();
};

class Timer {
  private:
    int starting_tick, paused_tick;
    bool started, paused;
  public:
    Timer();
    
    void start();
    
    void pause();
    
    void unpause();
    
    int get_ticks();
};


extern SDL_Surface *screen;
extern SDL_Rect camera_rect;
extern std::priority_queue<Z_Ordered_Image_Pointer, std::vector<Z_Ordered_Image_Pointer>, CompareZOrderedImagePointer> z_order_pq;
extern Image_loader image_loader;

#endif

