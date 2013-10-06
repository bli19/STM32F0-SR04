#include "main.h"
//#include "ultrasonic.h"
#include "delay.h"
//#include "lid.h"
#include "uart.h"

uint8_t Tx_Buffer[] = "good";
#define countof(a) (sizeof(a) / sizeof(*(a)))

void Ledinit(){
	
	
	GPIO_InitTypeDef GPIO_InitStructure;	 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	/* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
}

void ultra_sta(){
	GPIO_InitTypeDef GPIO_InitStructure;	 
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOF, ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;//Trig
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//Echo
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//control pin of the motor: PF4
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOF, &GPIO_InitStructure);
}

 void ultras(float *p){
	 unsigned char i;
  unsigned long int j;
	float Ultr_Temp;
	 for(i=0;i<5;i++){
		
	 GPIO_SetBits(GPIOB,GPIO_Pin_4);  
	 delay_ms(10);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_4); 
		 
	 //LCD_Clear(LCD_COLOR_GREY); 
   while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0); //Here connections o(∩_∩)o 
		
	 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==1){
	 delay_us(8);//8us
	 j++; 
   }
   Ultr_Temp+=340/2*j*10;// max = 3m, haha, somtimes can reach 5-6m which is funny
		j=0;
		delay_ms(60);//should be around 60, nothing much nothing less
	 }
	 *p=Ultr_Temp/5/1000000;
	 
   }
 

int main(void){
	int i;
  float temp;
 //cha DisNum[16];	
  uint8_t DisNum[16];
 	SystemInit();
	// USART_Configuration();
	
	delay_init(48);
	STM320518_LCD_Init();
 	ultra_sta(); 
	
//   Ledinit();
	LCD_Clear(LCD_COLOR_GREY); 
  while(1)
	{ 
  	ultras(&temp);
 //sprintf(DisNum," # Distance: %.3f", temp);		
    sprintf((char*)DisNum," # Distance: %.3f", temp);
// 	//	printf("s");
  	UART_Send(DisNum, 18);	 
//   //UART_Send(DisNum, countof(DisNum)-1);
  	LCD_DisplayStringLine(3,DisNum);  
//     
// //  
// // }
// 	
// 	 
//   }
 



