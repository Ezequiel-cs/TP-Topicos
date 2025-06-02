#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"

//#include "cabecera.h"

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


int indice_vacio(const t_indice *indice)
{
    if(indice->cantidad == 0)
        return INDICE_VACIO;
}


int indice_lleno(const t_indice *indice, unsigned tamDato)
{
    (void)tamDato; ///por ahora se supone que no lo voy a usar pinta que lo voy a necesitar en indice_insertar y indice_cargar

    if(indice->cantidad == indice->capacidad)
        return INDICE_LLENO;
}


int indice_insertar (t_indice *indice, const t_reg_indice *pReg)
{
    int i;
    int nuevaCapacidad;
    t_reg_indice *aux;

    if(indice_lleno(indice, sizeof(t_reg_indice)) == INDICE_LLENO)
    {
        nuevaCapacidad = indice->capacidad + ((indice->capacidad * PORCENTAJE_CRECIMIENTO) / 100);

        aux = (t_reg_indice *)realloc(indice->datos, sizeof(t_reg_indice) * nuevaCapacidad);

        if(!aux)
        {
            printf("Error de Ampliacion de Memoria.\n");
            exit(1); //return ERROR;
        }

        indice->datos = aux;                    ///Asigno la nueva memoria a datos
        indice->capacidad = nuevaCapacidad;     ///Asigno la nueva capacidad
    }

    //Inserto de manera ordenada



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
