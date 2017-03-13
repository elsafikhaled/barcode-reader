/*
 * Barcode.c
 *
 *  Created on: ٠٦‏/٠٢‏/٢٠١٧
 *      Author: El-safi
 */
#include "lcdEKE.h"
#include "TbUart.h"
#include "EEPROM.h"
#include <util/delay.h>
#include "RTC1307.h"

int main(void){
/* Data types for RTC */
U8_t h=0,m=0,s=0;
U8_t hour[2],minute[2],second[2];

/* Draw on LCD by GCRAM clock symbol*/
//U8_t pattern[8]={0x00, 0x0E, 0x15, 0x15, 0x17, 0x11, 0x0E, 0x00};

/*Data types for application*/
U8_t barcodeNew=13;
U8_t reading=0;
U8_t dataEEP[]={0};
U8_t eeprom_address=0;

/*Database system flags */
struct databaseSys{
	  U8_t flag:1;
}system;
 system.flag=1;

/*AVR registers  */
 DDRD|=(1<<PD5);
 PORTD&=~(1<<PD5);

/*System initialization*/
EKE_LCD_INIT();
TbUart_init();
EEPROM_init();
RTC1307_INIT();
EKE_LCD_INIT();
setDate(17,3,11);


while(1){

//set time
if(system.flag==1){
	hour[0]=TbUart_get_char()-'0';
	hour[1]=TbUart_get_char()-'0';
	minute[0]=TbUart_get_char()-'0';
	minute[1]=TbUart_get_char()-'0';
	second[0]=TbUart_get_char()-'0';
	second[1]=TbUart_get_char()-'0';
	if(hour[0]==0){
	   h=hour[0]+hour[1];
	}
	else{h=hour[0]*10+hour[1];}
    if(minute[0]==0){
	   m=minute[0]+minute[1];
    }
    else{m=minute[0]*10+minute[1];}
    if(second[0]==0){
	   s=second[0]+second[1];
    }
    else{s=second[0]*10+second[1];}
	setTime(h,m,s);
	TbUart_Send_stri((U8_t*)"setTime:OK");
	system.flag=0;
}
//get new data from barcode
barcodeNew=TB_getchar_notWait();

//get stored value from EEPROM
if(barcodeNew!='0'){
	barcodeNew=barcodeNew-'0';
 for(eeprom_address=0;eeprom_address<=57;eeprom_address++){
    reading=EEPROM_Read(eeprom_address,1);
    if(reading==barcodeNew){
        EEPROM_READ_STRING((eeprom_address+1),1,dataEEP);
        //buzzer firing
        PORTD|=(1<<PD5);
        _delay_ms(50);
        PORTD&=~(1<<PD5);
        EKE_clear_lcd();
        //TB GUI
        TbUart_Send_stri((U8_t*)dataEEP);
        TbUart_Send_char('\n');
        //lcd gui
        goToRowColumn(2,1);
        EKE_LCD_string(dataEEP);
        break;
    }
 }//end of for loop
}//end of searching loop


//LCD GUI
goToRowColumn(1,1);
EKE_LCD_string((U8_t*)"I-Cart    ");
goToRowColumn(1,12);
//EKE_LCD_DRAW(1,pattern);
lcdUpdateTime(h,m,s);
getTime(&h,&m,&s);


}

	return 0;
}

