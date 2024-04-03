#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>

#include "digit.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int init_window(int, int, int, int);
int destroy_window(void);
void read_input(void);
void update(void);

int running = 1;
int n = 0;
drawable_SDL_digit digit;

int main(int argc, char* argv[])
{
	int width = 400, height = 780;
	int pos_x = SDL_WINDOWPOS_CENTERED, pos_y=SDL_WINDOWPOS_CENTERED;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0)
		{
			if(sscanf(argv[++i], "%d", &width));
			else width = 400;
		} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0)
		{
			if(sscanf(argv[++i], "%d", &height));
			else height = 800;
		}
	}
	init_window(width, height, pos_x, pos_y);
	init_empty_digit(&digit);
	calculate_scale_for_digit(&digit, width, height);
	init_segments(&digit);
	move_digit_to(&digit, 0, 0);
	set_digit_state(&digit, n);
	render_digit(&digit,renderer);
	SDL_RenderPresent(renderer);
	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		read_input();
		update();
	}
	destroy_window();
	return 0;
}

void read_input(void)
{
	if (scanf("%d", &n))
	{
		if (n<0) running = 0;
	}
	else
	{
		printf("Invalid input!!!\n");
	}
	n = n%10;
}

void update(void)
{
	set_digit_state(&digit, n);
	render_digit(&digit,renderer);
	SDL_RenderPresent(renderer);
}

int init_window(int w, int h, int pos_x, int pos_y)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return 1;
	}
	window = SDL_CreateWindow(
		"SevenSegment",
		pos_x,
		pos_y,
		w,
		h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		fprintf(stderr, "Error initializing window.\n");
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error initializing renderer.\n");
		return 1;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	return 0;
}

int destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
