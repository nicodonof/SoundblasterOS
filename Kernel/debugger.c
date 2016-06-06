#include <serial.h>
#include <debugger.h>

void send_debug_msg(const char* s) {
	for (int i = 0; s[i] != 0; i++) {
		write_serial(s[i]);
	}
}

void send_debug_newline() {
	write_serial('\n');
}