#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#define CAP_INICIAL 100
#define PORCENTAJE_CRECIMIENTO 30
#define OK 0
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

//t_indice *generarIndice(const char *pathSocios, int cantRegistros, int (*cmp)(void *, void *));


/// FUNCIONES DE ENUNCIADO
void indice_crear (t_indice *indice);                                  //LISTO
int indice_insertar (t_indice *indice, const t_reg_indice*);           //HACIENDO
int indice_eliminar(t_indice* ind, t_reg_indice* reg_indice);          //LISTO
int indice_vacio(const t_indice *indice);                              //LISTO
int indice_lleno(const t_indice *indice, unsigned tamDato);            //LISTO
int indice_buscar (const t_indice *indice, t_reg_indice *reg_indice);  //LISTO
int indice_cargar (t_indice *indice, const char* path);                //LISTO
void indice_vaciar(t_indice *indice);                                  //LISTO

void mostrar_indice(const t_indice* ind);

#endif // INDICE_H_INCLUDED
