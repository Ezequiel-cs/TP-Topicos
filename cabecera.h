#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> ///Para booleanos
#include <time.h> ///Para la fecha actual

#define TAMNOMAP 60
#define TAMCAT 10

#define TODO_OK 1
#define ERROR 0

#define FALLA_DATO 1
#define DATO_OK 0

#define ARCH_TXTS "socios.txt"
#define ARCH_BIN "socios.bin"
#define ARCH_TXTE "scoios_error.txt"

#define TAM_LINEA 256


typedef struct{
    int dia;
    int mes;
    int anio;
}t_fecha;

typedef struct{
    long dni;
    char nomAp[TAMNOMAP];
    t_fecha fechNac;
    char sexo;
    t_fecha fechAfi;
    char categoria[TAMCAT];
    t_fecha fechUltCuot;
    char estado;
}t_datos;

typedef struct{
    long dni;
    int pos;
}t_indice;

///Main
void ingresarFechaProceso(t_fecha *f);
//void mostrarVector(t_datos* vPersonas);   // se debería ir

///Menu
char iniciarMenu();
char menuConErr(const char* texto, const char* opciones);


///Archivos
int abrirArchivos(t_fecha *fProceso);
void leerArchivos(FILE *ptxtS, FILE *pbin, FILE *ptxtE, t_fecha *fProceso);
void cargarEstructura(const char *linea, t_datos *socio);
void cargarArchivoBin(FILE* fpBin, t_datos* linea);
void cargarArchivoErr(FILE* fpTxt, const char* linea);
int contarCantidadRegistrosBin(const char* pathArchBin);
void mostrarArchBinario(const char* pathBin, int cantRegistros);///SOLO PARA MOSTRAR .BIN Y CORROBORAR

///INDICE
int ComparaAlumnosEnIndice(void *a, void *b);
t_indice* indiceArmar(const char *pathAlus, int cantRegistros, int (*cmp)(void *, void *));
void bubbleSort(void *vec, size_t cantReg, size_t tamanyo, int (*cmp)(void *, void *));
void interchange(void *a, void *b, size_t tamanyo);
void indiceMostrar(t_indice* idx, int cantRegistros);///SOLO PARA MOSTRAR EL INDICE Y CORROBORAR
int comparaDniEnIndice(void *a, void *b);

/// VALIDACIÓN DE DATOS
int validarDatos(t_datos *socio, t_fecha *fProceso);
int validarDocumento(long dni);
char* normalizarApeYNom(char *apeYNom);
int fechaFormal(t_fecha *fechNac, t_fecha *fProceso);
int validarSexo(char *sexo);
void aMayuscula(char *c);
int fechaAfiliacion(t_fecha *fechNac, t_fecha *fechAfi, t_fecha *fProceso);
int validarCategoria(char* categoria);
char* cadAMayuscula(char *categoria);
int fechaUltimaCuotaPaga(t_fecha *fechAfi, t_fecha *fechUltCuot, t_fecha *fProceso);
int validarEstado(char *estado);

///Validación de Fecha
int esFechaValida(const t_fecha *f);
int cantDiaMes(int mes, int anio);
bool esBisiesto(int anio);
void mostrarFechaSistema(const t_fecha* f);



#endif // CABECERA_H_INCLUDED
