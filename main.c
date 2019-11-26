#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "list.h"


int main(int argc, char const *argv[]) {

  char comando[100];

  char *token[50];

  char nomdb[100]="*";
  char nomfc[100];
  char sep[5];
  char vali[5]="";

  struct METADATOS *meta;
  struct COLUMNAS *columnas;
  meta = NULL;
  columnas = NULL;

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
        return 0;
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
            if (cargarFichero(nomfc) == 1)
            {
              strcpy(nomdb, nomfc);
              strcpy(vali, "-?");
            }
            //nomdb = eliminarMenorMayor(token[1]);
            //strcpy(nomdb, eliminarMenorMayor(token[1]));
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

        if (token[1] == NULL)
        {
          validarBD(nomfc, sep, meta);
        }
      break;

      case RENOMBRAR:
        printf("renombrar\n");
      break;

      case INFO:
        printf("info\n");
      break;

      case FILTRO:
        printf("filtro\n");
      break;

      case FILTROS:
        printf("filtroS\n");
      break;

      case BORRAR:
        printf("borrar\n");
      break;

      case APLICAR:
        printf("aplicar\n");
      break;

      default:
        printf("INTRODUCE UN COMANDO VALIDO\n");
    }


  }while(strcmp(comando, "salir") != 0);



  return 0;
}
