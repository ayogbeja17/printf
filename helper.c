#include  "main.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * _puts - prints a string to stdout
 * @buffer: pointer to buffer
 * @size: size of buffer
 * Return: void
 */
void _puts(char *buffer, int size)
{
	write(1, buffer, size);
}

/**
 * _memcpy - copies memory area
 * @dest: destination pointer
 * @src: source pointer
 * @n: number of bytes to copy
 * @bufferlen: size of buffer
 * Return: pointer to destination
 */
char *_memcpy(char *dest, char *src, unsigned int n, unsigned int bufferlen)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
		if (i + 1 == bufferlen)
		{
			_puts(dest, bufferlen);
			dest = dest - bufferlen;
			bufferlen = BUFSIZE;
		}
	}
	return (dest);
}

/**
 * _printf - prints formatted output to stdout
 * @format: format string to print
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list arg_list;
	int i, j, len = 0, buf_len = 0, conv_len = 0;
	char buffer[BUFSIZE], *hold, *temp, *final_string;
	char *(*valid_type_func)(va_list);
	int  total_chars = 0;

	if (format == NULL)
		return (-1);
	va_start(arg_list, format);
	for (i = 0; format[i]; i++)
	{
		if (format[i] != '%')
		{
			buffer[buf_len++] = format[i];
			if (buf_len == BUFSIZE)
			{
				_puts(buffer, BUFSIZE);
				buf_len = 0;
				total_chars += BUFSIZE;
			}
			continue;
		}
		len++;
		i++;
		while (format[i] == ' ')
			i++;
		if (!format[i])
			return (-1);
		valid_type_func = get_valid_type(format[i]);
		if (valid_type_func == NULL)
		{
			if (format[i] == '\0')
				return (-1);
			hold = found_nothing(format[i]);
			len += 2;
			temp = hold;
		}
		else
		{
			temp = valid_type_func(arg_list);
			conv_len = _strlen(temp);
			if (conv_len == 0)
				return (-1);
			len += conv_len - 2;
		}
		buf_len = alloc_buffer(temp, conv_len, buffer, buf_len, &total_chars);
	}
	_puts(buffer, buf_len);
	total_chars += buf_len;
	va_end(arg_list);
	final_string = malloc(total_chars + 1);
	if (final_string == NULL)
		return (-1);
	final_string[total_chars] = '\0';
	_puts(buffer, total_chars);
	for (j = 0; j < total_chars; j++)
		final_string[j] = buffer[j];
	buf_len = 0;
	free(final_string);
	return (len + 1);
}
