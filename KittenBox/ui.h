#ifndef __KittenBox__ui__
#define __KittenBox__ui__

#include <array>
#include <SDL2/SDL.h>

#include "game.h"

// GitHub debug

class UI {
 public:
  UI(Game* _game);
  
  void update();
  
  void handle_events();
  
  void loading_screen();
  
  bool is_game_loaded();
  
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* texture_loading_surface;
  SDL_Texture* kitten_texture;
  SDL_Texture* cross_texture;
  SDL_Rect* showKittensButton;
  SDL_Rect* newGameButton;
  Game* game;
  SDL_Colour colours [20];
  
  int width;
  int height;
  int insideWidth;
  int insideHeight;
  SDL_Point triangle [8]; //With 8 points, triangles of double thickness can be drawn
  int half_box_width;
  int triangle_side_length;
  int triangle_height;
  int length;
  int boxes_start_x, boxes_end_x; //Used for drawing left and right triangles
  bool game_loaded;

  std::array<std::array<std::array<SDL_Point, 3>, 8>, 4> button_boundaries;
  
  void draw_background();
  
  void draw_boxes_and_triangles();

  bool on_which_side_of_triangle_edge(int x, int y, SDL_Point v1, SDL_Point v2);

  void handle_mouse_click(int x, int y);

  inline void store_triangle_boundaries(SDL_Point* triangle, Position position, int button);
};

#endif
