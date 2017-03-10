/*
 * EEPROM.c
 *
 *  Created on: ٢٨‏/٠١‏/٢٠١٧
 *      Author: El-safi
 */
#include "EEPROM.h"

void EEPROM_init(void){

  EKE_I2C_init(0x47,0,0x01);

}

void EEPROM_Write(U8_t Addresse,U8_t WORDS){

 EKE_I2C_start();
 EKE_I2C_write(ID_ADD_WRITE);  // ID_ADD_WRITE
 EKE_I2C_write(Addresse);
 EKE_I2C_write(WORDS);
 EKE_I2C_stop();
 _delay_ms(15);
}

U8_t EEPROM_Read(U8_t Addresse,U8_t Ackn){
U8_t DATA=0;
//configure the eeprom and move eeprom pointer to  the addresse which I need to read from it
    EKE_I2C_start();
    EKE_I2C_write(ID_ADD_WRITE);
    EKE_I2C_write(Addresse);
// READ from the addresse which i point to it from last step
    EKE_I2C_start();
    EKE_I2C_write(0xA0|1);
    DATA=EKE_I2C_read(Ackn);
    EKE_I2C_stop();

	return DATA;
}


void EEPROM_WRITE_STRING(U8_t addresse,U8_t * str){

  while(*str!='\0'){

	  EEPROM_Write(addresse,(U8_t)*str);
	  addresse++;
	  str++;
  }
  EEPROM_Write(addresse,(U8_t)'\0');
}
void EEPROM_READ_STRING(U8_t addresse,U8_t ack,U8_t data[]){
U8_t x=0;

	data[x]=EEPROM_Read(addresse,ack);
	while(data[x]!='\0'){
		x++;
		addresse++;
		data[x]=EEPROM_Read(addresse,ack);


	}
	data[x]=EEPROM_Read(addresse,0);
	data[x]=(U8_t)'\0';

}
/*
void EEPROM_READ_STRING(U8_t addresse,U8_t ack,U8_t*data){

	*data=EEPROM_Read(addresse,ack);
	while(*data!='\0'){
		data++;
		addresse++;
		*data=EEPROM_Read(addresse,ack);


	}
	*data=EEPROM_Read(addresse,0);
	*data=(U8_t)'\0';

}
*/
void EF_void_EEPROM_Erase(void)
{
	U16_t eeprom_address;
	for(eeprom_address=0; eeprom_address <1024 ; eeprom_address++)
	{
	  EEPROM_Write(eeprom_address,0x00);     /* Write Each memory location with OxFF */
	}
}

