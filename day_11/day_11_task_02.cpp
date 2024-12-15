#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

void read_file(std::map<int64_t, int64_t>& stones) {
  std::ifstream file("data.txt");
  if (!file.is_open()) throw std::exception();
  int x;
  while (file >> x) stones[x] += 1;
  file.close();
}

void blinking(std::map<int64_t, int64_t>& stones) {
  std::string str;
  std::map<int64_t, int64_t> new_stones;
  for (auto& stone : stones) {
    if (stone.first == 0) {
      new_stones[1] += stone.second;
    } else if ((str = std::to_string(stone.first)).size() % 2 == 0) {
      new_stones[std::stoll(str.substr(0, str.size() / 2))] += stone.second;
      new_stones[std::stoll(str.substr(str.size() / 2, str.size()))] +=
          stone.second;
    } else {
      new_stones[stone.first * 2024] += stone.second;
    }
  }
  stones = std::move(new_stones);
}

int64_t list_size(const std::map<int64_t, int64_t>& stones) {
  int64_t count = 0;
  for (const auto& stone : stones) count += stone.second;
  return count;
}

int main() {
  std::map<int64_t, int64_t> stones;
  read_file(stones);

  for (int i = 0; i < 75; ++i) blinking(stones);

  std::cout << list_size(stones) << std::endl;

  return 0;
}