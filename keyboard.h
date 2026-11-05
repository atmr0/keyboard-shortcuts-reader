#ifndef KEYBOARD_H
#define KEYBOARD_H
char keyboardToChar(int code, char mod);
char *mountKeyStroke(char c, unsigned char currMod);
char getKeyMod(int code);
#endif
