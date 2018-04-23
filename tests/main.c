/*
** EPITECH PROJECT, 2018
** lizz_overlay
** File description:
** main tests
*/

# include "lizz.h"

void func_thread(void *data)
{
	for (int i = 0; i <= 10; i++) {
		printf("data = %d\n", *((int *)data));
		*((int *)data) += 1;
		usleep(3000000);
	}
}

void lizz_object_creation(void)
{
	int user_data = 8;

	lizz_btn_create("btn_play", stMain);
	lizz_btn_create("btn_settings", stMain);
	lizz_thread_create("thread_animation", &func_thread, &user_data);
}

int main(void)
{
	sfVideoMode video = { 1600, 800, 32 };
	sfRenderWindow *win = NULL;
	sfEvent event;
	btn_t *btn = NULL;
	thread_t *thread = NULL;

	if (lizz_start(true) < 0) // Start lizz overlay
		return (84);

	win = sfRenderWindow_create(video, "Lizz Overlay", sfClose, NULL);
	sfRenderWindow_setFramerateLimit(win, 60);

	// create lizz objects
	lizz_object_creation();

	// buttons tests
	btn = lizz_get_btn("btn_play", stMain);
	btn->setTexture(btn, "./assets/buttons/buttons.png", NULL);
	btn->setPosition(btn, 20, 20);
	sfIntRect r = { 30, 45, 45, 65 };
	btn->setTextureRect(btn, &r);
	btn->setTextureRect(btn, NULL);
	btn->setRotation(btn, 56);

	btn = lizz_get_btn("btn_settings", stMain);
	btn->setTexture(btn, "./assets/buttons/buttons.png", NULL);
	btn->setPosition(btn, 20, 20);
	sfIntRect rr = { 30, 45, 45, 65 };
	btn->setTextureRect(btn, &rr);
	btn->setTextureRect(btn, NULL);
	btn->setRotation(btn, 56);

	// threads tests
	thread = lizz_get_thread("thread_animation");
	thread->start(thread);

	while (sfRenderWindow_isOpen(win)) {
		while (sfRenderWindow_pollEvent(win, &event)) {
			if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
				sfRenderWindow_close(win);
			} else if (sfKeyboard_isKeyPressed(sfKeyT)) {
				thread->wait(thread);
			}
		}

		sfRenderWindow_display(win);
	}

	sfRenderWindow_destroy(win);
	lizz_stop(); // Stop lizz overlay
	return (0);
}
