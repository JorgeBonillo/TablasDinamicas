#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

METADATOS *crearMetadatos (int colum, int fila)
{
    METADATOS *nuevoMeta;
    nuevoMeta = (METADATOS*)malloc(sizeof(METADATOS));
    nuevoMeta->nCols = colum;
    nuevoMeta->nFils = 0;
    nuevoMeta->nErrs = 0;
    nuevoMeta->p = (COLUMNA*)malloc(sizeof(COLUMNA));

    return nuevoMeta;
}

COLUMNA *buscarCol (METADATOS* meta, char *nombre)
{
    COLUMNA* pColbuscarCol = NULL;

    pColbuscarCol = meta -> p;

    while (pColbuscarCol)
    {
        if (strcmp(pColbuscarCol->nom, nombre) == 0)
        {
            return pColbuscarCol;
        }
        pColbuscarCol = pColbuscarCol -> next;
        
    }

    return NULL;
}

ETIQUETA *buscarEtiq (char *cad, COLUMNA* pCol)
{
    ETIQUETA* pEtiq;

    pEtiq = pCol -> lista;

    while (pEtiq)
    {
        if (strcmp(pEtiq->etiqueta, cad) == 0)  
        {
            return pEtiq; 
        }    
        pEtiq = pEtiq -> siguiente;       
    }

    return NULL;
}

FILTRO *buscarFiltroNum (int numBuscar, FILTROS *metaFiltros)
{
    FILTRO *pFiltr = metaFiltros -> p;
    //int numBuscar = atoi(charNum);
    int contador = 1;

    while (pFiltr)
    {
        if (numBuscar == contador)
        {
            return pFiltr;
        }
        contador++;
        pFiltr = pFiltr -> next;
    }
    return NULL;
}

int buscarColumnaNum (METADATOS *meta, char *nombreColumna)
{
    COLUMNA *pCol = meta -> p;
    int contador = 0;
    
    /*if (strcmp(pCol->nom, nombreColumna) == 0)
    {
        return contador;
    }*/

    while (pCol)
    {
        if (strcmp(pCol->nom, nombreColumna) == 0)
        {
            return contador;
        }
        pCol = pCol ->next;
        contador++;
    }

    return contador;
}

FILTROS *crearFiltrosMeta ()
{
    FILTROS *nuevoFiltrMeta;
    nuevoFiltrMeta = (FILTROS*)malloc(sizeof(FILTROS));
    nuevoFiltrMeta -> num = 0;
    nuevoFiltrMeta -> p = NULL;

    return nuevoFiltrMeta;
}

int eliminarFiltro (FILTROS *metaFiltros, char *elemento)
{
    int numBorrar = atoi(elemento);
    int contador = 1;
    FILTRO *pFiltr = metaFiltros -> p;
    FILTRO *temp = NULL;
    if (metaFiltros == NULL)
    {
        printf("No hay filtros\n");
        return 0;
    }

    if (numBorrar > metaFiltros ->num)
    {
        printf("El numero no existe\n");
        return 0;
    }  
    else
    {
        temp = metaFiltros -> p;

        //Caso primer elemento
        if (numBorrar == 1)
        {
            metaFiltros -> p = temp ->next;
            metaFiltros -> num = (metaFiltros -> num - 1);
            free (temp);

        }
        //Caso ultimo elemento
        else if (numBorrar == (metaFiltros -> num))
        {
            while ((temp -> next)->next != NULL)
            {
                temp = temp -> next;
            }
            free(temp->next);
            temp -> next = NULL;
            metaFiltros -> num = (metaFiltros -> num - 1);
        }
        //Caso otro elemento
        else
        {
            while (contador != numBorrar-1)
            {
                temp = temp -> next;
                contador++;
            }
            free(temp -> next);
            temp -> next = (temp->next)->next;
            metaFiltros -> num = (metaFiltros -> num - 1);
            
        }
        
    }   
    return 0;
}

int liberarMemoriaMeta (METADATOS *metaColumnas)
{
    
    if (metaColumnas == NULL)
    {
        return 0;
    }

    COLUMNA *pCol = metaColumnas -> p;
    COLUMNA *pColAux = NULL;
    ETIQUETA *pEtiq, *pEtiqAux;
    

    while (pCol)
    {
        pColAux = pCol;
        pCol = pCol -> next;
        free(pColAux->nom);
        if (pColAux->t == STR)
        {
            pEtiq = pColAux->lista;
            while (pEtiq)
            {
                pEtiqAux = pEtiq;
                pEtiq = pEtiq ->siguiente;
                free(pEtiqAux->etiqueta);
                free (pEtiqAux);
            }
            
        }

        free (pColAux);
    }

    
    
    free(metaColumnas);
    return 0;
}

int liberarMemoriaFiltros(FILTROS *metaFiltros)
{

    if (metaFiltros == NULL)
    {
        return 0;
    }

    FILTRO *pFiltro = metaFiltros -> p;
    FILTRO *pFiltroAux = NULL;

    while (pFiltro)
    {
        pFiltroAux = pFiltro;
        pFiltro = pFiltro -> next;
        free (pFiltroAux);
    }

    free (metaFiltros);
    return 1;
}

OPERANDO comprobarOperando (char *operan)
{
  if (strcmp(operan, "==") == 0)
  {
    return IGUAL;
  }
  else if (strcmp(operan, "!=") == 0)
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
  }
  else
  {
    return nulo;
  }

}

TIPO comprobarTipo (char *cadena)
{
    if (esFecha(cadena) == 1)
    {
        return DATE;
    }
    else if (esNumero(cadena) == 1)
    {
        return NUM;
    }
    else if (esCadena(cadena) == 1)
    {
        return STR;
    }
    else
    {
        return VOID;
    }  
}

COLUMNA *buscarColumnaNumero (METADATOS *meta, int numeroCol)
{
    COLUMNA *pCol = meta -> p;

    for (int i = 0; i < numeroCol; i++)
    {  
        pCol = pCol ->next;
    }
    
    return pCol;
}
