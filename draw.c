#include "yedit.h"

void
display(App *app) {
    for(Frame* frame = app->frame; frame; frame = frame->nxt) {
	displayframe(frame);
    }
    displayappbar(app);
}

void
displayframe(Frame *frame) {
}

void
displayframebar(Frame *frame) {
}

void
displayappbar(App *app) {
}
