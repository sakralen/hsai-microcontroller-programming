/*=============================================================================*\
    
  Файл ParP_SysTick - шаблон программы, демонстрирующий технику использования
таймерного канала и аппаратного прерывания по переполнению таймера
   Демонстрируется использование таймерного канала Systick.

  
\*=============================================================================*/

  //  Макрос для одновременного сброса+установки (разных) битов в порте
  // прямой записью в регистр GPIO_SetRstBits
#define GPIO_SetRstBits(GPIOx,SetPin,RstPin) GPIOx->BSRR=SetPin|(RstPin<<16)

#define PEDESTRIANS
#define ns *3/625
#define mcs *3000/625
#define ms *3000000/625

    // ----- #include directives ------------------------------------------
#include <stm32f10x.h>

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define TIM_CR1_ENABLE   1
#define TIM_CR1_UDIS_DIS 1 << 1
#define TIM_CR1_ARPE_DIS 1 << 1

    // ---------- Global variables -----------------------------------------

u32 uiA, uiVar2;
u32 uiT1, uiT2, uiTp, uiTp2, uiDT, uiDT2;       //  Для измерения времен

    // ----- Function definitions --------------------------------------------
void Delay(u32 uiTDel) {while (uiTDel--) {} }

// Обработчик прерывания SysTick
void SysTick_Handler(void) { 
  GPIOC->ODR ^= 1<<8;           //  
	
}

void TIM4_IRQHandler()
{	
	TIM4->SR &= 0xFFFE; //Update interrupt flag 15.4.5. p.394 _STM32F103-RefManual.pdf
	GPIOC->ODR ^= 1<<9;           //  
	//Delay(0x2FFFFFF);


}

    // ===== Function main() =================================================
int main(void)
{ 
	  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	  GPIOC->CRH &= 0xffffff00;
	  GPIOC->CRH |= 0x33;// + (0x1 << 1);  // пин 0А - выход см. стр 101

__disable_irq ();
__enable_irq ();  // 	PRIMASK register prevents activation of all exceptions with configurable priority.
									//	p.20 STM32F103-ProgManual.pdf
	
	
  //_stm32F103x(8,b)-DataSheet-MenDens.pdf
	// fig.2 стр 12  	
	//  Настройка таймера SysTick 4.5.1. 151 STM32F103-ProgManual.pdf
	  // When the processor is halted for debugging the counter does not decrement
	SysTick->LOAD = 0x895440;   //  Константа перезагрузки  SystemCoreClock  
  SysTick->CTRL = 3;           //  Пуск при входной частоте = Ядро/8 или на частоте ядра
															// Бит 2 - разрешает прерывание от SysTick
// 
//NVIC->IP[(uint32_t)(IRQn)]	

	NVIC->IP[TIM4_IRQn] = 3<<4; // 4.3.7 p.125 STM32F103-ProgManual.pdf
	//SCB->SHP[((uint32_t)(SysTick_IRQn) & 0xF)-4] = ((3 << (8 - __NVIC_PRIO_BITS)) & 0xff);  /* set Priority for Cortex-M3 System Interrupts */

	SCB->SHP[11] = 5<<4; // 4.4.8 p.140 STM32F103-ProgManual.pdf + core_m3.h
	//IP[SysTick_IRQn] = 2<<4;
	//NVIC->IP[SysTick_IRQn] = 1<<4;
	
	
//  Настройка NVIC  118 STM32F103-ProgManual.pdf
NVIC->ISER[0] |= 1<<30; // TIM4_IRQn == 30 p.190 _STM32F103-RefManual.pdf
												// 4.3.2 p.120 STM32F103-ProgManual.pdf


	// Generalpurpose timers (2-5) 15 p.350 _STM32F103-RefManual.pdf
	RCC->APB1ENR |= RCC_APB1Periph_TIM4;  //7.3.8 114 _STM32F103-RefManual.pdf
	TIM4->PSC = 0x44A;
//	TIM4->EGR |= 1; // 396 UEV update generation
	TIM4->ARR = 0x100;
	
  TIM4->DIER |= TIM_IT_Update;  // 15.4.4. p.393
	
	TIM4->CR1 |= TIM_CR1_ENABLE ;// | TIM_CounterMode_Down;
	  	
	
	int t;
while(1)
{
   t++;
	t+=22;
	t=t<<2;
}	
	// AIRCR	PRIGROUP  p. 134 STM32F103-ProgManual.pdf Группы приоритеров
	
	//int i = SCB->AIRCR & 0x700;
//	return 0;
}
