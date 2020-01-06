#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadenas.h"
#include "datos.h"


int main(int argc, char const *argv[]) {

  char comando[100];

  char *token[10];
  int validado = 0;
  char nomdb[100]="*";
  char nomfc[100];
  char sep[50];
  char vali[50]="";
  char ejer1[100];

  METADATOS *meta;
  //struct COLUMNAS *columnas;
  meta = NULL;
  FILTROS *metaFiltros;
  metaFiltros = NULL;
  //columnas = NULL;

  datosPersonales();

  do{
    do{
        //Impresion del nombre del fichero
        printf("[%s%s]>> ", nomdb, vali);
        gets(comando);
        int d=0;

        //Caso que el usuario no ha introducido ningun comando
        if(strcmp(comando, "") ==0)
        {
          printf("INTRODUCE UN COMANDO\n");
        }
        /*else if (comando == NULL)
        {
          printf("INTRODUCE UN COMANDO\n");
        }
        else
        {
          
        }*/
        

        //Caso el usuario ha introducido algo
        if (strcmp(comando, "") !=0)
        {
          int nTok=0;
          token[0] = strtok(comando, " ");
          do
          {
            printf( "\nTOKENIZACION\n");
            printf( "%s\n", token[nTok]);
            nTok++;
            token[nTok] = strtok(NULL, " ");
          }while(token[nTok] != NULL );
          printf( "--------------\n\n");
        }

    }while(strcmp(comando, "") ==0);


    switch (comandoPrompt(token[0])) {

      case SALIR:
        printf("caso salir\n");
        printf("----------\n");
        liberarMemoriaFiltros(metaFiltros);
        liberarMemoriaMeta(meta);
        //return 0;
      break;

      case DATOS:
        printf("caso datos\n");
        printf("----------\n");

        if (token[1] == NULL || token[2] == NULL || token[3] != NULL)
        {
          printf("INTRODUCE UN COMANDO VALIDO\n");
        }
        else
        {
          vaciarChar(nomfc);
          strcpy(nomfc, token[1]);
          strcpy(sep, validarSep(token[2]));
          if (cargarFichero(nomfc) == 1)
          {
            strcpy(nomdb, nomfc);
            strcpy(vali, "-?");
            validado = 0;
            liberarMemoriaFiltros(metaFiltros);
            liberarMemoriaMeta(meta);
          }    
          else
          {
            printf("El fichero no existe\n");
          }
        }

      break;

      case VALIDAR:
        printf("caso validar\n");
        printf("------------\n");

        if (strcmp(nomdb, "*")==0)
        {
          printf("No se ha introducido ninguna base de datos\n");
        }
        else
        {
          if (token[1] == NULL)
          {
            //Primera vez que se pone validar
            if (validado == 0)
            {
              meta = crearMetadatos(numColumnas(nomfc, sep), numFilas(nomfc, sep));
              metaFiltros = crearFiltrosMeta();
              validarBD(nomfc, sep, meta);
              infoValidar(meta);
              sprintf(ejer1, " (%d,%d)", meta->nFils, meta ->nCols);
              strcpy(vali, ejer1);
              validado = 1;
            }
            //Segunda o posterior vez ponemos el comando
            else
            {
              infoValidar(meta);
            }
          }
          else
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          
        }
        
      break;

      case RENOMBRAR:
        printf("caso RENOMBRAR\n");
        printf("------------\n");

        if (validado == 1)
        {
          if ((token[1] == NULL) || (token[2] == NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {      
            renombrarColum(token[1], token[2], meta);
          }
        }
        else
        {
          printf("EL FICHERO NO ESTA VALIDADO\n");
        }
        
      break;

      case INFO:
        printf("caso INFO\n");
        printf("------------\n");

        if (validado == 1)
        {
          if (token[1] == NULL || token[2] != NULL)
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            infoColum(nomfc, sep, meta, token[1]);
          } 
        }
        else
        {
          printf("EL FICHERO NO ESTA VALIDADO\n");
        }
      break;

      case FILTROPROM:
        printf("caso FILTRO\n");
        printf("------------\n");

        if (validado == 1)
        {
          if ((token[1] == NULL) || (token[2] == NULL) || (token[3] == NULL) || (token[4] != NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {           
            anadirFiltro(metaFiltros, meta, token[1], token[2], token[3]);           
          }
        }
      break;

      case FILTROSPROM:
        printf("caso FILTROs\n");
        printf("------------\n");

        if (validado == 1)
        {
          if (token[1] == NULL)
          {
            imprimirFiltros(metaFiltros);
          }
          else
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
        }
        else
        {
          printf("EL FICHERO NO ESTA VALIDADO\n");
        }
      break;

      case BORRAR:
        printf("caso BORRAR\n");
        printf("------------\n");

        if (validado == 1)
        {
          if (token[1] == NULL || token[2] != NULL)
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
              eliminarFiltro(metaFiltros, token[1]);
          }
        }
        else
        {
          printf("EL FICHERO NO ESTA VALIDADO\n");
        }
      break;

      case APLICAR:
        printf("caso APLICAR\n");
        printf("------------\n");

        if (validado == 1)
        {
          if (strcmp(minus(token[1]), "cuenta") == 0)
          {
            printf("CUENTA\n");
            if (token[2] == NULL)
            {
              filtroCuenta(meta, metaFiltros, nomfc, sep);
            }
            else
            {
              printf("INTRODUCE UN COMANDO VALIDO\n");
            }
          }
          else if (strcmp(minus(token[1]), "total") == 0)
          {
            printf("TOTAL\n");
            if (token[3] == NULL)
            {
              filtroTotal(meta, metaFiltros, nomfc, sep, token[2]);
            }
            else
            {
              printf("INTRODUCE UN COMANDO VALIDO\n");
            }
            
          }
          else if (strcmp(minus(token[1]), "promedio") == 0)
          {
            printf("PROMEDIO\n");
            if (token[3] == NULL)
            {
              filtroPromedio(meta, metaFiltros, nomfc, sep, token[2]);
            }
            else
            {
              printf("INTRODUCE UN COMANDO VALIDO\n");
            }
          }
          else
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
        }
        else
        {
          printf("EL FICHERO NO ESTA VALIDADO\n");
        }
        
      break;

      case GUARDAR:
        printf("caso GUARDAR\n");
        printf("------------\n");

        if (token[1] == NULL || token[2] == NULL || token[3] != NULL)
        {
          printf("INTRODUCE UN COMANDO VALIDO\n");
        }
        else
        {
          if (strcmp(token[1], "meta") == 0)
          {
            guardarMeta(meta, token[2]);
          } 
        }
        
      break;

      default:
        printf("INTRODUCE UN COMANDO VALIDO\n");
    }


  }while(strcmp(comando, "salir") != 0);



  return 0;
}
