#include "cabecera.h"

void ingresarFechaProceso(t_fecha *f)
{
    printf("Bienvenido/a.\nIngrese fecha de proceso (DD/MM/AAAA): ");
    scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);

    while(esFechaValida(f) != TODO_OK)
    {
        printf("Fecha invalida.\nIngrese nuevamente (DD/MM/AAAA): ");
        scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);
    }
}


/*************************************** Validación de Fecha - INICIO ***************************************/

int esFechaValida(const t_fecha *f)
{
    if(f->anio >= 1601)
        if(f->mes >= 1 && f->mes <= 12)
            if(f->dia >= 1 && f->dia <= cantDiaMes(f->mes, f->anio))
                return TODO_OK;
    return ERROR;
}


int cantDiaMes(int mes, int anio)
{
    int diaMes [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; ///La posición 0 no la uso, empiezo en la poscicion 1 = enero

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return diaMes[mes];
}


bool esBisiesto(int anio)  ///Pregunar si se puede usar booleanos.
{
    return ((anio%4 == 0 && anio%100 != 0) || anio%400 == 0); ///me devuelve true o false
}

void mostrarFechaSistema(const t_fecha* f)
{
    time_t t = time(NULL);
    struct tm* fechaSistema = localtime(&t);

    int dia = fechaSistema->tm_mday;
    int mes = fechaSistema->tm_mon + 1;
    int anio = fechaSistema->tm_year + 1900;

    printf("Fecha del sistema: %02d/%02d/%d\n", dia, mes, anio);
}

/*************************************** Menu Opciones ***************************************/

char iniciarMenu()
{
    char opcion;
    opcion = menuConErr("Elijir una Opcion\n\n"
                        "A - Alta\n"
                        "B - Baja\n"
                        "C - Modificacion\n"
                        "D - Mostrar Informacion de un Socio\n"
                        "E - Listado de Socios Ordenados por DNI\n"
                        "F - Salir\n"
                        "--->",
                        "ABCDEFabcdef");
    printf("Opcion elegido: %c\n", opcion);

    return opcion;
}

char menuConErr(const char* mensaje, const char* opciones)
{
    char esOpcion;
    int priVez = 1;

    do
    {
        printf("%s%s",
               priVez ? priVez = 0, "" : "ERROR - OPCION NO VALIDA.\n",
               mensaje);
        fflush(stdin);
        scanf("%c", &esOpcion);
    }while(strchr(opciones, esOpcion)==NULL);
    return esOpcion;
}

/*************************************** Generar Idx  ***************************************/
int contarCantidadRegistrosBin(const char* pathArchBin)
{
    int cantRegistros = 0;
    FILE* fpBin;
    t_datos datos;

    fpBin = fopen(pathArchBin, "rb");
    if(fpBin == NULL)
    {
        printf("ERROR AL ABRIR ARCHIVO BINARIO");
        return -1;
    }

    fread(&datos, sizeof(datos),1,fpBin);

    while(!feof(fpBin))
    {
        cantRegistros++;
        fread(&datos, sizeof(datos),1,fpBin);
    }

    fclose(fpBin);
    return cantRegistros;
}

t_indice* indiceArmar(const char *pathAlus, int cantRegistros, int (*cmp)(void *, void *))
{
    t_indice* indice;
    FILE *fpBin;
    t_datos dato;
    int i = 0, j = 0, cantAltas = 0;

    fpBin = fopen(pathAlus, "rb");
    if(fpBin == NULL)
    {
        printf("ERROR AL ABRIR ARCHIVO BINARIO");
        exit(0);
    }

    indice = (t_indice *)malloc(sizeof(t_indice) * cantRegistros);
    if(!indice)
    {
        printf("ERROR EN LA RESERVA DE MEMORIA");
        system("PAUSE");
        exit(1);
    }

    fread(&dato, sizeof(dato), 1, fpBin);
    while(!feof(fpBin))
    {

        if(dato.estado == 'A')
        {
            indice[i].dni = dato.dni;
            indice[i].pos = j;
            i++;
            cantAltas++;
            fread(&dato, sizeof(dato), 1, fpBin);
        }else{
            fread(&dato, sizeof(dato), 1, fpBin);
        }

        j++;
    }

    bubbleSort(indice, cantAltas, sizeof(t_indice), cmp);

    fclose(fpBin);
    return indice;
}

void bubbleSort(void *vec, size_t cantReg, size_t tamanyo, int (*cmp)(void *, void *))
{
    int i, j;

    for(i = 0; i < cantReg; i++)
        for(j = 0; j < cantReg - 1; j++)
            if(cmp(vec + j * tamanyo,  vec + (j + 1) * tamanyo) > 0)
                interchange(vec + j * tamanyo,  vec + (j + 1) * tamanyo, tamanyo);
}

void interchange(void *a, void *b, size_t tamanyo)
{
    char *aux = malloc(tamanyo);

    memcpy(aux, a, tamanyo);
    memcpy(a, b, tamanyo);
    memcpy(b, aux, tamanyo);

    free(aux);
}

int comparaDniEnIndice(void *a, void *b)
{
    t_indice *idx1 = (t_indice *)a;
    t_indice *idx2 = (t_indice *)b;

    return idx1->dni - idx2->dni;
}

void indiceMostrar(t_indice* idx, int cantRegistros)
{

    printf("\nCONTENIDO DEL INDICE: \n");
    for(int i=0;i<cantRegistros; i++)
    {
        printf("%ld \t %d", idx[i].dni, idx[i].pos);
        printf("\n");
    }
}


/*************************************** Flujo - Inicio ***************************************/

int abrirArchivos(t_fecha *fProceso)
{
    FILE *ptxtS, *pbin, *ptxtE; ///ptxtS = texto Socio | ptxtE = texto Error

    ptxtS = fopen(ARCH_TXTS, "rt");
    pbin = fopen(ARCH_BIN, "wb");
    ptxtE = fopen(ARCH_TXTE, "wt");

    if(!ptxtS || !pbin || !ptxtE)
    {
        printf("Error al abrir Archivos.");
        return ERROR;
    }

    leerArchivos(ptxtS, pbin, ptxtE, fProceso);

    fclose(ptxtS);
    fclose(pbin);
    fclose(ptxtE);

    return TODO_OK;
}


void leerArchivos(FILE *ptxtS, FILE *pbin, FILE *ptxtE, t_fecha *fProceso)
{
    char linea[TAM_LINEA];
    t_datos socio;


    while(fgets(linea, TAM_LINEA, ptxtS))
    {
        cargarEstructura(linea, &socio);
        ///LEO UNA LINEA Y DECIDE EL IF

        if(validarDatos(&socio, fProceso) == 0)
        {
            ///ESCRIBO ARCHIVO BINARIO
            cargarArchivoBin(pbin, &socio);
        }
        else
        {
            ///ESCRIBO ARCHIVO ERROR
            cargarArchivoErr(ptxtE, linea);
        }
    }
}

void mostrarArchBinario(const char* pathBin, int cantRegistros)
{
    FILE* fpBin;
    t_datos dato;

    fpBin = fopen(pathBin, "rb");
    if(fpBin == NULL)
    {
        printf("NO SE PUDO ABRIR EL ARCHIVO BINARIO");
        return;
    }

    printf("CONTENIDO DEL ARCHIVO BINARIO: \n\n");
    fread(&dato, sizeof(t_datos), 1, fpBin);
    while(!feof(fpBin))
    {
        printf("%d\t%s\t%c\n", (int)dato.dni, dato.nomAp, dato.estado);
        fread(&dato, sizeof(t_datos), 1, fpBin);
    }

    fclose(fpBin);

}

void cargarArchivoBin(FILE* fpBin, t_datos* linea)
{
    fwrite(linea, sizeof(t_datos), 1, fpBin);
}

void cargarArchivoErr(FILE* fpTxt, const char* linea)
{
    fprintf(fpTxt, "%s", linea);
}

void cargarEstructura(const char *linea, t_datos *socio)
{
    sscanf(linea, "%ld|%[^|]|%d/%d/%d|%c|%d/%d/%d|%[^|]|%d/%d/%d|%c",
           &socio->dni,
           socio->nomAp,                                                    ///no pongo '&' porque ya es un puntero
           &socio->fechNac.dia, &socio->fechNac.mes, &socio->fechNac.anio,
           &socio->sexo,
           &socio->fechAfi.dia, &socio->fechAfi.mes, &socio->fechAfi.anio,
           socio->categoria,                                                ///no pongo '&' porque ya es un puntero
           &socio->fechUltCuot.dia, &socio->fechUltCuot.mes, &socio->fechUltCuot.anio,
           &socio->estado);
}

/*
void trozarCamposLongVariable(t_datos* d, char* cad)
{
    char* aux = strchr(cad, '\n');
    *aux = '\0';

    aux = strrchr(cad, '|');
    d->estado = aux;
    *aux='\0';

}
*/

/** CREO QUE ESTA FUNCION SE VA **/
//void mostrarVector(t_datos* vPersonas)
//{
//    printf("Datos sobre socios: \n");
//    for(int i = 0; i<2; i++)
//    {
//        printf("PERSONA [%d]:\n", i);
//        printf("%lg\t%s  %d/%d/%d   %c   %d/%d/%d\t%s\t%d/%d/%d   %c\n", vPersonas->dni,vPersonas->nomAp, vPersonas->fechNac.dia,vPersonas->fechNac.mes,vPersonas->fechNac.anio,
//        vPersonas->sexo, vPersonas->fechAfi.anio, vPersonas->fechAfi.mes, vPersonas->fechAfi.dia, vPersonas->categoria,
//        vPersonas->fechUltCuot.anio, vPersonas->fechUltCuot.mes, vPersonas->fechUltCuot.dia, vPersonas->estado);
//        vPersonas++;
//    }
//}

int validarDatos(t_datos *socio, t_fecha *fProceso)
{
   int hayError = 0;

    ///Documento
    hayError += validarDocumento(socio->dni);

    ///Nombre y apellido
    normalizarApeYNom(socio->nomAp); ///No valido nada, solo normalizo.

    ///FechaNacimiento
    if(esFechaValida(&socio->fechNac) == TODO_OK) ///hay error
        hayError += fechaFormal(&socio->fechNac, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Sexo
    hayError += validarSexo(&socio->sexo); ///Le mando la dirección para poder modificarlo en la función. Si no se la mando tira Warning

    ///Fecha Afilicación
    if(esFechaValida(&socio->fechAfi) == TODO_OK) ///hay error
        hayError += fechaAfiliacion(&socio->fechNac, &socio->fechAfi, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Categoria
    hayError += validarCategoria(socio->categoria);

    ///Ultima cuota paga
    if(esFechaValida(&socio->fechUltCuot) == TODO_OK) ///hay error
        hayError += fechaUltimaCuotaPaga(&socio->fechAfi, &socio->fechUltCuot, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Estado
    hayError += validarEstado(&socio->estado); ///Le mando la dirección para poder modificarlo en la función. Si no se la mando tira Warning


    //Si la variable hayError es > 0 hubo un error en algun lado y se guardará el registro leido en el Archivo de texto de errores.
    if(hayError > DATO_OK) ///DATO_OK = 0
        return FALLA_DATO; ///FALLA_DATO = 1

    return DATO_OK;
}
/**OBS: Creo que seria más eficiente si se pregunta después de cada validación, porque si falla una (hayError = 1) ya no preguntamos por las demás
Qué les parece? lo malo es que va a estar lleno de ifs. **/


///Documento
int validarDocumento(long dni)
{
    if(dni<10000 || dni>100000000)
    {
        return FALLA_DATO;
    }
    return DATO_OK;
}


///Nombre y apellido
char* normalizarApeYNom(char *apeYNom)
{
    /** Normalizar cadena **/
    return apeYNom;
}


///Fecha de Nacimiento
int fechaFormal(t_fecha *fechNac, t_fecha *fProceso)
{
    ///DESARROLLAR RESTA DE AÑOS, TENIENDO EN CUENTA LA CANTIDAD DE DIAS QUE TIENE UN AÑO (PUEDE SER BISIESTO)
    ///fecha de nacimiento < (fecha de proceso - 10)
    return DATO_OK;
}


///Sexo
int validarSexo(char *sexo)
{
    aMayuscula(sexo);   /**AGREGUÉ aMayúscula PARA QUE NO FALLE LA COMPARACIÓN **/
    if(*sexo == 'M' || *sexo == 'F')
    {
        return DATO_OK;
    }
	return FALLA_DATO;
}

void aMayuscula(char *c)
{
    if(*c >= 'a' && *c <= 'z')
        *c = *c - ('a' - 'A');
}


///fecha afiliacion
int fechaAfiliacion(t_fecha *fechNac, t_fecha *fechAfi, t_fecha *fProceso)
{
    ///Fecha de nacimiento < fecha de afiliación <= fecha de proceso
    return DATO_OK;
}


///Categoria
int validarCategoria(char* categoria)
{
    cadAMayuscula(categoria);   /**AGREGUÉ cadAMayuscula PARA QUE NO FALLE LA COMPARACIÓN **/

    if(strcmp(categoria, "MENOR") == 0)
        return DATO_OK;
    if(strcmp(categoria, "ADULTO") == 0)
        return DATO_OK;
    if(strcmp(categoria, "VITALICIO") == 0)
        return DATO_OK;
    if(strcmp(categoria, "HONORARIO") == 0)
        return DATO_OK;

    return FALLA_DATO;
}

char* cadAMayuscula(char *categoria)
{
    char *p = categoria;

    while(*p != '\0')
    {
        if(*p >= 'a' && *p <= 'A')
        {
            *p = *p - ('a' - 'A');
        }
        p++;
    }
    return categoria;
}


/// Ultima fecha de cuota paga
int fechaUltimaCuotaPaga(t_fecha *fechAfi, t_fecha *fechUltCuot, t_fecha *fProceso)
{
    ///Fecha de afiliación < fecha última cuota paga <= fecha de procesao
    return DATO_OK;
}


///Estado
int validarEstado(char *estado)
{
    aMayuscula(estado);     /**AGREGUÉ aMayúscula PARA QUE NO FALLE LA COMPARACIÓN **/

    if(*estado == 'A' || *estado == 'B')
    {
        return DATO_OK;
    }
    return FALLA_DATO;
}

