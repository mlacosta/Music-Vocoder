#define CANTDEBUFFER 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtro.h"

int main()
{
    //TEST DEL FILTRO---------------------------------------------------------------------------------
    float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS] = {{{0}}}; //ROM
    float Buffer [BUFFERSIZE];
    float BufferAudio [BUFFERSIZE]; //RAM
    float BufferSynth [BUFFERSIZE]; //RAM
    float SenalProcesada [CANTDEFILTROS][BUFFERSIZE] = {{0}};
    float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS] = {{{{0}}}};//RAM
    float gain[CANTDEFILTROS] = {0.0035977084408224391,0.0035977084408165979,0.0035977084408158819,0.0035977084408168086, //ROM
                                 0.0035977084408200153,0.0035977084408187294 ,0.0071913265931695166,0.0071913265931735273,
                                 0.007191326593173359,0.0071913265931752932,0.014366149927883182,0.014366149927882531,
                                 0.014366149927883883,0.014366149927883395,0.028665176698664935,0.028665176698665196,
                                 0.028665176698665376,0.028665176698665574,0.057053398221292843,0.057053398221292871,
                                 0.057053398221292725,0.057053398221292725,0.89203742665439878/1.23};

    float CoefHilbert[ETAPASHILBERT] = {0}; //ROM
    float CoefDelay[ETAPASHILBERT] = {0};
    float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2] = {{0}};//RAM
    float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1] = {{0}};//RAM
    float SenalEnvolvente[BUFFERSIZE] = {0};
    float SenalVocoder[BUFFERSIZE] = {0};//RAM
    float CoefLPF[6][ETAPASLPF] = {{0}}; //ROM
    float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF] = {{{0}}}; //RAM
    float gainLPF = 0.000042342377445; //ROM

    struct BPFilter BancoBPF [2][CANTDEFILTROS];
    struct LPFilter BancoLPF[CANTDEFILTROS];

    FILE *bf;
    FILE *BPF;
    FILE *Resultado;

    int Opcion = 5;

    switch (Opcion){
        case 1: //Banco de Filtros Test
            for(int m = 0; m<CANTDEFILTROS;m++){
                char nombreFiltro[20] = "BPF";
                char nombreRes[20] = "resultado";
                char str[3];

                sprintf(str, "%d", m+1);

                strcat(nombreFiltro,str);
                strcat(nombreRes,str);
                strcat(nombreFiltro,".dat");
                strcat(nombreRes,".dat");

                filterTest(Coefficientes[m],Buffer,SenalProcesada[m],Estado[1][m],gain[m],bf,BPF,Resultado,nombreFiltro,nombreRes);
            }

            break;
        case 2: //filter Buffering Test.
            {
            float vectorDeBuffers[CANTDEBUFFER][BUFFERSIZE] = {{0}};
            int m = 10; //numero del filtro

            char nombreFiltro[20] = "BPF";
            char str[3];

            sprintf(str, "%d", m+1);
            strcat(nombreFiltro,str);
            strcat(nombreFiltro,".dat");

            filterMultipleBuffersTest(CANTDEBUFFER,vectorDeBuffers,Coefficientes[m],SenalProcesada[m],Estado[1][m],gain[m],bf,BPF,Resultado,nombreFiltro,"resultadoBuffer.dat");
            }
            break;
        case 3: //Enevelope Detector Test.
            envelopTest(CoefHilbert,CoefDelay, Buffer,SenalEnvolvente,EstadoHilbert[1],EstadoDelay[1],CoefLPF,EstadoLPF[0],gainLPF);
            break;
        case 4: //Vocoder Test
            vocoderTest(Coefficientes,BufferAudio,BufferSynth,SenalVocoder,Estado,gain,CoefHilbert,EstadoHilbert,EstadoDelay,CoefLPF,EstadoLPF,gainLPF);
            break;
        case 5: //Vocoder Buffering Test
            vocoderBufferingtTest(Coefficientes,BufferAudio,BufferSynth,SenalVocoder,Estado,gain,CoefHilbert,EstadoHilbert,EstadoDelay,CANTDEBUFFER,CoefLPF,EstadoLPF,gainLPF);
            break;
        case 6: //Envelope Buffering Test
            //envelopBufferingtTest(Coefficientes,BufferAudio,BufferSynth,SenalVocoder,Estado,gain,CoefHilbert,EstadoHilbert,EstadoDelay,CANTDEBUFFER,CoefLPF,EstadoLPF,gainLPF);
            break;


    }
    //FIN TEST FILTRO-----------------------------------------------------------------------------------
    return 0;
}


