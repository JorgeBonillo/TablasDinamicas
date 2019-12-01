#include "tools.h"

METADATOS *crearMetadatos (int colum, int fila);

ETIQUETA *buscarEtiq (char *cad, COLUMNA* pCol);

COLUMNA *buscarCol (METADATOS* meta, char *nombre);

FILTROS *crearFiltrosMeta ();

void imprimirFiltros(FILTROS *metaFiltros);

int eliminarFiltro (FILTROS *metaFiltros, char *elemento);