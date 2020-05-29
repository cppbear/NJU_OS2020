#include "lib.h"
#include "types.h"

int uEntry(void) {
	char ch;
	printf("Input: 1 for bounded_buffer\n       2 for philosopher\n       3 for reader_writer\n");
	scanf("%c", &ch);
	switch (ch) {
		case '1':
			exec("/usr/bounded_buffer", 0);
			break;
		case '2':
			exec("/usr/philosopher", 0);
			break;
		case '3':
			exec("/usr/reader_writer", 0);
			break;
		default:
			break;
	}
	exit();
	return 0;
}
