#include "stm32f10x.h"

void input1(void);
void input2(void);
void pwm_Init(void);
void SystemClock_Config(void);
void Motor_Start(void);
void Motor_Stop(void);
void Motor_SetSpeed(uint16_t speed);
void Motor_Forward(void);
void Motor_Backward(void);

int main(void) {

  SystemClock_Config();
  input1();
  input2();
  pwm_Init();

  while (1) {
    //   Forward speed 0->100
      Motor_Forward();
      Motor_Start();
      for (uint16_t speed = 0; speed <= 100; speed += 5) {
          Motor_SetSpeed(speed);
          for (volatile int i = 0; i < 1000000; i++);
      }
      for (volatile int i = 0; i < 500000; i++);

	//   Backward speed 100->0
      Motor_Backward();
      for (uint16_t speed = 100; speed > 0; speed -= 5) {
          Motor_SetSpeed(speed);
          for (volatile int i = 0; i < 1000000; i++);
      }
      for (volatile int i = 0; i < 500000; i++);

    //   Backward speed 0->100
      Motor_Backward();
      for (uint16_t speed = 0; speed <= 100; speed += 5) {
    	  Motor_SetSpeed(speed);
    	  for (volatile int i = 0; i < 100000; i++);
      }

    //   Stop
      Motor_Stop();
      for (volatile int i = 0; i < 1000000; i++);

    //The motor rotates at a steady speed (==20)
      Motor_Forward();
      Motor_Start();
      Motor_SetSpeed(20);
      for (volatile int i = 0; i < 100000000; i++);
      Motor_Backward();
      Motor_SetSpeed(20);
      for (volatile int i = 0; i < 100000000; i++);
  }
}

void input1() {
      RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
      GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
      GPIOA->CRL |= GPIO_CRL_MODE3_0;
}

void input2() {
     RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
     GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
     GPIOA->CRL |= GPIO_CRL_MODE4_0;
}

void pwm_Init() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN;;
    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CR1 = 0;
    TIM1->PSC = 6399;
    TIM1->ARR = 99;
    TIM1->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM1->CCER = TIM_CCER_CC1E;
    TIM1->BDTR = TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Motor_Start(void) {
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Motor_Stop(void) {
    TIM1->CR1 &= ~TIM_CR1_CEN;
    GPIOA->BSRR = (1 << 20) | (1 << 19);
}

void Motor_SetSpeed(uint16_t speed) {
    if (speed > 100) speed = 100;
    uint32_t pulse = speed * (TIM1->ARR + 1) / 100;
    TIM1->CCR1 = pulse;
}

void Motor_Forward(void) {
    GPIOA->BSRR = (1 << 3);
    GPIOA->BSRR = (1 << 20);
}

void Motor_Backward(void) {
    GPIOA->BSRR = (1 << 4);
    GPIOA->BSRR = (1 << 19);
}
void SystemClock_Config(void) {

}
