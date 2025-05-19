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
    while (rs485.connect_flag == 0)
    {
        send_to_EB_16();
        Modbus_Event_485();
        delay_ms(10);
    }
    
    temp.temp_scan_flag = 0;
    delay_ms(20);
    //printf("========== code start ========== \r\n");

    while (1)
    {
        Modbus_Event_485();
        Modbus_Event_Sata();
        temp_scan();
        if( rs485.scan_04_flag == 1 )
        {
            send_to_EB_04();
            rs485.scan_04_flag = 0;
        }
        
    }  
}
