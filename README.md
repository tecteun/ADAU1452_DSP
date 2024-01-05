# ADAU1452_DSP
Chinese low cost eval board
Supposedly based on 

https://github.com/ohdsp/DSP-ADAU1452/blob/master/Drawings/Schematic/DSP-ADAU1452-2.0-Schematic.pdf
(https://www.diyaudio.com/forums/digital-line-level/309680-low-cost-adau1452-china-board-2.html)

## Description

### rev 1
![ADAU1452_DSP](https://raw.githubusercontent.com/tecteun/ADAU1452_DSP/master/board.jpg "Logo ADAU1452_DSP")

### rev 2 (Lusya)
![ADAU1452_DSP](https://raw.githubusercontent.com/tecteun/ADAU1452_DSP/master/board2.jpg "Logo ADAU1452_DSP")


## EEPROM ID
    А в ДШ заглянуть?

    ATML=ATMEL
    H= Industrial/NiPdAu fymish
    5= 2015 год
    46 = 46я неделя
    2EC=AT24C256C
    L= 1.7V min

The EEPROM used differs between versions, it can bet I2C or SPI flash, so just check the actual chips datasheet for the below settings.

### SigmaStudio EEPROM properties

I2C

    Memory size: 262144bits
    Page size: 64bytes
    Write speed: 1000Khz (or lower)
    Number of Adress Bytes: 2

#### For Lusya/Nvarcher V2 board (has spi flash)

SPI
	
	Memory size: 1048576bits
    Page size: 256bytes
    Write speed: 10000Khz 
    Number of Adress Bytes: 3

## Persist firmware with SigmaStudio

The jumper in the picture is set to write protect.
Switch it to the other position while writing the firmware in Sigmastudio with

	'Self-boot memory -> Write latest Compilation through DSP'



## Todo

    Figure out how to use the unpopulated SRAM spot
    with 23A1024 or similar
    https://docs.rs-online.com/5f59/0900766b8114ca33.pdf
    First tests show that this board is designed to use the ADAU1452 master SPI bus with either:
    - `EEPROM`
    - `SRAM`
    not both together. (`SS_M/MP0` does not have any select logic behind it)

## Links

### Sigma-tcp with SPI

https://github.com/Ark-Linux/sigma-tcp

### Other

- https://github.com/aventuri/sigma_tcp
- https://github.com/MCUdude/SigmaDSP
- https://ez.analog.com/dsp/sigmadsp/f/q-a/164008/sharing-tcpi-interface-for-sigma-studio-using-esp8266-or-esp32
- https://www.diyaudio.com/community/threads/low-cost-adau1452-china-board.309680/page-17
