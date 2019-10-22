#include "barcode.h"

/**
 * @brief Inicializa a serial
 */
void barcode_init()
{
    if((fd = serialOpen(DEVICE, BAUD)) < 0)
    {
        fprintf(stderr, "\nLeitor de codigo de barras\nerro ao abrir a serial: %s\n", strerror (errno));
        exit(-1);
    }
    delay(2000);
}

/**
 * @brief Faz a leitura do código de barras
 */
void barcode_get_data()
{
    int i=0;
    int timeout_clk_div;

    serialPutchar(fd,'b');

    timeout_clk_div = 0;

    while(!serialDataAvail(fd))
    {
        if(timeout_clk_div++ >= BARCODE_TIMEOUT_VALUE)
        {
            debug_msg(printf("\n>> barcode_check timeout\n"));
            break;
        }
    }

    timeout_clk_div = 0;
    while (1)
    {
        if(serialDataAvail(fd))
        {
            code[i] = serialGetchar(fd)-48;
            debug_msg(printf("%d", code[i]));
            i++;
        }
        if(i==MAX)
            break;

        delay(5);
        if(timeout_clk_div++ >= BARCODE_TIMEOUT_VALUE)
        {
            debug_msg(printf("\n>> barcode_check timeout\n"));
            break;
        }
    }
}

/**
 * @brief Confere os dígitos do código de barras
 * @return 1 se o números forem iguais
 * @return 0 se os números forem diferentes
 */
int barcode_check()
{
    int i;
    int BARCODE_REFERENCE[] = {7,8,9,6,8,0,6,4,0,0,0,9,9};

    for(i=0; i<MAX; i++)
    {
        if(code[i] != BARCODE_REFERENCE[i])
        {
            return 0;
        }
    }
    return 1;
}

void barcode_clear()
{
    int i;
    for(i=0;i<MAX;i++)
    {
        code[i] = 0;
    }
}
