#include <stdio.h>

int main(void)
{ //TODO: Нифига не работает ни Арсения ни мое
    int count_words = 0, is_word_now = 0; // Tracks the number of words and check if we are currently inside a word

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char symbol;

    // Read until end of file (or new line or null character in case of interactive input)
    while (scanf("%c", &symbol) && symbol != '\n' && symbol != '\0' && symbol != EOF)
    {
        if (symbol == '.') // Word boundary characters
        {
            if (is_word_now) // If we were inside a word, we just reached the end of a word
            {
                count_words++;
                is_word_now = 0; // Reset flag as we are no longer in a word
            }
        }
        else if (!is_word_now) // If we're at the start of a new word
        {
            is_word_now = 1; // Set the flag to indicate we're inside a word
        }
    }

    // Handle the last word if the input ends without a boundary character
    if (is_word_now)
    {
        count_words++;
    }

    /* do {
        scanf("%c", &symbol);
        if (symbol == '.' || symbol == '\n' || symbol == EOF && symbol == '\0') // Word boundary characters
        {
            if (is_word_now) // If we were inside a word, we just reached the end of a word
            {
                count_words++;
                is_word_now = 0; // Reset flag as we are no longer in a word
            }
        }
        else if (!is_word_now)  // If we're at the start of a new word
        {
            is_word_now = 1;  // Set the flag to indicate we're inside a word
        }
    }
    // Read until end of file (or new line or null character in case of interactive input)
    while (symbol != '\n' && symbol != EOF && symbol != '\0'); */

    // Output the total word count
    printf("%d", count_words);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
