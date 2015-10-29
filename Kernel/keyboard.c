#define LSHIFTR 0xFFFFFFAA
#define RSHIFTR 0xFFFFFFB6
#define CAPS 0x3A
#define LSHIFT 0x2A
#define RSHIFT 0x36

char buffer[250];
int last = 0;
int counter = 0;
int caps = 0;
int shift = 0;

unsigned static char scancodes[2][128] =
{{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '\'', '¿', '\b', '\t', 'q', 'w', 'e', 'r',/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '´', '+', '\n',	 0,	/* 29 */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
  '{', '|',   0, '}', 'z', 'x', 'c', 'v', 'b', 'n',	/* 49 */
  'm', ',', '.', '-',   0, '*',   0, ' ',   0,   0,	/* 59 */
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	/* 69 */
    0, '7', '8', '9', '-', '4',	'5', '6', '+', '1', /* 79 */
  '2', '3', '0', '.',   0,   0, '<',   0, 	0,   0,	/* 89 */
    0,   0,   0,   0,   0,   0,'\n',   0, '/',   0, /* 99 */
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, /* 109 */
}, {
    0,  27, '!', '"', '#', '$', '%', '&', '/', '(', /* 9 */
  ')', '=', '?', '¡', '\b', '\t', 'Q', 'W', 'E', 'R',/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '¨', '*', '\n',  0, /* 29 */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
  '[', '°',   0, ']', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
  'M', ';', ':', '_',   0, '*',   0, ' ',   0,   0, /* 59 */
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, /* 69 */
    0, '7', '8', '9', '-', '4', '5', '6', '+', '1', /* 79 */
  '2', '3', '0', '.',   0,   0, '>',   0,   0,   0, /* 89 */
    0,   0,   0,   0,   0,   0,'\n',   0, '/',   0, /* 99 */
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, /* 109 */
}};


void write_key(char scancode){
  if(scancode == CAPS){
    caps = !caps;
  }
  if(scancode == LSHIFT || scancode == RSHIFT || scancode == RSHIFTR || scancode == LSHIFTR)
    shift = !shift;
  if(scancode<128 && scancodes[0][scancode] != 0 && scancode>0){
    if(caps && scancode < 16 || (scancode > 25 && scancode < 30) || (scancode > 38 && scancode < 44) || (scancode > 50))
      if(shift)
        buffer[counter++] = scancodes[1][scancode];
      else
        buffer[counter++] = scancodes[0][scancode];
    else
      buffer[counter++] = scancodes[!(caps == shift)][scancode];
  }    
  if(counter == 250)
    counter = 0;
}

char getKey(){
  if(counter == last%250)
    return -1;
  //if(buffer[(last++&250)] != ' ')
    return buffer[(last++%250)];
}


