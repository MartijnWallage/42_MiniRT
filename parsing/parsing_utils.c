void	free_str_array(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
		free(chars[i++]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while
}
int	get_str_array_len(char **chars)
{
	int i;

	i = 0;
	while (chars[i])
		i++;
	return (i);
}