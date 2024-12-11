#include <forward_list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void read_file(std::forward_list<int64_t>& stones) {
  std::ifstream file("data.txt");
  if (!file.is_open()) throw std::exception();
  int x;
  auto pos = stones.before_begin();
  while (file >> x) {
    pos = stones.insert_after(pos, x);
  }
  file.close();
}

void blinking_times(std::forward_list<int64_t>& stones) {
  std::string str;
  for (auto stone = stones.begin(); stone != stones.end(); ++stone) {
    if (*stone == 0)
      *stone = 1;
    else if ((str = std::to_string(*stone)).size() % 2 == 0) {
      *stone = std::stoll(str.substr(0, str.size() / 2));
      stones.insert_after(stone,
                          std::stoll(str.substr(str.size() / 2, str.size())));
      ++stone;
    } else
      *stone *= 2024;
  }
}

int list_size(const std::forward_list<int64_t>& stones) {
  int count = 0;
  for (const auto& stone : stones) {
    (void)stone;
    ++count;
  }
  return count;
}

int main() {
  std::forward_list<int64_t> stones;
  read_file(stones);

  for (int i = 0; i < 25; ++i) blinking_times(stones);

  std::cout << list_size(stones) << std::endl;

  return 0;
}