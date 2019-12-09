#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

METADATOS *crearMetadatos (int colum, int fila)
{
    METADATOS *nuevoMeta;
    nuevoMeta = (METADATOS*)malloc(sizeof(METADATOS));
    nuevoMeta->nCols = colum;
    nuevoMeta->nFils = fila;
    nuevoMeta->nErrs = 0;
    nuevoMeta->p = (COLUMNA*)malloc(sizeof(COLUMNA));

    return nuevoMeta;
}

COLUMNA *buscarCol (METADATOS* meta, char *nombre)
{
    COLUMNA* pCol;

    pCol = meta -> p;

    while (pCol)
    {
        if (strcmp(pCol->nom, nombre) == 0)
        {
            return pCol;
        }
        pCol = pCol -> next;
        
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
    /*int posicion = 0;
    int numBorrar = atoi(elemento);


    FILTRO *pFiltr = buscarFiltroNum(numBorrar, metaFiltros);

    FILTRO *pFiltrAnterior = NULL;

    FILTRO *temp = NULL;

    if (pFiltr == NULL)
    {
       printf("El numero no existe\n");
       return 0;
    } 
    else
    {
        temp = metaFiltros;

        if (numBorrar == 1)
        {
            metaFiltros =metaFiltros->p;
            free (temp);
        }
        else
        {
            for (int i = 1; i < numBorrar; i++)
            {
                temp = temp -> next;
            }
            free (temp -> next);
            
        }
        
       
    }*/

    int numBorrar = atoi(elemento);
    FILTRO *pFiltr = metaFiltros -> p;
    FILTRO *temp = NULL;

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
            for (int i = 1; i <= numBorrar; i++)
            {
                temp = temp -> next;
            }
            
        }
        
    }   
}

void liberarMemoria(FILTROS *metaFiltros, METADATOS *metaColumnas)
{
    COLUMNA *pCol = metaColumnas -> p;
    COLUMNA *pColAux = NULL;
    FILTRO *pFiltro = metaFiltros -> p;
    FILTRO *pFiltroAux = NULL;

    while (pCol != NULL)
    {
        pColAux = pCol;
        pCol = pCol -> next;
        free (pColAux);
    }
    
    while (pFiltro)
    {
        pFiltroAux = pFiltro;
        pFiltro = pFiltro -> next;
        free (pFiltroAux);
    }
}
   
