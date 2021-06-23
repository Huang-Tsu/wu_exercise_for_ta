#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd;
	int read_size;
	char *buffer;

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		fprintf(stderr, "open error:%s\n", argv[1]);
		exit(1);
	}
	read_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	buffer = (char*)calloc(read_size, sizeof(char));
	read(fd, buffer, read_size);
	close(fd);

	fd = open(argv[2], O_RDWR | O_CREAT, 0600);
	if(fd == -1){
		fprintf(stderr, "open error:%s\n", argv[1]);
		exit(1);
	}
	write(fd, buffer, read_size);
	close(fd);

	free(buffer);

	return 0;
}
