
 /* File name:
 *
 * Description:
 *
 *
 * Last Changed By:  $Author:
 * Revision:         $Revision: $
 * Last Changed:     $Date: $
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stm32f401re.h>
#include <stm32f401re_rcc.h> // thêm thư viện RCC cấp xung clock cho GPOP
#include <stm32f401re_gpio.h>// thêm thư viện GPIO

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/

#define LED_GPIO_PORT						GPIOA
#define LED_GPIO_PIN						GPIO_Pin_0
#define LEDControl_SetClock					RCC_AHB1Periph_GPIOA
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static uint32_t globalVariable = 0;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
//Khai báo hàm nguyên mẫu
static void mainInit();
static void led_Init(void);
static void ButtonB2_Init(void);
void watchLocalVariable();
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

/**
 * @brief   main function
 *
 * @param [] : None
 *
 * @return value : int
 */
int main(void)
{
	// Initialize
	mainInit();
	watchLocalVariable();

	while(1)
	{
	// Sử dụng hàm GPIO_ReadInputDataBit để đọc trạng thái đầu vào của nút nhấn
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN);
		}
		else
		{
			GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
		}
	}
}

/**
 * @brief   main init
 *
 * @param [] : None
 *
 * @return value : None
 */
static void mainInit()
{
	SystemCoreClockUpdate(); //Khởi tạo tần số của hệ thống là 84 MHz.
	ButtonB2_Init();	     // khởi tạo button B2
	led_Init();

}

/**
 * @brief   test debug
 *
 * @param [] : None
 *
 * @return value : None
 */
void watchLocalVariable()
{
	uint8_t localVariable = 0;
	globalVariable = localVariable + 1;
	localVariable = globalVariable + 1;
}

/**
 * @brief   button init
 *
 * @param [] : None
 *
 * @return value : None
 */
static void ButtonB2_Init(void) {
	// Khai báo biến thuộc kiểu struct
	GPIO_InitTypeDef GPIO_InitStructure;

	// Cấp xung clock hoạt động cho PORT B

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// Chọn chân

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;

	//Chon Mode Input

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

	// Cấu hình tốc độ

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// Trạng thái ban đầu kéo lên

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	// Khởi tạo các giá trị

	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief   Led init
 *
 * @param [] : None
 *
 * @return value : None
 */
static void led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}
