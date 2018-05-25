/*----------------------------------------------------------------
|	Autors: Santiago Romani (v1.0), Pere Millan (v2.x, v3.x)
|	Data:   Maig, Desembre 2017, Maig 2018       Versio: 3.1
|-----------------------------------------------------------------|
|	Nom fitxer: barcos2018_p.c
|   Descripcio: "esquelet" de rutines a desenvolupar a la practica
|               de Fonaments de Computadors "Guerra de barcos".
|       Define las constantes y variables globables principales del
|       juego (NUM_PARTIDAS, matriz_barcos, matriz_disparos, ...),
|       la rutina principal() y la rutina multiples_partidas().
|-----------------------------------------------------------------|
|   programador/a 1: manueljavier.loira@estudiants.urv.cat
|   programador/a 2: oriol.lopez@estudiants.urv.cat
| ----------------------------------------------------------------*/

#include "barcos2018.h"
#include "rutslib2018.h"

/* Simbolos habituales */
#define NUM_PARTIDAS 150


/* variables globales */
unsigned char nd8, nd9, nd10;   /* Promedio de disparos
                                   para tableros de 8x8, 9x9, 10x10 */
char matriz_barcos[100];        /* Codigos de los barcos a hundir */
char matriz_disparos[100];      /* Codigos de los disparos realizados */


/* principal():
    rutina principal del programa de los barcos; 
    realiza n partidas (NUM_PARTIDAS) para cada uno de los 3 tamanyos 
    de tablero establecidos (8x8, 9x9 y 10x10), calculando el promedio 
    del numero de disparos necesarios para hundir toda la flota,
    que se inicializara en posiciones aleatorias en cada partida; 
    los valores promedio se deben escribir en las variables globales 
    'nd8', 'nd9' y 'nd10', respectivamente. */
void principal()
{
    multiples_partidas(matriz_barcos, matriz_disparos,  8, &nd8 );
    multiples_partidas(matriz_barcos, matriz_disparos,  9, &nd9 );
    multiples_partidas(matriz_barcos, matriz_disparos, 10, &nd10);
}



/* multiples_partidas(char tablero_barcos[], char tablero_disparos[],
                      unsigned int dim, unsigned char *var_promedio):
    rutina para realizar un cierto numero de partidas (NUM_PARTIDAS) de la
    guerra de barcos, sobre un tablero de barcos y un tablero de disparos
    pasados por parametro, junto con la dimension de dichos tableros,
    de modo que se calcula el promedio de disparos de cada partida
    necesarios para hundir todos los barcos; dicho promedio se almacena
    en la posicion de memoria referenciada por el parametro 'var_promedio'.
    Para hacer la division del promedio debe llamar a div_mod().
    Parametros:
        tablero_barcos[]: direccion base del tablero de barcos
        tablero_disparos[]: direccion base del tablero de disparos
        dim: tamanyo de los tableros (dim*dim)
        var_promedio (ref): direccion de la variable que albergara
                            el promedio de disparos. */
void multiples_partidas(char tablero_barcos[], char tablero_disparos[],
                        unsigned int dim, unsigned char *var_promedio)
{
    unsigned int i=0;
    int j;
    unsigned int dim2 = dim*dim;
    int disparos=0;
    unsigned int total_disparos = 0;
    unsigned int *quo=0;
    unsigned int *mod=0;
    while(i<NUM_PARTIDAS)
    {
        for(j=0; j<dim2; j++)
        {
            tablero_disparos[j]='?';
        }
        B_inicializa_barcos(tablero_barcos, dim2);

        disparos = partida_completa(tablero_disparos, dim2);
        total_disparos = total_disparos + disparos;
        i++;
    }
    div_mod(total_disparos, i, quo, mod);
    *var_promedio = (char)*quo;
}


