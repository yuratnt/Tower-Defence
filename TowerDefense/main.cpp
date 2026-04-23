#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

static SDL_Window* window;
static SDL_Renderer* renderer;


class TextureObj {
protected:
	SDL_FRect rect;
	SDL_FRect* path;
	SDL_Texture* texture;
public:
	TextureObj(
		SDL_FRect _rect, 
		SDL_FRect _path,
		SDL_Texture* _texture
	) {
		rect = _rect;
		path = &_path;
		texture = _texture;
	}

	TextureObj(
		SDL_FRect _rect,
		SDL_Texture* _texture
	) {
		rect = _rect;
		path = nullptr;
		texture = _texture;
	}


	virtual void render(SDL_Renderer* renderer) {
		SDL_RenderTexture(renderer, texture, path, &rect);
	}
};

class Button : public TextureObj {
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
		path = nullptr;
		texture = _texture;
		function = _function;
	}

	Button(
		SDL_FRect _rect,
		SDL_FRect _path,
		SDL_Texture* _texture,
		void (*_function)()
		) : TextureObj(_rect, _path, _texture)
	{
		rect = _rect;
		path = &_path;
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

class Menu {
protected:
	TextureObj* interface;
	Button* button;
	int buttonCount;
public:
	Menu(
		TextureObj _interface,
		Button* _button,
		int _buttonCount
	) {
		interface = &_interface;
		button = _button;
		buttonCount = _buttonCount;
	}

	void render(SDL_Renderer* renderer) {
		interface->render(renderer);
		for (int i = 0; i < buttonCount; i++) {
			button[i].render(renderer);
		}
	}
};

class Window {

};

TextureObj* background;
Menu* mainMenu;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_AUDIO);
	SDL_RenderClear(renderer);

	SDL_CreateWindowAndRenderer(
		"Tower Defence",
		1000, 800, 0,
		&window,
		&renderer
	);

	background = new TextureObj(
		{ 0, 0, 1000, 800 },
		IMG_LoadTexture(renderer, "assets\\menu\\background.png")
	);


	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	background->render(renderer);
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