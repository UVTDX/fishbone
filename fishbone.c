#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* disable canonical mode/ echoing */
void enableRawMode(struct termios *orig_termios) {
    tcgetattr(STDIN_FILENO, orig_termios); /* takes current terminal attr & makes copy to modify */
    struct termios raw = *orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); /* set new attr */
}


void disableRawMode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios); /* restore original attr */
}


int main() {
  struct termios orig_termios;
	enableRawMode(&orig_termios);

  /* open file for writing */
  FILE *file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("Failed to open file");
    exit(EXIT_FAILURE);
  }

  /* read and write input until ESC is pressed */
	char ch;
	while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 27) { /* ASCII for ESC key */
    fputc(ch, file);
}

  fclose(file);
  disableRawMode(&orig_termios);

	return 0; /* indicates successful execution */
}
