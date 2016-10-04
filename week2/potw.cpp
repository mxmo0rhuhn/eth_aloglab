#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Bomb {
  int parent;
  int time;
  int index;

  bool has_child1;
  int child1;

  bool has_child2;
  int child2;

  bool defused;

  friend bool operator< (const Bomb &i, const Bomb &j) {
    return i.time == j.time ? i.index > j.index : i.time > j.time;
  }
};

int main() {

  int num_cases; 
  int num_bombs; 
  int bottom_nr;
  int time;
  bool everything_fine;

  cin >> num_cases; 
//  printf("num_cases %d  \n", num_cases);

  for(int cur_case = 0; cur_case < num_cases; cur_case++) {
    cin >> num_bombs; 
//    printf("num_bombs %d  \n", num_bombs);

    vector<Bomb> bombs(num_bombs);
    priority_queue< Bomb > bottom_bombs; 
    everything_fine = true;

    bottom_nr = (num_bombs-2) / 2; 

    Bomb b; 
    b.parent = -1;
    bombs[0] = b; 

    for(int cur_bomb = 0; cur_bomb < num_bombs; cur_bomb++) {
      cin >> time; 
//      printf("time %d  \n", time);

      bombs[cur_bomb].index = cur_bomb; 
      bombs[cur_bomb].time = time; 
      bombs[cur_bomb].defused = false; 

      if ((2 * cur_bomb + 1) < num_bombs) {
        // create child
        Bomb new_b;
        new_b.parent = cur_bomb;
        bombs[(2 * cur_bomb + 1)] = new_b; 
        bombs[cur_bomb].has_child1 = true;
      } else {
        bombs[cur_bomb].has_child1 = false;
      }

      if ((2 * cur_bomb + 2) < num_bombs) {
        // create child
        Bomb new_b;
        new_b.parent = cur_bomb;
        bombs[(2 * cur_bomb + 2)] = new_b; 
        bombs[cur_bomb].has_child2 = true;
      } else {
        bombs[cur_bomb].has_child2 = false;
      }

      if( cur_bomb > bottom_nr ) {
// add to defusable queue
//        printf("cur bomb %d (time %d) > bottom_nr %d - push \n", cur_bomb, time, bottom_nr );
        bottom_bombs.push(bombs[cur_bomb]);
      }
    }

    int timer = 0;
    for(int cur_bomb = 0; everything_fine && cur_bomb < num_bombs; cur_bomb++) {

      Bomb b_pointer = bottom_bombs.top();
      bottom_bombs.pop();

      b = bombs[b_pointer.index];

//      printf("addr b %p / addr b_pointer %p \n", &b_pointer, &b );

//      printf("popped index %d has time %d \n", b_pointer.index, b.time );

      if ( bombs[b_pointer.index].time < timer ) {
        everything_fine = false;
//        printf("things are no longer fine index %d has time %d and it is time %d\n", b_pointer.index, b.time, timer );
      } else {
        bombs[b_pointer.index].defused = true;
//        printf("bomb defused(has to be? = %d \n", bombs[b_pointer.index].defused);


        bool b1 = true;
        if(bombs[b.parent].has_child1) {
//          printf("bomb index %d has child 1 (index %d) and this is defused = %d \n", b.parent ,bombs[b.parent].child2, bombs[(bombs[b.parent].child1)].defused );
          b1 = bombs[(bombs[b.parent].child1)].defused;
        }

        bool b2 = true;
        if(bombs[b.parent].has_child2) {
//          printf("bomb index %d has child 2 (index %d ) and this is defused = %d \n", b.parent , bombs[b.parent].child2, bombs[(bombs[b.parent].child2)].defused );
          b2 = bombs[(bombs[b.parent].child2)].defused;
        }

//        printf("b1 = %d , b2 = %d \n", b1, b2); 

        if ( b1 && b2 ) {
//          printf("add index %d to pr queue\n", bombs[b.parent].index );
          bottom_bombs.push(bombs[b.parent]);
        }
      }

      timer++;
    }

    if(everything_fine) {
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }

  return 0;
}
