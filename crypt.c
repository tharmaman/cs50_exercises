#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // checking if only one argument was entered
    if (argc == 2)
    {
        // storing string as code
        string h = argv[1];
        int hlength = strlen(h);

        // creating array of alphanumeric ASCII characters (including SPACE)
        char alphanum[95];


        for (int i = 0; i < 95; i++ )
        {
            alphanum[i] = (char) (i + 32);
        }


        if (hlength == 13)
        {
            // extracting salt from encrypted password
            char salt[3];
            salt[0] = h[0];
            salt[1] = h[1];
            salt[2] = '\0';
            // eprintf("%s\n", salt);
            // eprintf("%s\n",h);


            // checking passwords which are one character long
            for (int k = 0; k < 95; k++)
            {
                char test[2];
                test[0] = alphanum[k];
                test[1] = '\0';
                // eprintf("%s\n",test);
                // eprintf("%s\n",crypt(test,salt));
                if (strcmp(crypt(test, salt), h) == 0)
                {
                    printf("Hacked it my G!\nPassword is: %s\n", test);
                    return 0;
                }
            }


            // checking passwords which are two characters long
            for (int k = 0; k < 95; k++)
            {
                for (int l = 0; l < 95; l++)
                {
                    char test[3];
                    test[0] = alphanum[k];
                    test[1] = alphanum[l];
                    test[2] = '\0';
                    if (strcmp(crypt(test, salt), h) == 0)
                    {
                        printf("Hacked it my G!\nPassword is: %s\n", test);
                        return 0;
                    }
                }
            }

            // checking passwords which are three characters long
            for (int k = 0; k < 95; k++)
            {
                for (int l = 0; l < 95; l++)
                {
                    for (int m = 0; m < 95; m++)
                    {
                        char test[4];
                        test[0] = alphanum[k];
                        test[1] = alphanum[l];
                        test[2] = alphanum[m];
                        test[3] = '\0';
                        if (strcmp(crypt(test, salt), h) == 0)
                        {
                            printf("Hacked it my G!\nPassword is: %s\n", test);
                            return 0;
                        }
                    }
                }
            }

            // checking passwords which are four characters long
            for (int k = 0; k < 95; k++)
            {
                for (int l = 0; l < 95; l++)
                {
                    for (int m = 0; m < 95; m++)
                    {
                        for (int n = 0; n < 95; n++)
                        {
                            char test[5];
                            test[0] = alphanum[k];
                            test[1] = alphanum[l];
                            test[2] = alphanum[m];
                            test[3] = alphanum[n];
                            test[4] = '\0';
                            if (strcmp(crypt(test, salt), h) == 0)
                            {
                                printf("Hacked it my G!\nPassword is: %s\n", test);
                                return 0;
                            }
                        }
                    }
                }
            }

            // checking passwords which are five characters long
            for (int k = 0; k < 95; k++)
            {
                for (int l = 0; l < 95; l++)
                {
                    for (int m = 0; m < 95; m++)
                    {
                        for (int n = 0; n < 95; n++)
                        {
                            for (int o = 0; o < 95; o++)
                            {
                                char test[6];
                                test[0] = alphanum[k];
                                test[1] = alphanum[l];
                                test[2] = alphanum[m];
                                test[3] = alphanum[n];
                                test[4] = alphanum[o];
                                test[5] = '\0';
                                if (strcmp(crypt(test, salt), h) == 0)
                                {
                                    printf("Hacked it my G!\nPassword is: %s\n", test);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
            // if crack failed
            printf("Crack failed \n");
            return 1;
        }
        // error if hash != 13
        else
        {
            printf("ayo only a 13 letter hashed password is accepted \n");
        }
    }
    // if argc != 2
    else
    {
        printf("Error dawg moss \n");
        return 1;
    }
}