#include"Platform.h"

int Random() {
	srand(unsigned int(omp_get_wtime()));
	return rand();
}



int StringToInt(std::string s) {

	if (s.compare("0") == 0) {
		return 0;
	}
	else if (s.compare("1") == 0) {
		return 1;

	}
	else if (s.compare("2") == 0) {
		return 2;

	}
	else if (s.compare("3") == 0) {
		return 3;

	}
	else if (s.compare("4") == 0) {
		return 4;

	}
	else if (s.compare("5") == 0) {
		return 5;

	}
	else if (s.compare("6") == 0) {
		return 6;

	}
	else if (s.compare("7") == 0) {
		return 7;

	}
	else if (s.compare("8") == 0) {
		return 8;

	}
	else if (s.compare("9") == 0) {
		return 9;

	}
}

char* _printf_convert(unsigned int num, int base)
{
	static char Representation[] = "0123456789ABCDEF";
	static char buffer[50];
	char* ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num % base];
		num /= base;
	} while (num != 0);

	return(ptr);
}

void _printf(char* format, ...)
{
	char* traverse;
	int i;
	char* s;
	std::string output;

	//Module 1: Initializing Myprintf's arguments 
	va_list arg;
	va_start(arg, format);

	for (traverse = format; *traverse != '\0'; traverse++)
	{
		while (*traverse != '%' && *traverse != '\0')
		{
			output += *traverse; // Append char to current string.
			traverse++;
		}

		traverse++;

		//Module 2: Fetching and executing arguments
		switch (*traverse)
		{

		case 'c': i = va_arg(arg, int);		//Fetch char argument

			output += _printf_convert((i - 48), 10); // Variables under %c should be from '1'|...|'9'.
			break;

		case 'd': i = va_arg(arg, int); 		//Fetch Decimal/Integer argument
			if (i < 0)
			{
				i = -i;
				output += '-';
			}
			output += _printf_convert(i, 10);
			break;

		case 'o': i = va_arg(arg, unsigned int); //Fetch Octal representation
			output += _printf_convert(i, 8);
			break;

		case 's': s = va_arg(arg, char*); 		//Fetch string
			output += s;
			break;

		case 'x': i = va_arg(arg, unsigned int); //Fetch Hexadecimal representation
			output += _printf_convert(i, 16);
			break;
		}
	}

	//Module 3: Closing argument list to necessary clean-up
	// Module 3.1: Output the generated string.
	puts(output.c_str());
	va_end(arg);
}