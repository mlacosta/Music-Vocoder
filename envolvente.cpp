#include <stdio.h>
#include "filtro.h"
#include <math.h>


void envolvente (float CoefficientesH[], float Buffer[],float SenalProcesada[],float EstadoH[],float EstadoD[],
                 float CoefLPF[][ETAPASLPF],float EstadoLPF [][ETAPASLPF],float gainLPF ){

    float SenalIntermedia [BUFFERSIZE] = {0};
    float Max = 0;

    for (int i = 0; i<BUFFERSIZE;i++){
        SenalProcesada[i] = 0;
    }


    hilbert(CoefficientesH,Buffer,EstadoH,SenalIntermedia,ORDENHILBERT);

    filterDelay (Buffer,EstadoD,SenalProcesada,ORDENDELAY);

    //normalizar(SenalIntermedia);
    //normalizar(SenalProcesada);

    for (int i = 0; i<BUFFERSIZE;i++){
    SenalIntermedia[i] = sqrt(pow(SenalIntermedia[i],2) + pow(SenalProcesada[i],2))*2;
    //SenalProcesada[i] = sqrt(pow(SenalIntermedia[i],2) + pow(SenalProcesada[i],2))*2;
    }

    filtroLPF (CoefLPF,SenalIntermedia,EstadoLPF,SenalProcesada,gainLPF,ETAPASLPF);


}

float maximo(float Senal[]){

    float Max = 0;

    for (int i = 0;i<BUFFERSIZE;i++){
        if(fabsf (Senal[i])>Max){
           Max = Senal[i];
        }
    }
    return Max;
}

void normalizar(float Senal[]){

    float Max = maximo(Senal);

    for (int i = 0;i<BUFFERSIZE;i++){
        Senal[i] = Senal[i]/Max;
    }
}


