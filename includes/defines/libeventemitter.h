#pragma once
#include <glib.h>
// == 工具定义 ==
#ifdef LBLIBEE
#define g_memdup g_memdup2 // 历史遗留，{{SeeAlso|{{WikiLink|curid=1354}}}}
#ifndef NULL
#define NULL (void *)0x0 // 在部分情况下的修复
#endif
// 避免依赖stdbool.h
#define true (gboolean)1
#define false (gboolean)0
#ifdef __GCC_FUNCTION_FORMATED__
#define LIBEE_FUNC __GCC_FUNCTION_FORMATED__ // GCC 15+
#else
#ifdef __FUNCSIG__ // MSVC
#define LIBEE_FUNC __FUNCSIG__
#else
#ifdef __func__ // C99
#define LIBEE_FUNC __func__
#else
#define LIBEE_FUNC "未知"
#endif
#endif
#endif
#define LIBEE_FATALERROR(msg) g_error("%s 在 %s", msg, LIBEE_FUNC)
#define LIBEE_FATALERROR_NULLPTR LIBEE_FATALERROR("空指针")
#endif
// == 前向定义 ==
typedef struct Event Event;
typedef struct EventListener EventListener;
typedef struct EventEmitter EventEmitter;
// typedef enum EventEmitterBackwardTransferPolicy
    // EventEmitterBackwardTransferPolicy;
// 反传策略
typedef enum EventEmitterBackwardTransferPolicy {
    EEBTP_LAST = 0x4,
    EEBTP_FIRST = 0x8,
    EEBTP_LIST = 0xB,
    EEBTP_DEFAULT = EEBTP_LAST
} EventEmitterBackwardTransferPolicy;
// == 函数指针定义 ==
typedef gpointer(EventListenerFunc)(
    GList *, gboolean,
    struct EventEmitter
        *); // 1: emit时传递的参数列表 每个元素类型应是gpointer 但不是Event结构
            // 2: 返回值是否会反向传输 3: 来源发射器实例
typedef EventListenerFunc *EventListenerFuncPtr;
// == 结构定义 ==
typedef struct Event {
    gchar *e_action;           // emit调用时第一个参数
    GList *e_args;             // 实际传给回调的参数列表
    EventEmitter *e_source_ee; // 回调参数3为此
} Event;
typedef struct EventListener {
    gchar *el_listenee; // 被监听者名
    EventListenerFuncPtr el_listener_func;
    gboolean el_once;
    gboolean el_once_keep;
} EventListener;
typedef struct EventEmitter {
    guint ee_listener_count;
    gboolean ee_emitable; // 是否允许emit新事件
    gboolean ee_onable;   // 是否允许on新监听器
    // gsize ee_listener_arr_size; // 迁移到glib后废弃,
    // {{SeeAlso|{{WikiLink|curid=1440}}}}
    GQueue *ee_listeners;
    gboolean ee_do_bwtrans;                         // 是否做反向传播
    EventEmitterBackwardTransferPolicy ee_btpolicy; // 反传策略 since 1.1
} EventEmitter;
typedef struct EventEmitterEmission {
    gboolean eee_completed;
    gboolean eee_bted; // 是否反向传播了
    struct {           // 反传子结构
        EventListener *eee_bted_listener;
        gpointer eee_bted_data;
    } eee_bted_data;
    guint eee_listen_triggered_count;
} EventEmitterEmission;
