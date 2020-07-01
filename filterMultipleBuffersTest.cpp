
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtro.h"

void filterMultipleBuffersTest(int CantDeBuffers,float vectorDeBuffers[][BUFFERSIZE],float Coefficientes[][CANTDEETAPAS],float SenalProcesada[],float Estado[][CANTDEETAPAS],float gain, FILE* bf, FILE* BPF, FILE* Resultado, char filtroNombre [],char resNombre[]){

    Resultado = fopen(resNombre,"w");
    for(int y = 0; y<CantDeBuffers; y++){
        char nombreBuffer[20] = "buffer";
        char str[3];

        sprintf(str, "%d", y+1);
        strcat(nombreBuffer,str);
        strcat(nombreBuffer,".dat");

        //Lectura del Buffer-------------------------------------------------------------------------
        bf = fopen(nombreBuffer,"r");

        if (bf == NULL){
            printf("Open buffer N.%d failed. \n\n",y+1);
            return;
        }else{
            printf("Open buffer N.%d OK. \n\n",y+1);
            convertir(vectorDeBuffers[y],bf,BUFFERSIZE);
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


        if (Resultado == NULL){
            printf("Open resultado failed (%s). \n\n---------------------------\n\n",resNombre);
            return;
        }else{
            printf("\nOpen resultado OK (%s). \n\n\n",resNombre);
            filtro (Coefficientes,vectorDeBuffers[y],Estado,SenalProcesada,gain,CANTDEETAPAS);
            escribir(Resultado,SenalProcesada,BUFFERSIZE);
            printf("Filtering buffer N.%d Done. \n\n---------------------------\n\n",y+1);
        }//-------------------------------------------------------------------------------------------------
    }
    fclose(Resultado);
}
