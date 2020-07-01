#include <stdio.h>
#include <stdlib.h>
#include "filtro.h"
#include <math.h>

void envelopTest(float CoefficientesH[],float CoefficientesD[], float Buffer[],float SenalProcesada[],float EstadoH[],float EstadoD[],float CoefLPF[][ETAPASLPF],float EstadoLPF [][ETAPASLPF],float gainLPF ){

    FILE* bf;
    FILE* HILB;
    FILE* DELAY;
    FILE* Resultado;

    //Lectura del Buffer-------------------------------------------------------------------------
    bf = fopen("buffer.dat","r");

    if (bf == NULL){
        printf("Open buffer failed. \n\n");
    }else{
        printf("Open buffer OK. \n\n");
        convertir(Buffer,bf,BUFFERSIZE);
        fclose(bf);
    }//----------------------------------------------------------------------------------------------

    //Lectura del Filtro Hilbert-------------------------------------------------------------------
    HILB = fopen("hilbert.dat","r");

    if (HILB == NULL){
        printf("\nOpen filter failed (hilbert.dat). \n\n---------------------------\n\n");
        return;
    }else{
        printf("\nOpen filter OK (hilbert.dat) \n\n");

        convertir(CoefficientesH,HILB,ETAPASHILBERT);


        fclose(HILB);
    }//-------------------------------------------------------------------------------------------------

    //Lectura del Filtro Delay-------------------------------------------------------------------
    DELAY = fopen("delay.dat","r");

    if (DELAY == NULL){
        printf("\nOpen filter failed (delay.dat). \n\n---------------------------\n\n");
        return;
    }else{
        printf("\nOpen filter OK (delay.dat) \n\n");

        convertir(CoefficientesD,DELAY,ETAPASHILBERT);


        fclose(DELAY);
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

    //Filtrado de la senal--------------------------------------------------------------
    Resultado = fopen("envolvente.dat","w");

    if (Resultado == NULL){
        printf("Open resultado failed (%s). \n\n---------------------------\n\n","envolvente.dat");
    }else{
        printf("\nOpen resultado OK (%s). \n\n\n","envolvente.dat");
        envolvente (CoefficientesH,Buffer,SenalProcesada,EstadoH,EstadoD,CoefLPF,EstadoLPF,gainLPF);
        escribir(Resultado,SenalProcesada,BUFFERSIZE);
        fclose(Resultado);
        printf("Envolvente Done. \n\n---------------------------\n\n");
    }//-------------------------------------------------------------------------------------------------
}
