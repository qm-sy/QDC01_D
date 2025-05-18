#include "main.h"

void main( void )
{
    P_SW2 |= 0x80;
    
    GPIO_Init();

    /*  调试使用 printf  */
    Uart1_Init();
    Uart1_Send_Statu_Init();    //接收发送初始化

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

    eeprom_statu_judge();       //EEPROM初始化

    //printf("========== code start ========== \r\n");

    while (1)
    {
        Modbus_Event_485();
        Modbus_Event_Sata();
        temp_scan();
    }  
}