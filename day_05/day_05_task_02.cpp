#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

void read_file(std::multimap<int, int>& rules,
               std::vector<std::vector<int>>& updates) {
  std::ifstream file("data.txt");
  std::string line;
  bool is_rules = true;

  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream str_to_int(line);
      int x, y;
      char ch;
      if (line.empty()) {
        is_rules = false;
      } else if (is_rules) {
        str_to_int >> x >> ch >> y;
        rules.insert({x, y});
      } else {
        std::vector<int> update;
        while (str_to_int >> x) {
          update.push_back(x);
          str_to_int >> ch;
        }
        updates.push_back(update);
      }
    }
  }
  file.close();
}

int check_pages(std::vector<int>& pages, std::multimap<int, int>& rules) {
  bool is_right = true;
  for (int i = 1; i < (int)pages.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      auto range = rules.equal_range(pages[i]);
      for (auto r = range.first; r != range.second; ++r) {
        if (r->second == pages[j]) {
          std::swap(pages[i], pages[j]);
          is_right = false;
        }
      }
    }
  }
  return !is_right ? pages[pages.size() / 2] : 0;
}

int check_updates(std::multimap<int, int>& rules,
                  std::vector<std::vector<int>>& updates) {
  int sum_middle = 0;
  for (int i = 0; i < (int)updates.size(); ++i) {
    sum_middle += check_pages(updates[i], rules);
  }
  return sum_middle;
}

int main() {
  std::multimap<int, int> rules;
  std::vector<std::vector<int>> updates;
  read_file(rules, updates);
  int res = check_updates(rules, updates);

  std::cout << res << std::endl;

  return 0;
}