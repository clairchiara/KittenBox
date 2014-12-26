#include <SDL2/SDL.h>
#include <cmath>

#include "game.h"

class UI {
public:
  UI(Game* _game) {
    game = _game;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_SetWindowTitle(window, "KittenBox");

    texture_loading_surface = SDL_LoadBMP("kitten.bmp");
    kitten_texture = SDL_CreateTextureFromSurface(renderer, texture_loading_surface);
    SDL_FreeSurface(texture_loading_surface); 
  }

  void update() {
    draw_background();
    draw_boxes();
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
  }

  void handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	exit(0);
      case SDL_WINDOWEVENT:
	switch (event.window.event) {
	case SDL_WINDOWEVENT_SIZE_CHANGED:
	  width = event.window.data1;
	  height = event.window.data2;
	  break;
	}
      }
    }
  }

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* texture_loading_surface;
  SDL_Texture* kitten_texture;
  Game* game;

  int width = 800;
  int height = 800;

  void draw_background() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
  }

  void draw_boxes() {
    SDL_Point triangle [4];
    int half_box_width;
    int triangle_side_length;
    int triangle_height;
    int length = (width < height ? width : height);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 222); //Draw boxes in dark gray
    for (int y = 0; y < 8; y++) { //8 x 8 grid of boxes
      for (int x = 0; x < 8; x++) {
	SDL_Rect box;
	box.x = (int) (length < width ? (width-length)/2 : 0)+((length/10)+x*(length/10-1));
	box.y = (int) (length < height ? (height-length)/2 : 0)+(length/10)+y*(length/10-1);
	box.w = length/10;
	box.h = length/10;
	if (game->getBoard()[x][y].containsKitten) {
	  SDL_RenderCopy(renderer, kitten_texture, NULL, &box); //Draw kitten texture inside box
	}
	SDL_RenderDrawRect(renderer, &box);

	if (x == 0) {
	  half_box_width = box.w/2;
	  triangle_side_length = half_box_width-6;
	  triangle_height = (int) sqrt(pow(triangle_side_length, 2.0) + pow(triangle_side_length/2.0, 2.0));
	}
	if (y == 0) {
	  triangle[0] = {box.x+half_box_width, box.y-3};
	  triangle[1] = {box.x+3, box.y-triangle_height-3};
	  triangle[2] = {box.x+(half_box_width*2)-3, box.y-triangle_height-3};
	  triangle[3] = {box.x+half_box_width, box.y-3};
	  SDL_RenderDrawLines(renderer, triangle, 4);
	} else if(y == 7) {
	  triangle[0] = {box.x+half_box_width, box.y+box.h+3};
	  triangle[1] = {box.x+3, box.y+box.h+triangle_height+3};
	  triangle[2] = {box.x+(half_box_width*2)-3, box.y+box.h+triangle_height+3};
	  triangle[3] = {box.x+half_box_width, box.y+box.h+3};
	  SDL_RenderDrawLines(renderer, triangle, 4);
	}
      }
      
    }
  }
};
