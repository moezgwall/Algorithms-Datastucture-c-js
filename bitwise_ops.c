#include <stdio.h>


// bitwise ops (still learning them) 



// shift to left 
// equivalent to mult by 2 for n times 
// shift to right 
// equivalent to div by 2 for n times 


int shift_left_operand(int number, int n){
    return (number << n);
}
int shift_right_operand(int number, int n){
    return (number >> n);
}
// set the nth bit to be 1 (active)
int set_nth_bit_active(int data , int nth_bit){
    
     return (data |= ( 1 << nth_bit));
}
// for the nth bit to be 0
int clear_nth_bit(int data,int nth_bit){

    return (data &= ~( 1 << nth_bit));    
}

// toggle / flip a bit (on -> off) (off -> on)

int flip_nth_bit(int data, int nth_bit){
    return (data ^= ( 1 << nth_bit));
}





int main(){
    // examples 
    // RGB
    int red = 255; 
    int green = 128;
    int blue = 64;
    // [RRRRRRRR][GGGGGGGG][BBBBBBBB]

    int color = (red << 16) | (green << 8) | blue;
//  hex:color:0x   FF             80          40

    // unpack (extract) the values 

    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = (color & 0xFF);
    printf("Packed color: 0x%06X\n", color);
    printf("Unpacked R=%d, G=%d, B=%d\n", r, g, b);
    // other example 

    int game_mode = 3; // 3 bits
    int game_level = 17; // 5 bits
    int game_speed = 200; // 8 bits
    // packing
    int packed_flags = (game_mode << 13) | (game_level << 8) | game_speed;
    //                  [ mode ]            [level]             [speed]

    // unpacking 

    int gm = (packed_flags >> 13) & 0x7; // 0x7:00000111 3 bits active
    int gl = (packed_flags >> 8) &  0x1F;// 0x1F:00011111 5 bits active
    int gs = (packed_flags & 0xFF); // 0xFF:11111111  8 bits active

    
    printf("\nPacked flags: 0x%04X\n", packed_flags);
    printf("Unpacked -> Mode=%d, Level=%d, Speed=%d\n", gm, gl, gs);



    return 0;
}