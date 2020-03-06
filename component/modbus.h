//################################################################################
//# Copyright Statement: CVTE
//# Copyright (C) 2014 Guangzhou Shiyuan Electronics Co.,Ltd. All rights reserved.
//#      ____________        _______________  ___________
//#     / / ________ \      / / _____   ____|| |  _______|
//#    / / /      \ \ \    / / /   | | |     | | |
//#   | | |        \ \ \  / / /    | | |     | | |_______
//#   | | |         \ \ \/ / /     | | |     | |  _______|
//#   | | |          \ \ \/ /      | | |     | | |
//#    \ \ \______    \ \  /       | | |     | | |_______
//#     \_\_______|    \_\/        |_|_|     |_|_________|
//#
//################################################################################

/**
 ******************************************************************************
 * @file    demo.h
 * @author  chenzhipeng3472
 * @version V1.0.0
 * @date    10-sep-2018
 * @brief   
 ******************************************************************************
 * @attention
 * 
 ******************************************************************************
 */
    
/** @addtogroup Project
  * @{
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MODBUS_H__
#define __MODBUS_H__

/***********************************************
                    include
***********************************************/
#include <stdint.h>
#include <stdbool.h>
#include <core/device.h>
#include "core/croutine.h"
#include "component/state_machine.h"

/***********************************************
                    define
***********************************************/
#ifdef configUSING_MODBUS

#define	MODBUS_RTU_BUFF_LEN				0x7F
#define MAX_SLAVE_ADDR					0xFF
#define	MAX_HOLDRES						64

#define READ_HOLD_RES					0x03
#define WRITE_MULTI_HOLD_RES			0x10
#define WRITE_SINGLE_HOLD_RES			0x06
#define READ_INPUT_RES					0x04

#define	 MODBUS_RX_MAX					64
#define	 MODBUS_TX_MAX					512

/***********************************************
                    typedef
***********************************************/
//struct modbus_msg
//{
	//uint16_t slave_addr;
	//uint16_t opcode;
	//uint16_t start_addr;
	//uint16_t reg_cnt;
	//uint16_t  *buf;
//};

#pragma pack(1)
typedef struct ModbusFrame
{
	uint8_t slave_addr;
	uint8_t opcode;
	union {
		uint16_t reg_addr;
		uint16_t start_addr;
	};
	union {
		uint16_t reg_cnt;
		uint16_t reg_val;
	};
	uint16_t data[1];
} modbus_frame_t;

typedef struct ModbusRxFrame
{
	uint8_t slave_addr;
	uint8_t opcode;
    uint8_t reg_cnt;
	uint16_t data[1];
} modbus_rx_frame_t;
#define MODBUS_FRAME_HEAD (offset_of(modbus_frame_t, data))

typedef struct SmartFrame
{
	uint8_t stc;
	rx_indicate rx_ind;
	tx_complete tx_done;
    list_t 	entry;
	uint8_t len;
	uint8_t data[1];
} smart_frame_t;
#define SMART_FRAME_HEAD (offset_of(smart_frame_t, data))

#pragma pack()

typedef struct modbus_device
{
	device_t parent;
	uint16_t slave_addr;
	uint8_t rx_data[MODBUS_RX_MAX];
//	uint8_t tx_data[MODBUS_TX_MAX];
//    DECLARE_KFIFO(rx_kfifo, unsigned char, MODBUS_RX_MAX);
//    DECLARE_KFIFO(tx_kfifo, unsigned char, MODBUS_TX_MAX);
    list_t 	tx_list;
    state_machine_t sm;
}modbus_t;

/***********************************************
               function prototypes
***********************************************/
int readInputReg2(modbus_t *modbus, uint16_t slave_addr, uint16_t start_addr, uint16_t reg_cnt);
int writeMultiHoldReg2(modbus_t *modbus, uint16_t slave_addr, uint16_t reg_addr, uint16_t reg_cnt, uint16_t *data);
int writeSingleHoldReg2(modbus_t *modbus, uint16_t slave_addr, uint16_t reg_addr, uint16_t reg_val);
//int readHoldReg2(modbus_t *modbus, uint16_t slave_addr, uint16_t reg_addr, uint16_t reg_cnt);
int readHoldReg2(modbus_t *modbus, uint16_t slave_addr, uint16_t start_addr, uint16_t reg_cnt, rx_indicate rx_ind);

/***********************************************
					inline
***********************************************/

/***********************************************
                   variable
***********************************************/

#endif
/**
  * @}
  */

#endif  /* __MODBUS_H__ */

/*************** (C) COPYRIGHT Guangzhou Shiyuan Electronics Co.,Ltd *******END OF FILE******/



