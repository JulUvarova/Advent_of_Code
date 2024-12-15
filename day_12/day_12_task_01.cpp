#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void read_file(std::vector<std::string>& map) {
  std::ifstream file("data.txt");
  if (!file.is_open()) throw std::exception();
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      map.push_back(line);
    }
  }
  file.close();
}

struct RegionData {
  std::pair<int, int> start;
  char type;
  int area = 0;
  int perimeter = 0;
  std::set<std::pair<int, int>> coords;
  std::vector<std::string>& map;
  std::vector<std::pair<int, int>> environment = {
      {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  RegionData(int y, int x, std::vector<std::string>& m)
      : start({y, x}), map(m) {
    type = map[y][x];
    find_boundary(y, x);
  };

  int fence_price() { return area * perimeter; }

  void clear_region() {
    for (const auto& coord : coords) map[coord.first][coord.second] = '.';
  }

 private:
  void find_boundary(int y, int x) {
    if (coords.count({y, x})) return;
    ++area;
    coords.insert({y, x});

    for (const auto& env : environment) {
      if (y + env.first < 0 || y + env.first >= (int)map.size() ||
          x + env.second < 0 || x + env.second >= (int)map[0].size())
        ++perimeter;
      else if (map[y + env.first][x + env.second] == type)
        find_boundary(y + env.first, x + env.second);
      else
        ++perimeter;
    }
  }
};

int main() {
  std::vector<std::string> map;
  read_file(map);

  int price = 0;

  for (int i = 0; i < (int)map.size(); ++i) {
    for (int j = 0; j < (int)map[i].size(); ++j) {
      if (map[i][j] == '.') continue;
      RegionData region(i, j, map);
      price += region.fence_price();
      region.clear_region();
    }
  }

  std::cout << price << std::endl;

  return 0;
}