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
    int posicion = 0;
    int numBorrar = atoi(elemento);
    //FILTRO *pFiltr = metaFiltros -> p;

    /*if (metaFiltros -> num < borrar)
    {
        printf("Numero ha borrar es mayor que los elementos\n");
        return 0;
    }
    if (metaFiltros -> p == NULL)
    {
        printf("No hay elemento que borrar\n");
        return 0;
    }

    while (posicion < borrar)
    {
        pFiltr = pFiltr -> next;
        posicion++;
    }

    pFiltr = pFiltr -> next;*/

    FILTRO *pFiltr = buscarFiltroNum(numBorrar, metaFiltros);

    if (pFiltr == NULL)
   {
       printf("El numero no existe\n");
       return 0;
   } 
   else
   {
       printf("Numero encontrado\n");
   }
   
    

}