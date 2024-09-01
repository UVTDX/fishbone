#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void enableRawMode() {
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);

	raw.c_lflag &= ~(ECHO);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, & raw);
}

int main() {
	enableRawMode();

	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q');
	return 0; /* indicates successful execution */
}
