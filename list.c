#include "list.h"
#include <string.h>
#include <stdlib.h>

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

    //pCol = meta -> p;

    while (pCol)
    {
        if (strcmp(pCol->nom, nombre) == 0)
        return pCol;
    }

    return NULL;
}

ETIQUETA *buscarEtiq (char *cad, COLUMNA* pCol)
{
    ETIQUETA* pEtiq;

    pEtiq = pCol -> lista;

    /*if (pEtiq == NULL)
    {
        return NULL;
    }*/

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

