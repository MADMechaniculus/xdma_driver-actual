#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	int fd = -1;
	char * filename;
	if ((argc < 2) || (argc > 3)) {
		printf("Usage %s <device file>\n", argv[0]);
		return -1;
	}

	filename = argv[1];
	fd = open(filename, O_RDWR);

	if (fd < 0) {
		perror("Open file descriptor error!\n");
		return fd;
	}

	printf("Device \"%s\" is opened!\n", filename);

	u_int32_t testReg = 0;
	lseek(fd, 0x41000, SEEK_SET);
	read(fd, &testReg, sizeof (u_int32_t));
	printf("Value stored into %p => %x\n", (void*)0x41000, testReg);

	if (close(fd)) {
		perror("Closing error!\n");
		return -2;
	}

	printf("Done!\n");
	return 0;
}
