#include "cadenas.h"
#include "datos.h"
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
    printf("El fichero NO existe\n");
    ok = 0;
  }
  else
  {
    //printf("El fichero existe\n");
    ok = 1;
  }
  fclose(fp);
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
  int correctas = 1;
  int primerIter = 1;
  char temp[1000];
  char temp2[1000];
  char *cadena[30];
  char cad[100];
  char aux = '0';
  COLUMNA* pCol, pColAux;
  ETIQUETA* pEtiq;
  int i;

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
    for (i = 0; i < colum; i++)
      {
        obtenerCadena(temp, sep, i, cad);

        pCol->nom = strdup(trim(cad));
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
        for (i = 0; i < colum; i++)
        {
          obtenerCadena(temp2, sep, i, cad);

          if (comprobarTipo(trim(cad)) == STR)
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
            obtenerCadena(temp2, sep, i, cad);
            pCol -> t = comprobarTipo(trim(cad));
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
          for (i = 0; i < colum; i++)
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
                  pEtiq -> etiqueta = strdup(trim(cad));
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
              if (comprobarTipo(trim(cad)) == NUM)
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
              if (comprobarTipo(trim(cad)) == DATE)
              {
                
              }
              else
              {
                error = 1;
                break;
              }    
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
          correctas++;
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
        
      }
      else
      {
        printf("Error en la fila: %d\n", linea);
        //printf("error en la fila");
      }
      
    }
    
  }
  meta ->nFils = correctas;
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
  int i;
  for (i = 1; i<strlen(cadena)-1; i++)
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

int infoColum(char* nomFichero, char* sep, METADATOS *meta, char *nomColum)
{
  COLUMNA *pColBuscar = buscarCol(meta, nomColum);
  COLUMNA *pCol = meta -> p;
  char temp[1000];
  int colum = meta -> nCols;
  char cad[100];
  
  if(pColBuscar ==  NULL)
  {
    printf("No existe la columna a buscar\n");
    return 0;
  }
  else
  {
    FILE *fp;
    fp = fopen (nomFichero, "r" );
    COLUMNA *pCol = NULL;
    float valor;
    int primeraVez = 0;
    int veces = 1;
    int i;

    if (fp == NULL)
    {
      printf("Error apertura archivo\n");
      return 0;
    }
    else
    {
      fgets(temp,1000,fp);

      while (!feof(fp))
      {
        fgets(temp,1000,fp);

        if (obtenerColumnas(sep, temp) == colum)
        { 
          if (comprobacionFila(meta, temp, sep) == 1)
          {
            vaciarChar(cad);
            pCol = buscarCol(meta, nomColum);
            if (pCol == NULL)
            {
              printf("Columna INFO no existe\n"); 
              return 0;
            }
            else
            {
              if (pCol -> t == NUM)
              {
                obtenerCadena(temp, sep, buscarColumnaNombre(meta, nomColum), cad);
                valor = atof(trim(cad));
                if (primeraVez == 0)
                {
                  pCol ->max = valor;
                  pCol ->min = valor;
                  pCol ->prom = valor;
                  primeraVez = 1;
                  //printf("%s\n",cad);
                }
                else
                {
                  if (valor > pCol -> max)
                  {
                    pCol->max = valor;
                  }
                  if (valor < pCol -> min)
                  {
                    pCol ->min = valor;
                  }
                  //printf("%s\n",cad);
                  pCol -> prom = (((pCol -> prom) * veces) + valor)/ (veces + 1);
                  veces++;
                  //printf("%s\n",cad);
                }
              }
              else if (pCol -> t == DATE)
              {
                obtenerCadena(temp, sep, buscarColumnaNombre(meta, nomColum), cad);
                int anyo = atoi(strtok(cad,"/"));
                int mes = atoi(strtok(NULL, "/"));
                int dia = atoi(strtok(NULL, "/"));
                valor = fechaAserie(anyo, mes, dia);
                if (primeraVez == 0)
                {
                  pCol ->max = valor;
                  pCol ->min = valor;
                  pCol ->prom = valor;
                  primeraVez = 1;
                }
                else
                {
                  if (valor > pCol -> max)
                  {
                    pCol->max = valor;
                  }
                  if (valor < pCol -> min)
                  {
                    pCol ->min = valor;
                  }
                  //printf("%s\n",cad);
                  pCol -> prom = (((pCol -> prom) * veces) + valor)/ (veces + 1);
                  veces++;
                  //printf("%s\n",cad);
                }
              }
              else if (pCol -> t == STR)
              {
                ordenacionSTR(pCol);
                ETIQUETA *pEtiq = pCol ->lista;
                while (pEtiq)
                {
                  printf("Etiqueta: %s\n", pEtiq -> etiqueta);
                  printf("Repeticiones: %d\n", pEtiq -> cuenta);
                  printf("----------\n");
                  pEtiq = pEtiq -> siguiente;
                }
                return 1;               
              }            
            }
            obtenerCadena(temp, sep, buscarColumnaNombre(meta, nomColum), cad);   
          }
        }
      }
      //HISTOGRAMA NUM
      if (pCol -> t == NUM)
      {
        rewind(fp);
        fgets(temp,1000,fp);
        for (i = 0; i<5; i++)
        {
          pCol ->histograma[i] = 0;
        }

        //HISTOGRAMA
        while (!feof(fp))
        {
          fgets(temp,1000,fp);

          if (obtenerColumnas(sep, temp) == colum)
          { 
            if (comprobacionFila(meta, temp, sep) == 1)
            {
              vaciarChar(cad);
              obtenerCadena(temp, sep, buscarColumnaNombre(meta, nomColum), cad);
              valor = atof(trim(cad));
              float maxMinusmin = (((pCol -> max) - (pCol -> min))/5);
              if (valor <= (maxMinusmin + pCol -> min))
              {
                pCol ->histograma[0] = pCol ->histograma[0] +1;
              }
              else if (valor <= ((maxMinusmin*2) + pCol -> min))
              {
                pCol ->histograma[1] = pCol ->histograma[1] +1;
              }
              else if (valor <= ((maxMinusmin*3) + pCol -> min))
              {
                pCol ->histograma[2] = pCol ->histograma[2] +1;
              }
              else if (valor <= ((maxMinusmin*4) + pCol -> min))
              {
                pCol ->histograma[3] = pCol ->histograma[3] +1;
              }
              else if (valor <= ((maxMinusmin*5) + pCol -> min))
              {
                pCol ->histograma[4] = pCol ->histograma[4] +1;
              }
            }   
          }
        }
      } 
      else if (pCol -> t == DATE)
      {
        rewind(fp);
        fgets(temp,1000,fp);
        for (i = 0; i<5; i++)
        {
          pCol ->histograma[i] = 0;
        }

        //HISTOGRAMA
        while (!feof(fp))
        {
          fgets(temp,1000,fp);

          if (obtenerColumnas(sep, temp) == colum)
          { 
            if (comprobacionFila(meta, temp, sep) == 1)
            {
              vaciarChar(cad);
              obtenerCadena(temp, sep, buscarColumnaNombre(meta, nomColum), cad);
              int anyo = atoi(strtok(cad,"/"));
              int mes = atoi(strtok(NULL, "/"));
              int dia = atoi(strtok(NULL, "/"));
              valor = fechaAserie(anyo, mes, dia);
              float maxMinusmin = (((pCol -> max) - (pCol -> min))/5);
              if (valor <= (maxMinusmin + pCol -> min))
              {
                pCol ->histograma[0] = pCol ->histograma[0] +1;
              }
              else if (valor <= ((maxMinusmin*2) + pCol -> min))
              {
                pCol ->histograma[1] = pCol ->histograma[1] +1;
              }
              else if (valor <= ((maxMinusmin*3) + pCol -> min))
              {
                pCol ->histograma[2] = pCol ->histograma[2] +1;
              }
              else if (valor <= ((maxMinusmin*4) + pCol -> min))
              {
                pCol ->histograma[3] = pCol ->histograma[3] +1;
              }
              else if (valor <= ((maxMinusmin*5) + pCol -> min))
              {
                pCol ->histograma[4] = pCol ->histograma[4] +1;
              }
            }
          }
        }
      }
      if (pCol -> t == NUM)
      {
        printf("Min: %f\n", pCol ->min);
        printf("Max: %f\n", pCol ->max);
        printf("Prom: %f\n", pCol ->prom);
        printf("HISTOGRAMA\n");
        for (i = 0; i<5; i++)
        {
          printf("%d\n", pCol ->histograma[i]);
        }
      }
      else if (pCol -> t == DATE)
      {
        int anyo = 0;
        int mes = 0;
        int dia =0;
        int serieInt = (int)pCol ->min;
        serieAfecha(serieInt, &anyo, &mes, &dia);
        printf("Min: %d/%d/%d\n", anyo, mes, dia);

        serieInt = (int)pCol ->max;
        serieAfecha(serieInt, &anyo, &mes, &dia);
        printf("Max: %d/%d/%d\n", anyo, mes, dia);

        serieInt = (int)pCol ->prom;
        serieAfecha(serieInt, &anyo, &mes, &dia);
        printf("Prom: %d/%d/%d\n", anyo, mes, dia);

        printf("HISTOGRAMA\n");
        for (i = 0; i<5; i++)
        {
          printf("%d\n", pCol ->histograma[i]);
        }
      }
      
    
    }
  }
  return 1;
}

int anadirFiltro (FILTROS *metaFiltros, METADATOS *meta, char *columna, char *operadorFiltro, char *valorFiltro)
{
  FILTRO *pFiltro = metaFiltros -> p;
  COLUMNA *pColFiltro = buscarCol(meta, columna);
  char comprobacionFiltro[200];
  //char comprobacionOperando = comprobarOperando(operadorFiltro);

  if (comprobarOperando(operadorFiltro) == nulo)
  {
    printf("El operando no es valido\n");
    return 0;
  }
  strcpy(comprobacionFiltro, valorFiltro);
  if (pColFiltro ->t != comprobarTipo(comprobacionFiltro))
  {
    return 0;
  }
  /*
  strcpy(comprobacionFiltro, valorFiltro);
  if (pColFiltro -> t == DATE)
  {
    if (comprobarTipo(comprobacionFiltro) != DATE)
    {
      return 0;
    }
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
    pFiltro -> operador = comprobarOperando(operadorFiltro);
    pFiltro -> valor = strdup(valorFiltro);
    
  }
  

  return 0;
}

void imprimirFiltros(FILTROS *metaFiltros)
{
  FILTRO *pFiltro = metaFiltros -> p;
  int contador = 1;
  char devOperador[5];

  if(pFiltro == NULL)
  {
    printf("No hay filtros que mostrar\n");
  }
  else
  {
    while (pFiltro)
      {
        printf("Filtro %d:\n", contador);
        strcpy(devOperador, devuelveOperador(pFiltro));
        printf("columna: %s - operador: %s - valor: %s\n", pFiltro ->pCol ->nom, devOperador, pFiltro->valor);
        pFiltro = pFiltro -> next;
        contador++;
      }
  }
}

int esNumero(char *cadena)
{
  int i;
  int decimal = 0;
  for(i = 0; i < strlen(cadena); i++)
  {
    int codigoAscii = toascii(cadena[i]);
    int codigoAscii0 = toascii(cadena[0]);
    if(codigoAscii <= 57 && codigoAscii >= 48)
    {
      
    }
    else if (codigoAscii0 == 43 || codigoAscii0 == 45)
    {
      printf("%c",cadena[0]);
    }
    else if (codigoAscii == 46)
    {
      if (decimal == 0)
      {
        decimal = 1;
      }
      else
      {
        return 0;
      }
    } 
    else
    {
      return 0;
    }

  }
  return 1;
}

int esVoid(char *cadena)
{
  if (strcmp(cadena, "") == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*int esCadena (char *cadena)
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
}*/

int comprobacionFila(METADATOS *meta, char *fila, char *separador)
{
  COLUMNA *pCol = meta -> p;
  char cadena[100];
  int columnas = meta ->nCols;
  int i;
  
  for (i = 0; i < columnas; i++)
  {
    vaciarChar(cadena);
    obtenerCadena(fila, separador, i, cadena);
    if (pCol -> t == comprobarTipo(trim(cadena)))
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
  char tipo[10];

  printf("Numero de filas incorrectas: %d\n", meta -> nErrs);
  printf("Numero de filas correctas: %d\n", meta -> nFils);
  printf("Numero de columnas: %d\n", meta -> nCols);

  while (pCol)
  {
    strcpy(tipo, devuelveTipo(pCol));
    printf("Columna %d: %s -- Tipo: %s\n", contador, pCol -> nom, tipo);
    pCol = pCol -> next;
    contador++;
  }
  
}

char *minus(char *cadena)
{
    int l = 0;
    while (l != strlen(cadena)){
        if ((cadena[l] >= 'A') && (cadena[l]  <= 'Z')){cadena[l]  = cadena[l]  + 32;}
        l++;
    }
    return cadena;
}


int filtroCuenta(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep)
{
  FILTRO *pFiltro = NULL;
  COLUMNA *pCol = NULL;
  int colum = meta -> nCols;
  FILE *fp;
  fp = fopen (nomfc, "r" );
  char temp[1000];
  char cad[100];
  float cadF, valorFiltro;
  int cuenta=0;
  //int cumple = 3;

  if (fp == NULL)
  {
    printf("Error apertura archivo\n");
    return 0;
  }
  else
  {
    fgets(temp,1000,fp);

    while (!feof(fp))
    {
      fgets(temp,1000,fp);
      //cumple = 3;
      if (obtenerColumnas(sep, temp) == colum)
      { 
        if (comprobacionFila(meta, temp, sep) == 1)
        {
          if (filaCumpleFiltro(meta, metaFiltros, temp, sep) == 1)
          {
            cuenta++;
          }
        }
      }
    } 
  }
  if (cuenta == 0)
  {
    printf("No hay datos que cumplan el filtro\n");
  }
  else
  {
    printf("Recuento total que cumplen los filtros: %d\n", cuenta);
  }
  fclose(fp);
  return 1;
}


int filtroTotal(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep, char *columna)
{
  FILTRO *pFiltro = NULL;
  COLUMNA *pCol = buscarCol(meta, columna);
  FILE *fp;
  int colum = meta -> nCols;
  fp = fopen (nomfc, "r" );
  char temp[1000];
  char cad[100];
  int numColumna = buscarColumnaNombre(meta, columna);
  float cadTemp = 0;
  float total = 0;
  //int cumple = 3;
  float cadF, valorFiltro;

  if (pCol == NULL)
  {
    printf("La columna no existe\n");
    return 0;
  }
  else
  {
    if (pCol ->t != NUM)
    {
      printf("El tipo no es NUM\n");
      return 0;
    }
    else
    {
      if (fp == NULL)
      {
        printf("Error apertura archivo\n");
        return 0;
      }
      else
      {
        fgets(temp,1000,fp);

        while (!feof(fp))
        {
          fgets(temp,1000,fp);
          //cumple = 3;
          if (obtenerColumnas(sep, temp) == colum)
            { 
              if (comprobacionFila(meta, temp, sep) == 1)
              {
                if (filaCumpleFiltro(meta, metaFiltros, temp, sep) == 1)
                {
                  vaciarChar(cad);
                  obtenerCadena(temp, sep, numColumna, cad);
                  cadTemp = atof(cad);
                  total = total + cadTemp;
                }
              }
            }
        } 
      }
    }
  }
  if(total == 0)
  {
    printf("No hay datos que cumplan el filtro\n");
  }
  else
  {
  printf("Total :%f\n", total);
  }
  return 1;
}

int filtroPromedio(METADATOS *meta, FILTROS *metaFiltros, char *nomfc, char *sep, char *columna)
{
  FILTRO *pFiltro = NULL;
  COLUMNA *pCol = buscarCol(meta, columna);
  FILE *fp;
  int colum = meta -> nCols;
  fp = fopen (nomfc, "r" );
  char temp[1000];
  char cad[100];
  int numColumna = buscarColumnaNombre(meta, columna);
  float cadTemp = 0;
  float total = 0;
  int veces = 0;
  float cadF, valorFiltro;

  if (pCol == NULL)
  {
    printf("La columna no existe\n");
    return 0;
  }
  else
  {
    if (pCol ->t != NUM)
    {
      printf("El tipo no es NUM\n");
      return 0;
    }
    else
    {
      if (fp == NULL)
      {
        printf("Error apertura archivo\n");
        return 0;
      }
      else
      {
        fgets(temp,1000,fp);

        while (!feof(fp))
        {
          fgets(temp,1000,fp);
          if (obtenerColumnas(sep, temp) == colum)
            { 
              if (comprobacionFila(meta, temp, sep) == 1)
              {
                if (filaCumpleFiltro(meta, metaFiltros, temp, sep) == 1)
                {
                  vaciarChar(cad);
                  obtenerCadena(temp, sep, numColumna, cad);
                  cadTemp = atof(cad);
                  total = total + cadTemp;
                  veces++;
                }
              }
            }
        } 
      }
    }
  }
  if ((total/veces) == 0)
  {
    printf("No hay datos que cumplan el filtro\n");
  }
  else
  {
    printf("Promedio :%f\n", (total/veces));
  }
  return 1;
}

int filaCumpleFiltro(METADATOS *meta, FILTROS *metaFiltros, char *temp, char *sep)
{
  int cumple = 3;
  int colum = meta ->nCols;
  FILTRO *pFiltro = NULL;
  COLUMNA *pCol = NULL;
  char cad[100];
  float cadF, valorFiltro;
  int i;
  
  for (i = 0; i < colum; i++)
  {
    pFiltro = metaFiltros -> p;
    vaciarChar(cad);
    obtenerCadena(temp, sep, i, cad);
    pCol = buscarColumnaNumero(meta, i);

    //Cuando sea 0 es por que la fila no cumple los filtros
    if (cumple != 0)
    {
      while (pFiltro)
      {
        if (pFiltro->pCol == pCol)
        {
          if (pCol ->t == NUM)
          {
            cadF = atof(cad);
            valorFiltro = atof(pFiltro ->valor);
            if (pFiltro ->operador == IGUAL)
            {
              if (cadF == valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
              
            }
            else if (pFiltro ->operador == DISTINTO)
            {
              if (cadF != valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MENOR)
            {
              if (cadF < valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MENORIGUAL)
            {
              if (cadF <= valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MAYOR)
            {
              if (cadF > valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MAYORIGUAL)
            {
              if (cadF >= valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
          }
          else if (pCol ->t == STR)
          {
            if (pFiltro ->operador == IGUAL)
            {
              if (strcmp(cad, pFiltro->valor) == 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
            else if (pFiltro ->operador == DISTINTO)
            {
              if (strcmp(cad, pFiltro->valor) != 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
            else if (pFiltro ->operador == MENOR)
            {
              if (strcmp(cad, pFiltro->valor) < 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
            else if (pFiltro ->operador == MENORIGUAL)
            {
              if (strcmp(cad, pFiltro->valor) <= 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
            else if (pFiltro ->operador == MAYOR)
            {
              if (strcmp(cad, pFiltro->valor) > 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
            else if (pFiltro ->operador == MAYORIGUAL)
            {
              if (strcmp(cad, pFiltro->valor) >= 0)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
              }
            }
          }
          else if (pCol ->t == DATE)
          {
            int anyo = atoi(strtok(cad,"/"));
            int mes = atoi(strtok(NULL, "/"));
            int dia = atoi(strtok(NULL, "/"));
            cadF = (float)fechaAserie(anyo, mes, dia);

            anyo = atoi(strtok(pFiltro->valor,"/"));
            mes = atoi(strtok(NULL, "/"));
            dia = atoi(strtok(NULL, "/"));
            valorFiltro = (float)fechaAserie(anyo, mes, dia);

            if (pFiltro ->operador == IGUAL)
            {
              if (cadF == valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
              
            }
            else if (pFiltro ->operador == DISTINTO)
            {
              if (cadF != valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MENOR)
            {
              if (cadF < valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MENORIGUAL)
            {
              if (cadF <= valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MAYOR)
            {
              if (cadF > valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }
            else if (pFiltro ->operador == MAYORIGUAL)
            {
              if (cadF >= valorFiltro)
              {
                cumple = 1;
              }
              else
              {
                cumple = 0;
                break;
              }
            }

          }
        }
        pFiltro = pFiltro ->next;
      }
    }
  }
  return cumple;
}

char *devuelveOperador(FILTRO *pFiltro)
{
  if (pFiltro->operador == IGUAL)
  {
    return "==";
  }
  else if (pFiltro->operador == DISTINTO)
  {
    return "!=";
  }
  else if (pFiltro->operador == MENOR)
  {
    return "<";
  }
  else if (pFiltro->operador == MENORIGUAL)
  {
    return "<=";
  }
  else if (pFiltro->operador == MAYOR)
  {
    return ">";
  }
  else if (pFiltro->operador == MAYORIGUAL)
  {
    return ">=";
  }
  return " ";
}

char *devuelveTipo(COLUMNA *pCol)
{
  if (pCol->t == VOID)
  {
    return "VOID";
  }
  else if (pCol->t == NUM)
  {
    return "NUM";
  }
  else if (pCol->t == DATE)
  {
    return "DATE";
  }
  else if (pCol->t == STR)
  {
    return "STR";
  }
  return " ";
}


char *trim(char *s)
{
  while(isspace(*s)) s++;

  char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';

  return s; 
}

int es_bisiesto(int anyo)
{
	if(anyo % 400 == 0)
		return 1;
	else if(anyo % 100 == 0)
		return 0;
	else if(anyo % 4 == 0)
		return 1;
	else
		return 0;			
}

int validar_fecha(int anyo, int mes, int dia)
{
	if(anyo == 0)
		return 0;

	switch(mes){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: if(dia < 1 || dia > 31)
				 	return 0;
				break;
		case 4:
		case 6:
		case 9:
		case 11: if(dia < 1 || dia > 30)
				 	return 0;
				break;
		case 2: if(es_bisiesto(anyo))
        {
					if(dia < 1 || dia > 29)
						return 0;
				}
				else{
					if(dia < 1 || dia > 28)
						return 0;
				}
				break;
		default: return 0;
	}

	return 1;
}

int esFecha (char *cadenaFecha)
{
  int i;
  
  if (strlen(cadenaFecha) == 10)
  {
    
    //Comprobamos ANYO YYYY
    for (i = 0; i < 4; i++)
    {
      int codigoAscii = toascii(cadenaFecha[i]);

      if(codigoAscii <= 57 && codigoAscii >= 48)
      {

      }
      else
      {
        return 0;
      }
    }
    
    
    //Comprobamos primer /
    if (cadenaFecha[4] == '/')
    {
      
    }
    else
    {
      return 0;
    }
    
    
    //Comprobamos MESES MM
    for (i = 5; i < 7; i++)
    {
      int codigoAscii = toascii(cadenaFecha[i]);

      if(codigoAscii <= 57 && codigoAscii >= 48)
      {

      }
      else
      {
        return 0;
      }
    }

    //Comprobamos segundo /
    if (cadenaFecha[7] == '/')
    {
      
    }
    else
    {
      return 0;
    }

    //Comprobamos DIAS DD
    for (i = 8; i < 10; i++)
    {
      int codigoAscii = toascii(cadenaFecha[i]);

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
  int anyo = atoi(strtok(cadenaFecha,"/"));
  int mes = atoi(strtok(NULL, "/"));
  int dia = atoi(strtok(NULL, "/"));
  return validar_fecha(anyo, mes, dia);
  
}

int fechaAserie(int anyo, int mes, int dia)
{
	int bisiestos = (anyo-1) / 4 - anyo / 100 + anyo / 400;
	int Tdias = 365 * anyo + bisiestos;
	int acumuladoDiasMes[11] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

	if(es_bisiesto(++anyo)){
		int i;
		for(i = 1; i < 11; i++)
			acumuladoDiasMes[i]++;
	}

	int diasAcumAnyo;

	if(mes == 1)
		diasAcumAnyo = dia;
	else
		diasAcumAnyo = acumuladoDiasMes[mes - 2] + dia;

	return Tdias + diasAcumAnyo;
}

void serieAfecha(int serie, int *anyo, int *mes, int *dia){
	int acumuladoDiasMes[11] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	
	if(serie >= 146097) //146097 d�as en 400 a�os.
		serieFecha(serie, anyo, mes, dia, 0, acumuladoDiasMes);
	else if(serie >= 36524) //36524 d�as en 100 a�os.
		serieFecha(serie, anyo, mes, dia, 1, acumuladoDiasMes);
	else if(serie >= 1461) //1461 d�as en 4 a�os.
		serieFecha(serie, anyo, mes, dia, 2, acumuladoDiasMes);
	else if(serie >= 365) //365 d�as en 1 a�o.
		serieFecha(serie, anyo, mes, dia, 3, acumuladoDiasMes);
	else{
		*anyo = 1;
		diasRestMenorAnyo(serie, mes, dia, acumuladoDiasMes);		
	}			
}

void diasRestMenorAnyo(int diasRest, int *mes, int *dia, int *acumuladoDiasMes)
{
	if(diasRest <= 31)
  {
		*mes = 1;
		*dia = diasRest;
	}
	else
  {
		int i = 0;
		while(diasRest > acumuladoDiasMes[i + 1])
			i++;
	
		*mes = i + 2;
		*dia = diasRest - acumuladoDiasMes[i];
	}	
}


void serieFecha(int serie, int *anyo, int *mes, int *dia, int indice, int *acumuladoDiasMes)
{
	int diasRangoAnyos[4] = {146097, 36524, 1461, 365};
	int RangoAnyos[4] = {400, 100, 4, 1};
	int diasRest = serie, veces;

	*anyo = 0;

	int i;
	for(i = indice; i < 4 && diasRest != 0; i++)
  {
		veces = diasRest / diasRangoAnyos[i];
		*anyo += veces * RangoAnyos[i];
		diasRest %= diasRangoAnyos[i];
	}
	
	if(diasRest == 0 && veces == 4 && (i == 2 || i == 4))
  {
		*mes = 12;
		*dia = 30;		
	}
	else if(diasRest == 0)
  {
		*mes = 12;
		*dia = 31;
	}
	else
  {
		if(es_bisiesto(++*anyo))
    {
			for(i = 1; i < 11; i++)
				acumuladoDiasMes[i]++;
		}
		
		diasRestMenorAnyo(diasRest, mes, dia, acumuladoDiasMes);	
	}	
}

int guardarMeta(METADATOS *meta, char *nombreFichero)
{
  FILE *f;

  f = fopen(nombreFichero, "w");
  if (meta == NULL)
  {
    printf("No hay datos en META\n");
    return 0;
  }

  if (f==NULL)
  {
    printf("Error en la apertura del fichero\n");
    return 0;
  }
  else
  {
    fprintf(f, "Columnas: %d\n", meta ->nCols);
    fprintf(f, "Filas: %d\n", meta ->nFils);
    fprintf(f, "Errores: %d\n", meta ->nErrs);
  }
  fclose(f);
  return 1;

}



void datosPersonales()
{
    printf("\nNOMBRE:\tJORGE SANCHEZ BONILLO\n");
    printf("DNI:\t48725112-A\n");
    printf("EMAIL:\tjorge.sanchez17@goumh.umh.es\n");
}
