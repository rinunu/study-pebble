#include <pebble.h>

Window *window;
TextLayer *text_layer;

GBitmap *g_frame_bitmap;
BitmapLayer *g_frame_layer;

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  //Allocate long-lived storage (required by TextLayer)
  static char buffer[] = "00:00:00";

  //Write the time to the buffer in a safe manner
  strftime(buffer, sizeof("00:00:00"), "%H:%M:%S", tick_time);

  //Set the TextLayer to display the buffer
  text_layer_set_text(text_layer, buffer);
}

void init_bitmap(){
//Create and add the image
g_frame_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FRAME);
g_frame_layer = bitmap_layer_create(GRect(7, 56, 129, 60));
bitmap_layer_set_bitmap(g_frame_layer, g_frame_bitmap);
layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(g_frame_layer));
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

  init_bitmap();

	// Push the window
	window_stack_push(window, true);

tick_timer_service_subscribe(SECOND_UNIT, (TickHandler)tick_handler);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);

  gbitmap_destroy(g_frame_bitmap);
  bitmap_layer_destroy(g_frame_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
