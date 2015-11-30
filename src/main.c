#include <pebble.h>

static Window *s_main_window;
static TextLayer *message_layer;

static DictationSession *s_dictation_session;
static char display_message[512];

static void handle_message(char *ifttt_message) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  dict_write_cstring(iter, 0, ifttt_message);

  APP_LOG(APP_LOG_LEVEL_INFO, "got message");
  app_message_outbox_send();  
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
  window_stack_pop_all(true);
}

static void dictation_session_callback(DictationSession *session, DictationSessionStatus status, char *transcription, void *context) {
  if(status == DictationSessionStatusSuccess) {
    snprintf(display_message, sizeof(display_message), "Message sent!\n\n\"%s\"", transcription);
    text_layer_set_text(message_layer, display_message);
    handle_message(transcription);
  } else {
    static char error_message[128];
    snprintf(error_message, sizeof(error_message), "Error code:\n%d", (int)status);
    text_layer_set_text(message_layer, error_message);
  }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Got button press!");
  dictation_session_start(s_dictation_session);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, select_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  message_layer = text_layer_create(GRect(bounds.origin.x, (bounds.size.h - 72) / 2, bounds.size.w, bounds.size.h));
  text_layer_set_text(message_layer, "Press button and say message :)");
  text_layer_set_text_alignment(message_layer, GTextAlignmentCenter);
  text_layer_set_font(message_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(message_layer));
  APP_LOG(APP_LOG_LEVEL_INFO, "loaded!");
  dictation_session_start(s_dictation_session);
}

static void window_unload(Window *window) {
  text_layer_destroy(message_layer);
}

static void init() {
  s_main_window = window_create();
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);

  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  s_dictation_session = dictation_session_create(sizeof(display_message), dictation_session_callback, NULL);
  dictation_session_enable_confirmation(s_dictation_session, false);
  
  app_message_register_outbox_sent(outbox_sent_callback);
}

static void deinit() {
  dictation_session_destroy(s_dictation_session);

  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}