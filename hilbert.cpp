#include <stdio.h>
#include "filtro.h"

/*Especificaciones:
    *Filtro FIR de Orden M Impar con fase lineal
    *Recibe :
        -los coeficientes correspondientes al filtro que se esta utilizando (h[0] a h [(M-1)/2])
        -El buffer actual de procesamiento.
        -El estado anterior de los registros de memoria del filtro (son ceros si se utiliza por primera vez)
    *Devuelve el bloque procesado
*/

void hilbert (float Coefficientes[],float Buffer[] ,float Estado[] , float SenalProcesada[],int Orden){

    int Etapas = Orden/2+1;
    int N = Orden + 1;

    for(int j = 0; j<BUFFERSIZE;j++){
        SenalProcesada[j] =0;

        for(int i = N; i>0;i--){ //shift
            Estado[i] = Estado[i-1];
        }

        Estado[0] = Buffer[j];

        for(int i = 0; i<Etapas;i++){
            SenalProcesada[j] += (Estado[i] - Estado[Orden - i])*Coefficientes[i];
        }

    }

}

void filterDelay (float Buffer[] ,float Estado[] , float SenalProcesada[],int Orden){

    int N = Orden + 1;
    float Coefficientes[ORDENDELAY+1] = {0};

    Coefficientes[Orden] = 1;

    for(int j = 0; j<BUFFERSIZE;j++){
            SenalProcesada[j] = 0;

        for(int i = N; i>0;i--){ //shift
            Estado[i] = Estado[i-1];
        }

        Estado[0] = Buffer[j];

        for(int i = 0; i<Orden+1;i++){
            SenalProcesada[j] += Estado[i]*Coefficientes[i];
        }

    }

}
