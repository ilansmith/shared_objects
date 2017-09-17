#include <stdio.h>
#include "ias.h"

static int speak(char *greeting, char *subject)
{
	if (!subject)
		return -1;

	printf("%s %s!\n", greeting, subject);
	return 0;
}

int ias_hello(char *subject)
{
	return speak("hello", subject);
}

int ias_goodbye(char *subject)
{
	return speak("goodbye", subject);
}

int ias_hidden(void)
{
	return speak("hidden", "you should never see this");
}

