# ADAU1452_DSP
Chinese low cost eval board

## Description
![ADAU1452_DSP](https://raw.githubusercontent.com/tecteun/ADAU1452_DSP/master/board.jpg "Logo ADAU1452_DSP")


## EEPROM ID
    А в ДШ заглянуть?

    ATML=ATMEL
    H= Industrial/NiPdAu fymish
    5= 2015 год
    46 = 46я неделя
    2EC=AT24C256C
    L= 1.7V min

### SigmaStudio EEPROM properties

I2C

    Memory size: 262144bits
    Page size: 64bytes
    Write speed: 1000Khz (or lower)
    Number of Adress Bytes: 2

## Persist firmware with SigmaStudio

The jumper in the picture is set to write protect.
Switch it to the other position while writing the firmware in Sigmastudio with

	'Self-boot memory -> Write latest Compilation through DSP'