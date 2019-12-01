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
  IGUAL, DISTINTO, MENOR, MENORIGUAL, MAYOR, MAYORIGUAL
} OPERANDO;

typedef struct filtro
{
  COLUMNA *pCol;
  OPERANDO operador;
  char *valor;
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

OPERANDO comprobarOperando (char *operan);

void imprimirFiltros(FILTROS *metaFiltros);

//Funciones para datos PERSONALES
void datosPersonales(); //Funcion para imprimir datos personales

#endif // TOOLS_H_
