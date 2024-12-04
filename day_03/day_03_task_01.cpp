#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::pair<int, int> get_pair(std::string str) {
  std::regex pattern("(\\d+)");
  std::sregex_iterator beg_num{str.cbegin(), str.cend(), pattern};
  int x = stod(beg_num->str());
  int y = stod((++beg_num)->str());

  return std::make_pair(x, y);
}

void find_in_str(std::string& str, long int& mul_res) {
  std::regex rex{
      "(mul\\(([0-9]{1,2}|[1-9][0-9]{1,2}|[0-9]{3}),([0-9]{1,2}|[1-9][0-9]{"
      "2}|[0-9]{3})\\))"};
  std::sregex_iterator beg{str.cbegin(), str.cend(), rex};
  std::sregex_iterator end{};

  for (auto i = beg; i != end; ++i) {
    std::pair<int, int> numbers = get_pair(i->str());
    mul_res += numbers.first * numbers.second;
  }
}

int main() {
  long int mul_res = 0;

  std::ifstream file("data.txt");
  if (file.is_open()) {
    std::string str;
    while (getline(file, str)) {
      find_in_str(str, mul_res);
    }
  }
  file.close();

  std::cout << mul_res << std::endl;

  return 0;
}