#include "project2.h"

#define TEXT_COLOR 0x07
#define VIDEO_MEM 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Define a keymap to convert keyboard scancodes to ASCII
volatile static char keymap[128] = {
	[0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
	[0x20] = 'd',
	[0x12] = 'e',
	[0x21] = 'f',
	[0x22] = 'g',
	[0x23] = 'h',
	[0x17] = 'i',
	[0x24] = 'j',
	[0x25] = 'k',
	[0x26] = 'l',
	[0x32] = 'm',
	[0x31] = 'n',
	[0x18] = 'o',
	[0x19] = 'p',
	[0x10] = 'q',
	[0x13] = 'r',
	[0x1F] = 's',
	[0x14] = 't',
	[0x16] = 'u',
	[0x2F] = 'v',
	[0x11] = 'w',
	[0x2D] = 'x',
	[0x15] = 'y',
	[0x2C] = 'z',
	[0x02] = '1',
	[0x03] = '2',
	[0x04] = '3',
	[0x05] = '4',
	[0x06] = '5',
	[0x07] = '6',
	[0x08] = '7',
	[0x09] = '8',
	[0x0A] = '9',
	[0x0B] = '0',
	[0x39] = ' ',
	[0x34] = '.',
    [0x35] = '/',
	[0x1C] = '\n',
};

#if PROJECT == 2
// This function runs when compiled with the #define PROJECT 2 flag for make
int kernel()
{
	   
	  char string[101];
	  	while (1)
	{
		print("Type something: ");
		scan(string);
		print("You typed: ");
		print(string);
		print("\n");
	}
	
	return 0;
}
#endif

// Gets the character from the keyboard
// This is a blocking function that does not use interrupts
// Only I/O ports and polling are used
char getchar()
{
	while (1)
	{
	while ((inb(0x64) & 0x01) == 0)
	{
		// Wait for the keyboard to be ready
	}
   
	uint8 scancode = inb(0x60);
	uint8 isPressed = !(scancode & 0x80);
	if (isPressed && keymap[scancode] != '\0')
	{
		return keymap[scancode];
	}
}
}

// Read characters from the keyboard until the user hits the enter key
// Accepts a character array to fill with characters
// Terminates string with NULL terminator when done
void scan(char string[])
{
	int i = 0;
	char c;
	while ((c = getchar()) != '\n')
	{
		string[i++] = c;
		putchar(c);
	}
	string[i] = '\0';
	putchar('\n');
}

void scroll(int rows)

{
    uint8 *vidmem = (uint8 *)VIDEO_MEM;
    int offset = rows * SCREEN_WIDTH * 2;

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2 - offset; i++)
{
    vidmem[i] = vidmem[i + offset];
}

	// Clear the last rows
	for (int i = SCREEN_WIDTH * SCREEN_HEIGHT * 2 - offset; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i+=2)
	{
		vidmem[i] = ' ';
		vidmem[i + 1] = TEXT_COLOR;	
	}

}