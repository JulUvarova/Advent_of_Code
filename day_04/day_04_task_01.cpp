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

int find_xmas(std::vector<std::string>& matrix) {
  int count = 0;
  for (int i = 0; i < (int)matrix.size(); ++i) {
    for (int j = 0; j < (int)matrix[i].size(); ++j) {
      if (matrix[i][j] == 'X') {
        // horisontal
        if ((j + 3) < (int)matrix[i].size() && matrix[i][j + 1] == 'M' &&
            matrix[i][j + 2] == 'A' && matrix[i][j + 3] == 'S')
          ++count;
        if ((j - 3) >= 0 && matrix[i][j - 1] == 'M' &&
            matrix[i][j - 2] == 'A' && matrix[i][j - 3] == 'S')
          ++count;
        // vertical
        if ((i + 3) < (int)matrix.size() && matrix[i + 1][j] == 'M' &&
            matrix[i + 2][j] == 'A' && matrix[i + 3][j] == 'S')
          ++count;
        if ((i - 3) >= 0 && matrix[i - 1][j] == 'M' &&
            matrix[i - 2][j] == 'A' && matrix[i - 3][j] == 'S')
          ++count;
        // left top to right bottom
        if ((j + 3) < (int)matrix[i].size() && (i + 3) < (int)matrix.size() &&
            matrix[i + 1][j + 1] == 'M' && matrix[i + 2][j + 2] == 'A' &&
            matrix[i + 3][j + 3] == 'S')
          ++count;
        // right bottom to left top
        if ((i - 3) >= 0 && (j - 3) >= 0 && matrix[i - 1][j - 1] == 'M' &&
            matrix[i - 2][j - 2] == 'A' && matrix[i - 3][j - 3] == 'S')
          ++count;
        // right top to left bottom
        if ((j - 3) >= 0 && (i + 3) < (int)matrix.size() &&
            matrix[i + 1][j - 1] == 'M' && matrix[i + 2][j - 2] == 'A' &&
            matrix[i + 3][j - 3] == 'S')
          ++count;
        // right bottom to left top - reverse
        if ((j + 3) < (int)matrix[i].size() && (i - 3) >= 0 &&
            matrix[i - 1][j + 1] == 'M' && matrix[i - 2][j + 2] == 'A' &&
            matrix[i - 3][j + 3] == 'S')
          ++count;
      }
    }
  }
  return count;
}

int main() {
  std::vector<std::string> matrix;
  read_file(matrix);
  int res = find_xmas(matrix);

  std::cout << res << std::endl;

  return 0;
}