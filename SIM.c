#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL2/SDL.h>

draw_grid(int cell_width , int columns , int rows){

    

}

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);

    char* window_title="Conway's Game Of Life";
    int width = 900;
    int height = 600;

    int cell_width = 10;
    int columns=width /cell_width;
    int rows=height / cell_width;

    SDL_Window* window = SDL_CreateWindow(window_title,  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, width, height, 0);
    
    SDL_Surface* surface= SDL_GetWindowSurface(window);

    SDL_Rect rect = (SDL_Rect) {30,40,50,60};
    Uint32 color_white = 0xffffffff;
    SDL_FillRect (surface, &rect ,color_white);
    
    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);

    draw_grid(cell_width , columns , rows);

    return 0;
}