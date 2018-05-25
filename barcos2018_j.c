/*----------------------------------------------------------------
|	Autors: Santiago Romani (v1.0), Pere Millan (v2.x, v3.x)
|	Data:   Maig, Desembre 2017, Maig 2018       Versio: 3.1
|-----------------------------------------------------------------|
|	Nom fitxer: barcos2018_j.c
|   Descripcio: "esquelet" de rutines a desenvolupar a la practica
|               de Fonaments de Computadors "Guerra de barcos".
|       Define las rutinas para poder jugar una partida:
|       rutina partida_completa(), rutina decide_disparo() y 
|       rutina procesa_hundido().
|-----------------------------------------------------------------|
|   programador/a 1: manueljavier.loira@estudiants.urv.cat
|   programador/a 2: oriol.lopez@estudiants.urv.cat
| ----------------------------------------------------------------*/

#include "barcos2018.h"
#include "rutslib2018.h"

#define CASELLA_BUIDA            '?'
#define CASELLA_AIGUA            '.'
#define CASELLA_VAIXELL          '@'
int tocado;
unsigned int fi=-1, co=-1;
unsigned int arriba=1, abajo=0, izquierda=0, derecha=0;


/* unsigned int partida_completa(char tablero_disparos[],
                                 unsigned int dim):
    rutina para realizar los lanzamientos contra el tablero de barcos
    inicializado con la ultima llamada a B_inicializa_barcos(),
    anotando los resultados en el tablero de disparos que se pasa
    por parametro (por referencia), donde los dos tableros tienen
    el mismo tamanyo (dim = dimension del tablero de barcos).
    La rutina realizara los disparos necesarios hasta hundir todos
    los barcos, devolviendo el numero total de disparos realizado.
    Para generar numeros aleatorios debe llamar a mod_random().
    Parametros:
        char tablero_disparos[]: direccion base del tablero de disparos
        dim: tamanyo de los tableros (dim*dim)
    Resultado:
        numero total de disparos realizados para completar la partida */
unsigned int partida_completa(char tablero_disparos[], unsigned int dim)
{
    int enfonsat=0, s,f,c,mida, disparos=0, col, sumtrets=0;
    double efectivitat=0, efectivitat_tret=0;
    char fila;
    float ds;
    int pos;

    tocado = 0;
    //Aquesta funcio es el bucle perque la maquina jugui sola.
    while(enfonsat<=9)
    {

        decide_disparo(&f, &c, tablero_disparos, dim); //Decidim la coordenada on dispararem.
        fila=f+'A'; //En aquestes dos proximes linies cambiem les files de numero a lletra i fem un +1 a les columnes.
        col=c+1;
        s=B_dispara(fila, col);
        switch (s)
        {
            case -1:
                
                break;
            case 0:

                
                break;
            case 1:
                pos=((f+1)*dim)-(dim-(c+1));
                tablero_disparos[pos]=CASELLA_AIGUA;
                tocado = 0;
                
                break;
            case 2:
                pos=((f+1)*dim)-(dim-(c+1));
                tablero_disparos[pos]=CASELLA_VAIXELL;
                tocado = 1;
                break;
            case 3:
                pos=((f+1)*dim)-(dim-(c+1));
                tablero_disparos[pos]=CASELLA_VAIXELL;
                enfonsat=enfonsat+1;
                procesa_hundido(f, c, tablero_disparos, dim);
                tocado = 0;
                fi = -1;
                co = -1;
                break;
        } //Aquest switch ens serveix per a cambiar les caselles segons el resultat del tret.
        disparos=disparos+1;
    }

    return disparos;
}





/* void decide_disparo(int *f, int *c, char tablero_disparos[],
                        unsigned int dim):
    rutina que decide el siguiente disparo sobre el tablero de barcos.
	Consultando tablero_disparos y la informacion del ultimo disparo 
	(f, c), la rutina debe decidir cuales seran las coordenadas del 
	siguiente disparo. Se pueden aplicar diversas estrategias para
	decidir el siguiente disparo y reducir el numero de disparos
	necesarios para hundir todos los barcos (las 6 estrategias se
	indican en el apartado 3.1, pagina 11 del enunciado).
	La rutina devolvera por referencia (en f y c) las coordenadas
	del siguiente disparo a realizar.
    Parametros:
        f: numero de fila (0..dim-1).
			Entrada: anterior fila disparada.
			Salida: siguiente fila a disparar.
        c: numero de columna (0..dim-1)
			Entrada: anterior columna disparada.
			Salida: siguiente columna a disparar.
        tablero_disparos[]: direccion base del tablero de disparos
        dim: tamanyo de los tableros (dim*dim)
	*/
void decide_disparo(int *f, int *c, char tablero_disparos[], unsigned int dim) {
    int salir = 0;
    int pos;

    if (tocado = 1) 
    {
        fi = *f;
        co = *c;
    }

    if (fi != -1)
    {
        pos = (fi * dim) - (dim - co);
        if (arriba = 1)
        {
            *f=fi-1;
            if(tablero_disparos[pos] == CASELLA_AIGUA)
            {
                fi= fi - arriba;
                abajo = 1;
                arriba = 0;
            }
            else if (*f<0 || *f>dim)
            {
                abajo = 1;
                arriba = 0;
            }
            else
            {
                arriba++;
            }
        }
        if(abajo = 1)
        {
            *f=fi+1;
            if(tablero_disparos[pos] == CASELLA_AIGUA)
            {
                fi = fi - abajo;
                abajo = 0;
                derecha = 1;
            }
            else if (*f<0 || *f>dim)
            {
                abajo = 0;
                derecha = 1;
            }
            else
            {
                abajo++;
            }
        }
        if(derecha = 1)
        {
            *c=co+1;
            if(tablero_disparos[pos] == CASELLA_AIGUA)
            {
                co = co - derecha;
                derecha = 0;
                izquierda = 1;
            }
            else if (*c<0 || *c>dim)
            {
                derecha = 0;
                izquierda = 1;
            }
            else
            {
                derecha++;
            }
        }
        else if(izquierda=1)
        {
            *c=co-1;
            if(tablero_disparos[pos] == CASELLA_AIGUA)
            {
                co= co - izquierda;
                izquierda = 0;
                arriba = 1;
            }
            else if (*c<0 || *c>dim)
            {
                izquierda = 0;
                arriba = 1;
            }
            else 
            {
                izquierda++;
            }
        }
    }

    else 
    
    {
        while (salir == 0) 
        {
            *f = mod_random(dim - 1);
            *c = mod_random(dim - 1);

            pos = (*f * dim) - (dim - *c);
            if (tablero_disparos[pos] == CASELLA_BUIDA) {
                salir = 1;
            }
        }
    }
}




/* void procesa_hundido(int f, int c, char tablero_disparos[],
                        unsigned int dim):
    rutina que procesa tablero_disparos en caso de hundir un barco.
	Consultando tablero_disparos y la informacion del ultimo disparo 
	(f, c) para hundir el barco, la rutina debe decidir como anotar 
	el barco hundido, por ejemplo, con alguna de las estrategias 
	indicadas en el apartado 3.1, pagina 12 del enunciado).
    Parametros:
        f: numero de fila (0..dim-1) del barco hundido
        c: numero de columna (0..dim-1) del barco hundidos
        tablero_disparos[]: direccion base del tablero de disparos
        dim: tamanyo de los tableros (dim*dim)
    */
void procesa_hundido(int f, int c, char tablero_disparos[], unsigned int dim) {


    int pos, fil = f + 1, col = c + 1;
    pos = (fil * dim) - (dim - col);
    int col_derecha = pos + 1;
    int fila_arriba = pos - dim;
    int fila_abajo = pos + dim;
    int col_idquierda = pos - 1;
    int far_ci = pos - dim - 1;
    int far_cd = pos - dim + 1;
    int fab_ci = pos + dim - 1;
    int fab_cd = pos + dim + 1;
    int dim2 = dim * dim;
    if (fila_arriba >= 0) {

        if (tablero_disparos[fila_arriba] == CASELLA_BUIDA) {
            tablero_disparos[fila_arriba] = CASELLA_AIGUA;
        }
        if (col_idquierda >= 0) {
            if (tablero_disparos[far_ci] == CASELLA_BUIDA) {
                tablero_disparos[far_ci] = CASELLA_AIGUA;
            }
        }
        if (col_derecha < dim2) {
            if (tablero_disparos[far_cd] == CASELLA_BUIDA) {
                tablero_disparos[far_cd] = CASELLA_AIGUA;
            }
        }
    }


    if (col_idquierda >= 0) {
        if (tablero_disparos[col_idquierda] == CASELLA_BUIDA) {
            tablero_disparos[col_idquierda] = CASELLA_AIGUA;

        }
    }
    if (col_derecha < dim2) {
        if (tablero_disparos[col_derecha] == CASELLA_BUIDA) {
            tablero_disparos[col_derecha] = CASELLA_AIGUA;

        }
    }
    if (fila_abajo < dim2) {
        if (tablero_disparos[fila_abajo] == CASELLA_BUIDA) {
            tablero_disparos[fila_abajo] = CASELLA_AIGUA;
        }
        if (col_derecha < dim2) {
            if (tablero_disparos[fab_cd] == CASELLA_BUIDA) {
                tablero_disparos[fab_cd] = CASELLA_AIGUA;

            }
        }
        if (col_idquierda >= 0) {
            if (tablero_disparos[fab_ci] == CASELLA_BUIDA) {
                tablero_disparos[fab_ci] = CASELLA_AIGUA;

            }
        }

    }

    if (tablero_disparos[fila_arriba] == CASELLA_VAIXELL) {

        if (fila_arriba >= 0) {
            while (tablero_disparos[fila_arriba] == CASELLA_VAIXELL) {

                if (fila_arriba - 1 >= 0) {
                    if (tablero_disparos[fila_arriba - dim] == CASELLA_BUIDA) {
                        tablero_disparos[fila_arriba - dim] = CASELLA_AIGUA;
                    }
                    if (col_idquierda >= 0) {
                        if (tablero_disparos[far_ci - dim] == CASELLA_BUIDA) {
                            tablero_disparos[far_ci - dim] = CASELLA_AIGUA;

                        }
                    }
                    if (col_derecha < dim2) {
                        if (tablero_disparos[far_cd - dim] == CASELLA_BUIDA) {
                            tablero_disparos[far_cd - dim] = CASELLA_AIGUA;

                        }
                    }
                }

                fila_arriba = fila_arriba - dim;
            }
        }

    }
    if (tablero_disparos[fila_abajo] == CASELLA_VAIXELL) {

        if (fila_abajo < dim2) {
            while (tablero_disparos[fila_abajo] == CASELLA_VAIXELL) {

                if (fila_abajo + dim < dim2) {
                    if (tablero_disparos[fila_abajo + dim] == CASELLA_BUIDA) {
                        tablero_disparos[fila_abajo + dim] = CASELLA_AIGUA;

                    }
                    if (col_idquierda >= 0) {
                        if (tablero_disparos[fab_ci + dim] == CASELLA_BUIDA) {
                            tablero_disparos[fab_ci + dim] = CASELLA_AIGUA;

                        }
                    }
                    if (col_derecha < dim2) {
                        if (tablero_disparos[fab_cd + dim] == CASELLA_BUIDA) {
                            tablero_disparos[fab_cd + dim] = CASELLA_AIGUA;

                        }
                    }

                }

                fila_abajo = fila_abajo + dim;
            }
        }

    }

    if (tablero_disparos[col_idquierda] == CASELLA_VAIXELL) {
        if (col_idquierda >= 0) {
            while (tablero_disparos[col_idquierda] == CASELLA_VAIXELL) {

                if (col_idquierda - 1 >= 0) {
                    if (fila_arriba >= 0) {
                        if (tablero_disparos[far_ci - 1] == CASELLA_BUIDA) {
                            tablero_disparos[far_ci - 1] = CASELLA_AIGUA;

                        }
                    }
                    if (fila_abajo < dim2) {
                        if (tablero_disparos[fab_ci - 1] == CASELLA_BUIDA) {
                            tablero_disparos[fab_ci - 1] = CASELLA_AIGUA;

                        }
                    }

                    if (tablero_disparos[col_idquierda - 1] == CASELLA_BUIDA) {
                        tablero_disparos[col_idquierda - 1] = CASELLA_AIGUA;

                    }
                }

                col_idquierda--;
            }
        }

    }
    if (tablero_disparos[col_derecha] == CASELLA_VAIXELL) {
        if (col_derecha < dim) {
            while (tablero_disparos[col_derecha] == CASELLA_VAIXELL) {

                if (col_derecha + 1 < dim2) {
                    if (fila_arriba >= 0) {
                        if (tablero_disparos[far_cd + 1] == CASELLA_BUIDA) {
                            tablero_disparos[far_cd + 1] = CASELLA_AIGUA;

                        }
                    }
                    if (fila_abajo < dim2) {
                        if (tablero_disparos[fab_cd + 1] == CASELLA_BUIDA) {
                            tablero_disparos[fab_cd + 1] = CASELLA_AIGUA;

                        }
                    }

                    if (tablero_disparos[col_derecha + 1] == CASELLA_BUIDA) {
                        tablero_disparos[col_derecha + 1] = CASELLA_AIGUA;

                    }
                }

                col_derecha++;
            }

        }
    }
}





