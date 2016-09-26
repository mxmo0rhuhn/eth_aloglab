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
  vector<int> thisEntry(9,0); // DP infos for the currently viewed entry
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
     * 6 - crossways sum
     * 5 - Number of even quadruples ending here crossways
     * 7 - Number of odd quadruples ending here crossways
     */
    vector< vector<int> > lastLine((n+1), vector<int>(9,0)); 
    vector< vector<int> > thisLine((n+1), vector<int>(9,0)); 

    for(int line = 0; line < n; line++) {
      // entry starting at 1 to have a 0th entry in every line 

      for(int entry = 1; entry <= n; entry++) {
        cin >> number;

        thisLine[entry][0] = ((thisLine[entry-1][0] + number) % 2);
        thisLine[entry][3] = ((lastLine[entry][3] + number) % 2);
        thisLine[entry][6] = ((   thisLine[entry-1][0] 
                                + lastLine[entry][3] 
                                + lastLine[entry-1][6] 
                                + number) % 2);

        if ((thisLine[entry][0] % 2 ) == 0 ) {
          thisLine[entry][1] = thisLine[entry-1][1] + 1;
          thisLine[entry][2] = thisLine[entry-1][2];
          even_quadrupels += thisLine[entry][1];
          printf("even sum horizontally + %d \n", thisLine[entry][1]);
        } else {
          thisLine[entry][1] = thisLine[entry-1][1];
          thisLine[entry][2] = thisLine[entry-1][2] + 1;
          even_quadrupels += thisLine[entry-1][2];
          printf("odd sum horizontally + %d \n", thisLine[entry-1][2]);
        }

        if ((thisLine[entry][3] % 2 ) == 0 ) {
          thisLine[entry][4] = lastLine[entry][4] + 1;
          thisLine[entry][5] = lastLine[entry][5];
          even_quadrupels += thisLine[entry][4];
          printf("even sum vertically + %d \n", thisLine[entry][4]);
        } else {
          thisLine[entry][4] = lastLine[entry][4];
          thisLine[entry][5] = lastLine[entry][5] + 1;
          even_quadrupels += lastLine[entry][5];
          printf("odd sum vertically + %d\n", lastLine[entry][5]);
        }

        if ((thisLine[entry][6] % 2 ) == 0 ) {
          thisLine[entry][7] = lastLine[entry-1][7] + 1;
          thisLine[entry][8] = lastLine[entry-1][8];
          if (entry > 1 && line > 0) {
            // crossways numbers can not start at the border
            even_quadrupels += thisLine[entry][7];
            printf("even sum crossways + %d\n", thisLine[entry][7]);
          }
        } else {
          thisLine[entry][7] = lastLine[entry-1][7];
          thisLine[entry][8] = lastLine[entry-1][8] + 1;
          if (entry > 1 && line > 0) {
            // crossways numbers can not start at the border
            even_quadrupels += lastLine[entry-1][8];
            printf("odd sum crossways + %d\n", lastLine[entry-1][8]);
          }
        }
      }
      lastLine = thisLine;
    }
    printf("%d\n", even_quadrupels);
  }
}
