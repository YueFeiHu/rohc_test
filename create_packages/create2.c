/* A program to produce binary files from the output of the tcpdump command.
 *
 *   use like this to create 10 udp packages
 *   tcpdump -c 10 -s 0 -e -n -x -S udp | ./create2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0644

unsigned char decode(char *hexchar);
unsigned char converthex(char hex);
char *begin = "flow-";
char *end = "-ip.bin";

int main(int argc, char **argv)
{
	char *input = malloc(sizeof(char *) * 900);
	char *input2 = malloc(sizeof(char *) * 900);
	char *separate = malloc(sizeof(char *) * 3);
	char *ans = malloc(sizeof(char *) * 4);
	char *tmp = malloc(sizeof(char *) * 3);
	char *buf = malloc(sizeof(char *) * 4);
	char filename[300];

	int counter = 1;
	int filedes;
	int count = 0;
	int size = 0;
	ssize_t w1;

	unsigned char a[2];

	separate[0] = '\t';
	separate[2] = ' ';
	separate[1] = '\n';

	sprintf(buf, "%i", counter);

	strcpy(filename, begin);
	strcat(filename, buf);
	strcat(filename, end);

	if ((filedes = open(filename, O_RDWR | O_CREAT | O_TRUNC, PERMS)) == -1)
	{
		printf("Couldn't create %s\n", filename);
		exit(1);
	}
	input2 = fgets(input, 800, stdin);

	while (input2 != NULL)
	{
		input2 = fgets(input, 100, stdin);
		if ((input[0] == '\t') && (input2 != NULL))
		{

			ans = (strtok(input, separate));
			while (ans != NULL)
			{
				if (count == 1)
				{
					size = converthex(ans[2]) * 16 + converthex(ans[3]);
				}
				tmp[0] = ans[0];
				tmp[1] = ans[1];
				tmp[2] = '\0';
				a[0] = decode(tmp);
				if (ans[2] != '\0')
				{
					tmp[0] = ans[2];
					tmp[1] = ans[3];
					tmp[2] = '\0';
					a[1] = decode(tmp);
					w1 = write(filedes, a, 2);
				}
				else
				{
					a[1] = '\0';
					w1 = write(filedes, a, 1);
				}
				ans = (strtok(NULL, separate));
				count++;
			}
		}
		else if (input2 != NULL)
		{
			counter++;
			count = 0;
			close(filedes);
			sprintf(buf, "%i", counter);
			strcpy(filename, begin);
			strcat(filename, buf);
			strcat(filename, end);
			if ((filedes = open(filename, O_RDWR | O_CREAT | O_TRUNC, PERMS)) == -1)
			{
				printf("Couldn't create %s\n", filename);
				exit(1);
			}
			input2 = fgets(input, 500, stdin);
		}
	}
	printf("%d packets created \n", counter);
	free(input);
	free(input2);
	free(separate);
	free(ans);
	free(tmp);
	free(buf);
	return 0;
}

unsigned char decode(char *hexchar)
{
	int i = 0;
	i = converthex(hexchar[0]);
	i = i * 16 + converthex(hexchar[1]);
	return i;
}
unsigned char converthex(char hex)
{
	int temp = 0;
	switch (hex)
	{
	case 'a':
		temp = 10;
		break;
	case 'b':
		temp = 11;
		break;
	case 'c':
		temp = 12;
		break;
	case 'd':
		temp = 13;
		break;
	case 'e':
		temp = 14;
		break;
	case 'f':
		temp = 15;
		break;
	default:
		temp = hex - 48;
		break;
	}
	return temp;
}
