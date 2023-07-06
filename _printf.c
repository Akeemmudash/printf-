#include "main.h"

/**
  * _printf - Imitates the functionality of the C's printf function.
  * @format: A formatted string.
  * Return: The number of bytes written.
  */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, size = 0;
	variable_string *sp_var;
	char c[2] = {0}, buffer[BUFF_SIZE] = {0};

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	
	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] == '%')
		{
			sp_var = check_specifier(&format[i], args);
			if (sp_var && sp_var->string)
			{
				check_buffer(buffer, sp_var->string);
				size += strlen(sp_var->string);
				i += (sp_var->i + 1);
				free(sp_var->string);
				free(sp_var);
				continue;
			}
		}
		c[0] = format[i];
		check_buffer(buffer, c);
		size++;
		i++;
	}
	va_end(args);
	write(1, buffer, strlen(buffer));
	return (size);
}
