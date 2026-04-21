#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define COUNT 100

int numbers[COUNT];

typedef struct {
    bool swapped;
    int i,j; //bar that swapped
    bool sort_done;
} SortStatus;

void draw_bars(SortStatus status){
    for (int i = 0; i < COUNT; ++i) {
        int value = numbers[i];
        int bar_height = value*HEIGHT*0.75 / COUNT;

        Color color = WHITE;

        if(status.sort_done){
            color = DARKPURPLE;
        }

        else if (status.swapped  && (i == status.i || i == status.j)){
            color = RED;
        }
        DrawRectangle( ((float)i/COUNT)*WIDTH, HEIGHT*0.75-bar_height, WIDTH/COUNT-5, bar_height, color);
    }
}

void swap(int i, int j){
    int tmp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = tmp;
}

void init_numbers(){
    for (int i = 0; i < COUNT; ++i) {
        numbers[i] = i;
    }
    //fisher yates shuffer
    for (int i = COUNT - 1; i >= 0; i--){
        int j = rand() % (i + 1); //generate a random num between 0 and 1

        //swapping
        swap(i,j);        
    }
}

SortStatus sort_step(){
    static int i = 0; // i = current index
    static SortStatus status = (SortStatus){false,0,1,false};
    static bool any_swap_during_sweep = false;

    status.i = i;
    status.j = i+1;
    if(i<COUNT -1){
        int current_value = numbers[i];
        int next_value = numbers[i+1];
        if(current_value > next_value){
            swap(i,i+1);
            status.swapped = true;
            any_swap_during_sweep = true;
        }else{
            status.swapped = false;
        }
        i++;
    }else{
        if(!any_swap_during_sweep){
            //done
            status.sort_done = true;
        }
        i = 0; //reacg the end of array -> go back to 0 and sort again
        any_swap_during_sweep = false; 
    }     
    // SortStatus status = (SortStatus) {swapped, i, i+1, done};
    return status;

    // for (int i = 0; i < COUNT; i++){
    //     bool swapped = false;
    //     for (int j = 0; j < COUNT - i -1; j++){
    //         if (numbers[j] > numbers[j+1]){
    //             swap(j,  j +1);
    //             swapped = true;
    //         }
    //     }
    //     if(swapped == false)
    //         break;
    // }
}


int main(){
    init_numbers();

    InitWindow(WIDTH, HEIGHT, "Bubble Sorting VIsualizer");
    SetTargetFPS(COUNT*5);
    SortStatus status;
    while (!WindowShouldClose()) {
        if(status.sort_done != true){
            status = sort_step();
        }
        BeginDrawing();
        
        ClearBackground(BLACK);
        draw_bars(status);
        EndDrawing(); 
    }

    CloseWindow();
}