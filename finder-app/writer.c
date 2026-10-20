#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

/* writer.c - Assignment 2 (AESD / CU Boulder)
 *
 * Alternativa en C al script writer.sh del Assignment 1.
 * Uso: writer <archivo> <texto>
 *   - sin exactamente 2 argumentos -> mensaje de error + return 1
 *   - NO crea directorios (el llamador debe crearlos)
 *   - escribe el texto en el archivo, con logging via syslog (LOG_USER)
 */
int main(int argc, char **argv)
{
    /* 1) Validar argumentos */
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <archivo> <texto>\n", argv[0]);
        return 1;
    }

    /* 2) Configurar syslog con la facility LOG_USER */
    openlog("writer", LOG_PID, LOG_USER);

    /* 3) Abrir el archivo para escritura (sobrescribe si existe) */
    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Error al abrir el archivo %s para escritura", argv[1]);
        perror("fopen");
        closelog();
        return 1;
    }

    /* 4) Escribir el texto */
    if (fprintf(fp, "%s", argv[2]) < 0) {
        syslog(LOG_ERR, "Error al escribir en el archivo %s", argv[1]);
        fclose(fp);
        closelog();
        return 1;
    }

    /* 5) Cerrar y registrar el exito (LOG_DEBUG) */
    fclose(fp);
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
    closelog();

    return 0;
}
