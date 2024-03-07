#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

ssize_t my_write_wrapper(int fd, const void *buf, size_t count) {
	return syscall(SYS_write, fd, buf, count);
}

int main() {
	const char *buf_str = "Hello world";
	size_t str_length = strlen(buf_str);
	my_write_wrapper(1, buf_str, str_length);
	return 0;
}
