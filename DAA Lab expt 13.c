//Name : Vijyant
//  Roll no : 25/DA/063

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find and print the Longest Common Subsequence of two strings
void lcs(char* X, char* Y) {
    int m = strlen(X);
    int n = strlen(Y);
    
    // Allocate memory for the 2D DP table (m + 1) x (n + 1)
    int** L = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        L[i] = (int*)malloc((n + 1) * sizeof(int));
    }

    // Build the DP table in a bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Base case: if either string is empty, LCS length is 0
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            }
            // If characters match, take diagonal value and add 1
            else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            // If characters do not match, take the maximum from top or left cell
            else {
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
            }
        }
    }

    // Backtrack through the table to reconstruct the LCS string
    int index = L[m][n];
    char* lcsStr = (char*)malloc((index + 1) * sizeof(char));
    lcsStr[index] = '\0'; // Null-terminate the string

    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If characters match, they are part of the LCS
        if (X[i - 1] == Y[j - 1]) {
            lcsStr[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        // If not, move in the direction of the maximum value in the table
        else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Display the results
    printf("String 1: %s\n", X);
    printf("String 2: %s\n", Y);
    printf("Length of LCS: %d\n", L[m][n]);
    printf("Longest Common Subsequence: %s\n", lcsStr);

    // Free dynamically allocated memory to prevent memory leaks
    for (int k = 0; k <= m; k++) {
        free(L[k]);
    }
    free(L);
    free(lcsStr);
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    lcs(X, Y);

    return 0;
}