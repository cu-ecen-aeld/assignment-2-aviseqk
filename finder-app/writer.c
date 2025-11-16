#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	openlog("[LOGS:writer - assignment2]", 0, LOG_USER);
	if (argc != 3) {
		fprintf(stderr, "Invalid Number of Arguments passed: %d\n", argc);
		syslog(LOG_ERR, "Invalid Number of Arguments passed: %d\n", argc);
		closelog();
		return 1;
	}

	char *writefile = argv[1];
	char *writestr = argv[2];

	// as the assignment denies the requirement of checking if the directory exists
	int fd = open(writefile, O_RDWR | O_CREAT, 0666);
	if (fd == -1) {
		fprintf(stderr, "Couldn't create file %s: %s\n", writefile, strerror(errno));
		syslog(LOG_ERR, "Couldn't create file %s: %s\n", writefile, strerror(errno));
		closelog();
		return 1;
	}

	ssize_t bytes_written = write(fd, writestr, strlen(writestr));
	if (bytes_written == -1) {
		fprintf(stderr, "Couldn't write string: %s to file %s: %s\n", writestr, writefile, strerror(errno));
		syslog(LOG_ERR, "Couldn't write string: %s to file %s: %s\n", writestr, writefile, strerror(errno));
		close(fd);
		closelog();
		return 1;
	}
	if (bytes_written != (ssize_t) strlen(writestr)) {
		fprintf(stderr, "Wrote %ld bytes, but required to write %ld bytes\n", bytes_written, strlen(writestr));
		syslog(LOG_ERR, "Wrote %ld bytes, but required to write %ld bytes\n", bytes_written, strlen(writestr));
		close(fd);
		closelog();
		return 1;
	}

	syslog(LOG_DEBUG, "Writing %s to %s\n", writestr, writefile);
	fprintf(stdout, "Writing %s to %s\n", writestr, writefile);
	close(fd);
	closelog();
	return 0;
}
