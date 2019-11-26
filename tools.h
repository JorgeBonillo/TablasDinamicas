#ifndef TOOLS_H_
#define TOOLS_H_

#define SALIR 1
#define DATOS 2
#define VALIDAR 3
#define RENOMBRAR 4
#define INFO 5
#define FILTRO 6
#define FILTROS 7
#define BORRAR 8
#define APLICAR 9

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

int comandoPrompt (char *prompt);

int comprobarMenorMayor (char *cadena);

int cargarFichero(char *nombreFichero);

char *eliminarMenorMayor(char *cadena);

int validarBD(char *nomfc, char *sep, METADATOS *meta);

int obtenerColumnas(char *sep, char *cadena);

void obtenerCadena(char *cadena, char *sep, int n, char *cad);

//Funciones para datos PERSONALES
void datosPersonales(); //Funcion para imprimir datos personales


#endif // TOOLS_H_
