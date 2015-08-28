// Listing 5.9 (popen.c) Example Using popen

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	FILE* stream = popen("sort", "w");
	fprintf(stream, "This is a test.\n"
					"Hello, world.\n"
					"My dog has fleas.\n"
					"This program is great.\n"
					"One fish, two fish.\n");
	return pclose(stream);
}