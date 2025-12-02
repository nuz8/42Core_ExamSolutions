#include "get_next_line.h"

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

char	*join_parts(char *s1, char *s2)
{
	char*	joined_str;
	char	*s_ptr[2];
	size_t	s_len[2], len, i;
	s_len[0] = line_length(s1);
	s_len[1] = line_length(s2);
	len = s_len[0] + s_len[1];
	joined_str = malloc((len + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = 0;
	s_ptr[0] = s1;
	s_ptr[1] = s2;
	while (i < s_len[0])
		joined_str[i++] = *s1++;
	while (i > s_len[0] && i < len)
		joined_str[i++] = *s2++;
	joined_str[i] = '\0';
	return (free(s_ptr[0]), free(s_ptr[1]), joined_str);
}

char	*copy_n_shift(char *buffer)
{
	char	*line_part;
	char	*buf_ptr;
	size_t	i, line_len;
	if (!buffer)
		return (NULL);
	line_len = line_length(buffer);
	line_part = malloc((line_len + 1) * sizeof(char));
	if (!line_len)
		return (NULL);
	i = 0;
	buf_ptr = buffer;
	while (*buffer && i < line_len)
		line_part[i++] = *buffer++;
	line_part[i] = '\0';
	while (*buffer)
		*buf_ptr++ = *buffer++;
	*buf_ptr = *buffer;
	return (line_part);
}

char	*extract_rest(char *next_line, char *buffer, int fd)
{
	ssize_t bytes_read;
	char	*line_part;
	char	*joined_line;
	while (next_line[line_length(next_line) - 1] != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(next_line), NULL);
		else if (bytes_read == 0)
			return (next_line);
		buffer[bytes_read] = '\0';
		line_part = copy_n_shift(buffer);
		if (!line_part)
			return (free(next_line), NULL);
		joined_line = join_parts(next_line, line_part);
		if (!joined_line)
			return (free(next_line), free(line_part), NULL);
		next_line = joined_line;
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	char		*joined_line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!*buffer)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
	}
	next_line = copy_n_shift(buffer);
	if (!next_line)
		return (NULL);
	if (next_line[line_length(next_line) - 1] != '\n')
	{
		joined_line = extract_rest(next_line, buffer, fd);
		if (!joined_line)
			return (NULL);
		next_line = joined_line;
	}
	return (next_line);
}
