#ifndef __KittenBox__ui__
#define __KittenBox__ui__

#include <SDL2/SDL.h>

#include "game.h"

class UI {
 public:
  UI(Game* _game);
  
  void update();
  
  void handle_events();
  
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* texture_loading_surface;
  SDL_Texture* kitten_texture;
  Game* game;
  
  int width;
  int height;
  
  void draw_background();
  
  void draw_boxes_and_triangles();
};

#endif
