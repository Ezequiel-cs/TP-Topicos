#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#define CAP_INICIAL 100
#define PORCENTAJE_CRECIMIENTO 30
#define INDICE_VACIO 1
#define INDICE_LLENO 1

typedef struct
{
    long dni;
    unsigned nro_reg;
}t_reg_indice;

typedef struct
{
    t_reg_indice *datos;
    int capacidad;
    int cantidad;
}t_indice;

void indice_crear (t_indice *indice);
int indice_vacio(const t_indice *indice);
int indice_lleno(const t_indice *indice, unsigned tamDato);
int indice_insertar (t_indice *indice, const t_reg_indice *pReg);

//t_indice *generarIndice(const char *pathSocios, int cantRegistros, int (*cmp)(void *, void *));


/** FUNCIONES DE ENUNCIADO
void indice_crear (t_indice*);                          //1- LISTO
int indice_insertar (t_indice*, const t_reg_indice*);   //
int indice_eliminar (t_indice*, t_reg_indice*);         //
int indice_vacio(const t_indice *);                     //2- LISTO
int indice_lleno(const t_indice *, unsigned tamDato);   //3- LISTO
int indice_lleno(const t_indice *, unsigned tamDato);   //
int indice_cargar (t_indice*, const char* path);        //
void indice_vaciar(t_indice*);                          //

**/
#endif // INDICE_H_INCLUDED
