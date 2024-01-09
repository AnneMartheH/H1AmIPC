#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <math.h>
#define MatrixSize 4096
#define BlockSize 256
//the task dosn`t specify that the matrixes must contains floats so uses ints, but this can easely be changed 

void routine1(int M[MatrixSize][MatrixSize],int O[MatrixSize][MatrixSize]){
    int bi, bj, i, j, k, l;
    struct timespec start_time, end_time; 

    clock_gettime(CLOCK_REALTIME, &start_time);
    for(bi = 0; bi < MatrixSize; bi += BlockSize){
        int k = 0;
        for(bj = 0; bj < MatrixSize; bj += BlockSize){
            int l = 0;
            for(i = bi; i < bi + BlockSize; i++){
                k = 0;
                for(j = bj; j < bj + BlockSize; j++){
                    O[MatrixSize-BlockSize-bi+l][MatrixSize-BlockSize-bj+k] = M[i][j];
                    k +=1;
                }
                l+=1;
            }
        }
    }
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec)/1.0e9);
    printf("routine 1 [time(sec), n , b] = [%.9f, %d, %d] \n", elapsed_time, MatrixSize, BlockSize);
    /*
    printf("M:");
    for(i = 0; i < MatrixSize; i++){
        printf("\n");
        for ( j = 0; j < MatrixSize; j++){
            printf("%d ", M[i][j]);
        }
    }
    printf("\n O:");
    for(i = 0; i < MatrixSize; i++){
        printf("\n");
        for ( j = 0; j < MatrixSize; j++){
            printf("%d ", O[i][j]);
        }
    }*/
    return;
}


void routine2(int M[MatrixSize][MatrixSize],int O[MatrixSize][MatrixSize]){
    int bi, bj, i, j, k, l;
    struct timespec start_time, end_time; 

    clock_gettime(CLOCK_REALTIME, &start_time);
    for(bi = 0; bi < MatrixSize; bi += BlockSize){
        int k = 0;
        for(bj = 0; bj < MatrixSize; bj += BlockSize){
            int l = 0;
            for(i = bi; i < bi + BlockSize; i++){
                k = 0;
                for(j = bj; j < bj + BlockSize; j++){
                    //__builtin_prefetch(&O[MatrixSize-BlockSize-bi+l][MatrixSize-BlockSize-bj+k]);
                    __builtin_prefetch(&M[i+1][j+1]);
                    O[MatrixSize-BlockSize-bi+l][MatrixSize-BlockSize-bj+k] = M[i][j];
                    k +=1;
                }
                l+=1;
            }
        }
    }
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec)/1.0e9);
    printf("routine 2 [time(sec), n , b] = [%.9f, %d, %d] \n", elapsed_time, MatrixSize, BlockSize);
    /*
    printf("M:");
    for(i = 0; i < MatrixSize; i++){
        printf("\n");
        for ( j = 0; j < MatrixSize; j++){
            printf("%d ", M[i][j]);
        }
    }*/
    /*
    printf("\n O imp par:");
    for(i = 0; i < MatrixSize; i++){
        printf("\n");
        for ( j = 0; j < MatrixSize; j++){
            printf("%d ", O[i][j]);
        }
    }*/
    return;
}

int main(){
    int n, i, j;
    int M[MatrixSize][MatrixSize], O[MatrixSize][MatrixSize];

    for (i = 0; i < MatrixSize; ++i) {
        for(j = 0; j < MatrixSize ; j++)
            M[i][j] = (int)(rand()%10);
            O[i][j] = 0;
    }
    routine1(M,O);
    routine1(M,O);
    routine1(M,O);
    routine1(M,O);

    routine2(M,O);
    routine2(M,O);
    routine2(M,O);
    routine2(M,O);
    return 0;
}

