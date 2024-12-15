#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Robot {
  const static char ch_box = 'O';
  const static char ch_wall = '#';
  const static char ch_robot = '@';
  const static char ch_empty = '.';
  std::pair<int, int> robot;
  std::vector<std::string>& map;

  void start_point() {
    for (int i = 0; i < (int)map.size(); ++i) {
      for (int j = 0; j < (int)map[i].size(); ++j) {
        if (map[i][j] == ch_robot) {
          robot = {i, j};
          return;
        }
      }
    }
  }

  bool check_block(int shift_i, int shift_j) {
    int i = robot.first + shift_i;
    int j = robot.second + shift_j;
    if (map[i][j] == ch_wall) return true;
    if (map[i][j] == ch_box) {
      while (map[i + shift_i][j + shift_j] == ch_box) {
        i += shift_i;
        j += shift_j;
      }
      if (map[i + shift_i][j + shift_j] == ch_empty) {
        map[i + shift_i][j + shift_j] = ch_box;
        return false;
      } else
        return true;
    }
    return false;
  }

  void do_step(int i, int j) {
    if (!check_block(i, j)) {
      map[robot.first][robot.second] = ch_empty;
      map[robot.first += i][robot.second += j] = ch_robot;
    }
  }

 public:
  Robot(std::vector<std::string>& m) : map(m) { start_point(); }

  void move(char direction) {
    switch (direction) {
      case '<':
        do_step(0, -1);
        break;
      case '>':
        do_step(0, 1);
        break;
      case '^':
        do_step(-1, 0);
        break;
      case 'v':
        do_step(1, 0);
        break;
      default:
        break;
    }
  }
};

int sum_coords(std::vector<std::string>& map) {
  int sum = 0;
  for (int i = 0; i < (int)map.size(); ++i) {
    for (int j = 0; j < (int)map[i].size(); ++j) {
      if (map[i][j] == 'O') sum += 100 * i + j;
    }
  }
  return sum;
}

void read_file(std::vector<std::string>& map, std::string& path) {
  std::ifstream file("data.txt");
  std::string line;
  if (!file.is_open()) throw std::exception();

  while (getline(file, line) && !line.empty()) map.push_back(line);
  while (getline(file, line)) path.append(line);

  file.close();
}

int main() {
  std::vector<std::string> map;
  std::string path;
  read_file(map, path);

  Robot wh(map);
  for (int i = 0; i < (int)path.size(); ++i) wh.move(path[i]);

  std::cout << sum_coords(map) << std::endl;

  return 0;
}