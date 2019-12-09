#include "tools.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Funcion para el prompt
int comandoPrompt(char *prompt)
{

    if(strcmp(prompt, "salir")==0)
      return SALIR;

    if(strcmp(prompt, "datos")==0)
      return DATOS;

    if(strcmp(prompt, "validar")==0)
      return VALIDAR;

    if(strcmp(prompt, "renombrar")==0)
      return RENOMBRAR;

    if(strcmp(prompt, "info")==0)
      return INFO;

    if(strcmp(prompt, "filtro")==0)
        return FILTROPROM;

    if(strcmp(prompt, "filtros")==0)
        return FILTROSPROM;

    if(strcmp(prompt, "borrar")==0)
        return BORRAR;

    if(strcmp(prompt, "aplicar")==0)
        return APLICAR;

    if(strcmp(prompt, "guardar")==0)
        return GUARDAR;

    return 0;
}

//Funcion para comprobar < >
int comprobarMenorMayor(char *cadena)
{
  printf("%c\n",cadena[0]);
  int resultado;
  int len=strlen(cadena)-1;
  printf("%d\n", len);
  printf("%c\n",cadena[len]);
  if (cadena[0] == '<' && cadena[len] == '>')
  {
    printf("Tiene los caracteres\n");
    resultado = 1;
  }
  else
  {
    printf("Error\n");
    resultado = 0;
  }
  return resultado;
}

//Funcion para comprobar que el fichero existe
int cargarFichero(char *nombreFichero)
{
  FILE *fp;
  int ok = 0;
  //strcpy(nombreFichero, eliminarMenorMayor(nombreFichero));
  //printf("%s\n", nombreFichero);
  fp = fopen (nombreFichero, "r" );
  if (fp==NULL)
  {
    printf("El fichero no existe\n");
  }
  else
  {
    //printf("El fichero existe\n");
    ok = 1;
  }
  return ok;
}

//Funcion para obetener cadenas
void obtenerCadena(char *cadena, char *sep, int n, char *cad)
{
  int l = strlen(sep);
  char *p = cadena;
  char *p2;

  while ((p2=strstr(p,sep))!=NULL && n!=0)
  {
    n--;
    p = p2 + l;
  }
  if (p2 == NULL)
  {
    strcpy(cad, p);
    
    //strcat(cad, "\0");
  }
  else
  {
    strncpy(cad, p, p2-p);
    //strcat(cad, "\0");
  }
  
  
  //strncpy(cad, p, p2-p);
  //return *cad;
}

//Funcion para vaciar un char
void vaciarChar(char *cadenaLimpiar)
{
  int j=0;
  int longitud = strlen(cadenaLimpiar);
  for ( j = 0; j <= longitud; j++)
  {
    cadenaLimpiar[j]= '\0';
  }
}

char *validarSep(char *sep)
{
  if (strcmp(sep, "[tab]")==0)
  {
    vaciarChar(sep);
    strcpy (sep, "\t");
    return sep;
  }
  else if (strcmp(sep, "[esp]")==0)
  {
    vaciarChar(sep);
    strcpy (sep, " ");
    return sep;
  }

  return sep;
}

//Funcion para comprobar cuantas columnas tiene el fichero
int numColumnas(char *nomfc, char *sep)
{
  FILE *f;
  char temp[1000];
  f = fopen(nomfc, "r");
  if (f == NULL)
  {
    printf("Error en la apertura del archivo\n");
  }
  else
  {
    fgets(temp,1000,f);
    return obtenerColumnas(sep, temp);
  }
  close(f);
}

//Funcion para comprobar cuantas filas tiene el fichero
int numFilas(char *nomfc, char *sep)
{
  FILE *f;
  int fila = 0;
  char temp[1000];
  f = fopen(nomfc, "r");
  if (f == NULL)
  {
    printf("Error en la apertura del archivo\n");
  }
  else
  {
    fgets(temp,1000,f);
    while (!feof(f))
    {
      fgets(temp,1000,f);
      fila++;
    }
    printf("Filas: %d\n", fila);
    return fila;
  }
  close(f);
}

int validarBD(char *nomfc, char *sep, METADATOS *meta)
{

  FILE *f;
  int fila=0;
  int colum=0;
  char temp[1000];
  char temp2[1000];
  char *cadena[30];
  char cad[50];
  char aux = '0';
  COLUMNA* pCol, pColAux;
  ETIQUETA* pEtiq;

  f = fopen(nomfc, "r");
  if (f == NULL)
  {
    printf("Error en la apertura del archivo\n");
  }
  else
  {
    
    colum = meta->nCols;
    fila = meta->nFils;
    fgets(temp,1000,f);

    pCol = meta -> p;

    for (int j = 0; j <= 50; j++)
      {
        cad[j]= '\0';
      }
    for (int i = 0; i < colum; i++)
      {
        obtenerCadena(temp, sep, i, cad);

        pCol->nom = strdup(cad);
        pCol->lista = NULL;

        if (i == colum-1)
        {
          pCol = pCol->next = NULL;
        }
        else
        {
          pCol -> next = (COLUMNA*)malloc(sizeof(COLUMNA));
          pCol = pCol->next;
        }

        for (int j = 0; j <= 50; j++)
        {
          cad[j]= '\0';
        }
      }

    pCol = meta -> p;
    pEtiq = pCol -> lista;
    pColAux = *pCol;
    while (!feof(f))
    {
      fgets(temp2,1000,f);

      if (obtenerColumnas(sep, temp2) == colum)
      {
        for (int i = 0; i < colum; i++)
        {
          obtenerCadena(temp2, sep, i, cad);

          if(buscarEtiq(cad, pCol) == NULL)
          { 
            if (pCol->lista == NULL)
            {
              pCol->lista = (ETIQUETA*)malloc(sizeof(ETIQUETA));
              pEtiq = pCol ->lista;
              pEtiq ->siguiente = NULL;
            }
            else
            {
              while (pEtiq->siguiente)
              {
                pEtiq = pEtiq -> siguiente;
              }
              pEtiq = pEtiq -> siguiente = (ETIQUETA*)malloc(sizeof(ETIQUETA));
              pEtiq ->siguiente = NULL;
            }
            
            pEtiq -> etiqueta = strdup(cad);
            pEtiq -> cuenta = 1;
          } 
          else
          {
            pEtiq = buscarEtiq(cad, pCol);
            pEtiq -> cuenta = (pEtiq -> cuenta + 1);

          }
          
          pCol = pCol -> next;
          if (pCol == NULL)
          {
            pCol = &pColAux;
          }
          else
          {
            pEtiq = pCol -> lista;
          }
          for (int j = 0; j <= 50; j++)
          {
            cad[j]= '\0';
          }
        }
      }
      else
      {
        printf("error en la fila");
      }
      
      
    }
    
  }

  return 0;
}

int renombrarColum (char *columVieja, char *columNueva, METADATOS *meta)
{
  COLUMNA* pCol;

  pCol = buscarCol(meta, columVieja);

  if(pCol == NULL)
  {
    printf("No existe la columna a modificar");
  }
  else
  {
    if (buscarCol(meta, columNueva) == NULL)
    {
      pCol ->nom = columNueva;
    }
    else
    {
      printf("La columna nueva ya existe");
    }
  }
}

char *eliminarMenorMayor(char *cadena)
{
  char *cadenaTemporal = malloc(strlen(cadena)+1);
  int j=0;
  for (int i = 1; i<strlen(cadena)-1; i++)
  {
    cadenaTemporal[j]=cadena[i];
    j++;
  }
  return cadenaTemporal;
}

int obtenerColumnas(char *sep, char *cadena)
{
  int l = strlen(sep);
  char *p = cadena;
  int f = 1;

  while ((p=strstr(cadena,sep))!=NULL)
  {
    f++;
    p += l;
    cadena = p;
  }

  return f;
  
}

int infoColum(char *nomfc, METADATOS *meta, char *nomColum)
{
  COLUMNA *pCol = buscarCol(meta, nomColum);

  if(pCol != NULL)
  {
    
  }
  else
  {
    printf("No existe la columna a buscar\n");
  }
  

}

OPERANDO comprobarOperando (char *operan)
{
  if (strcmp(operan, "==") == 0)
  {
    
    return NULL;
  }
  /*else if (strcmp(operan, "!=") == 0)
  {
    return DISTINTO;
  }
  else if (strcmp(operan, ">") == 0)
  {
    return MENOR;
  }
  else if (strcmp(operan, ">=") == 0)
  {
    return MENORIGUAL;
  }
  else if (strcmp(operan, "<") == 0)
  {
    return MAYOR;
  }
  else if (strcmp(operan, "<=") == 0)
  {
    return MAYORIGUAL;
  }*/
  /*else
  {
    return NULL;
  }*/

}

int anadirFiltro (FILTROS *metaFiltros, METADATOS *meta, char *columna, char *operadorFiltro, char *valorFiltro)
{
  FILTRO *pFiltro = metaFiltros -> p;
  COLUMNA *pColFiltro = buscarCol(meta, columna);
  //char comprobacionOperando = comprobarOperando(operadorFiltro);

  /*if (comprobarOperando(operadorFiltro) == NULL)
  {
    printf("El operando no es valido\n");
    return 0;
  }
  else
  {
    printf("Operando valido");
  }*/
  
  if (pColFiltro == NULL)
  {
    printf("No existe la columna del filtro\n");
  }
  else
  {
    if (pFiltro == NULL)
    {
      metaFiltros -> num = (metaFiltros -> num + 1);
      pFiltro = metaFiltros -> p = (FILTRO*)malloc(sizeof(FILTRO));
      pFiltro -> next = NULL;
    }
    else
    {
      while (pFiltro -> next)
      {
        pFiltro = pFiltro -> next;
      }
      metaFiltros -> num = (metaFiltros -> num + 1);
      pFiltro = pFiltro -> next = (FILTRO*)malloc(sizeof(FILTRO));
      pFiltro -> next = NULL;
    }

    pFiltro -> pCol = pColFiltro;
    pFiltro -> operador = IGUAL;
    pFiltro -> valor = strdup(valorFiltro);
    
    
  }
  

  return 0;
}

void imprimirFiltros(FILTROS *metaFiltros)
{
  FILTRO *pFiltro = metaFiltros -> p;
  int contador = 1;

  if(pFiltro == NULL)
  {
    printf("No hay filtros que mostrar\n");
  }
  else
  {
    while (pFiltro)
      {
        printf("Filtro %d:\n", contador);
        printf("columna: %s - operador: %c - valor: %s\n", pFiltro ->pCol ->nom, pFiltro->operador, pFiltro->valor);
        pFiltro = pFiltro -> next;
        contador++;
      }
  }
}



void datosPersonales()
{
    printf("\nNOMBRE:\tJORGE SANCHEZ BONILLO\n");
    printf("DNI:\t48725112-A\n");
    printf("EMAIL:\tjorge.sanchez17@goumh.umh.es\n");
}
