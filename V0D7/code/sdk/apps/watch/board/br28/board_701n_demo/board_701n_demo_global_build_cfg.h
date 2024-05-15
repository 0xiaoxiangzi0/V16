#ifndef CONFIG_BOARD_701N_DEMO_POST_BUILD_CFG_H
#define CONFIG_BOARD_701N_DEMO_POST_BUILD_CFG_H

/* 改文件只添加和isd_config.ini相关的配置，用以生成isd_config.ini */
/* 其他不相关的配置请勿添加在改文件 */

#ifdef CONFIG_BOARD_701N_DEMO

/* Following Macros Affect Periods Of Both Code Compiling And Post-build */

#define CONFIG_DOUBLE_BANK_ENABLE               0       //单双备份选择(若打�?了改�?,FLASH结构变为双备份结构，适用于接入第三方协议的OTA�? PS: JL-OTA同样支持双备份升�?, �?要根据实际FLASH大小同时配置CONFIG_FLASH_SIZE)
#define CONFIG_APP_OTA_ENABLE                   0       //是否支持RCSP升级(JL-OTA)

#define CONFIG_UPDATE_JUMP_TO_MASK              0   	//配置升级到loader的方�?0为直接reset,1为跳�?(适用于芯片电源由IO口KEEP住的方案,�?要注意检查跳转前是否将使用DMA的硬件模块全部关�?)

#define CONFIG_LP_TOUCH_KEY_EN					0		//配置是否使用内置触摸
#define CONFIG_UPDATE_WITH_MD5_CHECK_EN			0 		//配置升级是否支持MD5校验

#define CONFIG_ANC_ENABLE           			0		//配置是否支持ANC

#define CONFIG_DEBUG_RECORD_ENABLE              0       //是否支持将异常信息记录到Flash功能

//flash size vaule definition
#define FLASH_SIZE_256K							0x40000
#define FLASH_SIZE_512K							0x80000
#define FLASH_SIZE_1M							0x100000
#define FLASH_SIZE_2M							0x200000
#define FLASH_SIZE_4M							0x400000
#define FLASH_SIZE_8M							0x800000
#define FLASH_SIZE_16M							0x1000000
#define FLASH_SIZE_32M							0x2000000

#define CONFIG_FLASH_SIZE                       FLASH_SIZE_2M    //配置FLASH大小

#define CONFIG_EXTERN_FLASH_SIZE                FLASH_SIZE_8M    //配置外挂FLASH大小
/*
 * 配置外挂FLASH VM大小
 * download.bat中的配置�?要和该配置对应上�?
 * 例如flash 16M，VM 128K，那么fat空间�?16*1024*1024 - 128*1024 = 0xfe0000�?
 * download.bat配置为：fat_comm.exe ...... -mark-bad-after 0xfe0000 ......
 */
#define CONFIG_EXTERN_USER_VM_FLASH_SIZE        (128*1024)

#define CONFIG_SPI_DATA_WIDTH                   4                //data_width[0 1 2 3 4] 3的时候uboot自动识别2或�??4�?
#define CONFIG_SPI_CLK_DIV                      3                //clk [0-255]
#define CONFIG_SPI_MODE                         0
#define CONFIG_SPI_PORT                         0

/* Above Macros Affect Periods Of Both Code Compiling And Post-build */

/* Following Macros Only For Post Bulid Configuaration */

#define CONFIG_DB_UPDATE_DATA_GENERATE_EN       0       //是否生成db_data.bin(用于第三方协议接入使�?)
#define CONFIG_ONLY_GRENERATE_ALIGN_4K_CODE     0    	//ufw只生�?1�?4K对齐的代�?

//config for supported chip version
#define CONFIG_SUPPORTED_CHIP_VERSION			A,B,D,M,N,O,P

//DON'T MODIFY THIS CONFIG EXCEPT SDK PUBLISHER
#define CONFIG_CHIP_NAME                        JL701N              //除了SDK发布�?,请不要修�?
//it can be modified before first programming,but keep the same as the original version
#define CONFIG_PID                              JL701N              //烧写或强制升级之前可以修�?,之后升级要保持一�?
//it can be modified before first programming,but keep the same as the original version
#define CONFIG_VID                              0.01				//烧写或强制升级之前可以修�?,之后升级要保持一�?

//Project with bluetooth,it must use OSC as PLL_SOURCE;
#define CONFIG_PLL_SOURCE_USING_LRC             0       			//PLL时钟源�?�择 1:LRC 2:OSC

//config alignment size unit
#ifdef CONFIG_256K_FLASH
#define ALIGN_UNIT_256B             1                 				//FLASH对齐方式选择，如果是256K的FLASH，�?�择256BYTE对齐方式
#else
#define ALIGN_UNIT_256B             0
#endif

//partial platform check this config to select the uart IO for wired update
#define CONFIG_UART_UPDATE_PIN                  PB05

//isd_download loader/uboot/update_loader debug io config
//#define CONFIG_UBOOT_DEBUG_PIN                  PA05
//#define CONFIG_UBOOT_DEBUG_BAUD_RATE            1000000

//config long-press reset io pin,time,trigger level
// #if CONFIG_LP_TOUCH_KEY_EN
// #define CONFIG_RESET_PIN                        LDO  //io pin
// #define CONFIG_RESET_TIME                       04   //unit:second
// #define CONFIG_RESET_LEVEL                      1	 //tigger level(0/1)
// #else
// #define CONFIG_RESET_PIN                        PB01 //io pin
// #define CONFIG_RESET_TIME                       08   //unit:second
// #define CONFIG_RESET_LEVEL                      0	 //tigger level(0/1)
// #endif

//reserved three custom cfg item for the future definition
//#define CONFIG_CUSTOM_CFG1_TYPE			POWER_PIN
//#define CONFIG_CUSTOM_CFG1_VALUE		 	PC01_1

//#define CONFIG_CUSTOM_CFG2_TYPE
//#define CONFIG_CUSTOM_CFG2_VALUE

//#define CONFIG_CUSTOM_CFG3_TYPE
//#define CONFIG_CUSTOM_CFG3_VALUE


//#define CONFIG_VDDIO_LVD_LEVEL                  4 ////VDDIO_LVD挡位�?0: 1.9V   1: 2.0V   2: 2.1V   3: 2.2V   4: 2.3V   5: 2.4V   6: 2.5V   7: 2.6V

//with single-bank mode,actual vm size should larger this VM_LEAST_SIZE,and dual bank mode,actual vm size equals this;
#define CONFIG_VM_LEAST_SIZE                    100K
//config whether erased this area when do a update,1-No Operation,0-Erase
#define CONFIG_VM_OPT							1

//config whether erased this area when do a update,1-No Operation,0-Erase
#define CONFIG_BTIF_OPT							1

//reserved two custom cfg area for the future definition
//#define CONFIG_RESERVED_AREA1					EXIF1
#ifdef CONFIG_RESERVED_AREA1
#define CONFIG_RESERVED_AREA1_ADDR				AUTO
#define CONFIG_RESERVED_AREA1_LEN				0x1000
#define CONFIG_RESERVED_AREA1_OPT				1
//#define CONFIG_RESERVED_AREA1_FILE				anc_gains.bin
#endif

//#define CONFIG_RESERVED_AREA2					EXIF2
#ifdef CONFIG_RESERVED_AREA2
#define CONFIG_RESERVED_AREA2_ADDR				AUTO
#define CONFIG_RESERVED_AREA2_LEN				0x1000
#define CONFIG_RESERVED_AREA2_OPT				1
//#define CONFIG_RESERVED_AREA2_FILE				anc_gains.bin
#endif

#if	(defined CONFIG_DEBUG_RECORD_ENABLE && CONFIG_DEBUG_RECORD_ENABLE)
#define CONFIG_DEBUG_ADDR						AUTO
#define CONFIG_DEBUG_LEN						0x1000
#define CONFIG_DEBUG_OPT						0 //0: 擦除, 1:不操�?
#endif /* #if (define CONFIG_DEBUG_RECORD_ENABLE && CONFIG_DEBUG_RECORD_ENABLE) */

/* Above Macros Only For Post Bulid Configuaration */
#endif

#endif

