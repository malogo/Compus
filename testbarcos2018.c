/*----------------------------------------------------------------
|	Autor: Pere Millan (DEIM, URV)
|	Data:  Abril, Desembre 2017. Maig 2018          Versio: 3.1
|-----------------------------------------------------------------|
|	Nom fitxer: testbarcos2018.c
|   Descripcio: Codi en C amb el conjunt de JOC DE PROVES
|               de les rutines a desenvolupar per a la practica
|               de Fonaments de Computadors "Guerra de barcos".
|               Exemple de joc de proves al fitxer testlib2018.c.
|   Rutina a cridar: void test(void);
|-----------------------------------------------------------------|
|   programador/a 1: manueljavier.loira@estudiants.urv.cat
|   programador/a 2: oriol.lopez@estudiants.urv.cat
| ----------------------------------------------------------------*/

#include "barcos2018.h"



#include "rutslib2018.h"

#ifndef __arm__ /* En sistemes no-ARM, podem fer printf's */
#include <stdio.h>  /* declaracio rutina printf() */
#endif

    /* Declaracions "forward" de rutines auxiliars */
void informar(char *missatge);
void informar_resultat(char *missatge, unsigned int num_oks,
                       unsigned int bits_error);
void set_bit_error(unsigned int *bits_error, unsigned int bit0_31);
int get_bit_error(int bits_error, int bit0_31);
unsigned int numCharsInArray(char car, char array[], unsigned int dim);
void mostraTaulell(char taulell[], unsigned int dim);
void mostraTaulellCoords(char taulell[], unsigned int dim);

/* Declarar variables globals definides a altres fitxers */
extern unsigned char nd8, nd9, nd10; /* Promedio de disparos
                                        para tableros de 8x8, 9x9, 10x10 */
extern char matriz_barcos[100];      /* Codigos de los barcos a hundir */
extern char matriz_disparos[100];    /* Codigos de los disparos realizados */

void iniciar_matriz (char matriz[], unsigned int dim, char c)
{
	int dim2;
	int i;
	dim2= dim*dim;
	for (i=0; i < dim2; ++i)
	{
		matriz_disparos[i]=c;
	}
}
/* =====================
   Proves rutina div_mod
   ===================== */
void provar_decide_disparo(unsigned int *num_oks, unsigned int *bits_error)
{
    int result;
    unsigned int quocient, residu;
    char matriz[9];
    int f, c;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (decide_disparo) ...\n");
    iniciar_matriz (matriz, 3, '@');
    matriz[4]='?';
    decide_disparo(f, c, matriz, 3);

    informar_resultat("Final de proves (decide_disparo)", *num_oks, *bits_error);
}





/* Realitzar tots els jocs de proves necessaris */
/* Exemple de joc de proves (de les rutines     */
/*      de llibreria) al fitxer testlib2018.c  */
void test(void)
{
	unsigned int *num_oks;
	unsigned int *bits_error;
	provar_decide_disparo(&num_oks, &bits_error);
	informar_resultat("Probando decide disparo", &num_oks, &bits_error);

	//Lo que haria la profe.

}


/**********************/
/* Rutines auxiliars: */
/**********************/

/* Rutina per mostrar un text per pantalla */
void informar(char *missatge)
{
    /* En sistemes ARM (sense pantalla) no escriu res */
#ifndef __arm__
    printf("%s",missatge);
#endif /* __arm__ */
}


/* Rutina per mostrar un text, numero d'oks i errors concrets per pantalla */
void informar_resultat(char *missatge, unsigned int num_oks,
                       unsigned int bits_error)
{
    /* En sistemes ARM (sense pantalla) no escriu res */
#ifndef __arm__
    int bit;
    printf("%s: %d ok; errors", missatge, num_oks);
    if (0 == bits_error)
        printf(" no\n");
    else
    {   /* Hi ha errors. Indicar quins */
        printf("!! en tests");
        for (bit = 0; bit < 32; bit++)
        {
            if (1 == get_bit_error(bits_error, bit))
                printf(" %d", bit);
        }
        printf("\n");
    }
#endif /* __arm__ */
}


/* Rutina per activar un bit indicatiu d'error en un test */
void set_bit_error(unsigned int *bits_error, unsigned int bit0_31)
{
    *bits_error |= (1<<bit0_31);
}


/* Rutina per consultar un bit indicatiu d'error en un test */
int get_bit_error(int bits_error, int bit0_31)
{
    return ((bits_error >> bit0_31) & 1);
}


unsigned int numCharsInArray(char car, char array[], unsigned int dim)
{
    unsigned int num=0;
    int i, max;
    
    for (i=0, max=dim*dim; i<max; i++)
        if ( array[i] == car )
            num++;
    return num;
}


void mostraTaulell(char taulell[], unsigned int dim)
{
    /* En sistemes ARM (sense pantalla) no escriu res */
#ifndef __arm__
    unsigned int f,c;

    for(f=0; f<dim; f++)
    {
        printf("\n");
        for(c=0; c<dim; c++)
        {
            printf("%c", taulell[f * dim + c] );
        }
    }
    printf("\n");
#endif /* __arm__ */
}


void mostraTaulellCoords(char taulell[], unsigned int dim)
{
    /* En sistemes ARM (sense pantalla) no escriu res */
#ifndef __arm__
    unsigned int f, c;

    printf("\n 12345678");
    if ( dim >= 9 )
        printf("9");
    if ( dim == 10 )
        printf("X");
    for(f=0; f<dim; f++)
    {
        printf("\n%c", 'A'+f );
        for(c=0; c<dim; c++)
        {
            printf("%c", taulell[f*dim+c] );
        }
    }
    printf("\n");
#endif /* __arm__ */
}

