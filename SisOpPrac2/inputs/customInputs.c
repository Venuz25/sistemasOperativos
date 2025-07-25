
#include <stdio.h>
#include <string.h>

#include "../main.h"
#include "inputs.h"

static inline void fflushstdin(void)
{
    if (!(feof(stdin) && ferror(stdin)))
        while (getchar() != '\n');
}

void checkIntPosValue(const char *msj, int *val)
{	
    SCR_CLEAR;
    printf("%s", msj);
    while (( scanf("%d", val) == 0 ) || (*val < 0))
    {
        fflushstdin();
        printf("Ingrese valor positivo mayor que cero\n");
        PAUSE;
        SCR_CLEAR;
        printf("%s", msj);
    }
}

void checkStrValue(const char *msj, char *str, size_t len)
{
    char tmp[1024];
    if (len == 0 || str == NULL)
    {
        return;
    }
    
    SCR_CLEAR;
    printf("%s", msj);
    while ((scanf("%1024s", tmp) == 0) || (len <= strlen(tmp)))
    {
        fflushstdin();
        printf("Ingrese una cadena de caracteres como maximo de 1023 como maximo\n");
        PAUSE;
        SCR_CLEAR;
        printf("%s", msj);
    }
    
    memcpy(str, tmp, len);
}