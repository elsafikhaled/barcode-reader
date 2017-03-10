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

int main(void){
/*Data types for application*/
U8_t barcodeNew=13;
U8_t barcodeOld=0;
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
/* LCD Main GUI */
goToRowColumn(1,1);
EKE_LCD_string((U8_t*)"   I-Cart      ");
goToRowColumn(2,1);
EKE_LCD_string((U8_t*)"waiting.......");

while(1){

if(system.flag==1){
//get new data from barcode
barcodeOld=barcodeNew;
barcodeNew=TbUart_get_char();
barcodeNew=barcodeNew-'0';

system.flag=0;
  }
//clear lcd
EKE_clear_lcd();
 for(eeprom_address=0;eeprom_address<=57;eeprom_address++){
    reading=EEPROM_Read(eeprom_address,1);
    if(reading==barcodeNew){
        EEPROM_READ_STRING((eeprom_address+1),1,dataEEP);
        while(1){
        //buzzer firing
        PORTD|=(1<<PD5);
        _delay_ms(50);
        PORTD&=~(1<<PD5);
        //TB GUI
        TbUart_Send_stri((U8_t*)dataEEP);
        TbUart_Send_char('\n');
        //LCD GUI
        goToRowColumn(1,1);
        EKE_LCD_string((U8_t*)"I-Cart Bill");
        goToRowColumn(2,1);
        EKE_LCD_string(dataEEP);
        //get new data from barcode
        barcodeOld=barcodeNew;
        // barcodeNew=TB_getchar_notWait(barcodeNew);
        barcodeNew=TbUart_get_char();
        barcodeNew=barcodeNew-'0';
        if(barcodeNew!=barcodeOld){
        eeprom_address=255;
        break;
 		        }//if
                }break;//while(1)
        	  }
          }

		}

	return 0;
}

