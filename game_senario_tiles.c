#include <stdio.h>


// game tile based senario 
// a simple use case for bitwise ops 




#define TILE_WALKABLE (1 << 0) // 0001
#define TILE_WATER (1 << 1) // 0010
#define TILE_LAVA ( 1 << 2) // 0100
#define TILE_TREASURE (1 << 3) // 1000


#define GAME_WIDTH 5
#define GAME_HEIGHT 5

#define BYTE unsigned char

void print_game_map(BYTE map[GAME_HEIGHT][GAME_WIDTH],int player_xpos, int player_ypos){

    for (int y = 0 ; y < GAME_HEIGHT; y++){
        for (int x = 0; x  < GAME_WIDTH; x++){

            if (x == player_xpos && y == player_ypos){
                printf("P "); // our player
            }else if (map[y][x] & TILE_LAVA){
                printf("L "); // lava 
            }else if (map[y][x] & TILE_TREASURE){
                printf("T "); // treasure
            }else if (map[y][x] & TILE_WATER){
                printf("W "); // water
            }else if (map[y][x] & TILE_WALKABLE){
                printf(". "); // can walk
            }else{
                printf("# "); // block
            }

        }

        printf("\n");

    }

}

int player_move(BYTE tile){
    return (tile & TILE_WALKABLE);
}

int main(){

    BYTE map[GAME_HEIGHT][GAME_WIDTH] = {

        {TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE},
        {TILE_WALKABLE, TILE_LAVA,     TILE_WALKABLE, TILE_TREASURE, TILE_WALKABLE},
        {TILE_WALKABLE, TILE_WALKABLE, TILE_WATER,    TILE_WALKABLE, TILE_WALKABLE},
        {TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE},
        {TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE, TILE_WALKABLE},
    };

    // intial player postion 
    int p_x = 0;
    int p_y = 0;
    // print the map
    print_game_map(map,p_x,p_y);

    for (int i = 0 ; i < 2; i++){
        int mov_x = p_x + 1;
        int mov_y = p_y + 2;
        if (player_move(map[mov_y][mov_x])){
            p_x = mov_x;
            printf("moved to( %d,%d) \n",p_x,p_y);
        }else{
            printf("cannot move \n");
            break;
        }

    }

    printf("\n updated map\n");
    print_game_map(map,p_x,p_y);


    return 0;


}
