#include "GestorAlmacenes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de almacenes en memoria
TDatosAlmacen *Almacenes = NULL;
int NAlmacenes = 0;

// Procedimiento para obtener los datos del almac�n
TDatosAlmacen *datosalmacen_1_svc(int *argp, struct svc_req *rqstp) {
    static TDatosAlmacen result;
    printf("Obteniendo datos del almac�n...\n");

    if (*argp < NAlmacenes) {
        result = Almacenes[*argp];
    } else {
        printf("Almac�n no encontrado.\n");
        memset(&result, 0, sizeof(TDatosAlmacen));
    }

    return &result;
}

// Procedimiento para obtener el n�mero de productos en el almac�n
int *nproductos_1_svc(int *argp, struct svc_req *rqstp) {
    static int result;
    printf("Obteniendo el n�mero de productos del almac�n...\n");

    if (*argp < NAlmacenes) {
        result = 10;
    } else {
        result = -1;
    }

    return &result;
}

// Procedimiento para crear un almac�n
int *crearalmacen_1_svc(TDatosAlmacen *argp, struct svc_req *rqstp) {
    static int result;
    printf("Creando almac�n: %s\n", argp->Nombre);

    TDatosAlmacen nuevoAlmacen;
    strcpy(nuevoAlmacen.Nombre, argp->Nombre);
    strcpy(nuevoAlmacen.Direccion, argp->Direccion);
    strcpy(nuevoAlmacen.Fichero, argp->Fichero);

    NAlmacenes++;
    Almacenes = (TDatosAlmacen *)realloc(Almacenes, NAlmacenes * sizeof(TDatosAlmacen));

    if (Almacenes == NULL) {
        printf("Error al asignar memoria para el nuevo almac�n.\n");
        result = 0;
        return &result;
    }

    Almacenes[NAlmacenes - 1] = nuevoAlmacen;
    result = 1;

    return &result;
}

// Procedimiento para abrir un almac�n desde un fichero
int *abriralmacen_1_svc(char *argp, struct svc_req *rqstp) {
    static int result;
    printf("Abriendo almac�n: %s\n", argp);

    result = 1;
    return &result;
}

// Procedimiento para guardar los datos del almac�n
bool_t *guardaralmacen_1_svc(int *argp, struct svc_req *rqstp) {
    static bool_t result;
    printf("Guardando datos del almac�n...\n");

    result = TRUE;
    return &result;
}

// Procedimiento para cerrar el almac�n
bool_t *cerraralmacen_1_svc(int *argp, struct svc_req *rqstp) {
    static bool_t result;
    printf("Cerrando almac�n con ID %d\n", *argp);

    result = TRUE;
    return &result;
}

// Procedimiento para verificar si el almac�n est� abierto en memoria
bool_t *almacenabierto_1_svc(int *argp, struct svc_req *rqstp) {
    static bool_t result;

    if (*argp < NAlmacenes) {
        printf("Almac�n con ID %d est� abierto en memoria.\n", *argp);
        result = TRUE;
    } else {
        printf("Almac�n con ID %d no est� abierto en memoria.\n", *argp);
        result = FALSE;
    }

    return &result;
}

// Procedimiento para buscar un producto en el almac�n
int *buscaproducto_1_svc(TBusProd *argp, struct svc_req *rqstp) {
    static int result;
    printf("Buscando producto %s en el almac�n %d\n", argp->CodProducto, argp->Almacen);

    result = -1;
    return &result;
}

// Procedimiento para obtener un producto de un almac�n
TProducto *obtenerproducto_1_svc(TObtProd *argp, struct svc_req *rqstp) {
    static TProducto result;
    printf("Obteniendo producto en la posici�n %d del almac�n %d\n", argp->PosProducto, argp->Almacen);

    strcpy(result.CodProd, "P001");
    result.Cantidad = 100;
    strcpy(result.NombreProd, "Producto Ejemplo");
    result.Precio = 10.50;
    strcpy(result.Descripcion, "Descripci�n del producto");
    result.Caducidad.Dia = 12;
    result.Caducidad.Mes = 12;
    result.Caducidad.Anyo = 2025;

    return &result;
}

// Procedimiento para a�adir un producto a un almac�n
bool_t *anadirproducto_1_svc(TActProd *argp, struct svc_req *rqstp) {
    static bool_t result;
    printf("A�adiendo producto %s al almac�n %d\n", argp->Producto.CodProd, argp->Almacen);

    result = TRUE;
    return &result;
}

// Procedimiento para actualizar un producto en un almac�n
bool_t *actualizarproducto_1_svc(TActProd *argp, struct svc_req *rqstp) {
    static bool_t result;
    printf("Actualizando producto %s en el almac�n %d\n", argp->Producto.CodProd, argp->Almacen);

    result = TRUE;
    return &result;
}

// Procedimiento para eliminar un producto de un almac�n
bool_t *eliminarproducto_1_svc(TBusProd *argp, struct svc_req *rqstp) {
    static bool_t result;
    printf("Eliminando producto %s del almac�n %d\n", argp->CodProducto, argp->Almacen);

    result = TRUE;
    return &result;
}

// Procedimiento para realizar operaciones con productos
TProducto *operacion_1_svc(TOperacion *argp, struct svc_req *rqstp) {
    static TProducto result;
    printf("Realizando operaci�n con el producto %d %s %f %f\n", argp->p1, argp->p2, argp->p3, argp->p4);

    strcpy(result.CodProd, "P001");
    result.Cantidad = 100;
    result.Precio = argp->p3 * argp->p4;

    return &result;
}
