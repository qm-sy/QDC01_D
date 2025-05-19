#include "ntc.h"

TEMP temp;

/**
 * @brief 取10次adc_val均值对应的temp
 *
 * @param[in] channle_x ntc通道1~4
 * 
 * @return  temp :最终温度
 * 
**/
uint16_t get_temp( uint8_t channle_x )
{
    uint8_t t;
    uint16_t adc_val = 0;
    uint16_t temp_val;

    /* 1, 取10次adc_val                           */
    for( t = 0; t < 10; t++ )
		{
			adc_val += Get_ADC_12bit(channle_x);
            
		}	       
    adc_val = adc_val/10;

    temp_val = (adc_val-654) / 23;
   
    return temp_val;
}
