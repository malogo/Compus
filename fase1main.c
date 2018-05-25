/*----------------------------------------------------------------
|	Autor: Pere Millan (DEIM, URV)
|	Data:  Abril, Desembre 2017, Maig 2018         Versio: 1.2
|-----------------------------------------------------------------|
|	Nom fitxer: fase1main.c
|   Descripcio: Programa principal de la fase 1 de la practica
|               de Fonaments de Computadors "Guerra de barcos".
|               Pot executar la rutina principal()
|               o be el Joc de proves, cridat amb test().
|-----------------------------------------------------------------|
|   programador/a 1: manueljavier.loira@estudiants.urv.cat
|   programador/a 2: oriol.lopez@estudiants.urv.cat
| ----------------------------------------------------------------*/


#include "barcos2018.h"
#include "rutslib2018.h"

extern void test(void);

int main()
{
    randomize();
    test();   /* Executar Joc de proves */
/*    principal(); */
    return 0;
}
