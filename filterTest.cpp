#include <stdio.h>
#include <stdlib.h>
#include "filtro.h"
void filterTest(float Coefficientes[][CANTDEETAPAS], float Buffer[],float SenalProcesada[],float Estado[][CANTDEETAPAS],float gain, FILE* bf, FILE* BPF, FILE* Resultado, char filtroNombre [],char resNombre[]){
    //Lectura del Buffer-------------------------------------------------------------------------
    bf = fopen("buffer.dat","r");

    if (bf == NULL){
        printf("Open buffer failed. \n\n");
    }else{
        printf("Open buffer OK. \n\n");
        convertir(Buffer,bf,BUFFERSIZE);
        fclose(bf);
    }//----------------------------------------------------------------------------------------------

    //Lectura del Filtro-------------------------------------------------------------------
    BPF = fopen(filtroNombre,"r");

    if (BPF == NULL){
        printf("\nOpen filter failed (%s). \n\n---------------------------\n\n",filtroNombre);
        return;
    }else{
        printf("\nOpen filter OK (%s) \n\n",filtroNombre);
        for(int k =0; k<6;k++){
            convertir(Coefficientes[k],BPF,CANTDEETAPAS);
        }

        fclose(BPF);
    }//-------------------------------------------------------------------------------------------------

    //Filtrado de la senal--------------------------------------------------------------
    Resultado = fopen(resNombre,"w");

    if (Resultado == NULL){
        printf("Open resultado failed (%s). \n\n---------------------------\n\n",resNombre);
    }else{
        printf("\nOpen resultado OK (%s). \n\n\n",resNombre);
        filtro (Coefficientes,Buffer,Estado,SenalProcesada,gain,CANTDEETAPAS);
        escribir(Resultado,SenalProcesada,BUFFERSIZE);
        fclose(Resultado);
        printf("Filtering Done. \n\n---------------------------\n\n");
    }//-------------------------------------------------------------------------------------------------
}
