#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> ///Para booleanos

#define TAMNOMAP 60
#define TAMCAT 10

#define TODO_OK 1
#define ERROR 0

#define FALLA_DATO 1
#define DATO_OK 0
#define ANIOS_RESTA 10

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

///Main
void ingresarFechaProceso(t_fecha *f);
//void mostrarVector(t_datos* vPersonas);   // se debería ir

///Archivos
int abrirArchivos(t_fecha *fProceso);
void leerArchivos(FILE *ptxtS, FILE *pbin, FILE *ptxtE, t_fecha *fProceso);
void cargarEstructura(const char *linea, t_datos *socio);

/// VALIDACIÓN DE DATOS
int validarDatos(t_datos *socio, t_fecha *fProceso);
int validarDocumento(long dni);
char* normalizarApeYNom(char *apeYNom);
int fechaFormal(t_fecha *fechNac, t_fecha *fProceso);
/**  10-05  **/
t_fecha restaFecha(t_fecha *fProceso);
/**  10-05  **/
int validarSexo(char *sexo);
void aMayuscula(char *c);
int fechaAfiliacion(t_fecha *fechNac, t_fecha *fechAfi, t_fecha *fProceso);
int comparaFechasMenorEstricto(t_fecha *fechA, t_fecha *fechB);
int comparaFechasMenorIgual(t_fecha *fechA, t_fecha *fechB);
int validarCategoria(char* categoria);
char* cadAMayuscula(char *categoria);
int fechaUltimaCuotaPaga(t_fecha *fechAfi, t_fecha *fechUltCuot, t_fecha *fProceso);
int validarEstado(char *estado);

///Validación de Fecha
int esFechaValida(const t_fecha *f);
int cantDiaMes(int mes, int anio);
bool esBisiesto(int anio);

#endif // CABECERA_H_INCLUDED
