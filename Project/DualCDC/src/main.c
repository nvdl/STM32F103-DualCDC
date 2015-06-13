#include "stm32f10x.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"

int fputc(int ch, FILE *f)
{
    USART1->DR = (u8) ch;
    // Loop until the end of transmission
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void GPIO_Config();

int main(void) {

  int i;

	HardwareInit();

	USB_Prepare();
	USB_Init();

  // Setup STM32 system (clock, PLL and Flash configuration)
  SystemInit();

  // Setup the GPIOs
  GPIO_Config();

	while (1)	{

	  if (bDeviceState == CONFIGURED) { // ATTACHED
			if (USB_USART1_Data.count_out != 0) {
			  //for (i = 0; i < VIRTUAL_COM_PORT_DATA_SIZE; i ++) {
			  /*for (i = 0; i < 1; i ++) {
			    USB_USART1_Data.buffer_out[i] = 'a';
			    USB_USART1_Data.buffer_in[i] = 'a';
			  }*/
			  GPIO_SetBits(GPIOB, GPIO_Pin_0);
        USB_To_USARTx_Send_Data(&USB_USART1_Data);
        Delay(0xAFFFF);
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			}


			if (USB_USART2_Data.count_out != 0) {
        /*for (i = 0; i < 1; i ++) {
          USB_USART2_Data.buffer_out[i] = 'a';
          USB_USART2_Data.buffer_in[i] = 'a';
        }*/
			  GPIO_SetBits(GPIOB, GPIO_Pin_0);
			  USB_To_USARTx_Send_Data(&USB_USART2_Data);
			  Delay(0xAFFFF);
			  GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			}
		}

	}

}

void Delay(volatile unsigned long delay) {
    for(; delay; --delay );
}

void GPIO_Config() {
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
