//
// main.cpp
//

#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

#include "lib_misc.h"
#include "lib_sdl.h"
#include "constants.h"
#include "map.h"


//The event structure that will be used
SDL_Event event;
//Array to hold keystates
Uint8 *keystates;

//Last tick
Uint32 last_update_tick = 0;
Uint32 last_draw_tick = 0;
//Current tick
Uint32 current_update_tick = 0;
Uint32 current_draw_tick = 0;


bool shouldRunUpdate() {
  current_update_tick = SDL_GetTicks();
  if (current_update_tick - last_update_tick >= 1000.0f / MAX_UPDATES_PER_SECOND) {
    last_update_tick = current_update_tick;
    return true;
  }
  return false;
}


bool shouldRedrawScreen() {
  current_draw_tick = SDL_GetTicks();
  if ((!CAP_FRAMERATE) or (current_draw_tick - last_draw_tick >= 1000.0f / MAX_FRAMES_PER_SECOND))
    last_draw_tick = current_draw_tick;
    return true;
  return false;
}


bool init(string caption) {
  //Initialize all SDL subsystems
  if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    return false;
  }
  //Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF );
  //If there was an error in setting up the screen
  if ( screen == NULL ) {
    return false;
  }
  //Initialize SDL_mixer
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
    return false;
  }
  //Turn on ogg decoder
  Mix_Init(MIX_INIT_OGG);
  //Set the window caption
  SDL_WM_SetCaption( caption.c_str(), NULL );
  //If everything so far has worked
  return true;
}


void clean_up() {
  //Quit SDL_mixer
  while(Mix_Init(0)) {
    Mix_Quit();
  }
  Mix_CloseAudio();
  //Quit SDL
  SDL_Quit();
}


int main( int argc, char* args[] ) {
  //Initialize
  if (!init("SDL Game")) {
    return 1;
  }
  //Keep the program running until quit == true
  bool quit = false;
  
  //TEST---
  //Music background_music("../music/song1.ogg");
  //background_music.play(-1);
  
  Map map;
  map.load_map("../main_files/test_level.txt");
  //---
  
  
  // Temporary holder of priority queue element
  Z_Ordered_Image_Pointer temp_pq;
  //While the program is still running
  while (!quit) {
    //Handle events
    while ( SDL_PollEvent( &event ) ) {
      if ( event.type == SDL_QUIT ) {
        //Quit the program
        quit = true;
      }
    }
    //Update game events
    if (shouldRunUpdate()) {
      //Get keystate information
      keystates = SDL_GetKeyState(NULL);
      
      if (keystates[SDLK_UP]) {
        map.move_player(0, -3);
      }
      if (keystates[SDLK_DOWN]) {
        map.move_player(0, 3);
      }
      if (keystates[SDLK_LEFT]) {
        map.move_player(-3, 0);
      }
      if (keystates[SDLK_RIGHT]) {
        map.move_player(3, 0);
      }
    }
    //Redraw screen
    if (shouldRedrawScreen()) {
      //Draw black over whole screen - clears the screen unless something is being drawn
      SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );
      //Redraw things
      
      map.draw();
      
      //Go through priority queue and draw lower z levels before upper z levels
      while (! z_order_pq.empty()) {
        temp_pq = z_order_pq.top();
        apply_surface( temp_pq.x, temp_pq.y, temp_pq.image_pointer, screen );
        z_order_pq.pop();
      }
      //Redraw Screen
      SDL_Flip( screen );
    }
  }
  
  // Clean up
  clean_up();
  
  return 0;
}

