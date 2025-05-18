/*
|P0^0|         |P1^0|Analog1    |P2^0|           |P3^0|RX1        |P4^0|           |P5^0|     
|P0^1|         |P1^1|Analog2    |P2^1|Signal_OUT |P3^1|TX1        |P4^1|AC_Out1    |P5^1|     
|P0^2|RX_485   |P1^2|           |P2^2|PWM        |P3^2|ZERO       |P4^2|AC_Out2    |P5^2|     
|P0^3|TX_485   |P1^3|Signal_IN  |P2^3|LED        |P3^3|           |P4^3|AC_Out3    |P5^3|     
|P0^4|DR_485   |P1^4|NTC1       |P2^4|           |P3^4|           |P4^4|           |P5^4|
|P0^5|         |P1^5|NTC2       |P2^5|           |P3^5|           |P4^5|           |P5^5|             
|P0^6|         |P1^6|NTC3       |P2^6|           |P3^6|FAN_TMEP   |P4^6|           |P5^6|     
|P0^7|         |P1^7|NTC4       |P2^7|           |P3^7|Signal_3V3 |P4^7|Buzzer     |P5^7|     
*/ 




#include "main.h"





#define S4TI    0X02
#define S4RI    0X01

typedef struct 
{
    uint8_t     RX4_rev_end_Flag;       //数据包接收完毕标志
    uint8_t     TX4_buf[128];           //SBUF TI缓冲区
    uint8_t     RX4_buf[128];           //SBUF RI缓冲区
    uint8_t     TX4_send_bytelength;    //发送字节数
    uint8_t     TX4_send_cnt;           //发送计数
    uint16_t    RX4_rev_timeout;        //接收超时
    uint8_t     RX4_rev_cnt;            //接收计数
    uint8_t     DR_Flag;                //DR
}RS485;

RS485 rs485;

void GPIO_Init( void )
{
    P0M0 = 0x18;    P0M1 = 0x00;        //P0.3、P0.4为推挽输出
    P1M0 = 0x00;    P1M1 = 0xf8;        //P1.4、P1.5、P1.6、P1.7为高阻输入
    P2M0 = 0x0e;    P2M1 = 0x00;        //P2.0、P2.1、P2.2、P2.3为推挽输出
    P3M0 = 0Xc2;    P3M1 = 0X00;        //P3.6、P3.7为推挽输出
    P4M0 = 0x8e;    P4M1 = 0x00;        //P4.1、P4.2、P4.3、P4.7为推挽输出       
    P5M0 = 0X00;    P5M1 = 0X00;    
}

void Uart4_Init(void)	//115200bps@11.0592MHz
{
	S4CON  = 0x10;		//8位数据,可变波特率
	S4CON |= 0x40;		//串口4选择定时器4为波特率发生器

	T4T3M |= 0x20;		//定时器时钟1T模式

	T4L    = 0xE8;			//设置定时初始值
	T4H    = 0xFF;			//设置定时初始值

	T4T3M |= 0x80;		//定时器4开始计时

	IE2   |= 0X10;		//ES4 = 1
}

void Timer0_Init( void )	 //1ms@11.0592MHz   16位手动重装载
{
	AUXR |= 0x80;			 //定时器时钟1T模式
	TMOD &= 0xF0;			 //设置定时器模式
	TL0   = 0xCD;			 //设置定时初始值
	TH0   = 0xD4;          	 //设置定时初始值
	TF0   = 0;				 //清除TF0标志
	TR0   = 1;				 //定时器0开始计时

    ET0   = 1;				 //打开IE-ET0，TIM0中断
}

void Uart4_Send_Statu_Init( void )
{
    rs485.RX4_rev_end_Flag = 0;
    rs485.TX4_buf[128] = 0;
    rs485.RX4_buf[128] = 0;
    rs485.TX4_send_bytelength = 0;
    rs485.TX4_send_cnt = 0;
    rs485.RX4_rev_timeout = 0;
    rs485.RX4_rev_cnt = 0;
    DR_485 = 0;
}

void Uart4_ISR() interrupt 18 
{   

    /* 1, 检测到S4TI置1，即发送完毕                       */
    if( S4CON & S4TI )          //
    {
        /* 2, 软件将S4TI清零，等待发送标志位重置，可继续发送    */
        S4CON &= ~S4TI;         
        
        /* 3, 依次将TX4_buf中数据送出（写S4BUF操作即为发送）    */
        if( rs485.TX4_send_bytelength != 0 )
        {
            S4BUF = rs485.TX4_buf[rs485.TX4_send_cnt++];
            rs485.TX4_send_bytelength--;
        }else
        {
            rs485.TX4_send_cnt = 0;
            DR_485 = 0;
        }
    }
    
    /* 1, 检测到S2RI置1，即接收完毕                       */
    if( S4CON & S4RI )
    {
        /* 2, 软件将S2RI清零，等待接收标志位重置，可继续发送    */
        S4CON &= ~S4RI;
        /* 3, 判断数据包是否接收完毕                           */
        if( !rs485.RX4_rev_end_Flag )
        {
            /* 4, 数据包大于RX_buf 则从头计数                  */
            if( rs485.RX4_rev_cnt > 128 )
            {
                rs485.RX4_rev_cnt = 0;
            }

            /* 5, 依次将RX4_buf中数据接收（读S2BUF操作即为接收）*/
            rs485.RX4_buf[rs485.RX4_rev_cnt] = S4BUF;
            rs485.RX4_rev_cnt++;
        }
        /* 6, 重置接收完毕判断时间                              */
        rs485.RX4_rev_timeout = 5;
    }
}

void Tim0_ISR( void ) interrupt 1   //1ms
{
    /* 1, 如果接收未超时                                             */
    if ( rs485.RX4_rev_timeout != 0 )  
    {
        rs485.RX4_rev_timeout--;
        /* 2, 如果接收超时                                          */
        if( rs485.RX4_rev_timeout == 0 )  
        {
            if( rs485.RX4_rev_cnt > 0 )  
            {   
                 /* 3, 接收完毕标志位亮起并初始化接收缓冲区         */
                rs485.RX4_rev_end_Flag = 1;    
            }
        }
    } 
}

void Modbus_Event_485( void )
{
    uint16_t crc,rccrc;
    
    /*1.接收完毕                                           */
    if( rs485.RX4_rev_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485.RX4_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485.RX4_buf, rs485.RX4_rev_cnt-2);
        rccrc = (rs485.RX4_buf[rs485.RX4_rev_cnt-1]) | (rs485.RX4_buf[rs485.RX4_rev_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485.RX4_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485.RX4_buf[0] == 0XEB )
            {
                switch ( rs485.RX4_buf[1] )
                {
                    case 0x03:
                        //Modbus_Fun3_485();
                        break;

                    case 0x04:
                        //Modbus_Fun4_485();
                        break;

                    case 0x06:
                        Modbus_Fun6_485();
                        break;  

                    case 0x10:  
                        //Modbus_Fun16_485();

                    default:
                        break;
                }
            }
        }
    }
}

void Modbus_Fun6_485( void )
{
    static uint8_t change = 1;
    switch (rs485.RX4_buf[3])
    {
        /*  40001  风速设置                 */
        case 0x00:                  

            break;

        /*  40002  LED 开关状态设置                          */
        case 0x01:                                         


            break;

        /*  40003 三路220V输出使能设置                          */
        case 0x02:                                         

            break;  
            
        /*  40004  同步状态设置                   */
        case 0x03:                                         
        change = 1 - change;                                  
        Buzzer = change;
            break;

        /*  40005  工作模式设置                   */
        case 0x04:     
        change = 1 - change;                                  
        Buzzer = change;
            break;

        /*  40006  报警温度设置                   */
        case 0x05:                                         
        change = 1 - change;                                  
        Buzzer = change;
            break;

        case 0x06:  
        change = 1 - change;                                  
        Buzzer = change;
            break;
            
        default:
            break;   
    }

    slave_to_master_485(0x06,8);
}

void slave_to_master_485(uint8_t code_num,uint8_t length)
{
    uint16_t crc;

    switch (code_num)
    {
        case 0x03:
            
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            
            break;
        case 0x04:
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            break;    

        case 0x06:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,8);

            rs485.TX4_send_bytelength = length;

            break;   

        case 0x10:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,6);
        
            crc = MODBUS_CRC16(rs485.TX4_buf,6);

            rs485.TX4_buf[7] = crc;                 //CRC H
            rs485.TX4_buf[6] = crc>>8;              //CRC L
        
            rs485.TX4_send_bytelength = length;
            
            break;         

        default:
            break;
    }

    DR_485 = 1;                                 //485可以发送
    delay_ms(2);
    S4CON |= S4TI;                              //开始发送
    delay_ms(1);
}

void delay_ms(uint16_t time)	//@11.0592MHz
{
	unsigned char data i, j;
    for(time;time>0;time--)
    {
        _nop_();
        _nop_();
        _nop_();
        i = 11;
        j = 190;
        do
        {
            while (--j);
        } while (--i);
    }
}

uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length)
{
	uint8_t	i;
	uint16_t	crc16;

    /* 1, 预置16位CRC寄存器为0xffff（即全为1）                          */
	crc16 = 0xffff;	

	do
	{
        /* 2, 把8位数据与16位CRC寄存器的低位相异或，把结果放于CRC寄存器     */        
		crc16 ^= (uint16_t)*buf;		//
		for(i=0; i<8; i++)		
		{
            /* 3, 如果最低位为1，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位 再异或0xA001    */
			if(crc16 & 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            /* 4, 如果最低位为0，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位                */
            else
            {
                crc16 >>= 1;
            }		
		}
		buf++;
	}while(--length != 0);

	return	(crc16);
}

void main( void )
{
    P_SW2 |= 0x80;
    
    GPIO_Init();

    /*  485控制  */
    Uart4_Init();               //串口4用作485
    Uart4_Send_Statu_Init();    //接收发送初始化

    Timer0_Init();              //不定长数据接收


    EA = 1;     //中断总开关

    while (1)
    {
        Modbus_Event_485();
    }  
}