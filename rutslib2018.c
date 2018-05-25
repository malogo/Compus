/*----------------------------------------------------------------
|	Autor: Pere Millan (DEIM, URV)
|	Data:  Maig, Desembre 2017, Maig 2018         Versio: 3.1
|-----------------------------------------------------------------|
|	Nom fitxer: rutslib2018.c
|   Descripcio: Codi en C d'una possible implementacio
|               de les rutines de llibreria de la practica
|               de Fonaments de Computadors "Guerra de barcos".
|               La implementacio en ARM de la fase 2 es diferent.
| ----------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>

#include "rutslib2018.h"

/* Declaracions "forward" */
int enfonsat(int f, int c);
mama
char _default[][8] = {
    "...@@.@.",
    ".@......",
    ".@..@.@.",
    ".@......",
    ".@.@@@..",
    ".......@",
    "...@.@.@",
    "@@.@...@"
};
char _default1[][8] = {
    "...@@.@.",
    ".@......",
    "...@@@@.",
    "........",
    ".@.@@@..",
    ".......@",
    "...@.@.@",
    "@@.@...@"
};
char _default2[][8] = {
    "@..@@.@.",
    "........",
    "...@@@@.",
    "@.......",
    "...@@@..",
    ".......@",
    "...@.@.@",
    "@@.@...@"
};


unsigned int _num_trets, _dim_actual;  /* total de trets; dimensio actual */
char *_t_actual;    /* taulell de vaixells actual */


void B_inicializa_barcos(char t_barcos[100], unsigned int dim)
{
    int i, f, c;
    int delta_f, delta_c;
    int swpf1, swpf0, swpc1, swpc0, invf, invc;

    _num_trets = 0;
    _t_actual = t_barcos;

    /* Comprovar dimensio: */
    if (dim < 8)
        dim = 8;
    if (dim > 10)
        dim = 10;

    _dim_actual = dim;

    /* Emplenar aigues: */
    for (i=0; i<100; i++)
        t_barcos[i]='.';

    /* Afegir vaixells desplacats: */
    delta_f = 0;
    delta_c = 0;
    if (dim > 8) {
        delta_f = mod_random( dim-7 );
        delta_c = mod_random( dim-7 );
    }

    /* Simetries, intercanvis */
    swpf1 = mod_random(2);
    swpf0 = 1-swpf1;
    swpc1 = swpf0;
    swpc0 = swpf1;
    invf = mod_random(2);
    if (invf) {
        swpf1 *= -1;
        swpf0 *= -1;
    }
    invc = mod_random(2);
    if (invc) {
        swpc1 *= -1;
        swpc0 *= -1;
    }

    /* Afegir vaixells, a partir d'un dels 3 taulells "base" */
    switch (mod_random(3))
    {
        case 0:
            for (f=0; f<8; f++)
                for (c=0; c<8; c++)
                    t_barcos[ (f + delta_f) * dim + (c + delta_c) ] =
                        _default[ 7 * invf + swpf1 * f + swpf0 * c]
                                [ 7 * invc + swpc1 * f + swpc0 * c];
            break;
        case 1:
            for (f=0; f<8; f++)
                for (c=0; c<8; c++)
                    t_barcos[ (f + delta_f) * dim + (c + delta_c) ] =
                        _default1[ 7 * invf + swpf1 * f + swpf0 * c]
                                 [ 7 * invc + swpc1 * f + swpc0 * c];
            break;
        default:
            for (f=0; f<8; f++)
                for (c=0; c<8; c++)
                    t_barcos[ (f + delta_f) * dim + (c + delta_c) ] =
                        _default2[ 7 * invf + swpf1 * f + swpf0 * c]
                                 [ 7 * invc + swpc1 * f + swpc0 * c];
    }

}


int B_dispara(char fila, int col)
{
    int f, c, result;
    char abans;

    _num_trets++;
    f = fila-'A';
    c = col-1;

    /* Verificar coordenades */
    if ( (f < 0) || (f >= _dim_actual) || (c < 0) || (c >= _dim_actual) )
        result = ERROR;
    else
    {
      abans = _t_actual[ f * _dim_actual + c];

      switch(abans) {
        case '-':
        case 'X':
            result = REPETIDO;
            break;
        case '.':
            _t_actual[ f * _dim_actual + c] = '-';
            result = AGUA;
            break;
        case '@':
            _t_actual[ f * _dim_actual + c] = 'X';
            if ( !enfonsat( f, c ) )
                result = TOCADO;
            else
                result = HUNDIDO;
            break;
        default:
            result = ERROR;
            break;
      }
    }

    return result;
}


unsigned int B_num_disparos()
{
    return _num_trets;
}


void randomize()
{
    time_t t;
    srand( (unsigned) time( &t ) );
}


unsigned int mod_random(unsigned int n)
{
    if (n < 2)
        n = 2;
    if (n > 255)
        n = 255;

    return rand() % n;
}


int div_mod(unsigned int num, unsigned int den,
            unsigned int *quo, unsigned int *mod)
{
    int ret;

    if (0 == den)
        ret = 1;
    else if (((int)quo & 3) || ((int)mod & 3))
        ret = 2;    /* Algun punter no esta aliniat en @ x4 */
    else if (quo == mod)
        ret = 3;    /* Els punters son el mateix */
    else
    {
        *quo = num / den;
        *mod = num % den;
        ret = 0;
    }

    return ret;
}



/* Rutines auxiliars: */

int enfonsat(int f, int c)
{
    int f0, c0, loop, result;
    char casella;

    result = 99;
    f0 = f;
    c0 = c;

    loop = 1;
    while( loop && result )
    {
        if (--f < 0)
            loop = 0;
        else
        {
            casella = _t_actual[f * _dim_actual + c];
            if (casella != 'X')
            {
                if (casella == '@')
                {
                    result = 0;
                }
                else
                {
                    if ( (casella == '.') || (casella == '-') )
                    {
                        loop = 0;
                    }
                    else
                    {
                        result = 0;
                    }
                }
            }
        }
    }

    f = f0;
    loop = 1;
    while( loop && result )
    {
        if (++f >= _dim_actual)
            loop = 0;
        else
        {
            casella = _t_actual[f * _dim_actual + c];
            if (casella != 'X')
            {
                if (casella == '@')
                {
                    result = 0;
                }
                else
                {
                    if ( (casella == '.') || (casella == '-') )
                    {
                        loop = 0;
                    }
                    else
                    {
                        result = 0;
                    }
                }
            }
        }
    }
    
    f = f0;
    loop = 1;
    while( loop && result )
    {
        if (--c < 0)
            loop = 0;
        else
        {
            casella = _t_actual[f * _dim_actual + c];
            if (casella != 'X')
            {
                if (casella == '@')
                {
                    result = 0;
                }
                else
                {
                    if ( (casella == '.') || (casella == '-') )
                    {
                        loop = 0;
                    }
                    else
                    {
                        result = 0;
                    }
                }
            }
        }
    }

    c = c0;
    loop = 1;
    while( loop && result )
    {
        if (++c >= _dim_actual)
            loop = 0;
        else
        {
            casella = _t_actual[f * _dim_actual + c];
            if (casella != 'X')
            {
                if (casella == '@')
                {
                    result = 0;
                }
                else
                {
                    if ( (casella == '.') || (casella == '-') )
                    {
                        loop = 0;
                    }
                    else
                    {
                        result = 0;
                    }
                }
            }
        }
    }

    return result;
}
