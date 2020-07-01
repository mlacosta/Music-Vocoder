#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtro.h"

void vocoder(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [],float BufferSynth [],float SenalProcesada [],
             float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
             float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF ){

    float BufferAux[BUFFERSIZE] = {0};
    float Envelop[BUFFERSIZE] = {0};

    for (int j = 0;j<BUFFERSIZE;j++){
            SenalProcesada[j] = 0 ;
    }

    for(int i = 0; i<CANTDEFILTROS;i++){
        filtro (Coefficientes[i],BufferAudio ,Estado[0][i],BufferAux,gain[i],CANTDEETAPAS); //ok

        for (int j = 0;j<BUFFERSIZE;j++){ //ganancia
            BufferAux[j]*=2;
        }

        envolvente (CoefHilbert,BufferAux,Envelop,EstadoHilbert[i],EstadoDelay[i],CoefLPF,EstadoLPF[i],gainLPF);

        filtro (Coefficientes[i],BufferSynth ,Estado[1][i],BufferAux,gain[i],CANTDEETAPAS); //ok

        for (int j = 0;j<BUFFERSIZE;j++){ //ganancia
            BufferAux[j]*=2;
        }

        for (int j = 0;j<BUFFERSIZE;j++){
            SenalProcesada[j]+= BufferAux[j]*Envelop[j];
        }
    }


}
