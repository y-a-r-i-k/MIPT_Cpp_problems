#include <iostream>

int main() {
  // Задача: учёт посадочных мест в учебных корпусах.
  // Есть B корпусов, в каждом корпусе своё число этажей, на каждом этаже своё
  // число аудиторий, для каждой аудитории известно число мест. Затем приходят
  // запросы «сколько всего мест» в выбранной части кампуса: во всём корпусе,
  // на одном этаже или в одной аудитории.
  //
  // Зачем int***: данные трёхмерные (корпус -> этаж -> аудитория), и все три
  // размера известны только при вводе и различаются от корпуса к корпусу и от
  // этажа к этажу («рваный» массив). Статический int a[B][F][R] здесь
  // невозможен, а плоский массив потребовал бы отдельных таблиц смещений.
  // seats[b] — корпус (int**), seats[b][f] — этаж (int*), seats[b][f][r] —
  // число мест в аудитории.
  //
  // Зачем void*: запрос выбирает объект разного уровня — корпус (int**), этаж
  // (int*) или одну аудиторию (int*, указывающий на одно число). Указатель на
  // выбранный объект хранится в одной переменной void* selected, а
  // фактический тип восстанавливается по уровню запроса через static_cast.
  // Без void* пришлось бы заводить три разные переменные под три типа и
  // дублировать логику выбора.
  //
  // Формат ввода:
  //   B
  //   для каждого корпуса: F, затем для каждого этажа: R и R чисел мест
  //   далее запросы до строки 0:
  //     1 b        — всего мест в корпусе b
  //     2 b f      — всего мест на этаже f корпуса b
  //     3 b f r    — мест в аудитории r
  // На неверные индексы печатается error.

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int buildingCount{0};
  std::cin >> buildingCount;

  int*** seats = new int**[buildingCount];
  int* floorCount = new int[buildingCount];
  int** roomCount = new int*[buildingCount];

  for (int b = 0; b < buildingCount; ++b) {
    std::cin >> floorCount[b];
    seats[b] = new int*[floorCount[b]];
    roomCount[b] = new int[floorCount[b]];

    for (int f = 0; f < floorCount[b]; ++f) {
      std::cin >> roomCount[b][f];
      seats[b][f] = new int[roomCount[b][f]];

      for (int r = 0; r < roomCount[b][f]; ++r) {
        std::cin >> seats[b][f][r];
      }
    }
  }

  int level{0};
  while (std::cin >> level && level != 0) {
    int b{-1}, f{-1}, r{-1};
    std::cin >> b;
    if (level >= 2) {
      std::cin >> f;
    }
    if (level >= 3) {
      std::cin >> r;
    }

    bool isValid = level >= 1 && level <= 3 && b >= 0 && b < buildingCount;
    if (isValid && level >= 2) {
      isValid = f >= 0 && f < floorCount[b];
    }
    if (isValid && level == 3) {
      isValid = r >= 0 && r < roomCount[b][f];
    }

    if (!isValid) {
      std::cout << "error\n";
      continue;
    }

    void* selected = nullptr;
    if (level == 1) {
      selected = seats[b];
    } else if (level == 2) {
      selected = seats[b][f];
    } else {
      selected = &seats[b][f][r];
    }

    long long total{0};
    if (level == 1) {
      int** building = static_cast<int**>(selected);
      for (int i = 0; i < floorCount[b]; ++i) {
        for (int j = 0; j < roomCount[b][i]; ++j) {
          total += building[i][j];
        }
      }
    } else if (level == 2) {
      int* floor = static_cast<int*>(selected);
      for (int j = 0; j < roomCount[b][f]; ++j) {
        total += floor[j];
      }
    } else {
      total = *static_cast<int*>(selected);
    }

    std::cout << total << "\n";
  }

  for (int b = 0; b < buildingCount; ++b) {
    for (int f = 0; f < floorCount[b]; ++f) {
      delete[] seats[b][f];
    }
    delete[] seats[b];
    delete[] roomCount[b];
  }
  delete[] seats;
  delete[] roomCount;
  delete[] floorCount;
}