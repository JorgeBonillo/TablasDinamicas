#ifndef TOOLS_H_
#define TOOLS_H_

#define SALIR 1
#define DATOS 2
#define VALIDAR 3
#define RENOMBRAR 4
#define INFO 5
#define FILTROPROM 6
#define FILTROSPROM 7
#define BORRAR 8
#define APLICAR 9
#define GUARDAR 10

//ESTRUCTURAS PARA FICHERO

typedef enum {VOID, NUM,  DATE, STR} TIPO;

typedef struct etiq
{
  char *etiqueta;
  int cuenta;
  struct etiq *siguiente;
} ETIQUETA;

typedef struct col
{
  char *nom;
  TIPO t;
  float max, min, prom;
  int histograma[5];
  ETIQUETA *lista;
  struct col *next;
} COLUMNA;

typedef struct
{
  int nErrs, nFils, nCols;
  COLUMNA *p;
} METADATOS;


//ESTRUCTURAS PARA FILTROS

typedef enum {
  IGUAL, DISTINTO, MENOR, MENORIGUAL, MAYOR, MAYORIGUAL, nulo, entre
} OPERANDO;

typedef struct filtro
{
  COLUMNA *pCol;
  OPERANDO operador;
  char *valor;
  char *valor2;
  struct filtro *next;
} FILTRO;

typedef struct 
{
  int num;
  FILTRO *p;
} FILTROS;

int comandoPrompt (char *prompt);

int comprobarMenorMayor (char *cadena);

int cargarFichero(char *nombreFichero);

char *eliminarMenorMayor(char *cadena);

int validarBD(char *nomfc, char *sep, METADATOS *meta);

int obtenerColumnas(char *sep, char *cadena);

void obtenerCadena(char *cadena, char *sep, int n, char *cad);

char *validarSep(char *sep);

void vaciarChar(char *cadenaLimpiar);

int anadirFiltro (FILTROS *metaFiltros, METADATOS *meta, char *columna, char *operador, char *valor);

void imprimirFiltros(FILTROS *metaFiltros);

int numColumnas(char *nomfc, char *sep);

int numFilas(char *nomfc, char *sep);

int renombrarColum (char *columVieja, char *columNueva, METADATOS *meta);

int esNumero(char *cadena);

int esFecha (char *cadena);

int esCadena (char *cadena);

int comprobacionFila(METADATOS *meta, char *fila, char *separador);

void infoValidar(METADATOS *meta);

int infoColum(char* nomFichero, char* sep, METADATOS *meta, char *nomColum);

int filtroCuenta(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep);

int filtroTotal(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep, char *columna);

int filaCumpleFiltro(METADATOS *meta, FILTROS *metaFiltros, char *temp, char *sep);

int filtroPromedio(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep, char *columna);

char *devuelveOperador(FILTRO *pFiltro);

char *trim(char *s);

int fechaAserie(int anyo, int mes, int dia);

void serieAfecha(int serie, int *anyo, int *mes, int *dia);

void diasRestMenorAnyo(int diasRest, int *mes, int *dia, int *acumuladoDiasMes);

void serieFecha(int serie, int *anyo, int *mes, int *dia, int indice, int *acumuladoDiasMes);

char *minus(char *cadena);

int guardarMeta(METADATOS *meta, char *nombreFichero);

char *devuelveTipo(COLUMNA *pCol);

int esVoid(char *cadena);

int anadirFiltroEntre(FILTROS *metaFiltros, METADATOS *meta, char *columna, char *valor1, char *valor2);

//Funciones para datos PERSONALES
void datosPersonales(); //Funcion para imprimir datos personales

#endif // TOOLS_H_
