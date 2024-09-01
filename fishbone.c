#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


struct termios orig_termios;


void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}


void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
	enableRawMode();

	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q');
	return 0; /* indicates successful execution */
}
