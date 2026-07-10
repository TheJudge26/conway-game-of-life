#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

Uint32 color_white = 0xffffffff;
Uint32 color_gray = 0x0f0f0f0f;
Uint32 color_black = 0x00000000;
int surface_width = 900;
int surface_height=600;
int cell_width=10;
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

void rand_game_matrix(int rows, int columns, int game_matrix[]){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){

            game_matrix[j + columns * i]= rand() % 2 && rand() % 2;

        };
    };
    
}

void blank_game_matrix(int rows, int columns, int game_matrix[]){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++){

            game_matrix[j + columns * i]= 0;

        };
    };
    
}

int count_neighbors (int i, int j, int row_count, int column_count, int game_matrix[]){
    
    int neighbor_counter = 0;
    
    // Left
    if (j > 0) neighbor_counter += game_matrix[(j - 1) + column_count * i];
    
    // Right
    if (j < (column_count - 1)) neighbor_counter += game_matrix[(j + 1) + column_count * i];
    
    // Above
    if (i > 0) neighbor_counter += game_matrix[j + column_count * (i - 1)];
    
    // Below
    if (i < (row_count - 1)) neighbor_counter += game_matrix[j + column_count * (i + 1)];
    
    // Above Left
    if (i > 0 && j > 0) neighbor_counter += game_matrix[(j - 1) + column_count * (i - 1)];
    
    // Above Right
    if (i > 0 && j < (column_count - 1)) neighbor_counter += game_matrix[(j + 1) + column_count * (i - 1)];
    
    // Below Left
    if (i < (row_count - 1) && j > 0) neighbor_counter += game_matrix[(j - 1) + column_count * (i + 1)];
    
    // Below Right
    if (i < (row_count - 1) && j < (column_count - 1)) neighbor_counter += game_matrix[(j + 1) + column_count * (i + 1)];
    
    return neighbor_counter;
}
    
 void sim_step(int rows, int columns, int game_matrix[]) {
    
    int temp_matrix[rows * columns];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            
            int neighbor_count = count_neighbors(i, j, rows, columns, game_matrix);
            int current_index = j + columns * i;
            int current_cell_value = game_matrix[current_index];
            
            temp_matrix[current_index] = 0;

            if (current_cell_value == 1) {
                
                if (neighbor_count == 2 || neighbor_count == 3) {
                    temp_matrix[current_index] = 1;
                }
            } else {
                
                if (neighbor_count == 3) {
                    temp_matrix[current_index] = 1;
                }
            }
        }
    }

    for (int i = 0; i < (rows * columns); i++) {
        game_matrix[i] = temp_matrix[i];
    }
}


void set_cell_matrix(Sint32 mouse_x, Sint32 mouse_y, int row_count, int column_count, int game_matrix[]){

    int j = mouse_x / cell_width ;
    int i = mouse_y / cell_width ;
    game_matrix[j + column_count*i]= !game_matrix[j + column_count*i];

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
    
    
    rand_game_matrix(row_count, column_count, game_matrix);
    draw_game_matrix(surface, row_count, column_count, game_matrix);
    draw_grid(surface , columns , rows);
    SDL_UpdateWindowSurface(window);
    int sim_on=1;
    int sim_pause=1;
    SDL_Event event;
    while (sim_on)
    {
        while (SDL_PollEvent(&event))
        {
                if (event.type == SDL_QUIT)
            {
                sim_on=0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    sim_pause = !sim_pause;
                }

                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    rand_game_matrix(row_count, column_count, game_matrix);
                    draw_game_matrix(surface, row_count, column_count, game_matrix);
                    draw_grid(surface , columns , rows);
                    SDL_UpdateWindowSurface(window);
                }

                if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    blank_game_matrix(row_count, column_count, game_matrix);
                    draw_game_matrix(surface, row_count, column_count, game_matrix);
                    draw_grid(surface , columns , rows);
                    SDL_UpdateWindowSurface(window);
                }
                
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                Sint32 mouse_x = event.button.x;
                Sint32 mouse_y = event.button.y;
                set_cell_matrix(mouse_x, mouse_y, row_count, column_count, game_matrix);
                draw_game_matrix(surface, row_count, column_count, game_matrix);
                draw_grid(surface , columns , rows);
                SDL_UpdateWindowSurface(window);
            }
            
            
        }


        if (! sim_pause)
        {
            sim_step(row_count, column_count, game_matrix);
            draw_game_matrix(surface, row_count, column_count, game_matrix);
            draw_grid(surface , columns , rows);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(100);
        }
        else{
            SDL_Delay(200);
        }
    }

    return 0;
}