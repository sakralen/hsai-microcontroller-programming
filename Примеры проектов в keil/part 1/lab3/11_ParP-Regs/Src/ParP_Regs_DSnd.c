/*=============================================================================*\
  APN: Тестирование работы с параллельнми портами на плате Discovery
c МК STM32F10xRB с генерацией звука
  
  Конфигурация [ParP-Regs_DSnd] - использует технику работы с параллельными
портами путем обращения напрямую к регистрам.

  Не только светодиод, но и динамик
на Discovery - СвДиоды подкл. к выводам PC8(гол) и PC9(зел)- сюда и динамик
             - кнопка к выводу PA0 - нажал - пищит, отпустил - мигает
  
 \*=============================================================================*/

// ---- Директивы #include подключают заголовочные файлы -----------------------
#include <stm32f10x.h>

// ---- Директивы #define - определения констант и макросов 

// ---- Глобальные переменные -----------------------------------------


    // ----- Function definitions --------------------------------------------
void Delay(u32 uiTDel) 
  {
    while (uiTDel--) {} 
  }	

    // ===== Function main() =================================================
int main(void)
{  	//  Разрешение тактирования порта А и порта С 
    // (к (разным)выводам этих портов на платах подключены кнопка User и СвДиоды)
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;        // p.89

    //  Включение режима "вывод" для светодиода (4 - вход, 3 - выход) // p. 101, 110
  GPIOC->CRH = 0x44444433;  //  Вывод PC8 - для управления USER СвДиод
                            //  Вывод PC9 - СвДиод и динамик
  
  GPIOC->BSRR ^= 0x100;      // p.112
  GPIOC->BSRR ^= 0x1000000;
  GPIOC->BSRR ^= 0x100;
  GPIOC->BSRR ^= 0x1000000;
  
  GPIOC->ODR  ^= 0x100;      // p.112
  GPIOC->ODR  ^= 0x100;      // p.112
  GPIOC->ODR  ^= 0x100;      // p.112
  GPIOC->ODR  ^= 0x100;      // p.112
  
                            
  while(1) 
  {  //  Звук по нажатию кнопки USER
    if(((GPIOA->IDR)&(1<<0))==(1<<0)) //  Если кнопка нажата - пищит  p. 111
    {
      GPIOC->ODR ^=1<<9;    //  СвДиодЗ+динамик (пищит) p.112
      Delay(2000);
      {             //  USER кнопка Discovery к PA0 (нажата - 1)
        __NOP();    //  см. core_cmInstr.h, строки 321++
      }             // чтобы можно было поставить "точку останова"
    }
    else                              //  Если кнопка отпущена - мигает           
    {
      GPIOC->ODR ^=1<<8;    //  СвДиодГ - мигает
      Delay(1000000);
      {             //  USER кнопка Discovery к PA0 (отпущена - 0)
        __NOP();    //  см. core_cmInstr.h, строки 321++
      }             // чтобы можно было поставить "точку останова"      
    }
  }
//	return 0;
}
