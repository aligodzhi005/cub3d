#include "get_next_line.h"
#include <stdio.h>

typedef struct set_data
{
	int		sW;
	int		sH;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
	int		floor;
	int		ceilling;
	int		mapW;
	int		mapH;
}				settings;

int checkWhtSpc(char chr)
{
	if(chr != ' ' && chr != '\t' 
		&& chr != '\n' && chr != '\v'
		&& chr != '\f' && chr != '\r')
		return(0);
	return (1);
}

int lineEmptyOrNot(char *line)
{
	int i = 0;
	while (line[i] != '\0')
	{
		if(checkWhtSpc(line[i]) == 0)
			return(0);
		i++;
	}
	return(1);
}

int line_correction(const char *line)
{
	size_t i;
	int isSpace;
	char *tmp;

	i = 0;
	tmp = (char *)line;
	if(!line)
		return(0);
	while(tmp[i] != '\0')
	{
		// if(ft_isprint(tmp[i]) == 0 || tmp[i] == '"')
		if(checkWhtSpc(tmp[i]) == 1)
			tmp[i] = ' ';
		i++;
	}
	return(i);
}

int printRepeatErr(void)
{
	printf("Error\nRepeatable type indentifier\n");
	return(1);
}

int check_resolution_number(char *widthOrLength)
{
	int i;
	i = 0;
	while (i < ft_strlen((const char *)widthOrLength))
	{
		if(ft_isdigit(widthOrLength[i]) == 0 || i >= 5)
		{
			printf("Error:\nBad resolution\n");
			return(1);
		}
		i++;
	}
	return(0);
}

int checkResNumber(char **res, int number, int length)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(res[i][j])
		j++;
	if(j != length)
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	while(res[i])
		i++;
	if(i != number)
	{
		printf("Error\nBad number of arguments\n");
		return(1);
	}
	return(0);
}

char	**ft_free_res(char **res)
{
	int k;

	k = 0;
	while (res[k] != NULL)
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

int set_resolution(const char *line, settings *settings)
{
	char **res;

	
	line_correction(line);
	if(settings->sW != 0 && settings->sH != 0)
		return(printRepeatErr());
	res = ft_split(line, ' ');
	if(res[0][1] != '\0' || res[0][0] != 'R')
	{
		printf("Error\nBad argument\n");
		return(1);
	}
	if(check_resolution_number(res[1]) == 1 || 
		checkResNumber(res, 3, 1) == 1)
		return(1);
	if(check_resolution_number(res[2]) == 1)
		return(1);
	settings->sW = ft_atoi(&res[1]);
	settings->sH = ft_atoi(&res[2]);
	ft_free_res(res);
	return(0);
}

int	check_line(const char *line, settings *settings)
{
	size_t line_length;
	int i;

	i = 0;
	// line_length = checkSettings(settings, line);
	// if(line_length == 1)
	// 	return(0);
	// else if(line_length == 2)
	// 	return(2);
	// line_length = line_correction(line);
	// if(line_length > settings->mapW)
	// 	settings->mapW = line_length;
	while(line[i])
	{
		// if(ft_strchr("RNSWEFC", line[i]) == NULL)
		// 	if(checkWhtSpc(*line) == 0)
		// 	{
		// 		printf("Error\nBad argument\n");
		// 		return(1);	
		// 	}
		if(line[i] == 'R')
		// if(ft_strnstr(line, "R", line_length))
		{
			if (set_resolution(line, settings) == 1)
				return(1);
			else
				return(2);
		}
		// else if(ft_strchr("FC", line[i]) != NULL)
		// // else if(ft_strnstr(line, "S ", line_length))
		// {
		// 	if(setColFC(&line[i], settings) != 0)
		// 		return(1);
		// 	else
		// 		return(2);
		// }
		// else if(ft_strchr("NSWE", line[i]) != NULL)
		// // else if(ft_strchr("NSWE", line[i]) != NULL && ft_strchr("OAE", line[i + 1]) != NULL)
		// {
		// 	if(setTex(&line[i], settings, 2) == 0)
		// 		return(2);
		// 	else
		// 		return(1);
		// }
		i++;
	}
	printf("Error\nBad argument\n");
	return(1);
}

int main(int argc, char **argv)
{
	settings	settings;
	settings.sW = 0;
	settings.sH = 0;
	settings.NO = NULL;
	settings.SO = NULL;
	settings.WE = NULL;
	settings.EA = NULL;
	settings.S = NULL;
	settings.floor = -1;
	settings.ceilling = -1;
	settings.mapH = 0;
	settings.mapW = 0;
	int res_check_line;
	char *line;

	line = NULL;
	int fd = open("checkLeaks.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		res_check_line = check_line((const char *)line, &settings);
		// if(res_check_line == 0)
		// 	ft_lstadd_back(&head, ft_lstnew(line));
		if(res_check_line == 1)
			return(0);
	}
}