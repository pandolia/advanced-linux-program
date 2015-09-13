/* p10.3-setuid-test.c
 * Setuid Demonstration Program
 */
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("uid=%d euid=%d\n", (int)getuid(), (int)geteuid());
    return 0;
}
