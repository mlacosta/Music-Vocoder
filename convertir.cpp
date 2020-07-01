#include <stdio.h>
#include <stdlib.h>
void convertir (float Coefficientes[],FILE *Archivo,int N);
void escribir(FILE* archivo,float senal[],int N);

void convertir (float Coefficientes[],FILE *Archivo,int N){

    for(int i = 0; i<N; i++){
        fscanf(Archivo,"%f,",&Coefficientes[i]);
    }
}

void escribir (FILE* archivo,float senal[],int N){

    for(int i = 0; i<N; i++){
        fprintf(archivo,"%f,",senal[i]);
    }

}
