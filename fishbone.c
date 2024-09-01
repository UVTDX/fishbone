#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


void enableRawMode(struct termios *orig_termios) {
    tcgetattr(STDIN_FILENO, orig_termios);
    struct termios raw = *orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void disableRawMode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}


int main() {
  struct termios orig_termios;
	enableRawMode(&orig_termios);

  FILE *file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 27) { /* ASCII for ESC key */
    fputc(ch, file);
}

  fclose(file);
  disableRawMode(&orig_termios);

	return 0; /* indicates successful execution */
}
