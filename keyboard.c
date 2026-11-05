#include <linux/input.h>
#include <stdlib.h>
typedef struct {
  int code;
  char key;
  char shiftKey;
} Keycode;

Keycode mods[] = {{KEY_LEFTCTRL,'C',0},{KEY_LEFTMETA, 's',0},{KEY_LEFTSHIFT, 'S',0}, {KEY_LEFTALT, 'M',0}};

Keycode keycodes[] = {
  {KEY_A, 'a',0}, {KEY_B, 'b',0}, {KEY_C, 'c',0}, {KEY_D, 'd',0}, {KEY_E, 'e',0}, {KEY_F, 'f',0}, {KEY_G, 'g',0}, {KEY_H, 'h',0}, {KEY_I, 'i',0}, {KEY_J, 'j',0}, {KEY_K, 'k',0}, {KEY_L, 'l',0}, {KEY_M, 'm',0}, {KEY_N, 'n',0}, {KEY_O, 'o',0}, {KEY_P, 'p',0}, {KEY_Q, 'q',0}, {KEY_R, 'r',0}, {KEY_S, 's',0}, {KEY_T, 't',0}, {KEY_U, 'u',0}, {KEY_V, 'v',0}, {KEY_W, 'w',0}, {KEY_X, 'x',0}, {KEY_Y, 'y',0}, {KEY_Z, 'z',0}, 
  {KEY_MINUS		,'-'	, '_'  },
  {KEY_EQUAL		,'='	, '+'  },
  {KEY_BACKSPACE	,8      , 0    },
  {KEY_LEFTBRACE	,'['	, '{'  },
  {KEY_RIGHTBRACE	,']'	, '}'  },
  {KEY_ENTER		,'\13'  , 0    },
  {KEY_SEMICOLON	,';'	, ':'  },
  {KEY_APOSTROPHE	,'\''	, '\"' },
  /* {KEY_GRAVE'	,'}	, */
  {KEY_BACKSLASH	,'\\'	, '|'  },
  {KEY_COMMA		,','	, '<'  },
  {KEY_DOT		,'.'	, '>'  },
  {KEY_SLASH		,'/'	, '?'  },
};

  
char keyboardToChar(int code, char mod) {
  if(code >= KEY_1 && code <= KEY_9) return '1'+ (code - KEY_1);
  if(code == KEY_0) return '0';
  char currChar = 'a';
  for(int i = 0; i < (int)(sizeof(keycodes)/sizeof(Keycode)); i+=1){
    if(code == keycodes[i].code) {
      if ((mod & 4) > 0) return keycodes[i].shiftKey > 0 ? keycodes[i].shiftKey : keycodes[i].key;
      return keycodes[i].key;
    }
    currChar += 1;
  }
  return 0;
}

char getKeyMod(int code) {
  for(int i = 0; i < (int)(sizeof(mods)/sizeof(Keycode)); i+=1){
    if (code == mods[i].code) return mods[i].key;
  }
  return 0;
}

char *mountKeyStroke(char c, unsigned char currMod){
  char *result = (char*)malloc(10);
  result[0] = '\0';
  char *mods = "CMSs";
  int size = 0;
  int cModCopy = currMod;
  for(int i = 0; i < 4; i+=1) {
    if((currMod & 1)) {
      result[size] = mods[i];
      result[size+1] = '-';
      result[size+2] = '\0';
      size += 2;
    };
    currMod = currMod >> 1;
  }
  
  // remove S-a
  if((c<'a' || c>'z') && (cModCopy & 4)){
    result[size-2] = '\0';
    size-=2;
  }
    
  result[size] = c;
  result[size+1] = ' ';
  result[size+2] = '\0';
  return result;
}
