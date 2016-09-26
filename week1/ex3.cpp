#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  int num_cases;
  int num_dominoes;
  int cur_high;
  int sum;
  int rem_high;
  bool finished;

  cin >> num_cases;

  for(int cur_case = 0; cur_case < num_cases ; cur_case++) {
    cin >> num_dominoes;
    sum = 0;
    rem_high = 0;
    finished = false; 

    for(int domino = 1; domino <= num_dominoes ; domino++) {
      cin >> cur_high;

      if(! finished) {
        sum++;
        rem_high--;

        if (cur_high > rem_high){
          rem_high = cur_high; 
        }

        if (rem_high <= 1) {
          finished = true; 
        }
      }
    }
    printf("%d\n", sum);
  }
  return 0;
}
