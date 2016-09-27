#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

/**
 * Input: The first line of the input contains the number 1 ≤ t ≤ 30 of test cases. 
 * Each of the t test cases is described as follows:
 * - It starts with a line that contains an integer n such that 1 ≤ n ≤ 50000.
 * - The next line contains n values x 1 , . . . , x n , separated by spaces. 
 *   Each value x i is either 0 or 1.
 * 
 * Output: For each test case output a line containing the number of 
 * pairs 1 ≤ i ≤ j ≤ n such that the sum x i + · · · + x j is even.
 */ 
int main() {

  int cases;          // number of cases
  int num_elem;       // number of elements in this case
  int num_even_pairs; // the result

  cin >> cases;       // read nr of cases

  for(int c = 0; c < cases; c++) {
    num_even_pairs = 0;
    cin >> num_elem; 

    int number;    // current number
    int sum = 0;   // sum up to this point (even or odd)
    int evens = 0; // number of even pairs ending here
    int odds = 0;  // number of odd pairs ending here

    for(int n = 0; n < num_elem; n++) {
      cin >> number;
      sum = (sum + number) % 2;

      if(sum == 0) {
        num_even_pairs++;
        num_even_pairs += evens;
        evens ++;
      } else {
        num_even_pairs += odds;
        odds ++;
      }
    }
    printf("%d\n", num_even_pairs);
  }
}
