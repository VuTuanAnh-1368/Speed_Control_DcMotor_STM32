# Speed_Control_DcMotor_STM32
By Vu Tuan Anh
# Features
Speed ​​Control DC Motor use STM32, IC L298 (H brigde circult), DC motor.
# Circuit Diagram and Connections
![image](https://github.com/VuTuanAnh-1368/Speed_Control_DcMotor_STM32/assets/92041804/c69f3c19-05b2-4923-9f5e-3641db5176a4)
| STM32f1xx     |     L298      |
| ------------- |:-------------:| 
| GPIOA_PIN3    | INPUT1(Pin5)  | 
| GPIOA_PIN4    | INPUT2(Pin7)  | 
|GPIOA_PIN8(PWM)| ENABLE_A(Pin6)|   

| DC Motor      |     L298      |
| ------------- |:-------------:| 
| PIN1          | OUTPUT1(Pin2) | 
| PIN2          | OUTPUT2(Pin3) | 

## Noted: Supply power to the pin and GND for L298 

# The motor is controlled in 2 directions and controls the speed:
- Direction/motor driver control. Can be FORWARD, BACKWARD, BRAKE, or RELEASE.
- Use:
  <ul>
  <li>void Motor_Start(void)</li>
  <li>void Motor_Stop(void);</li>
  <li>void Motor_SetSpeed(uint16_t speed);</li>
  <li>void Motor_Forward(void);</li>
  <li>void Motor_Backward(void);</li>
  </ul>
- SpeedPWM: Control the speed by changing the "speed" variable.
# All codes implement the functionality using direct register manipulation, without relying on the HAL library, for an STM32F1 series MCU. <space><space>
Click to there: [Source code](https://github.com/VuTuanAnh-1368/Speed_Control_DcMotor_STM32/blob/main/main.c)
