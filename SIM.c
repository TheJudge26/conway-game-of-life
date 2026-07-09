#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

Uint32 color_white = 0xffffffff;
Uint32 color_gray = 0x0f0f0f0f;
Uint32 color_black = 0x00000000;
int surface_width = 900;
int surface_height=600;
int cell_width=30;
int line_width=2;

void draw_cell(SDL_Surface* surface,int cell_x, int cell_y, int cell_value){

    int pixel_x=cell_x*cell_width;
    int pixel_y=cell_y*cell_width;
    Uint32 color = cell_value == 0 ? color_black : color_white;

    SDL_Rect cell_rect = (SDL_Rect){ pixel_x,pixel_y,cell_width,cell_width};
    SDL_FillRect(surface, &cell_rect, color);
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

void draw_game_matrix(SDL_Surface* surface,int rows,int columns,int game_matrix[]){

     for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){

            int cell_value = game_matrix[j + columns * i];
            draw_cell(surface,j,i,cell_value);

        };
    };
}

void init_game_matrix(int rows, int columns, int game_matrix[]){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){

            game_matrix[j + columns * i]= rand() % 2;

        };
    };
    
}

int count_neighbors (int i, int j, int row_count, int column_count, int game_matrix[]){
    
    int neighbor_counter = 0;
    //left
    if (j > 0)
    {
    
        neighbor_counter += game_matrix[j-- + column_count * i];

    }
    //right
    if (column_count - 1 )
    {
        neighbor_counter += game_matrix[j++ + column_count * i];
    }
    //above
    if (i > 0)
    {
        neighbor_counter += game_matrix[j + column_count * i--];
    }
    //above left
    if (i > 0 && j > 0)
    {
        neighbor_counter += game_matrix[j-- + column_count * i--];
    }
    //above right
    if (i > 0 && j < (column_count - 1))
    {
        neighbor_counter += game_matrix[j++ + column_count * i--];
    }
    //below
    if (i < (row_count - 1))
    {
        neighbor_counter += game_matrix[j + column_count * i++];
    }
    //below left
    if (i < (row_count - 1) && j > 0)
    {
        neighbor_counter += game_matrix[j-- + column_count * i--];
    }
    //below right
    if (i < (row_count) && j < (column_count - 1))
    {
        neighbor_counter += game_matrix[j++ + column_count * i++];
    }
    
    
    
    return neighbor_counter ;
}

void sim_step(int rows, int columns, int game_matrix[]){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){

            int neighbor_count = count_neighbors(i, j, rows, columns, game_matrix);

        };
    };

}

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);

    char* window_title="Conway's Game Of Life";

    int columns=surface_width /cell_width;
    int rows=surface_height / cell_width;

    SDL_Window* window = SDL_CreateWindow(window_title,  SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, surface_width, surface_height, 0);
    
    SDL_Surface* surface= SDL_GetWindowSurface(window);

    int row_count = surface_height / cell_width;
    int column_count = surface_width / cell_width;
    int game_matrix[row_count * column_count];
    
    
    init_game_matrix(row_count, column_count, game_matrix);
    int sim_on=1;
    SDL_Event event;
    while (sim_on)
    {
        while (SDL_PollEvent(&event))
        {
                if (event.type == SDL_QUIT)
            {
                sim_on=0;
            }
        }
        sim_step(row_count, column_count, game_matrix);
        draw_game_matrix(surface, row_count, column_count, game_matrix);
        draw_grid(surface , columns , rows);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000);
    }

    return 0;
}