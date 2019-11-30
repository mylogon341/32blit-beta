#include <algorithm>
#include <SDL.h>

#include "Renderer.hpp"
#include "System.hpp"

Renderer::Renderer(SDL_Window *window, int width, int height) : sys_width(width), sys_height(height) {
	//SDL_SetHint(SDL_HINT_RENDER_DRIVER, "openGL");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
	}

	current = ltdc_texture_RGB565;

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	resize(w, h);

	// Clear the window.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

Renderer::~Renderer() {
	SDL_DestroyTexture(fb_texture_RGB24);
	SDL_DestroyTexture(ltdc_texture_RGB565);
	SDL_DestroyRenderer(renderer);
}

void Renderer::set_mode(Mode new_mode) {
	mode = new_mode;
	if (mode == Stretch) {
		dest.x = 0; dest.y = 0;
		dest.w = win_width; dest.h = win_height;
	} else {
		float current_pixel_size = std::min((float)win_width / sys_width, (float)win_height / sys_height);
		if (mode == KeepPixels) current_pixel_size = (int)current_pixel_size;
		if (mode == KeepPixelsx2) current_pixel_size = 2*(int)(current_pixel_size/2);
		dest.w = sys_width * current_pixel_size;
		dest.h = sys_height * current_pixel_size;
		dest.x = (win_width - dest.w) / 2;
		dest.y = (win_height - dest.h) / 2;
	}
}

void Renderer::resize(int width, int height) {
	win_width = width;
	win_height = height;
	set_mode(mode);

	if (fb_texture_RGB24) {
		SDL_DestroyTexture(fb_texture_RGB24);
	}
	if (ltdc_texture_RGB565) {
		SDL_DestroyTexture(ltdc_texture_RGB565);
	}

	fb_texture_RGB24 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, sys_width, sys_height);
	ltdc_texture_RGB565 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_TARGET, sys_width * 2, sys_height * 2);
}

void Renderer::update(System *sys) {
	if (sys->mode() == SDL_PIXELFORMAT_RGB24) current = fb_texture_RGB24;
	else current = ltdc_texture_RGB565;
	sys->update_texture(current);
}

void Renderer::render(SDL_Texture *target) {
	SDL_SetRenderTarget(renderer, target);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, current, NULL, &dest);
}

void Renderer::render() {
	render(NULL);
}

void Renderer::present() {
	SDL_RenderPresent(renderer);
}
