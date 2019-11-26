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
        return FILTRO;

    if(strcmp(prompt, "filtros")==0)
        return FILTROS;

    if(strcmp(prompt, "borrar")==0)
        return BORRAR;

    if(strcmp(prompt, "aplicar")==0)
        return APLICAR;

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

int cargarFichero(char *nombreFichero)
{
  FILE *fp;
  int ok = 0;
  //strcpy(nombreFichero, eliminarMenorMayor(nombreFichero));
  printf("%s\n", nombreFichero);
  fp = fopen (nombreFichero, "r" );
  if (fp==NULL)
  {
    printf("El fichero no existe\n");
  }
  else
  {
    printf("El fichero existe\n");
    ok = 1;
  }
  return ok;
}

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



int validarBD(char *nomfc, char *sep, METADATOS *meta)
{

  FILE *f;
  int fila=0;
  int colum=0;
  char temp[1000]; //¿cuanto tamaños le asignamos? tenemos 200 caracteres
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
    fgets(temp,1000,f);
    colum = obtenerColumnas(sep, temp);
   
    printf("%d\n",colum);

    while (!feof(f))
    {
      fgets(temp,200,f);
      fila++;
    }
    printf("Filas: %d\n", fila);

    meta = crearMetadatos(colum, fila);

    rewind(f);
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
        //pCol->lista = (ETIQUETA*)malloc(sizeof(ETIQUETA));
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
            //pEtiq -> siguiente = (ETIQUETA*)malloc(sizeof(ETIQUETA));
            //pEtiq = pEtiq -> siguiente;
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
      //pCol = pCol -> next;
    }
    
    //int S = obtenerColumnas(sep, temp);

    /*for (int i = 0; i < colum; i++)
    {
      char cad[50];
      obtenerCadena(temp2, sep, i, cad);
      printf("cadena: %s", cad);
      for (int j = 0; j <= 50; j++)
      {
        cad[j]= '\0';
      }
    }*/
    
    /*fgets(temp,1000,f);
    //fgets(temp2,1000,f);
    pCol = meta -> p;
     for (int i = 0; i<= colum; i++)
     {
        if (i==0)
        {
          pCol->nom = strdup( strtok(temp, sep) );
          //pCol->t = ObtenerTipo( strtok(temp2, sep) );
          pCol -> next = (COLUMNA*)malloc(sizeof(COLUMNA));
          pCol = pCol->next;
        }
        else
        {
          cadena[i] = strtok(NULL, sep);
          pCol->nom = strdup(cadena[i]);
          pCol -> next = (COLUMNA*)malloc(sizeof(COLUMNA));
          pCol = pCol->next;
        }
        
          
     }*/



  }

  return 0;
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



void datosPersonales()
{
    printf("\nNOMBRE:\tJORGE SANCHEZ BONILLO\n");
    printf("DNI:\t48725112-A\n");
    printf("EMAIL:\tjorge.sanchez17@goumh.umh.es\n");
}
