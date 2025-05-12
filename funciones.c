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



/*************************************** Flujo - Inicio ***************************************/

int abrirArchivos(t_fecha *fProceso)
{
    FILE *ptxtS, *pbin, *ptxtE; ///ptxtS = texto Socio | ptxtE = texto Error

    ptxtS = fopen(ARCH_TXTS, "rt");
    pbin = fopen(ARCH_BIN, "wb");
    ptxtE = fopen(ARCH_TXTE, "wt");

    if(!ptxtS || !pbin || !ptxtE) ///10/05 - Agrgué el '!' en ptxtE
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

        if(validarDatos(&socio, fProceso) == 0)
        {
            //escribo en binario
        }
        else
        {
            //escribo en texto error
        }
    }
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
    if(esFechaValida(&socio->fechNac) == TODO_OK)
        hayError += fechaFormal(&socio->fechNac, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Sexo
    hayError += validarSexo(&socio->sexo); ///Le mando la dirección para poder modificarlo en la función. Si no se la mando tira Warning

    ///Fecha Afilicación
    if(esFechaValida(&socio->fechAfi) == TODO_OK)
        hayError += fechaAfiliacion(&socio->fechNac, &socio->fechAfi, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Categoria
    hayError += validarCategoria(socio->categoria);

    ///Ultima cuota paga
    if(esFechaValida(&socio->fechUltCuot) == TODO_OK)
        hayError += fechaUltimaCuotaPaga(&socio->fechAfi, &socio->fechUltCuot, fProceso);
    else
        hayError++; ///Podría poner return FALLA_DATO

    ///Estado
    hayError =+ validarEstado(&socio->estado); ///Le mando la dirección para poder modificarlo en la función. Si no se la mando tira Warning


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
int fechaFormal(t_fecha *fechNac, t_fecha *fProceso) ///Podria mandar una copia de fProceso y no la dirección ya que no tengo que modificarla o ponerle 'const' 10-05
{
    ///DESARROLLAR RESTA DE AÑOS, TENIENDO EN CUENTA LA CANTIDAD DE DIAS QUE TIENE UN AÑO (PUEDE SER BISIESTO)
    t_fecha fPMenosDiez;
    fPMenosDiez = restaFecha(fProceso);

    ///fecha de nacimiento < (fecha de proceso - 10)
    if(fechNac->anio > fPMenosDiez.anio)
        return FALLA_DATO;

    if(fechNac->anio == fPMenosDiez.anio)
    {
        if(fechNac->mes > fPMenosDiez.mes)
            return FALLA_DATO;

        if(fechNac->mes == fPMenosDiez.mes && fechNac->dia > fPMenosDiez.dia)
            return FALLA_DATO;
    }

    return DATO_OK;
}

t_fecha restaFecha(t_fecha *fProceso)
{
    int diasMes;
    t_fecha fProcesoMenosDiez = *fProceso;

    fProcesoMenosDiez.anio -= ANIOS_RESTA;

    diasMes = cantDiaMes(fProcesoMenosDiez.mes, fProcesoMenosDiez.anio);

    if(fProcesoMenosDiez.dia > diasMes)
        fProcesoMenosDiez.dia = diasMes;

    return fProcesoMenosDiez;
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


///fecha afiliacion - Asumo que tambien debe cumplir: fecha de nacimiento < (fecha de proceso - 10)
int fechaAfiliacion(t_fecha *fechNac, t_fecha *fechAfi, t_fecha *fProceso) ///Podria mandar una copia de fProceso y no la dirección ya que no tengo que modificarla o ponerle 'const'
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
    if(comparaFechas(fechAfi, fechUltCuot) == ERROR)
        return FALLA_DATO;

    if(comparaFechas(fechUltCuot, fProceso) == ERROR)
        return FALLA_DATO;

    return DATO_OK;
}

int comparaFechas(t_fecha *fechA, t_fecha *fechB)
{
    //if()

    return TODO_OK;
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

