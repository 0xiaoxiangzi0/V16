#include "app_config.h"
#include "ui/ui_api.h"
#include "ui/ui.h"
#include "ui/ui_style.h"
#include "app_task.h"
#include "system/timer.h"
#include "app_main.h"
#include "init.h"
#include "key_event_deal.h"

#define LOG_TAG_CONST       UI
#define LOG_TAG     		"[UI-ACTION]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


#if TCFG_UI_ENABLE && (!TCFG_LUA_ENABLE)
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#if 1	//TCFG_UI_ENABLE_PC

#define STYLE_NAME  JL

static u16 smoke_timer = 0;
static u8 pic_index = 0;

static void smoke_anim_refresh(void *p)
{
	static u8 pic_index = 0;

    if (smoke_timer) {
        smoke_timer = 0;
    }

	pic_index++;
	if(pic_index > 5)
		pic_index = 0;

    ui_pic_show_image_by_id(SMOKE_ANIM_PIC, pic_index);

    struct unumber num;
    static u8 test_num = 0;
    test_num++;
    if(test_num > 5){
        test_num = 0;
    }
    num.type = TYPE_NUM;
    num.numbs = 1;
    num.number[0] = test_num;
    ui_number_update_by_id(TEST_NUM, &num);

    smoke_timer = sys_timeout_add(NULL, smoke_anim_refresh, 500);
}

static int watch_test_onchange(void *_ctrl, enum element_change_event event, void *arg)
{
    switch (event) {
    case ON_CHANGE_INIT:
        ui_auto_shut_down_disable();
        break;
    case ON_CHANGE_RELEASE:
        ui_auto_shut_down_enable();
        break;
    }
    return 0;
}

static int watch_test_ontouch(void *ctr, struct element_touch_event *e)
{
	static u8 pic_index = 0;
    
    switch (e->event) {
    case ELM_EVENT_TOUCH_DOWN:
        break;
    case ELM_EVENT_TOUCH_L_MOVE:
	    pic_index++;
	    if(pic_index > 5)
		    pic_index = 0;
        ui_pic_show_image_by_id(WATCH_TEST, pic_index);
        return true;
        break;
    case ELM_EVENT_TOUCH_R_MOVE:
	    if(pic_index == 0){
		    pic_index = 5;
        }
        else{
	        pic_index--;
        }
        ui_pic_show_image_by_id(WATCH_TEST, pic_index);
        return true;
        break;
    default:
        return false;
        break;
    }
    return false;//不接管消息
}

REGISTER_UI_EVENT_HANDLER(ID_WINDOW_WATCH_TEST)
.onchange = watch_test_onchange,
 .onkey = NULL,
  .ontouch = watch_test_ontouch,
};

#endif
#endif
#endif /* #if (!TCFG_LUA_ENABLE) */

