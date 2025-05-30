#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> ///Para booleanos
#include "indice.h" //Temporal para que no arroje warinings, creo

#define TAMNOMAP 60
#define TAMCAT 12

#define TODO_OK 1
#define ERROR 0

#define FALLA_DATO 1
#define DATO_OK 0
#define ANIOS_RESTA 10
#define FALLA_CADENA "" ///???????????

#define ARCH_TXTS "socios.txt"
#define ARCH_BIN "socios.bin"
#define ARCH_TXTE "socios_error.txt" ///Corregí el error decia "scoios_error.txt"

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


///Main
void ingresarFechaProceso(t_fecha *f);


///Validación de Fecha
int esFechaValida(const t_fecha *f);
int cantDiaMes(int mes, int anio);
bool esBisiesto(int anio);


///Archivos
int abrirArchivos(t_fecha *fProceso);
void leerArchivos(FILE *ptxtS, FILE *pbin, FILE *ptxtE, t_fecha *fProceso);
void cargarEstructura(const char *linea, t_datos *socio);
void cargarArchivoBin(FILE* fpBin, t_datos* linea);
void cargarArchivoErr(FILE* fpTxt, const char* linea);
int contarCantidadRegistrosBin(const char* pathArchBin);
void mostrarArchBinario(const char* pathBin, int cantRegistros);    ///SOLO PARA MOSTRAR .BIN Y CORROBORAR


/// VALIDACIÓN DE DATOS
int validarDatos(t_datos *socio, t_fecha *fProceso);
///Documento
int validarDocumento(long dni);
///Nombre y apellido
char* normalizarApeYNom(char *apeYNom);
void aMayuscula(char *c);
void aMinuscula(char *c);
int esLetra(char c);
///Fecha Nacimiento
int fechaFormal(t_fecha *fechNac, t_fecha *fProceso);
t_fecha restaFecha(t_fecha *fProceso);
///sexo
int validarSexo(char *sexo);
///Fecha Afiliación
int fechaAfiliacion(t_fecha *fechNac, t_fecha *fechAfi, t_fecha *fProceso);
///Categoria
int validarCategoria(char* categoria);
char* cadAMayuscula(char *categoria);
///Última fecha de cuota paga
int fechaUltimaCuotaPaga(t_fecha *fechAfi, t_fecha *fechUltCuot, t_fecha *fProceso);
int comparaFechasMenorEstricto(t_fecha *fechA, t_fecha *fechB);
int comparaFechasMenorIgual(t_fecha *fechA, t_fecha *fechB);
///Estado
int validarEstado(char *estado);


///Menu
char iniciarMenu();
char menuConErr(const char* texto, const char* opciones);

int ComparaAlumnosEnIndice(void *a, void *b);
void bubbleSort(void *vec, size_t cantReg, size_t tamanyo, int (*cmp)(void *, void *));
void interchange(void *a, void *b, size_t tamanyo);
void indiceMostrar(t_indice* idx, int cantRegistros);               ///SOLO PARA MOSTRAR EL INDICE Y CORROBORAR
int comparaDniEnIndice(void *a, void *b);



#endif // CABECERA_H_INCLUDED
