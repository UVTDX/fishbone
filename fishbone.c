#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;



int main() {
	enableRawMode();

	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q');
	return 0; /* indicates successful execution */
}
