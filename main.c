#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "keyboard.h"
const char *device ="/dev/input/event11";



char command[32] = "\0";
unsigned char currMod = 0;
char shortcutToFind[] = "s-e r ";

void buildCommand(struct input_event ev){
  char mod = getKeyMod(ev.code);
  if(ev.value > 1 || ev.value < 0) return;   
  if(mod != 0){
    if(mod == 'C') currMod = currMod ^ 1;
    if(mod == 'M') currMod = currMod ^ 2;
    if(mod == 'S') currMod = currMod ^ 4;
    if(mod == 's') currMod = currMod ^ 8;
  }
    
  else {
    if(ev.value == 0) return;
    char r = keyboardToChar(ev.code, currMod);
    if(r == 0) return;
    char *keystroke = mountKeyStroke(r,currMod);
    if(strlen(command) == 0 && currMod == 0) return;
    if (strcmp(keystroke, "C-g ") == 0){
      command[0] = '\0';
      return;
    }
    strcat(command,keystroke);
    printf("\n%s, %d\n", command, strcmp(command, shortcutToFind));
  }
}

void readLoop(){
  struct input_event ev;
  int f = open(device, O_RDONLY);
  if(f<0) {
    perror("Could not open event");
    return;
  }

  while (read(f, &ev, sizeof(ev)) > 0) {
    buildCommand(ev);
    if(strcmp(command, shortcutToFind)==0){
      printf("Hello world\n");
      command[0] = '\0';
    }
  }
  close(f);
}

const char *delim = " ";

int main() {
  readLoop(); 
  return 0;
}
