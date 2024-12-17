#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Robot {
  const static char ch_lbox = '[';
  const static char ch_rbox = ']';
  const static char ch_wall = '#';
  const static char ch_robot = '@';
  const static char ch_empty = '.';
  std::pair<int, int> robot;
  std::vector<std::string> &map;

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

  void take_box_chain(int i, int j, int shift_i,
                       std::map<std::pair<int, int>, char> &chain) {
    char box = (map[i][j] == ch_lbox) ? ch_lbox : ch_rbox;
    int correction = (box == ch_lbox ? 1 : -1);
    chain[{i, j}] = box;
    chain[{i, j + correction}] = map[i][j + correction];

    if (map[i + shift_i][j] == ch_wall ||
        map[i + shift_i][j + correction] == ch_wall) {
      chain[{-1, -1}] = box;
      return;
    }
    if (map[i + shift_i][j] == ch_lbox || map[i + shift_i][j] == ch_rbox)
      take_box_chain(i + shift_i, j, shift_i, chain);

    if (map[i + shift_i][j + correction] == ch_lbox ||
        map[i + shift_i][j + correction] == ch_rbox)
      take_box_chain(i + shift_i, j + correction, shift_i, chain);
  }

  bool check_block(int shift_i, int shift_j) {
    int i = robot.first + shift_i;
    int j = robot.second + shift_j;
    if (map[i][j] == ch_wall)
      return true;
    if (map[i][j] != ch_empty) {
      if (shift_i != 0) {
        // vertical
        std::map<std::pair<int, int>, char> chain;
        take_box_chain(i, j, shift_i, chain);
        if (chain.find({-1, -1}) == chain.end()) {
          for (const auto &point : chain)
            map[point.first.first][point.first.second] = ch_empty;
          for (const auto &point : chain)
            map[point.first.first + shift_i][point.first.second] = point.second;
          return false;
        } else
          return true;
      }
      // horisontal
      char box = (map[i][j] == ch_lbox) ? ch_rbox : ch_lbox;
      while (map[i][j + shift_j] == ch_lbox || map[i][j + shift_j] == ch_rbox)
        j += shift_j;
      if (map[i][j + shift_j] == ch_empty) {
        map[i][j + shift_j] = box;
        while (map[i][j] != ch_robot) {
          map[i][j] = (map[i][j + shift_j] == ch_lbox ? ch_rbox : ch_lbox);
          j -= shift_j;
        }
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
  explicit Robot(std::vector<std::string> &m) : map(m) { start_point(); }

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

int sum_coords(std::vector<std::string> &map) {
  int sum = 0;
  for (int i = 0; i < (int)map.size(); ++i) {
    for (int j = 0; j < (int)map[i].size(); ++j) {
      if (map[i][j] == '[')
        sum += 100 * i + j;
    }
  }
  return sum;
}

void read_file(std::vector<std::string> &map, std::string &path) {
  std::ifstream file("data.txt");
  std::string line;
  if (!file.is_open())
    throw std::exception();

  while (getline(file, line) && !line.empty())
    map.push_back(line);
  while (getline(file, line))
    path.append(line);

  file.close();
}

void change_map(std::vector<std::string> &map) {
  std::vector<std::string> big_map;
  for (int i = 0; i < (int)map.size(); ++i) {
    std::string line;
    for (int j = 0; j < (int)map[i].size(); ++j) {
      if (map[i][j] == 'O')
        line.append("[]");
      else if (map[i][j] == '#')
        line.append("##");
      else if (map[i][j] == '@')
        line.append("@.");
      else
        line.append("..");
    }
    big_map.push_back(line);
  }
  map = std::move(big_map);
}

int main() {
  std::vector<std::string> map;
  std::string path;
  read_file(map, path);
  change_map(map);

  Robot wh(map);
  for (int i = 0; i < (int)path.size(); ++i)
    wh.move(path[i]);

  std::cout << sum_coords(map) << std::endl;

  return 0;
}