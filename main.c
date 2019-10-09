


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <DS3231.h>

uint8_t *seco;
uint8_t *minute;
uint8_t *hou;
uint8_t *dayOfWeek;
uint8_t *dayOfMonth;
uint8_t *month;
uint8_t *yea;

#define control_bus PORTB
#define controlbus_direction DDRB
#define data_bus PORTD
#define databus_direction DDRD

#define rs 0
#define en 1
#define d4 0
#define d5 1
#define d6 2
#define d7 3



void LCD_CmdWrite( char a)
{
	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	
	_delay_ms(2);
	
	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	
	_delay_ms(2);
}




void LCD_DataWrite( char a)
{
	
	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);
	
	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);
	
}





void LCD_Init()
{
	controlbus_direction |= ((1<<rs)|(1<<en));
	databus_direction |= ((1<<d7)|(1<<d6)|(1<<d5)|(1<<d4));
	_delay_ms(2);
	LCD_CmdWrite(0x01); // clear display
	LCD_CmdWrite(0x02); // back to home
	LCD_CmdWrite(0x28); // 4bit,2line,5x8 pixel
	LCD_CmdWrite(0x06); // entry mode,cursor increments by cursor shift
	LCD_CmdWrite(0x0c); // display ON,cursor OFF
	LCD_CmdWrite(0x80); // force cursor to begin at line1

}
void LCD_Init2()
{
	controlbus_direction |= ((1<<rs)|(1<<en));
	databus_direction |= ((1<<d7)|(1<<d6)|(1<<d5)|(1<<d4));
	_delay_ms(2);
	LCD_CmdWrite(0x01); // clear display
	LCD_CmdWrite(0x02); // back to home
	LCD_CmdWrite(0x20); // 4bit,1line,5x8 pixel
	LCD_CmdWrite(0x06); // entry mode,cursor increments by cursor shift
	LCD_CmdWrite(0x0c); // display ON,cursor OFF
	LCD_CmdWrite(0x80); // force cursor to begin at line1

}

void LCD_Disp(const char *p)
{
	while(*p!='\0')
	{
		LCD_DataWrite(*p);
		p++; _delay_ms(2);
	}
}

void LCD_setCursor(int a, int b)
{
	int i=0;
	switch(b){
		case 0:LCD_CmdWrite(0x80);break;
		case 1:LCD_CmdWrite(0xC0);break;
	}
	
	for(i=0;i<a;i++)
	LCD_CmdWrite(0x14);
}

void Menu_setclock()
{
	
	LCD_Init2();
	LCD_setCursor(0,0);
	LCD_Disp("   SET  CLOCK   ");
	//LCD_setCursor(79,0);
	//LCD_Disp(" ");
	
}

void Menu_deletealarm()
{
	
	LCD_Init2();
	LCD_setCursor(0,0);
	LCD_Disp("  DELETE ALARM  ");
	//LCD_setCursor(79,0);
	//LCD_Disp(" ");
	
}

void Menu_setalarm()
{
	
	LCD_Init2();
	LCD_setCursor(0,0);
	LCD_Disp("   SET  ALARM   ");
	//LCD_setCursor(79,0);
	//LCD_Disp(" ");
	
}

void test()
{
	
	LCD_Init2();
	LCD_setCursor(0,0);
	
	//LCD_setCursor(79,0);
	//LCD_Disp(" ");
	
}

int main()
{
	
	
	
	Menu_setalarm();
	char secstring[2];
	DS3231_getTime(*seco,*minute,*hou,*dayOfWeek,*dayOfMonth,*month,*yea);
	itoa(*seco,secstring,10);
	



	while(1)
	{
		LCD_Init2();
		LCD_setCursor(0,0);
		
		LCD_Disp(secstring);
		
		_delay_ms(1500);
	}
	
}

