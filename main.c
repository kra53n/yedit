#include "yedit.h"

#include <malloc.h>

#define PROC_SDL_ERR(err, msg) if(err) { SDL_Log("%s (%s)", msg, SDL_GetError()); return 1; }

int
main() {
    PROC_SDL_ERR(SDL_Init(SDL_INIT_VIDEO), "sub-systems initialization error");
    {
	SDL_Window* w = SDL_CreateWindow(
	    "yedit",
	    SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    500,
	    500,
	    0
	);
	PROC_SDL_ERR(w==0, "window creating error");
	{
	    App app;
	    app.flags |= APP_MODE_NORMAL;
	    
	    createbuffer(&app);

	    while(1) {
		if(app.flags & APP_QUIT)
		    break;
		process(&app);
		display(&app);
	    }
	}
	SDL_DestroyWindow(w);
    }
    SDL_Quit();
}

void
process(App *app) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
	switch(event.type) {
	case SDL_QUIT: {
	    app->flags |= APP_QUIT;
	} break;
	case SDL_KEYDOWN: {
	    size_t sym = event.key.keysym.sym;
	    size_t mod = event.key.keysym.mod;

	    if(SDLK_SPACE <= sym && sym <= SDLK_z) {
		processcommand(app, event.key.keysym);

	    } else {
		/* TODO(kra53n): can we do `if switch` */
		switch(event.key.keysym.sym) {
		case SDLK_ESCAPE: {
		    if(app->flags & APP_MODE_NORMAL) {
			nilbuf(app->commandbuf, APP_COMMAND_BUF_LEN);
		    } else {
			changemodeto(&app->flags, APP_MODE_NORMAL);
		    }
		} break;
		case SDLK_RETURN: {
		    processreturn(app);
		} break;
		case SDLK_BACKSPACE: {
		    processbackspace(app);
		} break;
		}
	    }
	} break;
	}
    }

}

Buffer*
createbuffer(App *app) {
    Buffer new;
    if(app->buffer) {
	app->buffer->nxt = &new;
    } else {
	app->buffer = &new;
    }
}
