#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main() {
  multiset<int> first_list{}, second_list{};

  ifstream fopen("data.txt");
  if (fopen.is_open()) {
    int first, second;
    while (fopen >> first >> second) {
      first_list.insert(first);
      second_list.insert(second);
    }
  }
  fopen.close();

  int distance = 0;
  auto elem_2 = second_list.begin();

  for (auto elem_1 : first_list) {
    distance += abs(elem_1 - *elem_2);
    ++elem_2;
  }

  cout << distance << endl;

  return 0;
}