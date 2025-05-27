#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"

int main()
{
    t_fecha fProceso;

    ingresarFechaProceso(&fProceso);
    ///Prueba para ver si lee bien la fecha ingresada
    //printf("La fecha es: %02d/%02d/%d", fechaProceso.dia, fechaProceso.mes, fechaProceso.anio);

    if(abrirArchivos(&fProceso) == TODO_OK)
    {
        ///CREAR MENÚ
    }
    else
        puts("Fin del programa.");

    return 0;
}
