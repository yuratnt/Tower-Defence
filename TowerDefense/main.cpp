#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

static SDL_Window* window;
static SDL_Renderer* renderer;


class TextureObj {
protected:
	SDL_FRect rect;
	SDL_Texture* texture;
public:
	TextureObj(SDL_FRect _rect, SDL_Texture* _texture) {
		rect = _rect;
		texture = _texture;
	}

	virtual void render(SDL_Renderer* renderer, SDL_FRect path) {
		SDL_RenderTexture(renderer, texture, &path, &rect);
	}
};

class Button : TextureObj {
private:
	void (*function)();
public:
	Button(
		SDL_FRect _rect,
		SDL_Texture* _texture, 
		void (*_function)()
		) : TextureObj(_rect, _texture) 
	{
		rect = _rect;
		texture = _texture;
		function = _function;
	}

private:
	bool inRect(int x, int y) {
		return x >= rect.x && x <= rect.x + rect.w &&
			y >= rect.y && y <= rect.y + rect.h;
	}

public:
	void click(int x, int y) {
		if (!inRect(x, y)) return;
		function();
	}
};

class Menu  {
protected:
	/*
	SDL_Texture* background;
	SDL_Renderer* renderer;
	SDL_FRect backgroundRect;
	SDL_Texture* test;
	SDL_FRect testRect;
	SDL_FRect startButton;
	SDL_FRect saveButton;
	SDL_FRect exitButton;
	*/
	TextureObj interface;
	Button* button;
public:
	Menu() {

	}

	void render() {
		//SDL_RenderTexture(renderer, background, NULL, &backgroundRect);
	}


/*
	Menu(SDL_Renderer* _renderer) {
		status = 1;
		renderer = _renderer;
		background = IMG_LoadTexture(renderer, "assets\\menu\\background.png");
		// тестовая текстура
		test = IMG_LoadTexture(renderer, "test.png");
		testRect = { 50, 50, 300, 300 };

		// ректы
		backgroundRect = { 0, 0, 1000, 800 };

		startButton = { 413, 354, 178, 30 };
		saveButton = { 413, 410, 178, 33 };
		exitButton = { 413, 470, 178, 30 };
	}

public:
	void menuBackground() {
		SDL_RenderTexture(renderer, background, NULL, &backgroundRect);
	}

private:
	void startGame() {
		SDL_RenderTexture(renderer, test, NULL, &testRect);
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
		SDL_RenderRect(renderer, &startButton);
		SDL_RenderRect(renderer, &saveButton);
		SDL_RenderRect(renderer, &exitButton);
	}

public:
	SDL_AppResult menuButton(int x, int y) {
		if (inRect(x, y, exitButton)) return SDL_APP_SUCCESS;

		return SDL_APP_CONTINUE;
	}

	void renderMenu() {

		switch (status) {
		case 1:
			menuBackground();
			break;
		case 2:
			menuBackground();
			startGame();
			break;
		case 3:
			menuBackground();
			break;

		}

	}

	void setStatus(int _status) {
		if (0 < _status > 10) return;
		status = _status;
	}
	*/
};

class MainMenu : Menu {

};

Menu* menu;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_AUDIO);
	SDL_RenderClear(renderer);

	SDL_CreateWindowAndRenderer(
		"Tower Defence",
		1000, 800, 0,
		&window,
		&renderer
	);

	//menu = new Menu(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	// menu->renderMenu();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		std::cout << event->button.x << "\t" << event->button.y << std::endl;
		// menu->setStatus(2);
		//return menu->menuButton(event->button.x, event->button.y);
		break;
	default:
		break;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {

}