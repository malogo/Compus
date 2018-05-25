/*----------------------------------------------------------------
|	Autor: Pere Millan, Susana Alvarez (DEIM, URV)
|	Data:  Maig, Desembre 2017, Maig 2018          Versio: 3.1
|-----------------------------------------------------------------|
|	Nom fitxer: testlib2018.c
|   Descripcio: Codi en C d'un possible JOC DE PROVES
|               de les rutines de llibreria de la practica
|               de Fonaments de Computadors "Guerra de barcos".
|   Rutina a cridar: void test(void);
| ----------------------------------------------------------------*/

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


/* =====================
   Proves rutina div_mod
   ===================== */
void provar_div_mod(unsigned int *num_oks, unsigned int *bits_error)
{
    int result;
    unsigned int quocient, residu;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (div_mod) ...\n");

    /*--------------------------------------------------
       prova 1: Divisio exacta: 12345/15 = 823 (r = 0) */
    result = div_mod(12345, 15, &quocient, &residu);
    if (0==result && 823==quocient && 0==residu)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 1);
        informar("#ERROR provant divisio exacta (div_mod)\n");
    }
    /*--------------------------------------------------
       prova 2: Divisio inexacta: 54321/15 = 3621 (r = 6) */
    result = div_mod(54321, 15, &quocient, &residu);
    if (0==result && 3621==quocient && 6==residu)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 2);
        informar("#ERROR provant divisio inexacta (div_mod)\n");
    }
    /*--------------------------------------------------
       prova 3: Divisio entre zero */
    result = div_mod(54321, 0, &quocient, &residu);
    if (1==result)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 3);
        informar("#ERROR provant divisio entre 0 (div_mod)\n");
    }
    /*--------------------------------------------------
       prova 4: Adreça quocient no alineada @ x4 */
    result = div_mod(1, 2, (unsigned int *)3, &residu);
    if (2==result)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 4);
        informar("#ERROR provant quocient no alineat @ x4 (div_mod)\n");
    }
    /*--------------------------------------------------
       prova 5: Adreça residu no alineada @ x4 */
    result = div_mod(1, 2, &quocient, (unsigned int *)3);
    if (2==result)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 5);
        informar("#ERROR provant residu no alineat @ x4 (div_mod)\n");
    }
    /*--------------------------------------------------
     prova 6: Adreça quocient i residu iguals */
    result = div_mod(1, 2, &quocient, &quocient);
    if (3==result)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 6);
        informar("#ERROR provant @quocient == @residu (div_mod)\n");
    }
    /*-------------------------------------------------- */

    informar_resultat("Final de proves (div_mod)", *num_oks, *bits_error);
}


/* RUTINES DE PROVA MES COMPLEXES: */

/* Cridar varies vegades a mod_random
    i comprovar el maxim i minim.
    Retorna 'true' si el maxim i minim son els esperats */
int mod_random__multiTest(
                            /* parametre de la crida a mod_random() */
                          unsigned int paramModRandom,
                            /* numero de vegades que es crida a mod_random() */
                          unsigned int numCrides,
                            /* valors minim i maxim esperats */
                          int minEsperat, int maxEsperat
                          )
{
    int max = -1, min = 1<<30;  /* Maxim molt petit, minim molt gran */
    int aleatori, i;

    for(i=0; i<numCrides; i++)
    {
        aleatori = mod_random(paramModRandom);
        if (aleatori>max)
            max = aleatori;
        if (aleatori<min)
            min = aleatori;
    }
    return (min == minEsperat) && (max == maxEsperat);
}


/* ========================
   Proves rutina mod_random
   ======================== */
void provar_mod_random(unsigned int *num_oks, unsigned int *bits_error)
{
    int result;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (mod_random) ...\n");

    /*--------------------------------------------------
       prova 1: numero dins de limits (parametre 2-255) */
    result = mod_random(123);
    if (result>=0 && result<123)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 1);
        informar("#ERROR resultat fora de rang (mod_random)\n");
    }
    /*--------------------------------------------------
       prova 2: parametre <2 ha de considerar-se 2 */
    result = mod_random(0);
    if (0==result || 1==result)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 2);
        informar("#ERROR amb parametre massa petit (mod_random)\n");
    }
    /*--------------------------------------------------
       prova 3: parametre >255 ha de considerar-se 255 */
    result = mod_random(12345);
    if (result>=0 && result<255)
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 3);
        informar("#ERROR amb parametre massa gran (mod_random)\n");
    }
    /*--------------------------------------------------
       prova 4: multiples crides han d'estar dins de limits */
    result = mod_random__multiTest(123, 5000, 0, 122);
    if ( result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 4);
        informar("#ERROR min/max fora de rang (mod_random)\n");
    }
    /*--------------------------------------------------
       prova 5: multiples crides amb parametre <2 han d'estar dins de limits */
    result = mod_random__multiTest(1, 100, 0, 1);
    if ( result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 5);
        informar("#ERROR amb param<2: min/max fora de rang (mod_random)\n");
    }
    /*--------------------------------------------------
       prova 6: multiples crides amb parametre >255 han d'estar dins de limits */
    result = mod_random__multiTest(1234, 5000, 0, 254);
    if ( result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 6);
        informar("#ERROR amb param>255: min/max fora de rang (mod_random)\n");
    }
    /*-------------------------------------------------- */

    informar_resultat("Final de proves (mod_random)", *num_oks, *bits_error);
}


/* =================================
   Proves rutina B_inicializa_barcos
   ================================= */
void provar_B_inicializa_barcos(unsigned int *num_oks, unsigned int *bits_error)
{
    char taulell_vaixells[100]; /* Taulell per a proves */
    unsigned int numCasellesAigua, numCasellesVaixell;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (B_inicializa_barcos) ...\n");

    /*--------------------------------------------------
       prova 1: amb 8x8 ha d'haver-hi 20 caselles vaixell i 44 aigues */
    B_inicializa_barcos(taulell_vaixells, 8);
    numCasellesVaixell=numCharsInArray('@', taulell_vaixells, 8);
    numCasellesAigua = numCharsInArray('.', taulell_vaixells, 8);
    if ( 20==numCasellesVaixell && 44==numCasellesAigua )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 1);
        informar("#ERROR caselles vaixell/aigua incorrectes (8x8)\n");
    }
    /*--------------------------------------------------
       prova 2: amb 9x9 ha d'haver-hi 20 caselles vaixell i 61 aigues */
    B_inicializa_barcos(taulell_vaixells, 9);
    numCasellesVaixell=numCharsInArray('@', taulell_vaixells, 9);
    numCasellesAigua = numCharsInArray('.', taulell_vaixells, 9);
    if ( 20==numCasellesVaixell && 61==numCasellesAigua )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 2);
        informar("#ERROR caselles vaixell/aigua incorrectes (9x9)\n");
    }
    /*--------------------------------------------------
       prova 3: amb 10x10 ha d'haver-hi 20 caselles vaixell i 80 aigues */
    B_inicializa_barcos(taulell_vaixells, 10);
    numCasellesVaixell=numCharsInArray('@', taulell_vaixells, 10);
    numCasellesAigua = numCharsInArray('.', taulell_vaixells, 10);
    if ( 20==numCasellesVaixell && 80==numCasellesAigua )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 3);
        informar("#ERROR caselles vaixell/aigua incorrectes (10x10)\n");
    }
    /*-------------------------------------------------- */

    informar_resultat("Final de proves (B_inicializa_barcos)", *num_oks, *bits_error);
}


/* =======================
   Proves rutina B_dispara
   ======================= */
void provar_B_dispara(unsigned int *num_oks, unsigned int *bits_error)
{
    int result, c;
    unsigned int nTocats, nEnfonsats, nAigues;
    char taulell_vaixells[100]; /* Taulell per a proves */
    char f;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (B_dispara) ...\n");

    /*--------------------------------------------------
       prova 1: fora de limits immediats (Nord) ha de donar error (-1) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('A'-1, 5);
    if ( ERROR == result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 1);
        informar("#ERROR: no detecta fora limit superior (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 2: fora de limits immediats (Sud) ha de donar error (-1) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('A'+8, 5);
    if ( ERROR == result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 2);
        informar("#ERROR: no detecta fora limit inferior (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 3: fora de limits immediats (Est) ha de donar error (-1) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('C', 9);
    if ( ERROR == result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 3);
        informar("#ERROR: no detecta fora limit dret (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 4: fora de limits immediats (Oest) ha de donar error (-1) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('C', 0);
    if ( ERROR == result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 4);
        informar("#ERROR: no detecta fora limit esquerre (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 5: acces a limit interior superior no ha de donar error (1..3) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('A', 5);
    if ( AGUA==result || TOCADO==result || HUNDIDO==result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 5);
        informar("#ERROR: acces incorrecte limit superior (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 6: acces a limit interior inferior no ha de donar error (1..3) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('H', 5);
    if ( AGUA==result || TOCADO==result || HUNDIDO==result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 6);
        informar("#ERROR: acces incorrecte limit inferior (B_dispara)\n");
    }
    /*--------------------------------------------------
      prova 7: acces a limit interior dret no ha de donar error (1..3) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('C', 8);
    if ( AGUA==result || TOCADO==result || HUNDIDO==result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 7);
        informar("#ERROR: acces incorrecte limit dret (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 8: acces a limit interior esquerre no ha de donar error (1..3) */
    B_inicializa_barcos(taulell_vaixells, 8);
    result=B_dispara('C', 1);
    if ( AGUA==result || TOCADO==result || HUNDIDO==result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 8);
        informar("#ERROR: acces incorrecte limit esquerre (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 9: tret a la mateixa posicio ha de detectar repetit (0) */
    B_inicializa_barcos(taulell_vaixells, 8);
    B_dispara('F', 4);
    result = B_dispara('F', 4);
    if ( REPETIDO == result )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 9);
        informar("#ERROR: no detecta tret repetit (B_dispara)\n");
    }
    /*--------------------------------------------------
       prova 10: trets a totes les caselles d'un taulell 8x8 ha de donar:
                 10 tocats, 10 enfonsats, 44 aigues */
    B_inicializa_barcos(taulell_vaixells, 8);
    nTocats = 0;
    nEnfonsats = 0;
    nAigues = 0;
    for (f='A'; f<='H'; f++)
        for (c=1; c<=8; c++)
        {
            result=B_dispara(f, c);
            if (AGUA==result)
                nAigues++;
            if (TOCADO==result)
                nTocats++;
            if (HUNDIDO==result)
                nEnfonsats++;
        }
    if ( 10==nTocats && 10==nEnfonsats && 44==nAigues )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 10);
        informar("#ERROR: num. total aigues/tocats/enfonsats 8x8 (B_dispara)\n");
    }

    /*-------------------------------------------------- */

    informar_resultat("Final de proves (B_dispara)", *num_oks, *bits_error);
}

/* ============================
   Proves rutina B_num_disparos
   ============================ */
void provar_B_num_disparos(unsigned int *num_oks, unsigned int *bits_error)
{
    char taulell_vaixells[100]; /* Taulell per a proves */

    int numTrets, trets;

    /* Inicialitzar control errors */
    *num_oks = 0;
    *bits_error = 0;

    informar("\nIniciant proves (B_num_disparos) ...\n");

    /*--------------------------------------------------
       prova 1: despres d'inicialitzar no hi ha d'haver trets */
    B_inicializa_barcos(taulell_vaixells, 9);
    numTrets = B_num_disparos();
    if ( 0==numTrets )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 1);
        informar("#ERROR: hi ha trets inicialment (B_num_disparos)\n");
    }
    /*--------------------------------------------------
       prova 2: el nombre de trets ha de coincidir amb les crides a B_dispara */
    B_inicializa_barcos(taulell_vaixells, 10);
    for (trets=0; trets<50; trets++)
        B_dispara('E',4);
    numTrets = B_num_disparos();
    if ( 50==numTrets )
        (*num_oks)++;
    else
    {
        set_bit_error(bits_error, 2);
        informar("#ERROR: trets comptats malament (B_num_disparos)\n");
    }
    /*-------------------------------------------------- */

    informar_resultat("Final de proves (B_num_disparos)", *num_oks, *bits_error);
}


/*////////////////////////////////////
   Joc de proves
//////////////////////////////////////
   Realitzar tots els jocs de proves */

/* Variables globals per desar resultats */
/* i poder consultar-les en fase 2 */
/* doncs no tindrem printf a pantalla */
unsigned int ok_div_mod, errors_div_mod;
unsigned int ok_mod_rand, errors_mod_rand;
unsigned int ok_Bini, errors_Bini;
unsigned int ok_Bdisp, errors_Bdisp;
unsigned int ok_Bnum, errors_Bnum;

void test(void)
{
    informar("\nIniciant Joc de proves GLOBAL ...\n");

    provar_div_mod(&ok_div_mod, &errors_div_mod);

    provar_mod_random(&ok_mod_rand, &errors_mod_rand);

    provar_B_inicializa_barcos(&ok_Bini, &errors_Bini);

    provar_B_dispara(&ok_Bdisp, &errors_Bdisp);

    provar_B_num_disparos(&ok_Bnum, &errors_Bnum);

    informar( "\nFinal Joc de proves GLOBAL\n" );
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

