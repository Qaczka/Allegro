#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>

enum KEYS {LEFT,ESC};

int main(void) {

	ALLEGRO_DISPLAY *okno = NULL;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	al_init();
	al_init_primitives_addon();
	al_install_keyboard();


	bool keys[2] = { false,false };
	bool done = false;

	int szer = 1920;
	int wys = 1080;
	int x= 0;
	int y=0;
	int c = 0;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO INIT FAIL", NULL, NULL);
		return -1;
	}

	okno = al_create_display(szer, wys);

	if (!okno) {
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO DISPLAY FAIL", NULL, NULL);
		return -1;
	}


	al_show_native_message_box(okno, "window title", "message title", "warning", NULL, ALLEGRO_MESSAGEBOX_YES_NO);

	timer = al_create_timer(1.0 / 60);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);



	while (!done)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP)//esc wylacza okno
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_LEFT:
				c = 5;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

				
			}
		}

		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{

			if (x <= 500 && x > -500 && y == 0)
			{
				x = x - c;
			}
			if (x == -500 && y >= 0 && y < 700)
			{
				y = y + c;
			}
			if (x < 500 && x >= -500 && y == 700)
			{
				x = x + c;
			}
			if (x == 500 && y > 0 && y <= 700)
			{
				y = y - c;
			}


			al_draw_filled_circle((szer / 2) + x, (wys / 4) + y, 50, al_map_rgb(255, 0, 0));

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
			
			
	}


	al_destroy_display(okno);

	return 0;
}