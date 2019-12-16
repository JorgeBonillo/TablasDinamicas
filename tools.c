#include "tools.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


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
  fp = fopen (nombreFichero, "r" );
  if (fp==NULL)
  {
    ok = 0;
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
  //int longitud = strlen(cadenaLimpiar);
  for ( j = 0; j <= 100; j++)
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
  }
  else if (strcmp(sep, "[esp]")==0)
  {
    vaciarChar(sep);
    strcpy (sep, " ");   
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
    fclose(f);
    return 0;
  }
  else
  {
    fgets(temp,1000,f);
    fclose(f);
    return obtenerColumnas(sep, temp);
  }
  
}

//Funcion para comprobar cuantas filas tiene el fichero
int numFilas(char *nomfc, char *sep)
{
  FILE *f;
  //Desde 0 por que la primera fila no se cuenta
  int fila = 0;
  char temp[1000];
  f = fopen(nomfc, "r");
  if (f == NULL)
  {
    printf("Error en la apertura del archivo\n");
    fclose(f);
    return 0;
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
    fclose(f);
    return fila;
  }
}

int validarBD(char *nomfc, char *sep, METADATOS *meta)
{

  FILE *f;
  int fila=0;
  int colum=0;
  int linea = 1;
  int primerIter = 1;
  char temp[1000];
  char temp2[1000];
  char *cadena[30];
  char cad[100];
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
    //Vaciar cad
    vaciarChar(cad);
    
    //Poner nombres a las cadenas
    for (int i = 0; i < colum; i++)
      {
        obtenerCadena(temp, sep, i, cad);

        pCol->nom = strdup(cad);
        pCol ->max = 0;
        pCol ->min = 0;
        pCol ->prom = 0;
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

        vaciarChar(cad);
      }

    pCol = meta -> p;
    pEtiq = pCol -> lista;
    pColAux = *pCol;

      fgets(temp2,1000,f);
      //Comprobar que la 1 y 2 fila tienen las mismas columnas
      if (obtenerColumnas(sep, temp2) == colum)
      { 
        for (int i = 0; i < colum; i++)
        {
          obtenerCadena(temp2, sep, i, cad);
          if (comprobarTipo(cad) == STR)
          {
            pCol -> t = STR;

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
          }
          else
          {
            // Tipo distinto a STR
            pCol -> t = comprobarTipo(cad);
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

          vaciarChar(cad);
        }
        linea++;
      }
      else
      {
        //Error archivo
        return 0;
      }
      
    pCol = meta -> p;
    pEtiq = pCol -> lista;
    pColAux = *pCol;
    
    int error;
    while (!feof(f))
    {
      linea++;
      error = 0;
      fgets(temp2,1000,f);

      if (obtenerColumnas(sep, temp2) == colum)
      { 

        //Comprobacion para saber si la fila es correcta
        // 1 = es correcta
        // 0 = NO 
        if (comprobacionFila(meta, temp2, sep) == 1)
        {
          //printf("Fila: %d correcta \n", linea);
          for (int i = 0; i < colum; i++)
          {
            obtenerCadena(temp2, sep, i, cad);
            if (pCol -> t == STR)
            {
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
            }
            else if (pCol -> t == NUM)
            {
              if (comprobarTipo(cad) == NUM)
              {
                
              }
              else
              {
                error = 1;
                break;
              }    
            }
            else if (pCol -> t == DATE)
            {
              /* code */
            }
            else
            {
              /* code */
            }
            
            //NEXT COL
            pCol = pCol -> next;
            if (pCol == NULL)
            {
              pCol = &pColAux;
            }
            else
            {
              pEtiq = pCol -> lista;
            }

            vaciarChar(cad);
          }
        }
        else
        {
          //error = 1;
          printf("Error en la fila: %d\n", linea);
          meta -> nErrs = (meta -> nErrs + 1);
          pCol = meta -> p;
          pEtiq = pCol -> lista;
          pColAux = *pCol;
          vaciarChar(cad);
        }
        
        
        /*if (error == 1)
        {
          printf("Error en la linea: %d\n", linea);
          meta -> nErrs = (meta -> nErrs + 1);
          pCol = meta -> p;
          pEtiq = pCol -> lista;
          pColAux = *pCol;
          vaciarChar(cad);
        }*/
        //linea ++;
      }
      else
      {
        printf("Error en la fila: %d\n", linea);
        printf("error en la fila");
      }
      
    }
    
  }
  fclose(f);
  return 0;
}

int renombrarColum (char *columVieja, char *columNueva, METADATOS *meta)
{
  COLUMNA* pColrenombrarColum = buscarCol(meta, columVieja);

  //pColrenombrarColum = buscarCol(meta, columVieja);

  if(pColrenombrarColum == NULL)
  {
    printf("No existe la columna a modificar\n");
    return 0;
  }
  else
  {
    if (buscarCol(meta, columNueva) == NULL)
    {
      pColrenombrarColum -> nom = strdup(columNueva);
      return 1;
    }
    else
    {
      printf("La columna nueva ya existe\n");
      return 0;
    }
  }
  
  //return 1;
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
  
  return 0;
}

int anadirFiltro (FILTROS *metaFiltros, METADATOS *meta, char *columna, char *operadorFiltro, char *valorFiltro)
{
  FILTRO *pFiltro = metaFiltros -> p;
  COLUMNA *pColFiltro = buscarCol(meta, columna);
  //char comprobacionOperando = comprobarOperando(operadorFiltro);

  if (comprobarOperando(operadorFiltro) == nulo)
  {
    printf("El operando no es valido\n");
    return 0;
  }
  else
  {
    printf("Operando valido");
  }
  
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
    pFiltro -> operador = comprobarOperando(operadorFiltro);
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

int esNumero(char *cadena)
{
  for(int i = 0; i < strlen(cadena); i++)
  {
    int codigoAscii = toascii(cadena[i]);
    if(codigoAscii <= 57 && codigoAscii >= 48)
    {
      
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

int esCadena (char *cadena)
{
  for(int i = 0; i < strlen(cadena); i++)
  {
    int codigoAscii = toascii(cadena[i]);
    if (codigoAscii <= 90 && codigoAscii >= 65)
    {

    }
    else if (codigoAscii <= 122 && codigoAscii >= 97)
    {

    }
    else
    {
      return 0;
    }
  }
  return 1;
}

int esFecha (char *cadena)
{
  int i;
  
  if (strlen(cadena) == 10)
  {
    
    //Comprobamos ANYO YYYY
    for (i = 0; i < 4; i++)
    {
      int codigoAscii = toascii(cadena[i]);

      if(codigoAscii <= 57 && codigoAscii >= 48)
      {

      }
      else
      {
        return 0;
      }
    }
    
    
    //Comprobamos primer /
    if (cadena[4] == '/')
    {
      
    }
    else
    {
      return 0;
    }
    
    
    //Comprobamos MESES MM
    for (i = 5; i < 7; i++)
    {
      int codigoAscii = toascii(cadena[i]);

      if(codigoAscii <= 57 && codigoAscii >= 48)
      {

      }
      else
      {
        return 0;
      }
    }

    //Comprobamos segundo /
    if (cadena[7] == '/')
    {
      
    }
    else
    {
      return 0;
    }

    //Comprobamos DIAS DD
    for (i = 8; i < 10; i++)
    {
      int codigoAscii = toascii(cadena[i]);

      if(codigoAscii <= 57 && codigoAscii >= 48)
      {

      }
      else
      {
        return 0;
      }
    }

  }
  else
  {
    return 0;
  }
  return 1;
  
}

int comprobacionFila(METADATOS *meta, char *fila, char *separador)
{
  COLUMNA *pCol = meta -> p;
  char cadena[100];
  int columnas = meta ->nCols;
  
  for (int i = 0; i < columnas; i++)
  {
    vaciarChar(cadena);
    obtenerCadena(fila, separador, i, cadena);
    if (pCol -> t == comprobarTipo(cadena))
    {
      pCol = pCol -> next;
    }
    else
    {
      return 0;
    }
    
  }
  return 1;
}

void infoValidar(METADATOS *meta)
{
  COLUMNA* pCol = meta -> p;
  int contador = 1;
  printf("Numero de filas incorrectas: %d\n", meta -> nErrs);
  printf("Numero de filas correctas: %d\n", meta -> nFils);
  printf("Numero de columnas: %d\n", meta -> nCols);

  while (pCol)
  {
    printf("Columna %d: %s\n", contador, pCol -> nom);
    pCol = pCol -> next;
    contador++;
  }
  
}

/*char trim (char *cadena)
{

}*/

/*char minus (char *cadena)
{
  for (int indice = 0; cadena[indice] != '\0'; ++indice)
  {
		cadena[indice] = tolower(cadena[indice]);
	}
  return 
}*/

void datosPersonales()
{
    printf("\nNOMBRE:\tJORGE SANCHEZ BONILLO\n");
    printf("DNI:\t48725112-A\n");
    printf("EMAIL:\tjorge.sanchez17@goumh.umh.es\n");
}
