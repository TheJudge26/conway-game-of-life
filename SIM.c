#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL2/SDL.h>

Uint32 color_white = 0xffffffff;
Uint32 color_gray = 0x0f0f0f0f;
int surface_width = 900;
int surface_height=600;
int cell_width=30;
int line_width=2;

void draw_cell(SDL_Surface* surface,int cell_x, int cell_y){

    int pixel_x=cell_x*cell_width;
    int pixel_y=cell_y*cell_width;

    SDL_Rect cell_rect = (SDL_Rect){ pixel_x,pixel_y,cell_width,cell_width};
    SDL_FillRect(surface, &cell_rect, color_white);
}

void draw_grid(SDL_Surface* surface , int columns , int rows){

    for (int i = 0; i < rows; i++)
    {
        SDL_Rect line = (SDL_Rect) {0, i*cell_width, surface_width, line_width};

        SDL_FillRect (surface, &line ,color_gray);
    }
    
    for (int i = 0; i < columns; i++)
    {
        SDL_Rect line = (SDL_Rect) {i*cell_width, 0, line_width, surface_height};

        SDL_FillRect (surface, &line ,color_gray);
    }
    

}

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);

    char* window_title="Conway's Game Of Life";

    int columns=surface_width /cell_width;
    int rows=surface_height / cell_width;

    SDL_Window* window = SDL_CreateWindow(window_title,  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, surface_width, surface_height, 0);
    
    SDL_Surface* surface= SDL_GetWindowSurface(window);
    
    int cell_x=10;
    int cell_y=6;
    draw_cell(surface, cell_x,cell_y);
    draw_grid(surface , columns , rows);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    return 0;
}