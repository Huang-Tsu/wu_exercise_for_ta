#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int RmNewLine(char *input);
void Swap(char *input, int idx1, int idx2);
void Reverse(char *input);

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
	if(RmNewLine(buffer))
		read_size --;

	Reverse(buffer);

	lseek(fd, 0, SEEK_SET);			//回到起頭
	write(fd, buffer, read_size);

	close(fd);

	free(buffer);

	return 0;
}
void Reverse(char *input){
	int len = strlen(input);
	for (int i=0, j=len-1; i<=j; i++, j--){
		Swap(input, i, j);
	}
}
void Swap(char *input, int idx1, int idx2){
	char temp = input[idx1];
	input[idx1] = input[idx2];
	input[idx2] = temp;
}
int RmNewLine(char *input){
	int len = strlen(input);
	if(input[len-1] == '\n'){
		input[len-1] = '\0';
		return 1;
	}

	return 0;
}
