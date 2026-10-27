//Name : Vijyant
//  Roll no : 25/DA/063

#include <stdio.h>
#include <limits.h>

// Function to find the most efficient way to multiply a chain of matrices
int matrixChainOrder(int p[], int n) {
    // m[i][j] stores the minimum number of scalar multiplications needed 
    // to compute the matrix A[i..j]
    int m[n][n];

    // Cost is zero when multiplying one matrix (i.e., length L = 1)
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length. It ranges from 2 to n-1.
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            // Try every possible partition point k between i and j-1
            for (int k = i; k <= j - 1; k++) {
                // q = cost/scalar multiplications for a specific partition
                // Formula: cost of subproblem (i..k) + cost of subproblem (k+1..j) + cost of multiplying the two resulting matrices
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    // Return the minimum multiplication cost for the full chain from matrix 1 to n-1
    return m[1][n - 1];
}

int main() {
    // Dimensions of matrices represented by array p[]:
    // Matrix A1 has dimensions p[0] x p[1] (10 x 30)
    // Matrix A2 has dimensions p[1] x p[2] (30 x 5)
    // Matrix A3 has dimensions p[2] x p[3] (5 x 60)
    int arr[] = {10, 30, 5, 60};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Minimum number of scalar multiplications is %d\n", matrixChainOrder(arr, size));

    return 0;
}