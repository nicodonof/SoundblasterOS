#include <types.h>
#include <serial.h>
#include <debugger.h>
#include <stdarg.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
int strlen(const char * s);
void itoc(int number, char str[]);
static char buffer[64] = { '0' };

void sPrint(const char* s) {
	for (int i = 0; s[i] != 0; i++) {
		write_serial(s[i]);
	}
}

void sPrintNl() {
	write_serial('\n');
}

void sPrintDec(uint64_t value)
{
	sPrintBase(value, 10);
}

void sPrintHex(uint64_t value)
{
	sPrintBase(value, 16);
}

void sPrintBin(uint64_t value)
{
	sPrintBase(value, 2);
}

void sPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    sPrint(buffer);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


//vprintf, printf y itoc sacados de https://github.com/sebikul/UnicOS/blob/5d9392625332343ccfcfdc20fb58c2adb5176ca6/Userland/libc/libc.c
static void vfprintf(int fd, char* fmt, va_list ap) {

	char str[1024];
	int i = 0;
	int j = 0;

	// i: posicion en el fmt
	// j: posicion en el str
	while (fmt[i] != 0 && i < 1024 - 1) {

		if (fmt[i] == '%') {

			int flag_zero = 0;
			uint32_t width = 0;
			int is_long = 0;

			i++;
			if (fmt[i] == 0) {
				//lo que le sigue al % es el final de la cadena
				str[j] = fmt[i];
				break;

			} else if (fmt[i] == '%') {

				str[j] = fmt[i];
				j++;
				i++;

			} else {
				// hay que procesar el siguiente caracter y actuar acorde
				int flag;
				do {
					flag = 0;
					switch (fmt[i]) {
					case 's': {
						//lo que se desea es imprimir una cadena
						char* arg = va_arg(ap, char*);
						int k = 0;

						//k: posicion en el argumento

						while (arg[k] != 0) {
							str[j++] = arg[k++];
						}

						if (width > 0) {
							int spaces = width - strlen(arg);
							while (spaces > 0) {
								str[j++] = ' ';
								spaces--;
							}
						}

						i++;
						break;
					}

					case 'l':
						is_long = 1;
						i++;
						flag = 1;
						break;


					case 'd': {

						long int arg;

						if (is_long) {
							arg = va_arg(ap, long int);
						} else {
							arg = (long int)va_arg(ap, int);
						}
						char number[10] = {0,0,0,0,0,0,0,0,0,0};
						itoc(arg, number);
						int k = 0;

						uint32_t numlen = strlen(number);

						// if (arg < 0) {
						// 	str[j++] = '-';
						// }

						//k: posicion en el argumento

						while (number[k] != 0) {
							str[j++] = number[k++];
						}

						if (numlen < width) {

							char chartowrite;
							int numtowrite = width - numlen;

							if (flag_zero) {
								chartowrite = '0';

							} else {
								chartowrite = ' ';
							}

							for (int i = 0; i < numtowrite; i++) {
								str[j++] = chartowrite;
							}
						}

						i++;
						break;
					}

					case 'c': {

						char arg = (char)va_arg(ap, int);

						str[j++] = arg;
						i++;
						break;
					}

					case 'x': {

						char buffer[128] = { 0 };

						uint64_t arg = va_arg(ap, uint64_t);
						uint32_t digits = uintToBase(arg, buffer, 16);

						for (uint32_t i = 0; i < digits; i++) {
							str[j++] = buffer[i];
						}

						i++;
						break;
					}

					case '0':
						if (width == 0) {
							if (!flag_zero) {
								flag_zero = 1;
								i++;
								flag = 1;
								break;
							}
							break;
						}


					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						if (width > 0) {
							width *= 10;
						}
						width += fmt[i] - '0';
						i++;
						flag = 1;
						break;

					}

				} while (flag);
			}

		} else if (fmt[i] != 0) {
			str[j] = fmt[i];
			j++;
			i++;
		} else {
			str[j] = fmt[i];
			break;
		}
	}
	str[j] = 0;
	sPrint(str);

}

void sPrintf(char* fmt, ...) {

	va_list ap;
	va_start(ap, fmt);

	vfprintf(1, fmt, ap);

	va_end(ap);
}

int strlen(const char * s){
    int n=0;
    while(*s++ != 0)
        n++;
    return n;
}

void itoc(int number, char str[]) {

	int i = 0;
	int j = 0;
	int cnt = 0;


	if (number < 0) {
		number = -number;
		str[i++] = '-';
	}

	while (number >= 10 ) {
		int dig = number % 10;
		number /= 10;
		str[i++] = dig + '0';
		cnt++;
	}
	str[i] = number + '0';

	while (cnt >= j) {
		char aux;
		aux = str[cnt];
		str[cnt--] = str[j];
		str[j++] = aux;
	}
}
