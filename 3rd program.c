#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ATTEMPTS 5

int main() {
    int secretNumber, guess, attempts = 0, score = 0;
    char playAgain;

    srand(time(NULL)); // Initialize random seed
    printf("Welcome to the Guess the Number game!\n");

    do {
        // Generate random number between 1 and 100
        secretNumber = rand() % 100 + 1;
        attempts = 0; // Reset attempts for each new game

        printf("\nI'm thinking of a number between 1 and 100. Can you guess it?\n");

        while (attempts < MAX_ATTEMPTS) {
            printf("Enter your guess (Attempt %d/%d): ", attempts + 1, MAX_ATTEMPTS);
            scanf("%d", &guess);

            if (guess < secretNumber) {
                printf("Too low! Try again.\n");
            } else if (guess > secretNumber) {
                printf("Too high! Try again.\n");
            } else {
                printf("Congratulations! You've guessed the number (%d) correctly!\n", secretNumber);
                score += MAX_ATTEMPTS - attempts; // Increase score based on remaining attempts
                break;
            }

            attempts++;
        }

        if (attempts == MAX_ATTEMPTS) {
            printf("Sorry, you've run out of attempts. The correct number was %d.\n", secretNumber);
        }

        printf("Your current score: %d\n", score);
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'Y' || playAgain == 'y');

    printf("Thanks for playing! Your final score is: %d\n", score);

    return 0;
}
