#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc != 3){
		printf("%s msg driver", argv[0]);
		return -1;
	}
	int rt, fd;
	fd = open(argv[2] , O_RDWR);
	if(fd < 0){
		perror("Irgendwas ist schiefgegangen!");
		return errno;
	}
	rt = write(fd, argv[1] , strlen(argv[1]));
	if(rt < 0){
		perror("Irgendwas ist schiefgegangen!");
		return errno;
	}
	return 0;
}
