#include <iomanip>
#include <iostream>
#include <limits>

using Operation = void (*)(long long& balance);

const int kMaxCommandLength = 32;

void skipLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool readAmount(long long& amount) {
  if (!(std::cin >> amount)) {
    skipLine();
    return false;
  }

  return amount > 0;
}

void deposit(long long& balance) {
  long long amount{0};
  if (!readAmount(amount)) {
    std::cout << "error\n";
    return;
  }

  balance += amount;
}

void withdraw(long long& balance) {
  long long amount{0};
  if (!readAmount(amount) || amount > balance) {
    std::cout << "error\n";
    return;
  }

  balance -= amount;
}

void printBalance(long long& balance) { std::cout << balance << "\n"; }

void reset(long long& balance) { balance = 0; }

void doubleBalance(long long& balance) { balance *= 2; }

bool isEqual(const char* first, const char* second) {
  int i = 0;
  while (first[i] != '\0' && first[i] == second[i]) {
    ++i;
  }

  return first[i] == second[i];
}

int findCommand(const char* const* names, const int count, const char* cmd) {
  for (int i = 0; i < count; ++i) {
    if (isEqual(names[i], cmd)) {
      return i;
    }
  }

  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  const char* commandNames[] = {"deposit", "withdraw", "balance", "reset",
                                "double"};
  Operation commandOperations[] = {deposit, withdraw, printBalance, reset,
                                   doubleBalance};
  const int commandCount = sizeof(commandNames) / sizeof(commandNames[0]);

  long long balance{0};
  char cmd[kMaxCommandLength];

  while (std::cin >> std::setw(kMaxCommandLength) >> cmd) {
    if (isEqual(cmd, "stop")) {
      break;
    }

    int index = findCommand(commandNames, commandCount, cmd);
    if (index == -1) {
      std::cout << "error\n";
      skipLine();
      continue;
    }

    commandOperations[index](balance);
  }
}