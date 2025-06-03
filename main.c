#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include "indice.h"

int main()
{
    t_fecha fProceso;
    t_indice indice;
    int cantRegistros = 0;
    char opcion;

    ingresarFechaProceso(&fProceso);

    if(abrirArchivos(&fProceso) != TODO_OK)
    {
        puts("Fin del programa.");
        return 0;
    }

    indice_crear(&indice);                  ///1. Creo indice

    cantRegistros = contarCantidadRegistrosBin(ARCH_BIN);
    indice.cantidad = cantRegistros;

    indice_cargar(&indice, ARCH_BIN);       ///2. Cargo el indice, deberia verificar que el indice este vacio?

    ///CREAR MENÚ
    do
    {
        opcion = iniciarMenu();             ///3. Se inicia el menu
        cargarMenu(&indice, opcion);        ///4. Voy al switch

    }while(opcion != 'S');

    indice_vaciar(&indice);
    return 0;
}
