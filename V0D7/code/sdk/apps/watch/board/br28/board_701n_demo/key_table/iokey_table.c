#include "key_event_deal.h"
#include "key_driver.h"
#include "app_config.h"
#include "board_config.h"
#include "app_task.h"

#ifdef CONFIG_BOARD_701N_DEMO
/***********************************************************
 *				bt 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_BT_EN
const u16 bt_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF,KEY_NULL, KEY_NULL,KEY_UI_SHORTCUT, KEY_NULL
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				fm 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_FM_EN
const u16 fm_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				linein 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_LINEIN_EN
const u16 linein_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				music 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_MUSIC_EN
const u16 music_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				pc 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_PC_EN
const u16 pc_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				record 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_RECORD_EN
const u16 record_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				rtc 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_RTC_EN
const u16 rtc_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				spdif 妯″紡鐨? iokey table
 ***********************************************************/
#if TCFG_APP_SPDIF_EN
const u16 spdif_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_UI_HOME, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_UI_SHORTCUT
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif

/***********************************************************
 *				idle 妯″紡鐨? iokey table
 ***********************************************************/
const u16 idle_key_io_table[KEY_IO_NUM_MAX][KEY_EVENT_MAX] = {
    //鍗曞嚮             //闀挎寜          //hold         //鎶捣            //鍙屽嚮                //涓夊嚮
    [0] = {
        KEY_NULL/*KEY_UI_HOME*/, KEY_UI_POWEROFF
    },
    [1] = {
        KEY_NULL/*KEY_UI_SHORTCUT*/
    },
    [2] = {
        KEY_NULL, KEY_NULL
    },
    [3] = {
        KEY_CHANGE_PAGE
    },
};
#endif
