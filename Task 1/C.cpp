#include <iomanip>
#include <iostream>
#include <limits>

const int kRows = 5;
const int kCols = 10;
const int kMaxInputLength = 256;

void skipLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int stringLength(const char* str) {
  int length = 0;
  while (str[length] != '\0') {
    ++length;
  }

  return length;
}

bool isEqual(const char* first, const char* second) {
  int i = 0;
  while (first[i] != '\0' && first[i] == second[i]) {
    ++i;
  }

  return first[i] == second[i];
}

bool isInside(const int x, const int y) {
  return x >= 0 && x < kCols && y >= 0 && y < kRows;
}

void clear(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool put(char board[kRows][kCols], const int x, const int y, const char c) {
  if (!isInside(x, y)) {
    return false;
  }

  board[y][x] = c;
  return true;
}

bool text(char board[kRows][kCols], const int x, const int y,
          const char* word) {
  int length = stringLength(word);
  if (length == 0 || !isInside(x, y) || !isInside(x + length - 1, y)) {
    return false;
  }

  for (int i = 0; i < length; ++i) {
    put(board, x + i, y, word[i]);
  }

  return true;
}

void print(const char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      std::cout << board[y][x];
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  char board[kRows][kCols];
  clear(board);

  char cmd[kMaxInputLength];
  while (std::cin >> std::setw(kMaxInputLength) >> cmd) {
    if (isEqual(cmd, "quit")) {
      break;
    }

    if (isEqual(cmd, "clear")) {
      clear(board);
    } else if (isEqual(cmd, "print")) {
      print(board);
    } else if (isEqual(cmd, "put")) {
      int x{0}, y{0};
      char c{' '};
      if (!(std::cin >> x >> y >> c) || !put(board, x, y, c)) {
        std::cout << "error\n";
        skipLine();
      }
    } else if (isEqual(cmd, "text")) {
      int x{0}, y{0};
      char word[kMaxInputLength];
      if (!(std::cin >> x >> y >> std::setw(kMaxInputLength) >> word) ||
          !text(board, x, y, word)) {
        std::cout << "error\n";
        skipLine();
      }
    } else {
      std::cout << "error\n";
      skipLine();
    }
  }
}