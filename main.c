#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "list.h"


int main(int argc, char const *argv[]) {

  char comando[100];

  char *token[200];

  char nomdb[100]="*";
  char nomfc[100];
  char sep[50];
  char vali[5]="";

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
        liberarMemoria(metaFiltros, meta);
        //return 0;
      break;

      case DATOS:
        printf("caso datos\n");
        printf("----------\n");

        if ((token[1] == NULL) || (token[2] == NULL))
        {
          printf("INTRODUCE UN COMANDO VALIDO\n");
        }
        else
        {
          if ((comprobarMenorMayor(token[1]) == 1) && (comprobarMenorMayor(token[2]) == 1))
          {
            printf("cumple condicion <>\n");
            strcpy(nomfc, eliminarMenorMayor(token[1]));
            strcpy(sep, eliminarMenorMayor(token[2]));
            validarSep(sep);
            if (cargarFichero(nomfc) == 1)
            {
              strcpy(nomdb, nomfc);
              strcpy(vali, "-?");
            }    
          }
          else
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
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
            meta = crearMetadatos(numColumnas(nomfc, sep), numFilas(nomfc, sep));
            metaFiltros = crearFiltrosMeta();
            validarBD(nomfc, sep, meta);
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

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{
          if ((token[1] == NULL) || (token[2] == NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            if ((comprobarMenorMayor(token[1]) == 1) && (comprobarMenorMayor(token[2]) == 1))
            {
              renombrarColum(eliminarMenorMayor(token[1]), eliminarMenorMayor(token[2]), meta);
            }
          }
        //}
      break;

      case INFO:
        printf("caso INFO\n");
        printf("------------\n");

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{

          if (token[1] == NULL)
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            if (comprobarMenorMayor(token[1]) == 1)
            {

            }
          }
          

        //}
      break;

      case FILTROPROM:
        printf("caso FILTRO\n");
        printf("------------\n");

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{
          if ((token[1] == NULL) || (token[2] == NULL) || (token[3] == NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            if ((comprobarMenorMayor(token[1]) == 1) && (comprobarMenorMayor(token[2]) == 1) && (comprobarMenorMayor(token[3]) == 1))
            {
              anadirFiltro(metaFiltros, meta, eliminarMenorMayor(token[1]), eliminarMenorMayor(token[2]), eliminarMenorMayor(token[3]));
            }
            else
            {
              printf("Error\n");
            }
            
            
          }
          
        //}
      break;

      case FILTROSPROM:
        printf("caso FILTROs\n");
        printf("------------\n");

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{
          if (token[1] == NULL)
          {
            imprimirFiltros(metaFiltros);
          }
          else
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          

        //}
      break;

      case BORRAR:
        printf("caso BORRAR\n");
        printf("------------\n");

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{
          if ((token[1] == NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            if (comprobarMenorMayor(token[1]) == 1)
            {
              eliminarFiltro(metaFiltros, eliminarMenorMayor(token[1]));
            }
            else
            {
              printf("Error\n");
            }
            
          }
          

        //}
      break;

      case APLICAR:
        printf("caso APLICAR\n");
        printf("------------\n");

        //TODO QUITAR CUANDO SE FINALICE EL COMANDO VALIDAR
        //if (strcmp(vali, "")==0)
        //{
          if ((token[1] == NULL))
          {
            printf("INTRODUCE UN COMANDO VALIDO\n");
          }
          else
          {
            
          }

        //}
      break;

      case GUARDAR:
        printf("caso GUARDAR\n");
        printf("------------\n");

        if (token[1] == NULL || token[2] == NULL)
        {
          printf("INTRODUCE UN COMANDO VALIDO\n");
        }
        else
        {
          if ((comprobarMenorMayor(token[1]) == 0) && comprobarMenorMayor(token[2]) == 1)
          {
            if (strcmp(token[1], "meta") == 0)
            {
              printf("COMANDO OK \n");
            }
          }
        }
        
      break;

      default:
        printf("INTRODUCE UN COMANDO VALIDO\n");
    }


  }while(strcmp(comando, "salir") != 0);



  return 0;
}
