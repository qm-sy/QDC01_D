#include "main.h"

void main( void )
{
    P_SW2 |= 0x80;
    
    GPIO_Init();
    output_statu_init();
    level_info_init();
    /*  调试使用 printf  */
    Uart3_Init();

    /*  温度控制  */
    ADC_Init();

    /*  485控制  */
    Uart4_Init();               //串口4用作485
    Uart4_Send_Statu_Init();    //接收发送初始化

    Timer0_Init();              //不定长数据接收

    /*  PWM控制  */
    PWM_Init();

    /*  定时事件  */
    Timer3_Init();

    EA = 1;     //中断总开关

    temp.temp_scan_flag = 0;

    printf("========== code start ========== \r\n");

    delay_ms(5);
    board_ctrl();
    inksac_ctrl(1);
    while (1)
    {
        Modbus_Event();
        temp_scan();
    }
}