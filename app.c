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
	int ret = -1;

	if (load_ias(&handle)) {
		printf("Error: %s\n", dlerror());
		return -1;
	}

	if (hello("world")) {
		printf("Error: hello()\n");
		goto exit;
	}

	if (goodbye("world")) {
		printf("Error: goodbye()\n");
		goto exit;
	}

	if (hidden) {
		printf("Error: ias_hidden() should not be exported\n");
		goto exit;
	} else {
		printf("ias_hidden() is not exported\n");
	}

	ret = 0;

exit:
	if (unload_ias(handle)) {
		printf("Error: unload()\n");
		ret = -1;
	}

	return ret;
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}

