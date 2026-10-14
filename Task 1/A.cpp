#include <climits>
#include <iomanip>
#include <iostream>

double averageTemperature(const int* journal, const int n) {
  double averageTemp = 0;
  for (int i = 0; i < n; ++i) {
    averageTemp += journal[i];
  }

  averageTemp = averageTemp / n;
  return averageTemp;
}

void findMinMax(const int* journal, const int n, int& min, int& max) {
  int localMin = INT_MAX;
  int localMax = INT_MIN;

  for (int i = 0; i < n; ++i) {
    if (journal[i] < localMin) {
      localMin = journal[i];
    }

    if (journal[i] > localMax) {
      localMax = journal[i];
    }
  }

  min = localMin;
  max = localMax;
}

int countBelowZero(const int* journal, const int n) {
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (journal[i] < 0) {
      ++count;
    }
  }

  return count;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{0};
  std::cin >> n;

  int* journal = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> journal[i];
  }

  std::cout << std::fixed << std::setprecision(1)
            << averageTemperature(journal, n) << "\n";

  int min{0}, max{0};
  findMinMax(journal, n, min, max);
  std::cout << min << " " << max << "\n";

  std::cout << countBelowZero(journal, n) << "\n";

  delete[] journal;
}