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
- `unique_ptr<InventoryItem>` — владение единицами парка (`Fleet::items_`).
- `shared_ptr<ModelSpec>` — общая спецификация модели (используется в самокатах и электровелосипедах).
- `weak_ptr<InventoryItem>` — фокус (`focus` / `show_focus`). После `remove` становится expired.

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
