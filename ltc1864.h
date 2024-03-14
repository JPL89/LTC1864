// @File		LTC1864.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		14/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef LTC1864_H
#define LTC1864_H

#define LTC1864_CLK PORTCbits.RC0
#define LTC1864_DIN PORTCbits.RC1
#define LTC1864_DOUT PORTCbits.RC2
#define LTC1864_CS PORTCbits.RC3

#define LTC1864_CLK_TRIS TRISCbits.RC0
#define LTC1864_DIN_TRIS TRISCbits.RC1
#define LTC1864_DOUT_TRIS TRISCbits.RC2
#define LTC1864_CS_TRIS TRISCbits.RC3

unsigned int LTC1864_read(void)
{
    unsigned int data = 0;
    
    LTC1864_CS = 0;
    
    for(unsigned int mask = 0x2000; mask; mask >>= 1)
    {
        data <<= 1;
        if(LTC1864_DOUT) data |= 1; 
            
         __asm__ __volatile__("nop");
         LTC1864_CLK = 1;
         __asm__ __volatile__("nop");
         LTC1864_CLK = 0;
         __asm__ __volatile__("nop");    
    }
    
    LTC1864_CS = 1;
    
    return ((unsigned int)data);
}

void LTC1864_Init(void)
{
    LTC1864_CLK_TRIS = 0;
    LTC1864_DIN_TRIS = 0;
    LTC1864_DOUT_TRIS = 1;
    LTC1864_CS_TRIS = 0;
    
    LTC1864_CS = 1;
}

#endif 
