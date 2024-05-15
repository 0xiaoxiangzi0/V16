/*
** 包含board的头文件，确定baord里面开关的屏驱宏
*/
#include "app_config.h"
#include "clock_cfg.h"
#include "asm/psram_api.h"


/*
** 驱动代码的宏开关
*/
//<<<[qspi屏 240*296]>>>//
#if TCFG_LCD_SPI_NV3030B_ENABLE

// #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE0_1T8B
// #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE1_1T2B
#define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE2_1T2B

/*
** 包含imd头文件，屏驱相关的变量和结构体都定义在imd.h
*/
#include "asm/imd.h"
#include "asm/imb.h"
#include "includes.h"
#include "ui/ui_api.h"


#if 1
#define SCR_X 0
#define SCR_Y 0
#define SCR_W 240
#define SCR_H 296
#define LCD_W 240
#define LCD_H 296
#define LCD_BLOCK_W 240
#define LCD_BLOCK_H 40
#define BUF_NUM 2
#else
#define SCR_X 0
#define SCR_Y 0
#define SCR_W 240
#define SCR_H 296
#define LCD_W 240
#define LCD_H 296
#define LCD_BLOCK_W 240
#define LCD_BLOCK_H 60
#define BUF_NUM 2
#endif



#if (TCFG_PSRAM_DEV_ENABLE)
#define LCD_FORMAT OUTPUT_FORMAT_RGB565
#else
#define LCD_FORMAT OUTPUT_FORMAT_RGB565
#endif




/*
** 初始化代码
*/
static const u8 lcd_spi_nv3030b_cmd_list_poweron[] ALIGNED(4) = {
    _BEGIN_, 0xfd, 0x06, 0x08, _END_,
    _BEGIN_, 0x61, 0x07, 0x07, _END_,
    _BEGIN_, 0x73, 0x70, _END_,
    _BEGIN_, 0x73, 0x00, _END_,
    _BEGIN_, 0x62, 0x00, 0x44, 0x40, _END_,
    _BEGIN_, 0x63, 0x41, 0x07, 0x12, 0x12, _END_,
    _BEGIN_, 0x65, 0x09, 0x17, 0x21, _END_,
    _BEGIN_, 0x66, 0x09, 0x17, 0x21, _END_,
    _BEGIN_, 0x67, 0x20, 0x40,_END_,
    _BEGIN_, 0x68, 0x90, 0x30, 0x1c, 0x27, _END_,
    _BEGIN_, 0xb1, 0x0F, 0x02, 0x01, _END_,
    _BEGIN_, 0xb4, 0x01, _END_,
    _BEGIN_, 0xb5, 0x02, 0x02, 0x0a, 0x14, _END_,
    _BEGIN_, 0xb6, 0x44, 0x01, 0x9f, 0x00, 0x02, _END_,
    _BEGIN_, 0xdf, 0x11, _END_,
    _BEGIN_, 0xe2, 0x0d, 0x0f, 0x11, 0x33, 0x36, 0x3f, _END_,
    _BEGIN_, 0xe5, 0x3f, 0x37, 0x33, 0x12, 0x10, 0x04, _END_,
    _BEGIN_, 0xe1, 0x2c, 0x74, _END_,
    _BEGIN_, 0xe4, 0x74, 0x2b, _END_,
    _BEGIN_, 0xe0, 0x08, 0x07, 0x0D, 0x13, 0x11, 0x13, 0x0e, 0x14, _END_,
    _BEGIN_, 0xe3, 0x17, 0x0f, 0x14, 0x11, 0x13, 0x0c, 0x06, 0x04, _END_,
    _BEGIN_, 0xe6, 0x00, 0xff, _END_,
    _BEGIN_, 0xe7, 0x01, 0x04, 0x03, 0x03, 0x00, 0x12, _END_,
    _BEGIN_, 0xe8, 0x00, 0x70, 0x00, _END_,
    _BEGIN_, 0xec, 0x52, _END_,
    _BEGIN_, 0xf1, 0x01, 0x01, 0x02, _END_,
    _BEGIN_, 0xf6, 0x01, 0x30, 0x00, 0x00, _END_,
    _BEGIN_, 0xfd, 0xfa, 0xfc, _END_,
    _BEGIN_, 0x3a, 0x55, _END_,
    _BEGIN_, 0x35, 0x00, _END_,
    _BEGIN_, 0x36, 0x00, _END_,
    _BEGIN_, 0x11, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
    _BEGIN_, 0x29, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
    _BEGIN_, 0x2c, 0x00, 0x00, 0x00, 0x00, _END_,
    _BEGIN_, 0x2c, 0x00, 0x00, 0x00, 0x00, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
};


static const u8 lcd_cmd_list_sleepout[] ALIGNED(4) = {
    _BEGIN_, 0xfd, 0x06, 0x08, _END_,
    _BEGIN_, 0x61, 0x07, 0x07, _END_,
    _BEGIN_, 0x73, 0x70, _END_,
    _BEGIN_, 0x73, 0x00, _END_,
    _BEGIN_, 0x62, 0x00, 0x44, 0x40, _END_,
    _BEGIN_, 0x63, 0x41, 0x07, 0x12, 0x12, _END_,
    _BEGIN_, 0x65, 0x09, 0x17, 0x21, _END_,
    _BEGIN_, 0x66, 0x09, 0x17, 0x21, _END_,
    _BEGIN_, 0x67, 0x20, 0x40,_END_,
    _BEGIN_, 0x68, 0x90, 0x30, 0x1c, 0x27, _END_,
    _BEGIN_, 0xb1, 0x0F, 0x02, 0x01, _END_,
    _BEGIN_, 0xb4, 0x01, _END_,
    _BEGIN_, 0xb5, 0x02, 0x02, 0x0a, 0x14, _END_,
    _BEGIN_, 0xb6, 0x44, 0x01, 0x9f, 0x00, 0x02, _END_,
    _BEGIN_, 0xdf, 0x11, _END_,
    _BEGIN_, 0xe2, 0x0d, 0x0f, 0x11, 0x33, 0x36, 0x3f, _END_,
    _BEGIN_, 0xe5, 0x3f, 0x37, 0x33, 0x12, 0x10, 0x04, _END_,
    _BEGIN_, 0xe1, 0x2c, 0x74, _END_,
    _BEGIN_, 0xe4, 0x74, 0x2b, _END_,
    _BEGIN_, 0xe0, 0x08, 0x07, 0x0D, 0x13, 0x11, 0x13, 0x0e, 0x14, _END_,
    _BEGIN_, 0xe3, 0x17, 0x0f, 0x14, 0x11, 0x13, 0x0c, 0x06, 0x04, _END_,
    _BEGIN_, 0xe6, 0x00, 0xff, _END_,
    _BEGIN_, 0xe7, 0x01, 0x04, 0x03, 0x03, 0x00, 0x12, _END_,
    _BEGIN_, 0xe8, 0x00, 0x70, 0x00, _END_,
    _BEGIN_, 0xec, 0x52, _END_,
    _BEGIN_, 0xf1, 0x01, 0x01, 0x02, _END_,
    _BEGIN_, 0xf6, 0x01, 0x30, 0x00, 0x00, _END_,
    _BEGIN_, 0xfd, 0xfa, 0xfc, _END_,
    _BEGIN_, 0x3a, 0x55, _END_,
    _BEGIN_, 0x35, 0x00, _END_,
    _BEGIN_, 0x36, 0x00, _END_,
    _BEGIN_, 0x11, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
    _BEGIN_, 0x29, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
    _BEGIN_, 0x2c, 0x00, 0x00, 0x00, 0x00, _END_,
    _BEGIN_, 0x2c, 0x00, 0x00, 0x00, 0x00, _END_,
    _BEGIN_, REGFLAG_DELAY, 120, _END_,
};

extern struct lcd_spi_platform_data *lcd_get_platform_data();

static void lcd_send_cmd_enable()
{
    u8 para[2];
    para[0] = 0x5a;
    para[1] = 0x5a;
    lcd_write_cmd(0xc0, para, 2);
    lcd_write_cmd(0xc1, para, 2);
}

static void lcd_send_cmd_disable()
{
    u8 para[2];
    para[0] = 0xa5;
    para[1] = 0xa5;
    lcd_write_cmd(0xc0, para, 2);
    lcd_write_cmd(0xc1, para, 2);
}

static void lcd_adjust_display_brightness(u8 percent)
{
    u16 brightness;
    u8 para[2];

    brightness = percent * 0x3ff / 100;

    para[0] = brightness & 0xff;
    para[1] = (brightness >> 8) & 0x3;

    lcd_write_cmd(0x51, para, 2);
    /* lcd_write_cmd(0x4a, para, 2); //Brightness Value of AOD Mode, 无效果 */
    /* lcd_write_cmd(0x63, para, 2); //Brightness Value of HBM Mode, 无效果 */
}

/*
** lcd背光控制
** 考虑到手表应用lcd背光控制需要更灵活自由，可能需要pwm调光，随时亮灭等
** 因此内部不操作lcd背光，全部由外部自行控制
*/
static int lcd_spi_nv3030b_backlight_ctrl(u8 percent)
{
    if (percent) {
        lcd_write_cmd(0x29, NULL, 0);
        if (percent <= 20) {
            lcd_adjust_display_brightness(1);
        } else if (percent <= 40) {
            lcd_adjust_display_brightness(3);
        } else if (percent <= 60) {
            lcd_adjust_display_brightness(6);
        } else if (percent <= 80) {
            lcd_adjust_display_brightness(10);
        } else if (percent <= 100) {
            lcd_adjust_display_brightness(100);
        }
        g_printf("lcd backlight percent:%d",percent);
    } else {
        lcd_write_cmd(0x28, NULL, 0);
    }

    return 0;
}


/*
** lcd电源控制
*/
static int lcd_spi_nv3030b_power_ctrl(u8 onoff)
{
    lcd_en_ctrl(onoff);
    return 0;
}


#define DEEP_STANDBY  1

/*
** 设置lcd进入睡眠
*/
static void lcd_spi_nv3030b_entersleep(void)
{
    u8 dstb = 0x01;

    lcd_write_cmd(0x28, NULL, 0);
    lcd_write_cmd(0x10, NULL, 0);
    delay_2ms(120 / 2);	// delay 120ms
#if DEEP_STANDBY
    lcd_write_cmd(0x4f, &dstb, sizeof(dstb));
    delay_2ms(102 / 2);	// delay 120ms
    struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
    if (lcd_dat->pin_te != NO_CONFIG_PORT) {
        gpio_set_pull_up(lcd_dat->pin_te, 0);
        gpio_set_pull_down(lcd_dat->pin_te, 0);
        gpio_direction_input(lcd_dat->pin_te);
        gpio_set_die(lcd_dat->pin_te, 0);
    }
#endif

}



/*
** 设置lcd退出睡眠
*/
static void lcd_spi_nv3030b_exitsleep(void)
{
#if DEEP_STANDBY
    struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
    if (lcd_dat && lcd_dat->pin_reset) {
        gpio_direction_output(lcd_dat->pin_reset, 0);
        delay_2ms(4);	// delay >5ms
        gpio_direction_output(lcd_dat->pin_reset, 1);
        delay_2ms(4);	// delay >5ms
    }

    lcd_write_cmd(0x11, NULL, 0);
    delay_2ms(5);
    lcd_write_cmd(0x29, NULL, 0);
    delay_2ms(5);

    extern struct imd_param lcd_spi_nv3030b_param;
    lcd_init(&lcd_spi_nv3030b_param);
    lcd_drv_cmd_list(lcd_cmd_list_sleepout, sizeof(lcd_cmd_list_sleepout) / sizeof(lcd_cmd_list_sleepout[0]));
#else
    lcd_write_cmd(0x11, NULL, 0);
    delay_2ms(5);	// delay 120ms
    lcd_write_cmd(0x29, NULL, 0);
#endif
}

static u32 lcd_spi_nv3030b_read_id()
{
    u8 id[3];
    lcd_read_cmd(0x04, id, sizeof(id));
    return ((id[0] << 16) | (id[1] << 8) | id[2]);
}

struct imd_param lcd_spi_nv3030b_param = {
    .scr_x    = SCR_X,
    .scr_y	  = SCR_Y,
    .scr_w	  = SCR_W,
    .scr_h	  = SCR_H,

    .in_width  = SCR_W,
    .in_height = SCR_H,
    .in_format = LCD_FORMAT,

    .lcd_width  = LCD_W,
    .lcd_height = LCD_H,

    .lcd_type = LCD_TYPE_SPI,

    .buffer_num = BUF_NUM,
    .buffer_size = LCD_BLOCK_W * LCD_BLOCK_H * 2,

    .fps = 60,

    .spi = {
        .spi_mode = SPI_IF_MODE(LCD_DRIVE_CONFIG),
        .pixel_type = PIXEL_TYPE(LCD_DRIVE_CONFIG),
        .out_format = OUT_FORMAT(LCD_DRIVE_CONFIG),
        .port = SPI_PORTA,
        .spi_dat_mode = SPI_MODE_UNIDIR,
    },

    .debug_mode_en = false,
    .debug_mode_color = 0xff0000,
};

REGISTER_LCD_DEVICE(nv3030b) = {
    .logo = "nv3030b",
    .row_addr_align    = 2,
    .column_addr_align = 2,

    .lcd_cmd = (void *) &lcd_spi_nv3030b_cmd_list_poweron,
    .cmd_cnt = sizeof(lcd_spi_nv3030b_cmd_list_poweron) / sizeof(lcd_spi_nv3030b_cmd_list_poweron[0]),
    .param   = (void *) &lcd_spi_nv3030b_param,
    
    .reset = NULL,	// 没有特殊的复位操作，用内部普通复位函数即可
    .backlight_ctrl = NULL, //lcd_spi_nv3030b_backlight_ctrl,
    .power_ctrl = lcd_spi_nv3030b_power_ctrl,
    .entersleep = lcd_spi_nv3030b_entersleep,
    .exitsleep = lcd_spi_nv3030b_exitsleep,
    .read_id = lcd_spi_nv3030b_read_id,
    .lcd_id = 0x303001,
};


#endif


