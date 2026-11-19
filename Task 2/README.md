# ФизКат — учёт парка

Консольное приложение для учёта парка самокатов, велосипедов и вещей.

## Сборка и запуск
```bash
make
./fizkat
```

## Схема наследования

```
InventoryItem (абстрактный)
├── Transport
│   ├── Bike
│   ├── ElectricScooter : Transport, EnergyConsumer
│   └── EBike : Transport, EnergyConsumer
├── Helmet
├── DockStation : InventoryItem, EnergyConsumer
└── PowerBank : InventoryItem, EnergyConsumer   ← креатив

EnergyConsumer (абстрактный)
```

Множественное наследование используется в `ElectricScooter`, `EBike`, `DockStation`, `PowerBank`.

## Smart-указатели
- `shared_ptr<InventoryItem>` — владение принятыми единицами парка (`Fleet::items_` — `vector<shared_ptr<InventoryItem>>`).
- `shared_ptr<ModelSpec>` — общая спецификация модели (используется в самокатах и электровелосипедах).
- `weak_ptr<InventoryItem>` — витрина (`focus` / `show_focus`). После `remove` становится expired и выводится `removed`.

## Исключения
- `FleetError` — базовый.
- `InspectionRejected` — отказ техосмотра (в имени есть "broken").
- `InvalidCommand` — некорректные аргументы или неизвестная команда.

## Шаблон
`Registry<T, Capacity>` — журнал последних добавленных объектов.  
Используется в `Fleet::add` (поле `recent_`).

## Креативная часть
- Новый тип: `PowerBank` (пауэрбанк) + команда `add powerbank id name energy`.
- Дополнительная команда: `count` — выводит количество единиц на балансе.

## Пример работы

Ввод:
```
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add scooter S-2 brokenX 1.0 9
add helmet H-1 Pro
add dock D-1 Hub 10.0
add powerbank P-1 Charge 1.5
list
novice
energy
count
focus S-1
show_focus
remove S-1
show_focus
quit
```

Вывод:
```
error: inspection rejected
B-1 City
D-1 Hub
H-1 Pro
P-1 Charge
S-1 ModelX
S-1 ModelX
14.0
5
S-1 ModelX
removed
```

(в реальном выводе были небольшие проблемы с кодировкой, в примере эти сторки вырезаны)