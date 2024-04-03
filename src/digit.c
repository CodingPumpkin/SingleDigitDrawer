#include "digit.h"

const uint8_t states[10] = 
{
	0x77,//0
	0x24,//1
	0x5d,//2
	0x6d,//3
	0x2e,//4
	0x6b,//5
	0x7b,//6
	0x25,//7
	0x7f,//8
	0x6f //9
};

void init_empty_digit(drawable_SDL_digit *d)
{
	d->sc.smaller_side_size = 1;
	d->sc.larger_side_size = 1;
	d->sc.padding = 1;
	d->color.r = 255;
	d->color.g = 255;
	d->color.b = 255;
	set_digit_state(d, 0);
}

//calculate scale for a digit based on the the size of the box around it
void calculate_scale_for_digit(drawable_SDL_digit *d, int width, int height)
{
	if (height > 2*width)
	{
		d->sc.smaller_side_size = width/8;
		d->sc.padding = d->sc.smaller_side_size/4;
		d->sc.larger_side_size = width - 2*d->sc.smaller_side_size - 2*d->sc.padding;
	} else
	{
		d->sc.smaller_side_size = height/15;
		d->sc.padding = d->sc.smaller_side_size/4;
		d->sc.larger_side_size = (height - 3*d->sc.smaller_side_size - 4*d->sc.padding)/2;
	}
}

//initialize digit's segments
void init_segments(drawable_SDL_digit *d)
{
	for (int i = 0; i<7; i++)
	{
		if(i%3 == 0) 
		{
			d->bars[i].w = (d->sc).larger_side_size; 
			d->bars[i].h = (d->sc).smaller_side_size;
		}
		else 
		{
			d->bars[i].h = (d->sc).larger_side_size; 
			d->bars[i].w = (d->sc).smaller_side_size;
		}
	}
	d->bars[0].x = (d->sc).smaller_side_size + (d->sc).padding;
	d->bars[0].y = 0;

	d->bars[1].x = 0;
	d->bars[1].y = (d->sc).smaller_side_size + (d->sc).padding;

	d->bars[2].x = (d->sc).larger_side_size + (d->sc).smaller_side_size + 2*(d->sc).padding;
	d->bars[2].y = (d->sc).smaller_side_size + (d->sc).padding;

	d->bars[3].x = (d->sc).smaller_side_size + (d->sc).padding;
	d->bars[3].y = (d->sc).larger_side_size + (d->sc).smaller_side_size + 2*(d->sc).padding;

	d->bars[4].x = 0;
	d->bars[4].y = (d->sc).larger_side_size + 2*((d->sc).smaller_side_size + (d->sc).padding);

	d->bars[5].x = (d->sc).larger_side_size + (d->sc).smaller_side_size + 2*(d->sc).padding;;
	d->bars[5].y = (d->sc).larger_side_size + 2*((d->sc).smaller_side_size + (d->sc).padding);

	d->bars[6].x = (d->sc).smaller_side_size + (d->sc).padding;
	d->bars[6].y = 2*(d->sc).larger_side_size + 2*(d->sc).smaller_side_size + 4*(d->sc).padding;
}

//move digit to certain coordinates on screen
void move_digit_to(drawable_SDL_digit *d, int x, int y)
{
	for (int i = 0; i<7; i++)
	{
		(d->bars[i]).x += x;
		(d->bars[i]).y += y; 
	}
}

//set digit state (select which digit is to be displayed)
void set_digit_state(drawable_SDL_digit *d, int n)
{
	d->bar_states = states[n%10];
}

//render digit via an SDL renderer
void render_digit(drawable_SDL_digit *d, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (int i = 0; i<7; i++)
	{
		if((d->bar_states>>i) & 1)
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 128);
		SDL_RenderFillRect(renderer, &(d->bars[i]));
	}
}
