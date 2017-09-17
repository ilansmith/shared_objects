#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "ias.h"

#define SO_FILE "ias.so"
#define PWD "PWD"

typedef int (*func_hello_t)(char *subject);
typedef int (*func_goodbye_t)(char *subject);
typedef int (*func_hidden_t)(void);

static func_hello_t hello;
static func_goodbye_t goodbye;
static func_hidden_t hidden;

static int unload_ias(void *handle)
{
	hello = NULL;
	goodbye = NULL;
	hidden = NULL;

	return dlclose(handle);
}

static int load_ias(void **handle)
{
	int ret_val = -1;
	char *pwd;
	char so_file[256];

	if (!(pwd = getenv(PWD)))
		return -1;

	sprintf(so_file, "%s/%s", pwd, SO_FILE);
	printf("Loading: %s\n", so_file);

	if (!(*handle = dlopen(so_file, RTLD_LAZY)))
		return -1;

	if (!(hello = (func_hello_t)dlsym(*handle, "ias_hello"))) {
		printf("failed to load ias_hello()\n");
		goto Exit;
	}

	if (!(goodbye = (func_goodbye_t)dlsym(*handle, "ias_goodbye"))) {
		printf("failed to load ias_goodbye()\n");
		goto Exit;
	}

	hidden = (func_hidden_t)dlsym(*handle, "ias_hidden");

	ret_val = 0;

Exit:
	if (ret_val)
		unload_ias(*handle);

	return ret_val;
}

static int test(void)
{
	void *handle;

	if (load_ias(&handle)) {
		printf("Error: %s\n", dlerror());
		return -1;
	}

	if (hello("world")) {
		printf("Error: hello()\n");
		return -1;
	}

	if (goodbye("world")) {
		printf("Error: goodbye()\n");
		return -1;
	}

	if (hidden) {
		printf("Error: ias_hidden() should not be exported\n");
		return -1;
	} else {
		printf("ias_hidden() is not exported\n");
	}

	if (unload_ias(handle)) {
		printf("Error: unload()\n");
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}

