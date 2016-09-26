#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int num_tests; 
  int num_cards;
  int k;     // value to be reached
  int value; // of a current card

  int above_num;
  int above_index;

  int below_num;
  int below_index;

  int exact_index;
  bool finished;  // we found a value 

  cin >> num_tests;

  for(int test = 0; test < num_tests; test++){

    cin >> num_cards;
    cin >> k;

    finished = false;

    above_num = 0;
    below_num = 0;

    exact_index = -1;
    above_index = -1;
    below_index = -1;

    vector< int > card_values(num_cards, 0);
    // An vector containing all numbers from 0 to k and the index of the card that can reach this number
    vector< int > card_sums(k+1, -1);

    for(int card = 0; card < num_cards; card++){
      cin >> value; 
      card_values[card] = value;
      printf("Value is %d \n", value);

      if(!finished) {
        if (value == k) {
          // card value is k 
          exact_index = card;
          card_sums[value] = card;
          finished = true;
          printf("Value %d is exact k = %d \n", value,k);
        } else if (value > k) {
          // card value is larger than k 
          printf("Value %d is bigger as k = %d \n", value,k);
          if(above_num == 0) {
            above_num = value;
            above_index = card;
          } else {
            if(value < above_num) {
              above_num = value;
              above_index = card;
            }
          }
        } else {
          // card value < k
          card_sums[value] = card;

          for(int i = (value+1); i <= k; i++) {
            if(card_sums[i] >= 0 && card_sums[i] != card) {
              // value could already be reached using the preceeding cards
              int sum = i + value;
              if (sum == k) {
                exact_index = card;
                card_sums[sum] = card;
                finished = true;
              } else if (sum > k) {
                // sum is larger than k 
                if(above_num == 0) {
                  above_num = sum;
                  above_index = card;
                } else {
                  if(sum < above_num) {
                    above_num = sum;
                    above_index = card;
                  }
                }
              } else {
                // sum < k
                card_sums[sum] = card;
                if(sum > below_num) {
                  below_num = sum;
                  below_index = card;
                }
              }
            } else {
              // value could not yet be reached using the preceeding cards
              if(card_sums[i-value] >= 0 && card_sums[i-value] != card) {
                // value can be reached using this and a preceeding card
                card_sums[i] = card;
              }
            }
          }
        }
      }
    }
    // get the result
    //
    // - check whether above or below num is the right choice
    // - backtrack until value is 0
    int best_index;
    int rem_value;

    if(exact_index >= 0) {
      best_index = exact_index;
      rem_value = k;
    } else {
      int below = k - below_num;
      int above = above_num - k;
      if(above > below) {
        best_index = below_index;
        rem_value = below_num;
      } else {
        best_index = above_index;
        rem_value = above_num;
      }
    }
    int cur_start = best_index;
    rem_value -= card_values[cur_start];

    while(rem_value > 0) {
      // this gives us the index of the card used to get the value
      cur_start = card_sums[rem_value];
      // this gives us the remaining value after deducing the value of the used card
      rem_value -= card_values[cur_start];
    }

    if ( rem_value < 0) {
      printf("The remaining value ( %d ) after the last card is < 0 - should not happen\n", rem_value);
      return 1; 
    }
    printf("%d %d\n", cur_start, best_index);
  }
  return 0; 
}
