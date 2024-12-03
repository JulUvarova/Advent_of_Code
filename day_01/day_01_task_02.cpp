#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int main() {
  multiset<int> first_list{};
  multiset<int> second_list{};

  ifstream file("data.txt");
  if (file.is_open()) {
    int first, second;
    while (file >> first >> second) {
      first_list.insert(first);
      second_list.insert(second);
    }
  }
  file.close();

  int similarity = 0;

  for (auto elem : first_list) {
    similarity += elem * second_list.count(elem);
  }

  cout << similarity << endl;

  return 0;
}