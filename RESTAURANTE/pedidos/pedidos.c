#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Pedido {
    char nombre[50];
    float monto;
};

int main() {
    int n, i;
    float total = 0, promedio = 0;
    FILE *archivo;
    time_t t;
    struct tm *fecha;

    
    time(&t);
    fecha = localtime(&t);

    printf("=== REPORTE DE VENTAS ===\n");
    printf("Cuantos pedidos se registraron hoy? ");
    scanf("%d", &n);
    getchar(); 

    struct Pedido pedidos[100]; 

    
    for (i = 0; i < n; i++) {
        printf("\nPedido #%d\n", i + 1);
        printf("Nombre del cliente: ");
        fgets(pedidos[i].nombre, sizeof(pedidos[i].nombre), stdin);
        pedidos[i].nombre[strcspn(pedidos[i].nombre, "\n")] = '\0'; 

        printf("Monto del pedido: $");
        scanf("%f", &pedidos[i].monto);
        getchar(); 

        total += pedidos[i].monto;
    }

    promedio = total / n;

    printf("\nTotal de pedidos: %d\n", n);
    printf("Ventas totales: $%.2f\n", total);
    printf("Promedio de venta por pedido: $%.2f\n", promedio);

    
    archivo = fopen("reportes.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return 1;
    }

    fprintf(archivo, "Reporte de ventas - %02d/%02d/%d\n",
            fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900);
    fprintf(archivo, "---------------------------------\n");

    for (i = 0; i < n; i++) {
        fprintf(archivo, "Pedido #%d - %s - $%.2f\n", i + 1, pedidos[i].nombre, pedidos[i].monto);
    }

    fprintf(archivo, "---------------------------------\n");
    fprintf(archivo, "Total general: $%.2f\n", total);

    fclose(archivo);

    printf("\nArchivo generado: reportes.txt\n");
    printf("\nContenido del archivo reportes.txt:\n\n");

    
    archivo = fopen("reportes.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    char linea[120];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);

    printf("\n\nProceso completado con exito.\n");

    return 0;
}
