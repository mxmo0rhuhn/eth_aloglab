#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

/** 
 * Input The first line of the input contains the number 1 ≤ t ≤ 15 of test cases. 
 * Each of the t test cases is described as follows.
 * - It starts with a line that contains an integer n such that 1 ≤ n ≤ 200.
 * - This is followd by n lines, where the i-th line contains the n 
 *   bits x i,1 , . . . , x i,n , separated by spaces.
 *
 * Output: For each test case output a line that contains the number of 
 * quadruples (i 1 , i 2 , j 1 , j 2 ) where 
 * 1 ≤ i 1 ≤ i 2 ≤ n and 1 ≤ j 1 ≤ j 2 ≤ n and for which the sum is even.
 */

int main() {
  int cases;      // case per testset
  int n;          // cardinality of the matrix (lines per case / entries per line)
  int number;     // the currently viewed matrix entry
  vector<int> thisEntry(6,0); // DP infos for the currently viewed entry
  int even_quadrupels;        // the result

  cin >> cases;

  for(int c = 0; c < cases; c++) {
    even_quadrupels = 0;
    cin >> n;
    /** 
     * The 4 entries in the vector for every point in the matrix are: 
     * 0 - Is the horizontally sum of the line ending here even or odd (0 even, 1 odd)
     * 1 - Number of even quadruples ending here horizontally
     * 2 - Number of odd quadruples ending here horizontally
     * 3 - Is the vertically sum of the line ending here even or odd (0 even, 1 odd)
     * 4 - Number of even quadruples ending here vertically
     * 5 - Number of odd quadruples ending here vertically
     */
    vector< vector<int> > lastLine((n+1), vector<int>(6,0)); 
    vector< vector<int> > thisLine((n+1), vector<int>(6,0)); 

    for(int line = 0; line < n; line++) {
      // entry starting at 1 to have a 0th entry in every line 
      for(int entry = 1; entry < n; entry++) {
        cin >> number;

        // horizontal 
        if( ((thisLine[n-1][0] + number) % 2) == 0) {
          // even
          thisLine[n][0] = 0;
          // number of even quadruples ending here is the last evens + 1
          thisLine[n][1] = thisLine[n-1][1] + 1;
          thisLine[n][2] = thisLine[n-1][2];
        } else {
          // odd
          thisLine[n][0] = 1;
          // number of even quadruples ending here is the last odds + 1
          thisLine[n][1] = thisLine[n-1][2] + 1;
          thisLine[n][2] = thisLine[n-1][1];
        }
        // vertically
        if( ((lastLine[n][0] + number) % 2) == 0) {
          // even
          thisLine[n][3] = 0;
          // number of even quadruples ending here is the last evens + 1
          thisLine[n][4] = lastLine[n][4] + 1;
          thisLine[n][5] = lastLine[n][5];
        } else {
          // odd
          thisLine[n][3] = 1;
          // number of even quadruples ending here is the last odds + 1
          thisLine[n][4] = lastLine[n][5] + 1;
          thisLine[n][5] = lastLine[n][4];
        }
        even_quadrupels += thisLine[n][1] + thisLine[n][4];
      }
      lastLine = thisLine;
    }
  }

  printf("%d\n", even_quadrupels);
}
