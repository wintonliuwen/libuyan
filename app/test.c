#include <lwzy.h>

int main(int argc, char **argv)
{
       pid_t pid = getPidByName(argv[1]);
       if (pid > 0)
       {
               printf("%s pid :%d\n", argv[1], pid);
       }
       else
       {
               printf("can't get %s\n", argv[1]);
       }
       return 0;
}

