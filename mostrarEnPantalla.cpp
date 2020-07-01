#include <stdio.h>
#include <stdlib.h>


void mostrarEnPantalla(char mensaje[],float datos[],int N){


    printf("\n\n%s: ",mensaje);

    for(int i = 0; i<N; i++){
        printf("%f ",datos[i]);
    }
    printf("\n\n ");


}
