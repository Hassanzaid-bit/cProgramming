#include <stdio.h>
#include <windows.h>

void fatal(const char *message)
{
    // Display error message and exit
    perror(message);
    exit(EXIT_FAILURE);
}

int main()
{
    char username[256];
    DWORD usernameSize = sizeof(username);

    if (!GetUserName(username, &usernameSize))
    {
        printf("Error getting the username.\n");
        return 1;
    }

    printf("Username: %s\n", username);

    return 0;
}
