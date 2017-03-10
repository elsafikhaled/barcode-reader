/*
 * EEPROM.h
 *
 *  Created on: ٢٨‏/٠١‏/٢٠١٧
 *      Author: El-safi
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include "EKE_I2C.h"

enum CONFIG{
	ID_ADD_READ=0xA0|1,
	ID_ADD_WRITE=0xA0
};


void EEPROM_init(void);

U8_t EEPROM_Read(U8_t Addresse,U8_t Ackn);

void EEPROM_Write(U8_t Addresse,U8_t WORDS);

void EEPROM_WRITE_STRING(U8_t addresse,U8_t * str);

void EEPROM_READ_STRING(U8_t addresse,U8_t ack,U8_t*data);
void EF_void_EEPROM_Erase(void);


#endif /* EEPROM_H_ */
