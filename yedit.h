#pragma once

#include <stdio.h>
#include <fcntl.h>

#include <SDL2/SDL.h>

#define BUFFER_CAP 100

typedef struct Buffer {
    char *name;
    char *buf;
    size_t len;
    size_t cap;
    struct Buffer *nxt;
} Buffer;

typedef struct Cursor {
    size_t beg;
    size_t end;
    size_t marked;
    struct Cursor *nxt;
} Cursor;

typedef struct Frame {
    Buffer *buffer;
    Cursor *cursors;
    struct Frame *nxt;
} Frame;

/* The storage of the closed buffers. Used for deacrising memory allocation */
typedef struct BuffersStorage {
    Buffer *buffer;
    size_t n;
} BuffersStorage;

typedef enum {
    APP_QUIT             = 0x1,
    APP_MODE_NORMAL      = 0x2,
    APP_MODE_VISUAL      = 0x4,
    APP_MODE_INSERT      = 0x8,
    APP_MODE_COMMAND     = 0x10,
    APP_MODE_FIND_FILE   = 0x20,
} APP_FLAGS;

#define APP_COMMAND_BUF_LEN 10

typedef struct App {
    int flags;
    Frame *frame;
    Frame *currentframe;
    Buffer *buffer;
    Buffer *currentbuffer;
    char commandbuf[APP_COMMAND_BUF_LEN];
    BuffersStorage storage;
} App;

void process(App *app);
void display(App *app);
void displayframe(Frame *frame);
void displayframebar(Frame *frame);
void displayappbar(App *app);

Buffer* createbuffer(App *app);
void nilframestates(Frame *frame);
void changemodeto(int *flags, int mode);

void processreturn(App *app);
void processbackspace(App *app);
void processcommand(App *app, SDL_Keysym keysym);
void appendcommandbuf(char *keybuf, int len, char sym);
void nilbuf(char* buf, int len);
void insertletter(Buffer *buffer);

void movecursorsup(Frame *frame, int step);
void movecursorsdown(Frame *frame, int step);
void movecursorsleft(Frame *frame, int step);
void movecursorsright(Frame *frame, int step);
void movecursorstowordbeg(Frame *frame, int step);
void movecursorstowordend(Frame *frame, int step);
void movecursorstolinebeg(Frame *frame);
void movecursorstolineend(Frame *frame);

Buffer* openfile(const char* path);
Buffer* opendir(const char* path);

void addstorage(BuffersStorage *bs, Buffer *b);
Buffer* getstorage(BuffersStorage *bs, int len);
