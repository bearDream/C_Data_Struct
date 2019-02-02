#include "util.h"

// int main(int argc, char const *argv[])
// {
//     for(int i = 0; i < 5; i++){
//         printf("%d \n", get_random(1, 10));
//     }
//     return 0;
// }

int get_rand(int a, int b){
    return (rand() % (b-a+1)) + a;
}