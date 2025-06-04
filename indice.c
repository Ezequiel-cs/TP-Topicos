#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"
#include "cabecera.h"

//#include "cabecera.h"
void mostrar_indice(const t_indice* ind)
{
    printf("=== CONTENIDO DEL ÍNDICE ===\n");
    for(int i = 0; i < ind->cantidad; i++)
    {
        printf("DNI: %ld | Nro Registro: %u\n",
               ind->datos[i].dni,
               ind->datos[i].nro_reg);
    }
    printf("=== FIN DEL ÍNDICE ===\n");
}

void indice_crear (t_indice *indice)
{
    indice->datos = (t_reg_indice *)malloc(sizeof(t_reg_indice) * CAP_INICIAL);

    if(!indice->datos)
    {
        printf("Error de Reserva de Memoria.\n");
        indice->capacidad = 0;
        indice->cantidad = 0;
        exit(1);
    }

    indice->capacidad = CAP_INICIAL;
    indice->cantidad = 0;
}


//int indice_insertar (t_indice *indice, const t_reg_indice *pReg)
//{
////    int i;
////    int nuevaCapacidad;
////    t_reg_indice *aux;
////
////    if(indice_lleno(indice, sizeof(t_reg_indice)) == INDICE_LLENO)
////    {
////        nuevaCapacidad = indice->capacidad + ((indice->capacidad * PORCENTAJE_CRECIMIENTO) / 100);
////
////        aux = (t_reg_indice *)realloc(indice->datos, sizeof(t_reg_indice) * nuevaCapacidad);
////
////        if(!aux)
////        {
////            printf("Error de Ampliacion de Memoria.\n");
////            exit(1); //return ERROR;
////        }
////
////        indice->datos = aux;                    ///Asigno la nueva memoria a datos
////        indice->capacidad = nuevaCapacidad;     ///Asigno la nueva capacidad
////    }
////
////    //Inserto de manera ordenada
////
////
//    return 0;
//}


int indice_eliminar(t_indice* ind, t_reg_indice* reg_indice)
{
    int i, j;

    // Buscar la posición del DNI en el índice
    for (i = 0; i < ind->cantidad; i++) {
        if (ind->datos[i].dni == reg_indice->dni)
            break;
    }

    // Si no se encontró, no hacemos nada
    if (i == ind->cantidad) {
        printf("DNI no encontrado en el índice.\n");
        return 0;
    }

    // Desplazar todos los elementos a la izquierda desde la posición i+1
    for (j = i; j < ind->cantidad - 1; j++) {
        ind->datos[j] = ind->datos[j + 1];
    }

    // Reducir la cantidad de elementos
    ind->cantidad--;

    printf("Registro eliminado del índice correctamente.\n");
    return 0;
}


int indice_vacio(const t_indice *indice)
{
    if(indice->cantidad == 0)
        return INDICE_VACIO;

    return OK;
}


int indice_lleno(const t_indice *indice, unsigned tamDato)
{
    if(indice->cantidad == indice->capacidad)
        return INDICE_LLENO;

    return OK;
}


int indice_buscar(const t_indice* indice, t_reg_indice* reg_indice)
{
    int i = 0;

    while(i!=indice->cantidad)
    {
        if(reg_indice->dni == indice->datos[i].dni)
        {
            reg_indice->nro_reg = indice->datos[i].nro_reg;
        }
        i++;
    }

    ///printf("El registro se encuentra en la pos: %d\n\n\n", (int)reg_indice->nro_reg);

    return 0;
}


int indice_cargar(t_indice *indice, const char* path)
{
    FILE* fpBin;
    t_datos persona;
    t_reg_indice regInd;
    int posInd = 0;

    fpBin = fopen(path, "rb");
    if(fpBin == NULL)
    {
        printf("EL ARCHIVO NO PUDO SER GENERADO");
        return -1;
    }

    fread(&persona, sizeof(t_datos), 1, fpBin);
    while(!feof(fpBin))
    {

        if(persona.estado == 'A')
        {

            regInd.dni = persona.dni;
            regInd.nro_reg = posInd;
            if(!indice_insertar(indice, &regInd))
            {
                printf("NO SE PUDO AGREGAR PERSONA");
                return -1;
            }
        }
         posInd++;
         fread(&persona, sizeof(t_datos), 1, fpBin);
    }

    fclose(fpBin);
    return 0;
}
int indice_insertar(t_indice* ind, const t_reg_indice* elem)
{
    /// SI NO HAY ESPACIO REDIMENCIONO. POR ESO LA PREGUNTA
    if (ind->cantidad == ind->capacidad)
    {
        int nuevaCapacidad = ind->capacidad + (ind->capacidad * PORCENTAJE_CRECIMIENTO) / 100;
        void* nuevoVDato = realloc(ind->datos, nuevaCapacidad * sizeof(t_reg_indice));
        if (!nuevoVDato)
        {
            printf("OJO QUE HUBO PROBLEMA CON LA MEMORIA\n");
            return 0;
        }

        ind->datos = nuevoVDato;
        ind->capacidad = nuevaCapacidad;
    }

    /// Busco la posición de inserción manteniendo orden por DNI
    int i = ind->cantidad - 1;
    while (i >= 0 && ind->datos[i].dni > elem->dni)
    {
        ind->datos[i + 1] = ind->datos[i];  /// desplazamos a la derecha
        i--;
    }

    /// Inserta el nuevo elemento
    ind->datos[i + 1] = *elem;
    ind->cantidad++;

    return 1;
}


void indice_vaciar(t_indice *indice)
{
    free(indice->datos);
    indice->datos = NULL;
    indice->cantidad = 0;
    indice->capacidad = 0;
}








//t_indice *generarIndice(const char *pathSocios, int cantRegistros, int (*cmp)(void *, void *))
//{
//    t_indice *indice;
//    FILE *fpBin;
//    t_datos dato;
//    int i = 0;
//    j = 0, cantAltas = 0;
//
//    fpBin = fopen(ARCH_BIN, "rb");
//    if(fpBin == NULL)
//    {
//        printf("ERROR AL ABRIR ARCHIVO BINARIO");
//        exit(0);
//    }
//
//    indice = (t_indice *)malloc(sizeof(t_indice) * cantRegistros);
//
//    if(!indice)
//    {
//        printf("ERROR EN LA RESERVA DE MEMORIA");
//        system("PAUSE");
//        exit(1);
//    }
//
//    fread(&dato, sizeof(dato), 1, fpBin);
//    while(!feof(fpBin))
//    {
//
//        if(dato.estado == 'A')  ///Modificar, ya que asumimon que todos vienen con 'A' por defecto
//        {
//            indice[i].dni = dato.dni;
//            indice[i].pos = j;
//            i++;
//            cantAltas++;
//            fread(&dato, sizeof(dato), 1, fpBin);
//        }else{
//            fread(&dato, sizeof(dato), 1, fpBin);
//        }
//
//        j++;
//    }
//    while(!feof(fpBin))
//    {
//        indice[i].dni = dato.dni;
//        indice[i].pos = i;
//        i++;
//        fread(&dato, sizeof(dato), 1, fpBin);
//    }
//
//    fclose(fpBin);
//
//    bubbleSort(indice, cantRegistros, sizeof(t_indice), cmp);
//
//    return indice;
//}
