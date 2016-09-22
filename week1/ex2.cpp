#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {

  int cases; // number of cases
  int num; // numbers of values for a case
  int num_even_pairs;
  string in_string; 

  cin >> cases; // read nr of cases

  for(int c = 0; c < cases; c++) {
    num_even_pairs = 0;
    cin >> num; 

    vector<int> numbers(num, 0); 
    vector<int> sums(num, 0);  // sum up to that number
    vector<int> evens(num, 0); 
    vector<int> odds(num, 0);  

    for(int n = 0; n < num; n++) {
      cin >> numbers[n];
      sums[n] += sums[n-1] + numbers[n];

      if((sums[n] % 2) == 0) {
        evens[n] = evens[n-1] + 1;
        odds[n] = odds[n-1]; 
      } else {
        evens[n] = evens[n-1]; 
        odds[n] = odds[n-1] + 1;
      }
    }

    for(int i = 0; i < num; i++) {
      if((sums[i] % 2) == 0) {
        num_even_pairs++;
        num_even_pairs += evens[i-1];
      } else {
        num_even_pairs += odds[i-1];
      }
    }

    printf("%d\n", num_even_pairs);
  }
}
