#include "internals.h"
#include <glib.h>
#include <libeventemitter.h>
#include <libeventemitter/e.h>
#include <libeventemitter/ee.h>

EventEmitterEmission EventEmitter_action_emit(EventEmitter **ee, gchar *act,
                                              GList *args) {
    if (ee == NULL || *ee == NULL || act == NULL) {
        LIBEE_FATALERROR_NULLPTR;
    }
    if (!(*ee)->ee_emitable) {
        EventEmitterEmission emission = {
            .eee_completed = false,
            .eee_bted = false,
            .eee_bted_data = {.eee_bted_listener = NULL,
                              .eee_bted_data = NULL}};
        return emission;
    }
    EventEmitterEmission emission = {
        .eee_completed = false,
        .eee_bted = false,
        .eee_bted_data = {.eee_bted_listener = NULL, .eee_bted_data = NULL}};

    Event *event = g_malloc(sizeof(Event));

    Event_action_create(&event, act, args, *ee);

    EventEmittingBTData data = EventEmitter_internals_execEmitting(ee, event);

    emission.eee_completed = true;
    emission.eee_bted = data.eebtd_who != NULL;
    emission.eee_bted_data.eee_bted_listener = data.eebtd_who;
    emission.eee_bted_data.eee_bted_data = data.eebtd_what;

    Event_action_destroy(&event);
    g_free(event);

    return emission;
}