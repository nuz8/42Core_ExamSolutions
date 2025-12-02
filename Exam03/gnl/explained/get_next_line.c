#include "get_next_line.h"

char	*get_next_line(int fd);
char	*copy_n_shift(char *buffer);
char	*extract_rest(next_line, buffer, fd);
size_t	line_length(char *str);
char	*join_parts(char *s1, char *s2);

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	char		*joined_line;

	// Part 1: Check and protect if fd or BUFFER_SIZE are invalid 
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Part 2: Read into the buffer for the first time by checking that it has
	// not already been done before this call. Also, check if any bytes are left
	// to be read, and null-terminate the buffer right after read bytes.
	if (!*buffer)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}

	// Part 3: Assign the memory address to the line read, to next_line pointer
	// Also protect if anything fails in the assigning function
	next_line = copy_n_shift(buffer);
	if (!next_line)
		return (NULL);

	// Part 4: Check if next_line has a \n at its end. If yes, simply return
	// next_line pointer, else call the extract_rest function to join the rest
	// part until the \n character or the EOF is found.
	// Also, protect if somthing fails in the extracting function.
	if (next_line[line_length(next_line) - 1] != '\n')
	{
		joined_line = extract_rest(next_line, buffer, fd);
		if (!joined_line)
			return (NULL);
		next_line = joined_line;
	}
	return (next_line);
}

// copy_n_shift():
// Function to copy contents of the buffer to a new allocated 
// memory address until a \n line is found, otherwise everything is copied.
// Also, if \n is found, shift the contents of the buffer beyond the \n to the
// beginning of the buffer.
char	*copy_n_shift(char *buffer)
{
	char	*line_part;
	char	*buf_ptr;
	size_t	i;
	size_t	line_len;

	// Return null if buffer is null
	if (!buffer)
		return (NULL);
	
	// Count the line-length until \n is found, and malloc with that size
	line_len = line_length(buffer);
	line_part = malloc((line_len + 1) * sizeof(char));
	if (!line_len)
		return (NULL);
	
	// Copy the contents of the buffer until \n is found, to the line_part pointer
	i = 0;
	buf_ptr = buffer;
	while (*buffer && i < line_len)
		line_part[i++] = *buffer++;
	line_part[i] = '\0';
	
	// Shift the contents of the buffer beyond \n to the front of the buffer and
	// also copy the null-terminator of the buffer
	while (*buffer)
		*buf_ptr++ = *buffer++;
	*buf_ptr = *buffer;
	return (line_part);
}

// line_length():
// Function to return the number of characters in the string until \n is found
// If \n is not found, it behaves the same way as strlen funciton
size_t	line_length(char *str)
{
	size_t	i;

	if (!str)
		return (0);

	i = 0;
	while (*str && *str != '\n')
	{
		str++;
		i++;
	}

	if (*str == '\n')
		i++;
	return (i);
}

// extract_rest():
// Function to extract the rest of the line until the next \n character by
// repeatedly reading and joining to the line_parts read beforehand. If \n is
// not found, it keeps reading and joining until the EOF is encountered.
char	*extract_rest(char *next_line, char *buffer, int fd)
{
	ssize_t bytes_read;
	char	*line_part;
	char	*joined_line;

	while (next_line[line_length(next_line) - 1] != '\n')
	{
		// Read more bytes from fd if available and null-terminate the buffer
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(next_line), NULL);
		else if (bytes_read == 0)
			return (next_line);
		buffer[bytes_read] = '\0';

		// Use copy_n_shift to get the new line_part
		line_part = copy_n_shift(buffer);
		if (!line_part)
			return (free(next_line), NULL);

		// Join the new line_part to the next_line pointer using join_parts fn
		// and assign it to the joined_line pointer
		joined_line = join_parts(next_line, line_part);
		if (!joined_line)
			return (free(next_line), free(line_part), NULL);
		next_line = joined_line;
	}
	return (next_line);
}

char	*join_parts(char *s1, char *s2)
{
	char	*joined_str;
	char	*s_ptr[2];
	size_t	s_len[2];
	size_t	len;
	size_t	i;

	// Count the lengths of s1 and s2, and malloc joined_str with total length
	s_len[0] = line_length(s1);
	s_len[1] = line_length(s2);
	len = s_len[0] + s_len[1];
	joined_str = malloc((len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);

	// Copy all contents of both strings into joined_str, and null-terminate it
	i = 0;
	s_ptr[0] = s1;
	s_ptr[1] = s2;
	while (i < s_len[0])
		joined_str[i++] = *s1++;
	while (i > s_len[0] && i < len)
		joined_str[i++] = *s2++;
	joined_str[i] = '\0';

	// Free received str pointers and return the new joined_str pointer
	return (free(s_ptr[0]), free(s_ptr[1]), joined_str);
}
