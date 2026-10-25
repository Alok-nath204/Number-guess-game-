#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    char name[50];
    int level, max, number, guess;
    int attempts = 0;
    int maxAttempts = 10;
    int score;

    srand(time(NULL));

    printf("=================================\n");
    printf("      NUMBER GUESSING GAME\n");
    printf("=================================\n");

    printf("Enter Your Name: ");
    scanf(" %49[^\n]", name);

    printf("\nSelect Difficulty Level\n");
    printf("1. Easy (1-50)\n");
    printf("2. Medium (1-100)\n");
    printf("3. Hard (1-500)\n");
    printf("Enter Choice: ");
    scanf("%d", &level);

    if(level == 1)
        max = 50;
    else if(level == 2)
        max = 100;
    else if(level == 3)
        max = 500;
    else
    {
        printf("Invalid Level!\n");
        return 0;
    }

    number = rand() % max + 1;

    printf("\nGuess the number between 1 and %d\n", max);

    while(attempts < maxAttempts)
    {
        printf("Enter Guess: ");
        scanf("%d", &guess);

        attempts++;

        if(guess == number)
        {
            score = (maxAttempts - attempts + 1) * 10;

            printf("\nCongratulations %s!\n", name);
            printf("Correct Number = %d\n", number);
            printf("Attempts = %d\n", attempts);
            printf("Score = %d\n", score);

            /* Save Data */
            FILE *fp = fopen("players.txt", "a");

            if(fp != NULL)
            {
                time_t t = time(NULL);
                char *dt = ctime(&t);

                fprintf(fp, "=============================\n");
                fprintf(fp, "Player Name : %s\n", name);
                fprintf(fp, "Level       : %d\n", level);
                fprintf(fp, "Attempts    : %d\n", attempts);
                fprintf(fp, "Score       : %d\n", score);
                fprintf(fp, "Date & Time : %s", dt);

                fclose(fp);

                printf("\nPlayer data saved successfully.\n");
            }

            return 0;
        }

        else if(guess > number)
            printf("Too High!\n");
        else
            printf("Too Low!\n");

        if(number % 2 == 0)
            printf("Hint: EVEN Number\n");
        else
            printf("Hint: ODD Number\n");

        printf("Remaining Attempts: %d\n\n",
               maxAttempts - attempts);
    }

    printf("\nGame Over!\n");
    printf("Correct Number = %d\n", number);

    /* Save Lost Game */
    FILE *fp = fopen("players.txt", "a");

    if(fp != NULL)
    {
        time_t t = time(NULL);
        char *dt = ctime(&t);

        fprintf(fp, "=============================\n");
        fprintf(fp, "Player Name : %s\n", name);
        fprintf(fp, "Level       : %d\n", level);
        fprintf(fp, "Attempts    : %d\n", attempts);
        fprintf(fp, "Score       : 0\n");
        fprintf(fp, "Result      : Lost\n");
        fprintf(fp, "Date & Time : %s", dt);

        fclose(fp);
    }

    return 0;
}
