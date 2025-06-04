#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include "indice.h"

int main()
{
    t_fecha fProceso;
    t_indice indice;
    char opcion;

    ingresarFechaProceso(&fProceso);

    if(abrirArchivos(&fProceso) != TODO_OK)
    {
        puts("Fin del programa.");
        return 0;
    }

    ///1. Creo indice
    indice_crear(&indice);

    ///ARMO ARCHIVO .BIN A PARTIR DE .TXT Y GENERO TAMBIEN ARCHERROR.TXT
    abrirArchivos(&fProceso);

    ///2. Cargo el indice,
    indice_cargar(&indice, ARCH_BIN);

    ///SOLO ESTÁ PARA CORROBORAR QUE EL STRUCT INDICE ESTÁ BIEN
    mostrar_indice(&indice);

    ///CREAR MENÚ
    do
    {
        opcion = iniciarMenu();             ///3. Se inicia el menu
        cargarMenu(&indice, opcion);        ///4. Voy al switch

    }while(opcion != 'S');

    indice_vaciar(&indice);
    return 0;
}
