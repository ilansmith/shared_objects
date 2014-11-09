#include <stdio.h>
#include "ias.h"

static int speak(char *greeting, char *subject)
{
	if (!subject)
		return -1;

	printf("%s %s!\n", greeting, subject);
	return 0;
}

int hello(char *subject)
{
	return speak("hello", subject);
}

int goodbye(char *subject)
{
	return speak("goodbye", subject);
}

