#include "yedit.h"

void
nilframestates(Frame *frame) {
}

void
changemodeto(int *flags, int mode) {
    *flags &= ~(
	APP_MODE_NORMAL |
	APP_MODE_VISUAL |
	APP_MODE_INSERT |
	APP_MODE_COMMAND
    );
    *flags |= mode;
}

void
processreturn(App *app) {
}

void
processbackspace(App *app) {
}

void
processcommand(App *app, SDL_Keysym keysym) {
    int step;

    step = atoi(app->commandbuf);
    if(step == 0) {
	step = 1;
    }
    printf("command wass suspend\n");

    if(keysym.mod & KMOD_LSHIFT || keysym.mod & KMOD_RSHIFT) {
	switch(keysym.sym) {
	case SDLK_a: {
	    movecursorstolinebeg(app->currentframe);
	} goto clean;
	case SDLK_i: {
	    movecursorstolineend(app->currentframe);
	} goto clean;  
	}
    } else {
	switch(keysym.sym) {
	case SDLK_LEFTBRACKET: {
	    movecursorstoparagraphbeg(app->currentframe, step);
	} goto clean;
	case SDLK_RIGHTBRACKET: {
	    movecursorstoparagraphend(app->currentframe, step);
	} goto clean;
	case SDLK_a: {
	    movecursorsright(app->currentframe, step);
	    changemodeto(&app->flags, APP_MODE_INSERT);
	} goto clean;
	case SDLK_b: {
	    movecursorstowordbeg(app->currentframe, step);
	} goto clean;
	case SDLK_e: {
	    movecursorstowordend(app->currentframe, step);
	} goto clean;
	case SDLK_f: {
	    changemodeto(&app->flags, APP_MODE_FIND_FILE);
	    openfile("/home/kra53n/Desktop/test/strtol/main.c");
	} goto clean;
	case SDLK_h: {
	    movecursorsleft(app->currentframe, step);
	} goto clean;
	case SDLK_i: {
	    changemodeto(&app->flags, APP_MODE_INSERT);
	} goto clean;
	case SDLK_j: {
	    movecursorsdown(app->currentframe, step);
	} goto clean;
	case SDLK_k: {
	    movecursorsup(app->currentframe, step);
	} goto clean;
	case SDLK_l: {
	    movecursorsright(app->currentframe, step);
	} goto clean;
	case SDLK_v: {
	    changemodeto(&app->flags, APP_MODE_VISUAL);
	} goto clean;
	case SDLK_x: {
	    changemodeto(&app->flags, APP_MODE_COMMAND);
	} goto clean;
	}
    }
    
    appendcommandbuf(app->commandbuf, APP_COMMAND_BUF_LEN, keysym.sym);
    for(int i = 0; i <= APP_COMMAND_BUF_LEN; i++) {
	if(i == APP_COMMAND_BUF_LEN) {
	    goto clean;
	}
	else if(app->commandbuf[0] == 0) {
	    break;
	}
    }
    return;

clean:
    nilbuf(app->commandbuf, APP_COMMAND_BUF_LEN);
    return;
}

void
appendcommandbuf(char *keybuf, int len, char sym) {
    for(int i = 0; i < len; i++) {
	if(keybuf[i] == 0) {
	    keybuf[i] = sym;
	    return;
	}
    }
}

void
nilbuf(char *buf, int len) {
    for(int i = 0; i < len; i++) {
	buf[i] = 0;
    }
}

void
insertletter(Buffer *buffer) {
}

Buffer*
openfile(const char* path) {
    if(open(path, O_RDONLY | O_DIRECTORY) >= 0) {
	return opendir(path);
    }
    FILE *f;
    int sz, cap;
    char *buf;
    Buffer* buffer;
    
    f = fopen(path, "r");
    
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    cap = sz + BUFFER_CAP;
    buffer = malloc(sizeof(Buffer));
    buf = malloc(sizeof(*buf)*cap);
    fread(buf, sizeof(*buf), sz, f);

    buffer->name = (char*)path;
    buffer->buf = buf;
    buffer->len = sz;
    buffer->cap = cap;
    
    fclose(f);
    return buffer;
}

Buffer*
opendir(const char* path) {
    if(open(path, O_RDONLY | O_DIRECTORY) < 0) {
	return 0;
    }
    /* UNIMPLEMENTED(kra53n)  */
    return 0;
}
