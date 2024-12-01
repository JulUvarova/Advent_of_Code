#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main() {
  multiset<int> first_list{};
  multiset<int> second_list{};

  ifstream fopen("data.txt");
  if (fopen.is_open()) {
    int first, second;
    while (fopen >> first >> second) {
      first_list.insert(first);
      second_list.insert(second);
    }
  }
  fopen.close();

  int similarity = 0;

  for (auto elem : first_list) {
    similarity += elem * second_list.count(elem);
  }

  cout << similarity << endl;

  return 0;
}