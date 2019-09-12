#ifndef _CONFIG_H_
#define _CONFIG_H_

#define configSYS_CLOCK   (168000000U)
#define configHZ          (1000U)

//#define configUSE_PLL
//#define configUSE_HOSE
#define configTOTAL_HEAP_SIZE   (4*1024)

#define configUSING_I2C

#define configUSING_INA219

#define configUSING_SHELL

#define configUSING_SERIAL


#endif
