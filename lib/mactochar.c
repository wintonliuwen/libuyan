#include <lwzy.h>

int mac_str_to_bin( char *str, char *mac)
{
    int i;
    char *s, *e; 

    if ((mac == NULL) || (str == NULL))
    {   
        return -1; 
    }   

    s = (char *) str;
    for (i = 0; i < 6; ++i)
    {   
        mac[i] = s ? strtoul (s, &e, 16) : 0;
        if (s) 
           s = (*e) ? e + 1 : e;
    }   
    return 0;
}

