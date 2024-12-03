#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void fill_vector(std::vector<int>& vector, std::string& line) {
  std::stringstream str_to_int(line);
  int number = 0;
  while (str_to_int >> number) vector.push_back(number);
}

template <class Compare>
void check_conditions(std::vector<int>& vector, bool& is_safe) {
  for (int i = 1; i < (int)(vector.size()) && is_safe; ++i) {
    if (!Compare()(vector[i], vector[i - 1]) ||
        std::abs(vector[i] - vector[i - 1]) > 3)
      is_safe = false;
  }
}

void check_safety(std::vector<int>& vector, bool& is_safe) {
  if (vector[1] - vector[0] > 0)
    check_conditions<std::greater<int>>(vector, is_safe);
  else
    check_conditions<std::less<int>>(vector, is_safe);
}

int main() {
  int safe_report = 0;

  std::ifstream file("data.txt");
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      std::vector<int> report;
      fill_vector(report, line);

      bool is_safe = true;
      check_safety(report, is_safe);

      safe_report += (int)is_safe;
    }
  }
  file.close();

  std::cout << safe_report << std::endl;

  return 0;
}