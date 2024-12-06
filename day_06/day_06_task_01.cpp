#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void read_file(std::vector<std::string>& map) {
  std::ifstream file("data.txt");
  std::string line;
  if (!file.is_open()) throw std::exception();
  while (getline(file, line)) {
    map.push_back(line);
  }
  file.close();
}

enum Direct { UP, DOWN, LEFT, RIGHT, EXIT };

struct Patrol {
  std::pair<int, int> guard;
  Direct direct;
  std::vector<std::string>& map;

  Patrol(std::vector<std::string>& map) : direct(UP), map(map) {
    for (int i = 0; i < (int)map.size(); ++i) {
      for (int j = 0; j < (int)map[i].size(); ++j)
        if (map[i][j] == '^') guard = std::make_pair(i, j);
    }
  }

  bool check_leave() {
    if (guard.first < 0 || guard.second < 0 || guard.first >= (int)map.size() ||
        guard.second >= (int)map[0].size())
      return true;
    return false;
  }

  bool check_attaching(int first, int second, Direct new_direct) {
    if (check_leave()) {
      direct = EXIT;
    } else if (map[guard.first][guard.second] == '#') {
      guard.first += first;
      guard.second += second;
      direct = new_direct;
      return true;
    }
    return false;
  }

  void patrol_loop() {
    while (direct != EXIT) {
      switch (direct) {
        case UP:
          --guard.first;
          check_attaching(1, 0, RIGHT);
          break;
        case DOWN:
          ++guard.first;
          check_attaching(-1, 0, LEFT);
          break;
        case LEFT:
          --guard.second;
          check_attaching(0, 1, UP);
          break;
        case RIGHT:
          ++guard.second;
          check_attaching(0, -1, DOWN);
          break;
        default:
          break;
      }
      if (direct != EXIT) map[guard.first][guard.second] = 'X';
    }
  }

  int get_vizits() {
    int count = 1;
    for (int i = 0; i < (int)map.size(); ++i) {
      for (int j = 0; j < (int)map[i].size(); ++j)
        if (map[i][j] == 'X') ++count;
    }
    return count;
  }
};

int main() {
  std::vector<std::string> map;
  read_file(map);
  Patrol protocol{map};

  protocol.patrol_loop();

  std::cout << protocol.get_vizits() << std::endl;

  return 0;
}