#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void read_file(std::vector<std::string>& matrix) {
  std::ifstream file("data.txt");
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      matrix.push_back(line);
    }
  }
  file.close();
}

int find_mas(std::vector<std::string>& matrix) {
  int count = 0;
  for (int i = 1; i < (int)matrix.size(); ++i) {
    for (int j = 1; j < (int)matrix[i].size(); ++j) {
      if (matrix[i][j] == 'A') {
        if (i + 1 < (int)matrix.size() && j + 1 < (int)matrix[i].size() &&
            ((matrix[i - 1][j - 1] == 'M' && matrix[i + 1][j + 1] == 'S') ||
             (matrix[i - 1][j - 1] == 'S' && matrix[i + 1][j + 1] == 'M')) &&
            ((matrix[i + 1][j - 1] == 'M' && matrix[i - 1][j + 1] == 'S') ||
             (matrix[i + 1][j - 1] == 'S' && matrix[i - 1][j + 1] == 'M')))
          ++count;
      }
    }
  }
  return count;
}

int main() {
  std::vector<std::string> matrix;
  read_file(matrix);
  int res = find_mas(matrix);

  std::cout << res << std::endl;

  return 0;
}