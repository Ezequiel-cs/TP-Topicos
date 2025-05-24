#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"

int main()
{
    t_fecha fProceso;
    t_indice* indice;
    int cantRegistros = 0;
    char opcion;

    ///ingresarFechaProceso(&fProceso);
    ///Prueba para ver si lee bien la fecha
    //printf("La fecha es: %02d/%02d/%d", fechaProceso.dia, fechaProceso.mes, fechaProceso.anio);
    mostrarFechaSistema(&fProceso);



    if(abrirArchivos(&fProceso) == TODO_OK)
    {
        ///UNA VEZ ESTÉN BIEN CREADOS LOS ARCHIVOS PROCEDO A CARGAR IDX
        cantRegistros = contarCantidadRegistrosBin(ARCH_BIN);
        mostrarArchBinario(ARCH_BIN, cantRegistros);
        printf("LA CANTIDAD DE REGISTROS ES: %d\n", cantRegistros);

        indice = indiceArmar(ARCH_BIN, cantRegistros, comparaDniEnIndice);
        indiceMostrar(indice, cantRegistros);
        fflush(stdin);
        ///CREAR MENÚ
        opcion = iniciarMenu();

        ///ZONA DE SWITCH PARA FUNCION DEPENDIENDO DE OPCION


    }
    else
        puts("Fin del programa.");


    free(indice);
    return 0;
}
