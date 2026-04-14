#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window* window;
static SDL_Renderer* renderer;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_AUDIO);

	SDL_CreateWindowAndRenderer(
		"Tower Defence", 
		800, 640, 0, 
		&window, 
		&renderer
	);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
	SDL_FRect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 50;
	rect.h = 50;

	SDL_RenderLine(renderer, 50, 50, 50, 200);
	
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {

}

