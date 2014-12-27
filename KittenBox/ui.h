#ifndef __KittenBox__ui__
#define __KittenBox__ui__

#include <array>
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

  std::array<std::array<std::array<SDL_Point, 3>, 8>, 4> button_boundaries;
  
  void draw_background();
  
  void draw_boxes_and_triangles();

  bool on_which_side_of_triangle_edge(int x, int y, SDL_Point v1, SDL_Point v2);

  void handle_mouse_click(int x, int y);

  inline void store_triangle_boundaries(SDL_Point* triangle, Position position, int button);
};

#endif
