#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"
#include "count_friends_of_ten.c"

int main() {
    int N = 100;
    int M = 100;
    int friends_of_ten;
    srand (time(NULL));

    int **v = allocate_2D_int(M, N);
   
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++){
            v[i][j] = rand() % (9 + 1 - 0) + 0;
        }
    }

    friends_of_ten = count_friends_of_ten(M, N, v);
    /*
    //Optional print for matrix
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%i ", v[i][j]);
        }
        printf("\n");
    }
    */
    printf("Friends of ten: %i\n", friends_of_ten);

    free(v[0]);
    free(v);
    return 0;
}