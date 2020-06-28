#include "stm32f10x.h" 
#include "gp_drive.h" 
#include "systick_time.h"
#include "SPI_drive.h"

enum nrf_reg
{
	//command registers
	nrf_read = 0x1f,
	nrf_write = 0x20,
	
	R_RX_PAYLOAD = 0x61,
	
	
	FLUSH_TX = 0xE1,
	FLUSH_RX = 0xE2,
	
	R_RX_PL_WID = 0x60,
	W_TX_PAYLOAD = 0xA0,
	
	// Address registers
	NRF_CONFIG = 0x00,
	NRF_EN_AA = 0x01,
  NRF_RXADDR = 0x02,
  NRF_SETUP_AW = 0x03,
	NRF_SETUP_RETR = 0x04,
	NRF_RF_CH = 0x05,
	NRF_SETUP = 0x06,
	NRF_STATUS = 0x07,
	NRF_OBSERVE_TX = 0x08,
	NRF_RPD = 0x09,
	
	NRF_ADDR_P0 = 0x0A,
	NRF_ADDR_P1 = 0x0B,
	NRF_ADDR_P2 = 0x0C,
	NRF_ADDR_P3 = 0x0D,
	NRF_ADDR_P4 = 0x0E,
	NRF_ADDR_P5 = 0x0F,
	
	NRF_TX_ADDR = 0x10,
	NRF_RX_PW_P0 = 0x11,
	NRF_RX_PW_P1 = 0x12,
	NRF_RX_PW_P2 = 0x13,
	NRF_RX_PW_P3 = 0x14,
	NRF_RX_PW_P4 = 0x15,
	NRF_RX_PW_P5 = 0x16,
	
	NRF_FIFO_STATUS = 0x17,
	NRF_DYNPD = 0x1C,
	NRF_FEATURE = 0x1D,
	
	// Setup regiesters
	POWER_UP = 0x02,
	POWER_DOWN = 0x00,
	POWER_MASK = 0xfd,
	
	PRIM_RX = 1,
	PRIM_TX = 0,
	PRIM_RX_MASK = 0xFE,
	
	
	/****New Reges**/
	EN_DPL = 0x4,
	EN_DPL_MASK = 0xFB,
	
	EN_DPL_P0 = 1,
	EN_DPL_P0_MASK = 0xFE,
	
	RX_DR_SET = 0x40,
	RX_DR_MASK = 0xBF,
	
	MAX_RT_SET = 0x10,
	MAX_RT_MASK = 0xEF,
	
	TX_DS_SET = 0x20,
	TX_DS_MSAK = 0xDF,
	
	ADR_4000 = 0xF0,
	ADR_MASK = 0x0F,
	
	
	RF_PWR_18db = 0x00,
	RF_PWR_MASK = 0xF9,
	
	RF_DR_LOW = 0x20,
	RF_DR_MASK = 0xD7,
	
	ARD_750us = 0x20,
	ARD_MASK = 0x0F,
};


void nrf_init(unsigned short spi);
char nrf_cmd(unsigned short spi, char cmd);
char nrf_cmd_rd(unsigned short spi, char register_add);
char nrf_cmd_wr(unsigned short spi, char register_add, char new_value,char mask);
void nrf_prx_init(unsigned short spi);
void nrf_rf_rx(unsigned short spi,char payload[]);
void nrf_ptx_init(unsigned short spi);
void nrf_rf_tx(unsigned short spi,char payload[]);


