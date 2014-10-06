#include <reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;
uint16 cnt=0;
uint8 Buf[] = "hello world1!\n";
void UART_init(void){
	SCON = 0x50;
	TMOD = 0x21;
	PCON = 0;							   
	TH0 = 0xD8;	//设置定时器0
	TL0 = 0xF0;
	TH1 = 0xFD;	//设置波特率
	TL1 = 0xFD;
	TR0 = 1;
	TR1 = 1;
	ET1 = 0;
	ES = 1;
	EA = 1;
	ET0 = 1;
}

void UART_send_byte(uint8 dat){
	SBUF = dat;
	while(TI==0);
	TI = 0;
}

void UART_send_string(uint8 *buf){
	while(*buf!='\0'){
		UART_send_byte(*buf++);
	}
}

main(){
	UART_init();	
	while(1);
}

void timeint() interrupt 1{
	TH0 = 0xD8;
	TL0 = 0xF0;
	if(cnt==200){
		cnt = 0;
		UART_send_string(Buf);
	}
	cnt++;
}
