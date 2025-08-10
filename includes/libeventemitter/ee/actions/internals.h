#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/ee.h>

// == 结构定义 ==
typedef struct EventEmittingBTData {
    EventListener *eebtd_who;
    gpointer eebtd_what; // 最后向后传输的具体数据
} EventEmittingBTData;
// == 函数定义 ==
EventEmittingBTData EventEmitter_internals_execEmitting(EventEmitter **ee,
                                                        Event *event);
gpoibter EventEmitter_internals_applyBtPolicy(EventEmitter **ee, GList* rawdata);