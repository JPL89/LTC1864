// @File		AD5621.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		13/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef AD5621_H
#define AD5621_H

#define AD5621_CLK PORTCbits.RC0
#define AD5621_DIN PORTCbits.RC1
#define AD5621_DOUT PORTCbits.RC2
#define AD5621_CS PORTCbits.RC3

#define AD5621_CLK_TRIS TRISCbits.RC0
#define AD5621_DIN_TRIS TRISCbits.RC1
#define AD5621_DOUT_TRIS TRISCbits.RC2
#define AD5621_CS_TRIS TRISCbits.RC3

#define AD5621_NORMAL 0x00
#define AD5621_1K 0x01
#define AD5621_100K 0x02
#define AD5621_THREE_STATE 0x03

static const void SPI_transfer(unsigned int data)
{     
    for(unsigned int mask = 0x8000; mask; mask >>= 1)
    {
        if(data & mask) AD5621_DIN = 1; else AD5621_DIN = 0;
            
         __asm__ __volatile__("nop");
         AD5621_CLK = 1;
         __asm__ __volatile__("nop");
         AD5621_CLK = 0;
         __asm__ __volatile__("nop");    
    }
}

void AD5621_Write(unsigned char mode, unsigned int value)
{
    unsigned int data = 0;
    
    data |= (mode << 14);
    data |= (value << 2);
    
    AD5621_CS = 0;
    SPI_transfer(data);
    AD5621_CS = 1;   
}

void AD5621_Init(void)
{
    AD5621_CLK_TRIS = 0;
    AD5621_DIN_TRIS = 0;
    AD5621_DOUT_TRIS = 1;
    AD5621_CS_TRIS = 0;
    
    AD5621_CS = 1;
}

#endif 