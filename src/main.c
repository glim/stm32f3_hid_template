/**
  ******************************************************************************
  * @file    USB_Example/main.c  
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f30x.h"
#include "stm32f3_discovery.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
__IO uint8_t SentDataFlag = 1;
__IO uint8_t ReceivedDataFlag = 0;
__IO uint8_t ReceiveBuffer[64];
__IO uint8_t SendBuffer[64];
//__IO uint32_t *SoftwareKey;
unsigned int SoftwareKey __attribute__((persistent,section("boot_software_key")));

/* Private function prototypes -----------------------------------------------*/
void LED_Config(void);
void HandleDataPacket(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int main(void)
{  
  uint8_t i = 0;
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

  /* prove to me that it works */
  LED_Config();
    
  /* Configure the USB */
  USB_Config();

  /* Infinite loop */
  while (1)
  {
    if (ReceivedDataFlag)
    {
    	//This function returns a flag that decides whether or not a response is readied from that last packet
    	if (HandleDataPacket())
    	{
        	//TODO: Make this a macro
        	if (SentDataFlag)
        	{
        		SentDataFlag = 0;
    			USB_SIL_Write(EP1_IN, (uint8_t *)SendBuffer, USB_PACKET_SIZE);
    			SetEPTxValid(ENDP1);
        	}
    	}

    	ReceivedDataFlag = 0;
    }
  }
}

/**
 * Initialize the LEDS on the Discovery board
 */
void LED_Config(void)
{
	  STM_EVAL_LEDInit(LED3);
	  STM_EVAL_LEDInit(LED4);
	  STM_EVAL_LEDInit(LED5);
	  STM_EVAL_LEDInit(LED6);
	  STM_EVAL_LEDInit(LED7);
	  STM_EVAL_LEDInit(LED8);
	  STM_EVAL_LEDInit(LED9);
	  STM_EVAL_LEDInit(LED10);
}

bool HandleDataPacket()
{
	//allow toggling of the Discovery LEDs as an example;
	//the first byte of the return packet is the state of the LED
	//the final 63 bytes are the same as the sent packet + 1
	//if the command is out of range ( > 7), an error packet of all FF's is returned

	uint8_t command = ReceiveBuffer[0];
	uint8_t j = 1;

	switch(command)
	{
		case LED3:
		case LED4:
		case LED5:
		case LED6:
		case LED7:
		case LED8:
		case LED9:
		case LED10:
			STM_EVAL_LEDToggle(command);
			SendBuffer[0] = GPIO_PIN[command];
			for(j=1;j<USB_PACKET_SIZE;j++)
				SendBuffer[j] = ReceiveBuffer[j]+1;
			break;
		default:
			for(j=0;j<USB_PACKET_SIZE;j++)
				SendBuffer[j] = 0xFF;
			break;
	}

	return TRUE; //if you return false, no response will be sent to the host
}

/**
  * @brief  Configure the USB.
  * @param  None
  * @retval None
  */
void USB_Config(void)
{
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  
  USB_Init();

  while (bDeviceState != CONFIGURED)
  {}
}


/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
