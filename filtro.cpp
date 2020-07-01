#include <stdio.h>
#include "filtro.h"

/*Especificaciones:
    *Filtro IIR de Orden 20 Castada forma Directa II
    *Recibe :
        -los coeficientes correspondientes al filtro que se esta utilizando (orden 20)
        -El buffer actual de procesamiento.
        -El estado anterior de los registros de memoria del filtro (son ceros si se utiliza por primera vez)
    *Devuelve el bloque procesado
*/
void filtro (float Coefficientes[][CANTDEETAPAS],float Buffer[] ,float Estado[][CANTDEETAPAS] , float SenalProcesada[],float gain,int NumEtapas){

    for(int j = 0; j<BUFFERSIZE;j++){
        //SenalProcesada[j] = 0;
        for(int i = 0;i <NumEtapas; i++){
            Estado[6][i] = Estado[4][i];
            Estado[4][i] = Estado[1][i];
            Estado[5][i] = Estado[4][i]*Coefficientes[1][i] + Estado[6][i]*Coefficientes[2][i];
            Estado[3][i] = -Estado[4][i]*Coefficientes[4][i] - Estado[6][i]*Coefficientes[5][i];
            if(i == 0){
                Estado[0][i] = Buffer[j]*gain + Estado[3][i];
            }else{
                Estado[0][i] = Estado[2][i-1]*gain  + Estado[3][i];
            }
            Estado[1][i] = Estado[0][i];
            Estado[2][i] = Estado[1][i]*Coefficientes[0][i] + Estado[5][i];

        }

        SenalProcesada[j] = Estado[2][NumEtapas-1];

    }

}

void filtroLPF (float Coefficientes[][ETAPASLPF],float Buffer[] ,float Estado[][ETAPASLPF] , float SenalProcesada[],float gain,int NumEtapas){

    for(int j = 0; j<BUFFERSIZE;j++){
        SenalProcesada[j] = 0;
        for(int i = 0;i <NumEtapas; i++){
            Estado[6][i] = Estado[4][i];
            Estado[4][i] = Estado[1][i];
            Estado[5][i] = Estado[4][i]*Coefficientes[1][i] + Estado[6][i]*Coefficientes[2][i];
            Estado[3][i] = -Estado[4][i]*Coefficientes[4][i] - Estado[6][i]*Coefficientes[5][i];
            if(i == 0){
                Estado[0][i] = Buffer[j]*gain + Estado[3][i];
            }else{
                Estado[0][i] = Estado[2][i-1]*gain  + Estado[3][i];
            }
            Estado[1][i] = Estado[0][i];
            Estado[2][i] = Estado[1][i]*Coefficientes[0][i] + Estado[5][i];

        }

        SenalProcesada[j] = Estado[2][NumEtapas-1];

    }

}
