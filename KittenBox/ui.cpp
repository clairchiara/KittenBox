#include <SDL2/SDL.h>
#include "game.h"

class UI {
public:

  UI(Game * _game){
	  game = _game;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "KittenBox");

    texture_loading_surface = SDL_LoadBMP("kitten.bmp");
    kitten = SDL_CreateTextureFromSurface(renderer, texture_loading_surface);
    SDL_FreeSurface(texture_loading_surface); 
  }

  void update(){
    draw_background();
    draw_boxes();
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
  }

  void handle_events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch(event.type){
      case SDL_QUIT:
	exit(0);
      case SDL_WINDOWEVENT:
	switch(event.window.event){
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
  SDL_Texture* kitten;
	Game* game;

  int width = 800;
  int height = 800;

  void draw_background(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
  }

  void draw_boxes(){
    int length = (width < height ? width : height);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 222);
    for(int y = 0; y < 8; y++){
      for(int x = 0; x < 8; x++){
	SDL_Rect box;
	box.x = (int) (length < width ? (width-length)/2 : 0)+((length/10)+x*(length/10-1));
	box.y = (int) (length < height ? (height-length)/2 : 0)+(length/10)+y*(length/10-1);
	box.w = length/10;
	box.h = length/10;
		  if (game->getBoard()[x][y].containsKitten) {
			  SDL_RenderCopy(renderer, kitten, NULL, &box);
		  }
	SDL_RenderDrawRect(renderer, &box);
      }
    }
  }
};



/* Temporary main() as I work on ui */
//int main(){
//  UI ui;
//
//  while(true){
//    ui.update();
//    ui.handle_events();
//  }
//}
