#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include "indice.h"

int main()
{
    t_fecha fProceso;
    t_indice* indice;
    int cantRegistros = 0;
    //char opcion;

    ingresarFechaProceso(&fProceso);
    ///Prueba para ver si lee bien la fecha
    //printf("La fecha es: %02d/%02d/%d", fechaProceso.dia, fechaProceso.mes, fechaProceso.anio);



    if(abrirArchivos(&fProceso) == TODO_OK)
    {
        ///UNA VEZ ESTÉN BIEN CREADOS LOS ARCHIVOS PROCEDO A CARGAR IDX
        cantRegistros = contarCantidadRegistrosBin(ARCH_BIN);

//        indice_crear(&indice);
//        indice->cantidad = contarCantidadRegistrosBin(ARCH_BIN);


        mostrarArchBinario(ARCH_BIN, cantRegistros);                ///SOLO PARA MOSTRAR .BIN Y CORROBORAR
        printf("LA CANTIDAD DE REGISTROS ES: %d\n", cantRegistros); ///Imagino que prueba

        //indice = generarIndice(ARCH_BIN, cantRegistros, comparaDniEnIndice);
        //indiceMostrar(indice, cantRegistros);                       ///SOLO PARA MOSTRAR EL INDICE Y CORROBORAR
        fflush(stdin);

        ///CREAR MENÚ
        //opcion = iniciarMenu();

        ///ZONA DE SWITCH PARA FUNCION DEPENDIENDO DE OPCION


    }
    else
        puts("Fin del programa.");


    free(indice);
    return 0;
}
