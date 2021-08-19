#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "tpk_lcd8.h"

unsigned char mcp3208_read() //데이터 read 함수 
{
int high, low;

   PORTB=0x00; //mcp3208 선택 (Slave Select)
   SPDR=0x06; //SPDR=0x06; //READ 명령 첫번째 바이트 
   while(!(SPSR&0x80)); //전송 완료 대기 
   SPDR=0x3f; //READ 명령 두번째 바이트
   while(!(SPSR&0x80)); //전송 완료 대기 
   SPDR=0x00; //더미 
   while(!(SPSR&0x80)); //전송 완료 대기 
   high=SPDR; //상위 7비트 read
   SPDR=0x00; //더미 
    while(!(SPSR&0x80)); //전송 완료 대기 
   low=SPDR; //하위 7비트 read 
   PORTB=0x01; //mcp3208 (Slave) 디스에이블 
   high=high&0x0f;
   return (high<<8) + low;
}

int main(void)
{

float data;
char msg[16];

   lcd_init();
   lcd_display_OnOff(1,0,0);

   DDRF=0x00;
   DDRB=0b00000111;
   PORTB=0x01;
   SPCR=0x5c;
   SPSR=0x00;
 
   lcd_display_clear();
   lcd_string("SPI <= mcp3208");

   
while (1) {

      data=mcp3208_read();
      sprintf(msg,"ADC=%.2f",data);
      lcd_display_position(2,1);
      lcd_string(msg);

  }
}
