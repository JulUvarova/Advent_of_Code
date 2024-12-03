#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main() {
  multiset<int> first_list{}, second_list{};

  ifstream file("data.txt");
  if (file.is_open()) {
    int first, second;
    while (file >> first >> second) {
      first_list.insert(first);
      second_list.insert(second);
    }
  }
  file.close();

  int distance = 0;
  auto elem_2 = second_list.begin();

  for (auto elem_1 : first_list) {
    distance += abs(elem_1 - *elem_2);
    ++elem_2;
  }

  cout << distance << endl;

  return 0;
}