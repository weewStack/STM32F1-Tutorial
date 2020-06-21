/*
Actual setup

SPI - 1
--> 
PA4 --> SS
PA5 --> SCLK
PA6 --> MISO
PA7 --> MOSI

SP2 - 2

PB12 --> SS
PB13 --> SCLK
PB14 --> MISO
PB15 --> MOSI

*/



void spi_init(unsigned short spi);
void spi_tx(unsigned short spi, char tx_char);
void spi_msg(unsigned short spi, char str[]);
void spi_cs(unsigned short spi, unsigned short LOW_HIGH);
char spi_rx(unsigned short spi, char value);
