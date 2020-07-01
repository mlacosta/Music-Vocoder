#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtro.h"

void vocoderBufferingtTest(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [],float BufferSynth [],float SenalProcesada [],
             float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
             float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],int CantDeBuffers,float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF){

    FILE* BPF;
    FILE* bf ;
    FILE* Resultado = fopen("resultadoVocoderMultiple.dat","w");
        //Lectura de los Filtros-------------------------------------------------------------------
    for(int m = 0; m<CANTDEFILTROS;m++){
        char nombreFiltro[20] = "BPF";
        char str[3];

        sprintf(str, "%d", m+1);

        strcat(nombreFiltro,str);
        strcat(nombreFiltro,".dat");
        BPF = fopen(nombreFiltro,"r");

        if (BPF == NULL){
            printf("\nOpen filter failed (%s). \n\n---------------------------\n\n",nombreFiltro);
            return;
        }else{
            printf("\nOpen filter OK (%s) \n\n",nombreFiltro);
            for(int k =0; k<6;k++){
                convertir(Coefficientes[m][k],BPF,CANTDEETAPAS);
            }
            fclose(BPF);
        }
    }//-------------------------------------------------------------------------------------------------

    //Lectura del Filtro Hilbert-------------------------------------------------------------------
    FILE* HILB = fopen("hilbert.dat","r");

    if (HILB == NULL){
        printf("\nOpen filter failed (hilbert.dat). \n\n---------------------------\n\n");
        return;
    }else{
        printf("\nOpen filter OK (hilbert.dat) \n\n");

        convertir(CoefHilbert,HILB,ETAPASHILBERT);

        fclose(HILB);
    }//-------------------------------------------------------------------------------------------------

    //Lectura del LPF-------------------------------------------------------------------
    FILE* LF;
    LF = fopen("LPF.dat","r");

    if (LF == NULL){
        printf("\nOpen filter failed (LPF.dat). \n\n---------------------------\n\n");
        return;
    }else{
        printf("\nOpen filter OK (LPF.dat) \n\n");

         for(int k =0; k<6;k++){
            convertir(CoefLPF[k],LF,ETAPASLPF);
        }


        fclose(LF);
    }//-------------------------------------------------------------------------------------------------

    for(int y = 0; y<CantDeBuffers; y++){
        //Lectura del Buffer Audio-------------------------------------------------------------------------
        char nombreBuffer[30] = "bufferAudio";
        char str[4];

        sprintf(str, "%d", y+1);
        strcat(nombreBuffer,str);
        strcat(nombreBuffer,".dat");

        //Lectura del Buffer-------------------------------------------------------------------------
        bf = fopen(nombreBuffer,"r");


        if (bf == NULL){
            printf("Open buffer audio (%s) failed. \n\n",nombreBuffer);
            return;
        }else{
            printf("Open buffer audio (%s)OK. \n\n",nombreBuffer);
            convertir(BufferAudio,bf,BUFFERSIZE);
            fclose(bf);
        }//----------------------------------------------------------------------------------------------

        //Lectura del Buffer Synth-------------------------------------------------------------------------
        char nombreSynth[30] = "bufferSynth";

        sprintf(str, "%d", y+1);
        strcat(nombreSynth,str);
        strcat(nombreSynth,".dat");

        bf = fopen(nombreSynth,"r");

        if (bf == NULL){
            printf("Open buffer synth (%s) failed. \n\n",nombreSynth);
            return;
        }else{
            printf("Open buffer synth (%s) OK. \n\n",nombreSynth);
            convertir(BufferSynth,bf,BUFFERSIZE);
            fclose(bf);
        }//---------------------------------------------------------------------------------------------

        //Filtrado de la senal--------------------------------------------------------------

        if (Resultado == NULL){
            printf("Open resultado failed (%s). \n\n---------------------------\n\n","resultadoVocoderMultiple.dat");
            return;
        }else{
            printf("\nOpen resultado OK (%s). \n\n\n","resultadoVocoderMultiple.dat");
            vocoder(Coefficientes ,BufferAudio,BufferSynth ,SenalProcesada,Estado,gain, CoefHilbert,EstadoHilbert,EstadoDelay,CoefLPF,EstadoLPF,gainLPF) ;

            printf("Vocoding Chunk N.%d Done. \n\n---------------------------\n\n",y+1);
            escribir(Resultado,SenalProcesada,BUFFERSIZE);

        }//-------------------------------------------------------------------------------------------------
    }
    fclose(Resultado);
}
