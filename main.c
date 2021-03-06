/*********************************************************************************************
* 文件：main.c
* 作者：Meixin 2017.09.25
* 说明：可燃气体传感器实验 例程    
*       
* 修改：2017.11.08 chennian 将led文件替换为通用版驱动文件
*       2018.01.02 zhoucj   修改为串口一
* 注释：
*********************************************************************************************/

/*********************************************************************************************
* 头文件
*********************************************************************************************/
#include <ioCC2530.h>
#include <stdio.h>
#include "clock.h"
#include "delay.h"
#include "mp-4.h"
#include "led.h"
#include "uart1.h"

/*********************************************************************************************
* 名称：main()
* 功能：逻辑代码
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void main(void)
{
  unsigned int combustiblegas = 0;                           	//存储可燃气体状态变量
  char tx_buff[64];
  xtal_init();                                                  //系统时钟初始化     
  led_init();                                                   //LED初始化
  combustiblegas_init();                                    	//可燃气体传感器初始化
  uart1_init(0x00,0x00);                                        //串口初始化
  
  while(1)
  {
    combustiblegas = get_combustiblegas_data();                 //获取可燃气体状态
    sprintf(tx_buff,"combustiblegas:%dppm\r\n",combustiblegas);    //添加可燃气体状态数据字符串到串口缓存
    uart1_send_string(tx_buff);                                  //串口打印
    delay_s(1);                                                	//延时1s
  }
}
