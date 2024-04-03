#ifndef SDL_DIGIT
#define SDL_DIGIT
#include <SDL2/SDL.h>

typedef struct
{
	int smaller_side_size;
	int larger_side_size;
	int padding;
} scale;
typedef struct {
	SDL_Rect bars[7];
	int bar_states;
	scale sc;
	SDL_Color color;
} drawable_SDL_digit;

void init_empty_digit(drawable_SDL_digit *);
void calculate_scale_for_digit(drawable_SDL_digit *, int, int);
void init_segments(drawable_SDL_digit *);
void move_digit_to(drawable_SDL_digit *, int, int);
void set_digit_state(drawable_SDL_digit *, int);
void render_digit(drawable_SDL_digit *, SDL_Renderer *);
#endif
