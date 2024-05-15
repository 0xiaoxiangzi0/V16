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

static int quick_func_page_onchange(void *_ctrl, enum element_change_event event, void *arg)
{
    switch (event) {
    case ON_CHANGE_INIT:
        // ui_auto_shut_down_disable();
        break;
    case ON_CHANGE_RELEASE:
        // ui_auto_shut_down_enable();
        break;
    }
    return 0;
}

REGISTER_UI_EVENT_HANDLER(ID_WINDOW_QUICK_FUNC)
  .onchange = quick_func_page_onchange,
  .onkey = NULL,
  .ontouch = NULL,
};

#endif
#endif
#endif /* #if (!TCFG_LUA_ENABLE) */

