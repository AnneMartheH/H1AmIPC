#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <math.h>

void routine1(float A[],float B[], float C[], int n){
    int i, j;
    int avrage = 10;
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_REALTIME, &start_time);
    for(j = 0; j < avrage; j++){
        for( i = 0; i <n ; i++){
            C[i] = A[i] + B[i];
        }
    }
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec)/1.0e9)/avrage;
    /*
    for( i = 0; i <n; i++){
        printf("A[%d] = %f, + B[%d] = %f, gives c[%d] = %f \n", i, A[i], i, B[i], i, C[i]);
        C[i] = A[i] + B[i];
    }*/
    printf("routine 1, serial [time(sec), n] = [%.9f, %d] \n", elapsed_time, n);
}

void routine2(float A[],float B[], float C[], int n){
    int i, j;
    int avrage = 10;
    struct timespec start_time, end_time; 
    
    clock_gettime(CLOCK_REALTIME, &start_time);
    for(j = 0; j < avrage; j++){
        for( i = 0; i <n ; i++){
            __builtin_prefetch(&A[i+1]);
            __builtin_prefetch(&B[i+1]);
            C[i] = A[i] + B[i];
        }
    }
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec)/1.0e9)/avrage;
    /*
    for( i = 0; i <n; i++){
        printf("A[%d] = %f, + B[%d] = %f, gives c[%d] = %f \n", i, A[i], i, B[i], i, C[i]);
        C[i] = A[i] + B[i];
    }*/
    printf("routine 2         [time(sec), n] = [%.9f, %d] \n", elapsed_time, n);
}

int main(){
    int n, i;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    float A[n], B[n], C[n];

    for (i = 0; i < n; ++i) {
        A[i] = (float)(rand()%1000);
        B[i] = (float)(rand()%1000);
        C[i] = 0;
    }

    routine1(A,B,C,n);
    routine1(A,B,C,n);
    routine1(A,B,C,n);
    routine1(A,B,C,n);

    routine2(A,B,C,n);
    routine2(A,B,C,n);
    routine2(A,B,C,n);
    routine2(A,B,C,n);

    return 0;
}
//finne ut om du vil ha med eller uten gjenomsnitt inne i funkjsonen

