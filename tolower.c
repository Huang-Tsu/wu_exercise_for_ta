#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void ToLower(char *input);

int main(int argc, char **argv){
	int fd;
	int read_size;
	char *buffer;

	fd = open(argv[1], O_RDWR);
	if(fd == -1){
		fprintf(stderr, "open error:%s\n", argv[1]);
		exit(1);
	}

	read_size = lseek(fd, 0, SEEK_END);

	lseek(fd, 0, SEEK_SET);			//回到起點
	buffer = (char*)calloc(read_size+1, sizeof(char));

	read(fd, buffer, read_size);
	buffer[read_size] = '\0';

	ToLower(buffer);

	lseek(fd, 0, SEEK_SET);			//回到起頭
	write(fd, buffer, read_size);

	close(fd);

	free(buffer);

	return 0;
}
void ToLower(char *input){
	int len = strlen(input);
	for (int i=0; i<len; i++){
		if(isalpha(input[i]))
		input[i] = tolower(input[i]);
	}
}
