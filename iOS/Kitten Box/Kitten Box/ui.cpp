#include <cmath>
#include <iostream>

#include "ui.h"

UI::UI(Game* _game) {
  game_loaded = false;
  game = _game;
  width = 1000;
  height = 1000;
  insideWidth = 850;
  insideHeight = 850;
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
  
  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &window, &renderer);
  SDL_SetWindowTitle(window, "KittenBox");
  
  texture_loading_surface = SDL_LoadBMP("kitten.bmp");
  kitten_texture = SDL_CreateTextureFromSurface(renderer, texture_loading_surface);
  SDL_FreeSurface(texture_loading_surface);
  texture_loading_surface = SDL_LoadBMP("redx.bmp");
  cross_texture = SDL_CreateTextureFromSurface(renderer, texture_loading_surface);
  SDL_FreeSurface(texture_loading_surface);
  
  
  colours[empty] = {92, 92, 92, 255};
  colours[returned] = {0xff, 0x56, 0xc1, 255};
  colours[captured] = {0x56, 0xff, 0xd2, 0xff};
  colours[4] = {41, 128, 77, 255};
  colours[5] = {0, 5, 194, 255};
  colours[6] = {52, 90, 227, 255};
  colours[7] = {168, 220, 228, 255};
  colours[8] = {29, 170, 161, 255};
  colours[9] = {255, 20, 137, 255};
  colours[10] = {170, 31, 31, 255};
  colours[11] = {144, 199, 45, 255};
  colours[12] = {245, 227, 183, 255};
  colours[13] = {218, 176, 124, 255};
  colours[14] = {137, 102, 215, 255};
  colours[15] = {255, 221, 2, 255};
  colours[16] = {255, 155, 2, 255};
  colours[17] = {255, 60, 1, 255};
  colours[18] = {109, 146, 241, 255};
  colours[19] = {255, 174, 186, 255};
  
  showKittensButton = new SDL_Rect;
  newGameButton = new SDL_Rect;
  game_loaded = true;
}

void UI::update() {
  draw_background();
  draw_boxes_and_triangles();
  SDL_RenderPresent(renderer);
  SDL_Delay(20);
}

void UI::handle_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            width = event.window.data1;
            insideWidth = width * 0.85;
            height = event.window.data2;
            insideHeight = height * 0.85;
            break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        handle_mouse_click(event.button.x, event.button.y);
        //      std::cout << event.button.x << " " << event.button.y << std::endl;
    }
  }
}

//TODO: complete loading_screen()

void UI::loading_screen() {
  SDL_Rect box;
  SDL_SetRenderDrawColor(renderer, 0xf8, 0xb5, 0xcb, 255);
  box.x = 0;
  box.y = 0;
  box.w = width;
  box.h = height;
  SDL_RenderDrawRect(renderer, &box);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_Delay(2000);
}

void UI::draw_background() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void UI::draw_boxes_and_triangles() {
  OutsideArea triangle_state;
  SDL_Colour tri_col = {0, 0, 0, 255}; //Temporarily store colour for each triangle
  length = (insideWidth < insideHeight ? insideWidth : insideHeight);
  
  for (int y = 0; y < 8; y++) { //8 x 8 grid of boxes
    SDL_Rect box;
    for (int x = 0; x < 8; x++) {
      box.x = (int) (length < insideWidth ?
                     ((insideWidth - length) / 2) : 0) + ((length / 10) + x * (length / 10 - 1));
      box.y = (int) (length < insideHeight ?
                     ((insideHeight - length) / 2) : 0) + ((length / 10) + y * (length / 10 - 1));
      box.w = length/10;
      box.h = length/10;
      if (game->getBoard()[x][y].containsKitten && game->areKittensShown()) {
        SDL_RenderCopy(renderer, kitten_texture, NULL, &box); //Draw kitten texture inside box
      }
      if (game->isPlayerSelected(x, y)) {
        SDL_RenderCopy(renderer, cross_texture, NULL, &box); //Draw cross texture inside box
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 227); //Boxes colour
      SDL_RenderDrawRect(renderer, &box);
      
      if (x == 0) {
        boxes_start_x = box.x;
        half_box_width = box.w/2;
        triangle_side_length = half_box_width-6;
        triangle_height = (int) sqrt(pow(triangle_side_length, 2.0) + pow(triangle_side_length/2.0, 2.0));
      } else if (x == 7) {
        boxes_end_x = box.x + box.w;
      }
      if (y == 0) { //Draw top triangle for this column
        triangle_state = game->getOutsideArea()[TOP][x];
        tri_col = colours[triangle_state.state + triangle_state.deviation];
        
        SDL_SetRenderDrawColor(renderer, tri_col.r, tri_col.g, tri_col.b, tri_col.a);
        
        triangle[0] = {box.x + half_box_width, box.y - 3};
        triangle[1] = {box.x + 3, triangle[0].y - triangle_height};
        triangle[2] = {box.x + (half_box_width * 2) - 3, triangle[1].y};
        triangle[3] = triangle[0];
        triangle[4] = {triangle[0].x, triangle[0].y - 1};
        triangle[5] = {triangle[1].x + 1, triangle[1].y + 1};
        triangle[6] = {triangle[2].x - 1, triangle[2].y + 1};
        triangle[7] = {triangle[4].x, triangle[4].y};
        SDL_RenderDrawLines(renderer, triangle, 8);
        store_triangle_boundaries(triangle, TOP, x);
        
      } else if (y == 7) { //Draw bottom triangle for this column
        triangle_state = game->getOutsideArea()[BOTTOM][x];
        tri_col = colours[triangle_state.state + triangle_state.deviation];
        
        SDL_SetRenderDrawColor(renderer, tri_col.r, tri_col.g, tri_col.b, tri_col.a);
        
        triangle[0] = {box.x + half_box_width, box.y + box.h + 3};
        triangle[1] = {box.x + 3, box.y + box.h + triangle_height + 3};
        triangle[2] = {box.x + (half_box_width * 2) - 3, box.y + box.h + triangle_height + 3};
        triangle[3] = triangle[0];
        triangle[4] = {triangle[0].x, triangle[0].y + 1};
        triangle[5] = {triangle[1].x + 1, triangle[1].y - 1};
        triangle[6] = {triangle[2].x - 1, triangle[2].y - 1};
        triangle[7] = {triangle[4].x, triangle[4].y};
        SDL_RenderDrawLines(renderer, triangle, 8);
        store_triangle_boundaries(triangle, BOTTOM, x);
      }
    }
    //Draw showKitten button
    if (width > height) {
      // Draw on the right
      showKittensButton->x = width * 0.85;
      showKittensButton->y = height * 0.15;
      showKittensButton->w = box.w;
      showKittensButton->h = box.h;
    } else {
      // Draw at the bottom
      showKittensButton->x = width * 0.15;
      showKittensButton->y = height * 0.85;
      showKittensButton->w = box.w;
      showKittensButton->h = box.h;
    }
    //Draw newGame button
    if (width > height) {
      // Draw on the right
      newGameButton->x = width * 0.85;
      newGameButton->y = height * 0.85;
      newGameButton->w = box.w;
      newGameButton->h = box.h;
    } else {
      // Draw at the bottom
      newGameButton->x = width * 0.85;
      newGameButton->y = height * 0.85;
      newGameButton->w = box.w;
      newGameButton->h = box.h;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 227); //Button colour
    SDL_RenderDrawRect(renderer, showKittensButton);
    SDL_RenderDrawRect(renderer, newGameButton);
    //Draw left triangle for this row
    triangle_state = game->getOutsideArea()[LEFT][y];
    tri_col = colours[triangle_state.state + triangle_state.deviation];

    SDL_SetRenderDrawColor(renderer, tri_col.r, tri_col.g, tri_col.b, tri_col.a);
    
    triangle[0] = {boxes_start_x - 3, box.y + half_box_width};
    triangle[1] = {triangle[0].x - triangle_height, box.y + 3};
    triangle[2] = {triangle[1].x, box.y + box.w - 3};
    triangle[3] = triangle[0];
    triangle[4] = {triangle[0].x - 1, triangle[0].y};
    triangle[5] = {triangle[1].x + 1, triangle[1].y + 1};
    triangle[6] = {triangle[2].x + 1, triangle[2].y - 1};
    triangle[7] = {triangle[4].x, triangle[4].y};
    SDL_RenderDrawLines(renderer, triangle, 8);
    store_triangle_boundaries(triangle, LEFT, y);
    
    //Draw right triangle for this row
    triangle_state = game->getOutsideArea()[RIGHT][y];
    tri_col = colours[triangle_state.state + triangle_state.deviation];
    
    SDL_SetRenderDrawColor(renderer, tri_col.r, tri_col.g, tri_col.b, tri_col.a);
    
    triangle[0] = {boxes_end_x + 3, box.y + half_box_width};
    triangle[1] = {triangle[0].x + triangle_height, box.y + 3};
    triangle[2] = {triangle[1].x, box.y + box.w - 3};
    triangle[3] = triangle[0];
    triangle[4] = {triangle[0].x + 1, triangle[0].y};
    triangle[5] = {triangle[1].x - 1, triangle[1].y + 1};
    triangle[6] = {triangle[2].x - 1, triangle[2].y - 1};
    triangle[7] = {triangle[4].x, triangle[4].y};
    SDL_RenderDrawLines(renderer, triangle, 8);
    store_triangle_boundaries(triangle, RIGHT, y);
  }
}

bool UI::on_which_side_of_triangle_edge(int x, int y, SDL_Point v1, SDL_Point v2) {
  return (x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (y - v2.y) < 0.0f;
}

void UI::handle_mouse_click(int x, int y) {
  bool side_of_edge [3];
  for (int p = 0; p < 4; p++) { //Loop through members of Position enum
    for (int b = 0; b < 8; b++) { //Loop through the 8 buttons at each position
      side_of_edge[0] = on_which_side_of_triangle_edge(x, y, button_boundaries[p][b][0], button_boundaries[p][b][1]);
      side_of_edge[1] = on_which_side_of_triangle_edge(x, y, button_boundaries[p][b][1], button_boundaries[p][b][2]);
      side_of_edge[2] = on_which_side_of_triangle_edge(x, y, button_boundaries[p][b][2], button_boundaries[p][b][0]);
      
      if ((side_of_edge[0] == side_of_edge[1]) && (side_of_edge[1] == side_of_edge[2])) {
        std::cout << "Clicked " << p << " " << b << std::endl;
        game->clickedArea(b, (Position) p);
      }
    }
  }
  if (x > showKittensButton->x && x < showKittensButton->x + showKittensButton->w
      && y > showKittensButton->y && y < showKittensButton->y + showKittensButton->h) {
    if (game->areKittensShown()) game->hideKittens();
    else game->showKittens();
  }
  if (x > newGameButton->x && x < newGameButton->x + newGameButton->w
      && y > newGameButton->y && y < newGameButton->y + newGameButton->h) {
    delete game;
    game = new Game;
  }
  int _width = length / 10;
  int _boxes_start_x = boxes_start_x;
  int _boxes_end_x = boxes_end_x;
  if (x >= _boxes_start_x && x <= _boxes_end_x && y >= _boxes_start_x - _width && y <= _boxes_end_x - _width) {
    std::cout << "INSIDE " << std::time(0) << "\n";
    int _x = floorf((x - _boxes_start_x) / _width);
    int _y = floorf((y - _boxes_start_x + _width) / _width);
    game->setPlayerSelected(_x, _y, !game->isPlayerSelected(_x, _y));
  }
}

inline void UI::store_triangle_boundaries(SDL_Point* triangle, Position position, int button) {
  button_boundaries[position][button][0] = triangle[0];
  button_boundaries[position][button][1] = triangle[1];
  button_boundaries[position][button][2] = triangle[2];
}

bool UI::is_game_loaded() {
  return game_loaded;
}
