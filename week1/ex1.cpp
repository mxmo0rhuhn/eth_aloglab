#include <iostream>

using namespace std;

/** Build the sum of the numbers you’ll get.
 *
 * Input: The first line of the input file will contain an integer giving the number of test cases that follow.
 *        Each test case starts with a line containing m (0 ≤ m ≤ 10), the number of numbers you have to sum up.
 *        The following m lines contain m floating point numbers you’ll have to read and sum up.
 *
 * Output For each test case write the sum you’ve calculated in a single line. Your output will be accepted
 *        if it differs from the correct result by at most 10 −6 in terms of either absolute or relative precision
 */
int main() {
    int cases;
    cin >> cases; // read nr of cases

    int numin;
    float curnum;
    float sum;

    for(int c = 0; c < cases; c++){
        cin >> numin; // read nr of floats
        sum = 0;

        for(int n = 0; n < numin; n++){
            cin >> curnum; // read the current float
            sum += curnum;

        }
        cout << sum << endl;
    }

    return 0;
}