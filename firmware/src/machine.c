/**
* @file machine.c
*/

#include "machine.h"

void machine_init()
{

}

void machine_run()
{
    if(clk)
    {
        clk = 0;

        switch (state_machine) {
            case IDLE:
            task_idle();
            break;

            case RUNNING:

            break;

            default:
            break;
        }
    }
}

void task_idle(void)
{
    if(led_clk_div++ > 50)
    {
        cpl_led();
    }

    if(buzzer_clk_div == 0)
    {
        set_buzzer();
    }
    if(buzzer_clk_div++ > 2)
    {
        clr_buzzer();
    }
    if(buzzer_clk_div++ > 100)
        buzzer_clk_div = 0;

    #ifdef DISPLAY_ON

    #endif

}

void task_running(void)
{
    if(led_clk_div++ > 20)
    {
        led_clk_div = 0;
        cpl_led();
    }
}
