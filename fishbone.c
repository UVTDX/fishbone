#include <unistd.h>

int main() {
	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'q');
	return 0; /* indicates successful execution */
}
