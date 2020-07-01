#ifndef FILTRO_H_INCLUDED
#define FILTRO_H_INCLUDED

#define ORDENFILTROS 20
#define ORDENHILBERT 20
#define BUFFERSIZE 512
#define CANTDEFILTROS 23
#define ORDENLPF 10

#define CANTDEETAPAS ORDENFILTROS/2
#define ETAPASHILBERT ORDENHILBERT/2 + 1
#define ORDENDELAY ORDENHILBERT/2
#define ETAPASDELAY ORDENDELAY/2 + 1
#define ETAPASLPF ORDENLPF/2

struct BPFilter {

    float Coefficientes [6][CANTDEETAPAS]; //ROM
    float Estado[7][CANTDEETAPAS];//RAM
    float gain;
};

struct HilbertFilter{

    float CoefHilbert[ETAPASHILBERT]; //ROM
    float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2];//RAM

};

struct LPFilter{

    float CoefLPF[6][ETAPASLPF]; //ROM
    float EstadoLPF [7][ETAPASLPF]; //RAM
    float gainLPF ; //ROM

};



void convertir (float Coefficientes[],FILE *Archivo,int N);
void escribir(FILE* archivo,float senal[],int N);
void filtro (float Coefficientes[][CANTDEETAPAS],float Buffer[],float Estado[][CANTDEETAPAS], float SenalProcesada[],float gain,int NumEtapas);
void filtroLPF (float Coefficientes[][ETAPASLPF],float Buffer[] ,float Estado[][ETAPASLPF] , float SenalProcesada[],float gain,int NumEtapas);
void mostrarEnPantalla(char mensaje[],float datos[],int N);
void filterTest(float Coefficientes[][CANTDEETAPAS], float Buffer[],float SenalProcesada[],float Estado[][CANTDEETAPAS],float gain, FILE* bf, FILE* BPF, FILE* Resultado,char filtroNombre [],char resNombre[]);
void filterMultipleBuffersTest(int CantDeBuffers,float vectorDeBuffers[][BUFFERSIZE],float Coefficientes[][CANTDEETAPAS],float SenalProcesada[],float Estado[][CANTDEETAPAS],float gain, FILE* bf, FILE* BPF, FILE* Resultado, char filtroNombre [],char resNombre[]);
void hilbert (float Coefficientes[],float Buffer[] ,float Estado[], float SenalProcesada[],int Orden);
void envelopTest(float CoefficientesH[],float CoefficientesD[], float Buffer[],float SenalProcesada[],float EstadoH[],float EstadoD[],float CoefLPF[][ETAPASLPF],float EstadoLPF [][ETAPASLPF],float gainLPF );
void envolvente (float CoefficientesH[], float Buffer[],float SenalProcesada[],float EstadoH[],float EstadoD[],float CoefLPF[][ETAPASLPF],float EstadoLPF [][ETAPASLPF],float gainLPF );
void filterDelay (float Buffer[] ,float Estado[] , float SenalProcesada[],int Orden);
void normalizar(float Senal[]);
float maximo(float Senal[]);
void vocoder(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [BUFFERSIZE],float BufferSynth [BUFFERSIZE],float SenalProcesada [BUFFERSIZE],
             float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
             float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF );
void vocoderTest(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [BUFFERSIZE],float BufferSynth [BUFFERSIZE],float SenalProcesada [BUFFERSIZE],
         float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
         float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF );
void vocoderBufferingtTest(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [BUFFERSIZE],float BufferSynth [BUFFERSIZE],float SenalProcesada [BUFFERSIZE],
             float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
             float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],int CantDeBuffers,float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF );
void envelopBufferingtTest(float Coefficientes [CANTDEFILTROS][6][CANTDEETAPAS],float BufferAudio [],float BufferSynth [],float SenalProcesada [],
             float Estado[2][CANTDEFILTROS][7][CANTDEETAPAS],float gain[CANTDEFILTROS],float CoefHilbert[ETAPASHILBERT],float EstadoHilbert[CANTDEFILTROS][ORDENHILBERT+2],
             float EstadoDelay [CANTDEFILTROS][ORDENDELAY+1],int CantDeBuffers,float CoefLPF[][ETAPASLPF],float EstadoLPF [CANTDEFILTROS][7][ETAPASLPF],float gainLPF );

#endif // FILTRO_H_INCLUDED
