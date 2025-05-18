#include "modbus_rtu.h"

MODBIS_INFO modbus;

/**
 * @brief	modbus_rtu  无奇偶校验
 *
 * @param   void
 *
 * @return  void 
**/
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
            if( rs485.RX4_buf[0] == ADDR_485 )
            {
                switch ( rs485.RX4_buf[1] )
                {
                    case 0x03:
                        Modbus_Fun3_485();
                        break;

                    case 0x04:
                        Modbus_Fun4_485();
                        break;

                    case 0x06:
                        Modbus_Fun6_485();
                        break;  

                    case 0x10:  
                        Modbus_Fun16_485();

                    default:
                        break;
                }
            }
        }
    }
}


/**
 * @brief	modbus_rtu  无奇偶校验
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Event_Sata( void )
{
    uint16_t crc,rccrc;
    
    /*1.接收完毕                                           */
    if( sata.RX1_rev_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        sata.RX1_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(sata.RX1_buf, sata.RX1_rev_cnt-2);
        rccrc = (sata.RX1_buf[sata.RX1_rev_cnt-2]) | (sata.RX1_buf[sata.RX1_rev_cnt-1]<<8);

        /*4.清空接收计数                                    */
        sata.RX1_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( sata.RX1_buf[0] == ADDR_SATA )
            {
                switch ( sata.RX1_buf[1] )
                {
                    case 0x03:
                        Modbus_Fun3_Sata();

                        break;

                    case 0x04:
                        Modbus_Fun4_Sata();
                        
                        break;

                    case 0x06:
                        Modbus_Fun6_Sata();

                        break;  

                    case 0x10:  
                        Modbus_Fun16_Sata();

                    default:
                        break;
                }
            }
        }
    }
}

/**
 * @brief	读输入寄存器  03
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun3_485( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                //DATA1 H 位置
    modbus.byte_cnt   = (rs485.RX4_buf[4]<<8 | rs485.RX4_buf[5]) *2;
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    rs485.TX4_buf[0]  = ADDR_485;                //Addr
    rs485.TX4_buf[1]  = 0x03;                   //Fun
    rs485.TX4_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {   
            /*  40001 风速查询                     */
            case 0x00:


                break;

            /*  40002 LED开关状态查询                     */    
            case 0x01:

                break;

            /*  40003 3路220V开关使能查询                         */
            case 0x02:    

                break;

            /*  40004 同步状态查询              */
            case 0x03:    


                break;

            /*  40005 工作模式查询                     */
            case 0x04:   

                break;

            /*  40006 报警温度查询                     */
            case 5:   
        

                break;
            default:
                break;
        }
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master_485(0x03,3 + modbus.byte_cnt);
}


/**
 * @brief	读输入寄存器  03
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun3_Sata( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                //DATA1 H 位置
    modbus.byte_cnt   = (sata.RX1_buf[4]<<8 | sata.RX1_buf[5]) *2;
    modbus.start_addr = sata.RX1_buf[2]<<8 | sata.RX1_buf[3];

    sata.TX1_buf[0]  = ADDR_SATA;                //Addr
    sata.TX1_buf[1]  = 0x03;                   //Fun
    sata.TX1_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {   
            /*  40001 胶辊加热                     */
            case 0x00:
                modbus.byte_info_H = qdc_info.roller_temp;
                modbus.byte_info_L = qdc_info.roller_switch;

                break;

            /*  40002 LED开关状态查询                     */    
            case 0x01:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = qdc_info.led_switch;

                break;

            /*  40003 风扇                         */
            case 0x02:    
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = qdc_info.fan_level;

                break;

            /*  40004 底板加热              */
            case 0x03:    
                modbus.byte_info_H = qdc_info.board_temp;
                modbus.byte_info_L = qdc_info.board_switch;

                break;

            /*  40005 墨囊加热                     */
            case 0x04:   
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = qdc_info.inksac_switch;

                break;

            /*  40006 循环控制                     */
            case 0x05:   
                modbus.byte_info_H = (qdc_info.cir_stop_time << 1) | (qdc_info.cir_start_time >> 5);
                modbus.byte_info_L = qdc_info.cir_switch | (qdc_info.cir_start_time << 3);
                
                break;
            /*  40007 搅拌控制                     */
            case 0x06:   
                modbus.byte_info_H = (qdc_info.stir_stop_time << 1) | (qdc_info.stir_start_time >> 5);
                modbus.byte_info_L = qdc_info.stir_switch | (qdc_info.stir_start_time << 3);

                break;

            /*  40008  缺墨延时时间                      */
            case 0x07:   
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = qdc_info.ink_out_time;
                
                break;

            default:
                break;
        }
        sata.TX1_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        sata.TX1_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master_Sata(0x03,3 + modbus.byte_cnt);
}

/**
 * @brief	读输出寄存器  04
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun4_485( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                 //DATA1 H 位置
    modbus.byte_cnt   = (rs485.RX4_buf[4]<<8 | rs485.RX4_buf[5]) *2;
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    rs485.TX4_buf[0]  = ADDR_485;                //Addr
    rs485.TX4_buf[1]  = 0x04;                   //Fun
    rs485.TX4_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {
            /*  30001  NTC1、NTC2温度查询                           */
            case 0x00:


                break;

            /*  30002  NTC3、NTC4温度查询                */
            case 0x01:


                break;

            /*  30003 环境温湿度查询                   */
            case 0x02:

                break;

            /*  30004 Signal_IN状态查询                   */
            case 0x03:
 

                break;
                
            /*  30005 运行时间（min）                   */
            case 0x04:

                break;

            /*  30006 运行时间（h）                   */
            case 0x05:
    

                break;

            default:
                break;
        }
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        rs485.TX4_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master_485(0x04,3 + modbus.byte_cnt);
}


/**
 * @brief	读输出寄存器  04
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun4_Sata( void )
{
    uint16_t i;

    modbus.send_value_addr  = 3;                 //DATA1 H 位置
    modbus.byte_cnt   = (sata.RX1_buf[4]<<8 | sata.RX1_buf[5]) *2;
    modbus.start_addr = sata.RX1_buf[2]<<8 | sata.RX1_buf[3];

    sata.TX1_buf[0]  = ADDR_SATA;                //Addr
    sata.TX1_buf[1]  = 0x04;                   //Fun
    sata.TX1_buf[2]  = modbus.byte_cnt;        //Byte Count

    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus.byte_info_H = modbus.byte_info_L = 0X00;
        switch (i)
        {
            /*  30001  1~7通道液位信息                           */
            case 0x00:
                modbus.byte_info_H = qdc_info.level_info2;
                modbus.byte_info_L = qdc_info.level_info1;

                break;

            /*  30002 废墨液位信息                 */
            case 0x01:
                waste_ink_scan();
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = qdc_info.waste_ink;

                break;

            /*  30003 环境温湿度查询                   */
            case 0x02:
                modbus.byte_info_H = temp.dht11_humidity;
                modbus.byte_info_L = temp.dht11_temp;

                break;

            /*  30004 NTC温度                  */
            case 0x03:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = temp.temp_value1;

                break;
                
            /*  30005 热电堆温度                   */
            case 0x04:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = 25;
                
                break;

            default:
                break;
        }
        sata.TX1_buf[modbus.send_value_addr++] = modbus.byte_info_H;
        sata.TX1_buf[modbus.send_value_addr++] = modbus.byte_info_L;
    }
    slave_to_master_Sata(0x04,3 + modbus.byte_cnt);
}

/**
 * @brief	写单个输出寄存器  06
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun6_485( void )
{
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
            qdc_info.board_temp = sata.RX1_buf[4];     
            qdc_info.board_switch = sata.RX1_buf[5];   
            eeprom_data_record();
            break;

        /*  40005  工作模式设置                   */
        case 0x04:                                         
            qdc_info.inksac_switch = sata.RX1_buf[5]; 
            eeprom_data_record();
            break;

        /*  40006  报警温度设置                   */
        case 0x05:                                         
            qdc_info.cir_switch = (sata.RX1_buf[5] & 0x07);     
            qdc_info.cir_start_time = (sata.RX1_buf[5] >> 3) | ((sata.RX1_buf[4] & 0x01) << 5);
            qdc_info.cir_stop_time = sata.RX1_buf[4] >> 1;
            
            break;

        case 0x06:  
            qdc_info.stir_switch = (sata.RX1_buf[5] & 0x07);     
            qdc_info.stir_start_time = (sata.RX1_buf[5] >> 3) | ((sata.RX1_buf[4] & 0x01) << 5);
            qdc_info.stir_stop_time = sata.RX1_buf[4] >> 1;
            eeprom_data_record();

            break;
            
        default:
            break;   
    }
    
    slave_to_master_Sata(0x06,8);
    
}


/**
 * @brief	写单个输出寄存器  06
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun6_Sata( void )
{
    switch (sata.RX1_buf[3])
    {
        /*  40001  胶辊加热                 */
        case 0x00:                  
            qdc_info.roller_temp = sata.RX1_buf[4];
            qdc_info.roller_switch = sata.RX1_buf[5];
            rubber_roller_ctrl(qdc_info.roller_switch);

            slave_to_master_Sata(0x06,8);
            eeprom_data_record();

            break;

        /*  40002  LED 开关状态设置                          */
        case 0x01:        
            qdc_info.fan_level = sata.RX1_buf[5];                                 
            led_ctrl(sata.RX1_buf[5]);

            slave_to_master_Sata(0x06,8);
            eeprom_data_record();    

            break;

        /*  40003 风扇                          */
        case 0x02: 
            qdc_info.fan_level = sata.RX1_buf[5];                                     
            fan_ctrl(qdc_info.fan_level);

            slave_to_master_Sata(0x06,8);
            eeprom_data_record();

            break;  
            
        /*  40004  底板加热                   */
        case 0x03:            
            send_to_EB_06(0x03,sata.RX1_buf[4],sata.RX1_buf[5]);   

            break;

        /*  40005  墨囊加热                   */
        case 0x04:                   
            send_to_EB_06(0x04,0x00,sata.RX1_buf[5]);                      


            break;

        /*  40006  循环控制                   */
        case 0x05:                
            send_to_EB_06(0x05,sata.RX1_buf[4],sata.RX1_buf[5]);                       

            break;
        /*  40007  搅拌控制                   */
        case 0x06:       
            send_to_EB_06(0x06,sata.RX1_buf[4],sata.RX1_buf[5]);                                          
    
            break;

        /*  40008  缺墨延时时间                   */
        case 0x07:                                         
            qdc_info.ink_out_time = sata.RX1_buf[5];  

            slave_to_master_Sata(0x06,8);
            eeprom_data_record();

            break;

        default:
            break;   
    }
}

/**
 * @brief	写多个输出寄存器  16
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun16_485( void )
{
    uint16_t i;

    modbus.rcv_value_addr = 7;                  //DATA1 H位置
    modbus.byte_cnt   = rs485.RX4_buf[6];
    modbus.start_addr = rs485.RX4_buf[2]<<8 | rs485.RX4_buf[3];

    
    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++)
    {
        modbus.byte_info_H = rs485.RX4_buf[modbus.rcv_value_addr];
        modbus.byte_info_L = rs485.RX4_buf[modbus.rcv_value_addr + 1];
        switch (i)
        {
            /*  40001  风速设置                 */
            case 0x00:

                break;
            
            /*  40002  LED 开关状态设置                          */
            case 0x01:
                led_ctrl(modbus.byte_info_L);

                eeprom.led_info = modbus.byte_info_L;

                break;

            /*  40003 三路220V输出使能设置                          */
            case 0x02:


                break;

            
            /*  40004  同步状态设置                   */
            case 0x03:


                break;

            /*  40005  工作模式设置                   */
            case 0x04:                                         


                break;

            /*  40006  报警温度设置                   */
            case 0x05:                                         

                
                break;
                
            default:
                break;
        }
        modbus.rcv_value_addr += 2;         //从Value1_H →→ 从Value2_H
    }

    slave_to_master_485(0x10,8);

    eeprom_data_record();                      //记录更改后的值
}


/**
 * @brief	写多个输出寄存器  16
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun16_Sata( void )
{
    uint16_t i;

    modbus.rcv_value_addr = 7;                  //DATA1 H位置
    modbus.byte_cnt   = sata.RX1_buf[6];
    modbus.start_addr = sata.RX1_buf[2]<<8 |sata.RX1_buf[3];

    
    for( i = modbus.start_addr; i < modbus.start_addr + modbus.byte_cnt/2; i++)
    {
        modbus.byte_info_H = sata.RX1_buf[modbus.rcv_value_addr];
        modbus.byte_info_L = sata.RX1_buf[modbus.rcv_value_addr + 1];
        switch (i)
        {
            /*  40001  风速设置                 */
            case 0x00:
                qdc_info.roller_temp = sata.RX1_buf[4];
                qdc_info.roller_switch = sata.RX1_buf[5];
                rubber_roller_ctrl(qdc_info.roller_switch);

                slave_to_master_Sata(0x06,8);
                eeprom_data_record();

                break;
            
            /*  40002  LED 开关状态设置                          */
            case 0x01:
                qdc_info.fan_level = sata.RX1_buf[5];                                 
                led_ctrl(sata.RX1_buf[5]);

                slave_to_master_Sata(0x06,8);
                eeprom_data_record();     

                break;

            /*  40003 三路220V输出使能设置                          */
            case 0x02:
                qdc_info.fan_level = sata.RX1_buf[5];                                     
                fan_ctrl(qdc_info.fan_level);

                slave_to_master_Sata(0x06,8);
                eeprom_data_record();

                break;

            
            /*  40004  同步状态设置                   */
            case 0x03:


                break;

            /*  40005  工作模式设置                   */
            case 0x04:                                         


                break;

            /*  40006  报警温度设置                   */
            case 0x05:                                         

                
                break;
                
            default:
                break;
        }
        modbus.rcv_value_addr += 2;         //从Value1_H →→ 从Value2_H
    }

    slave_to_master_Sata(0x10,8);

    //eeprom_data_record();                      //记录更改后的值
}

/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
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


/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave_to_master_Sata(uint8_t code_num,uint8_t length)
{
    uint16_t crc;

    switch (code_num)
    {
        case 0x03:
            crc = MODBUS_CRC16(sata.TX1_buf,length);

            sata.TX1_buf[length+1] = crc>>8;                 //CRC H
            sata.TX1_buf[length] = crc;            //CRC L

            sata.TX1_send_bytelength = length + 2;
            
            break;
        case 0x04:
            crc = MODBUS_CRC16(sata.TX1_buf,length);

            sata.TX1_buf[length+1] = crc>>8;                 //CRC H
            sata.TX1_buf[length] = crc;            //CRC L

            sata.TX1_send_bytelength = length + 2;
            
            break;    

        case 0x06:
            memcpy(sata.TX1_buf,sata.RX1_buf,8);

            sata.TX1_send_bytelength = length;
            
            break;   

        case 0x10:
            memcpy(sata.TX1_buf,sata.RX1_buf,6);
        
            crc = MODBUS_CRC16(sata.TX1_buf,6);

            sata.TX1_buf[6] = crc;                 //CRC H
            sata.TX1_buf[6] = crc>>8;              //CRC L

            sata.TX1_send_bytelength = length;

            break;         

        default:
            break;
    }
    TI  = 1;                              //开始发送
    delay_ms(1);
}

/**
 * @brief	crc校验函数
 * 
 * @param   buf：  Address(1 byte) +Funtion(1 byte) ）+Data(n byte)   
 * @param   length:数据长度           
 * 
  @return  crc16:crc校验的值 2byte
 */
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

void waste_ink_scan( void )
{
        if( WASTE_INK == 0 )
        {
            qdc_info.waste_ink = 0;
        }else
        {
            qdc_info.waste_ink = 1;
        }
}

void send_to_EB_16( void )
{
    uint8_t send_buf[17];
   uint16_t crc;

   send_buf[0] = 0xEB;
   send_buf[1] = 0x10;
   send_buf[2] = 0x00;
   send_buf[3] = 0x00;
   send_buf[4] = 0x00;
   send_buf[5] = 0x04;
   send_buf[6] = 0x08;

   send_buf[7] = qdc_info.board_temp;
   send_buf[8] = qdc_info.board_switch;

   send_buf[9] = 0x00;
   send_buf[10] = qdc_info.inksac_switch;

   send_buf[11] = (qdc_info.cir_stop_time << 1) | (qdc_info.cir_start_time >> 5);
   send_buf[12] = qdc_info.cir_switch | (qdc_info.cir_start_time << 3);

   send_buf[13] = (qdc_info.stir_stop_time << 1) | (qdc_info.stir_start_time >> 5);
   send_buf[14] = qdc_info.stir_switch | (qdc_info.stir_start_time << 3);

   crc = MODBUS_CRC16(send_buf,15);

   send_buf[15] = crc>>8;
   send_buf[16] = crc;

   memcpy(rs485.TX4_buf,send_buf,17);
   
   rs485.TX4_send_bytelength = 17;
   DR_485 = 1;                                 //485可以发送
   delay_ms(2);
   S4CON |= S4TI;                              //开始发送
   delay_ms(1);
}


void send_to_EB_06( uint8_t addr, uint8_t val_H, uint8_t val_L)
{
    uint8_t send_buf[8];
    uint16_t crc;

    send_buf[0] = 0xEB;
    send_buf[1] = 0x06;
    send_buf[2] = 0x00;
    send_buf[3] = addr;
    send_buf[4] = val_H;
    send_buf[5] = val_L;

    crc = MODBUS_CRC16(send_buf,6);

    send_buf[6] = crc>>8;
    send_buf[7] = crc;

    memcpy(rs485.TX4_buf,send_buf,8);

    rs485.TX4_send_bytelength = 8;
    DR_485 = 1;                                 //485可以发送
    delay_ms(2);
    S4CON |= S4TI;                              //开始发送
    delay_ms(1);
}

