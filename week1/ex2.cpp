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
  int num;            // numbers of values for a case
  int num_even_pairs; // the result

  cin >> cases;       // read nr of cases

  for(int c = 0; c < cases; c++) {
    num_even_pairs = 0;
    cin >> num; 

    int number;
    int last_number;
    int evens;
    int odds;
    last_number = 0;
    evens = 0;
    odds = 0;

    for(int n = 0; n < num; n++) {
      cin >> number;
      number = (last_number + number) % 2;

      if(number == 0) {
        num_even_pairs++;
        num_even_pairs += evens;
        evens += 1;
      } else {
        num_even_pairs += odds;
        odds += 1;
      }
      last_number = number;
    }
    printf("%d\n", num_even_pairs);
  }
}
