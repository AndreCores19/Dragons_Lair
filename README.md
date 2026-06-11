# Dragon's Lair

Dragon's Lair is a C++ automatic turn-based simulation game.

A hunter travels through different regions, fights dragons, collects weapons, buys items from villagers, and records the adventure in a logbook.

The main objective is to reach the final region and defeat the Hydra.

---

## Core Classes

* `Menu`: Validates the input files, loads the game data, and starts the simulation.
* `Simulation`: Controls the turn loop, combat, movement, purchases, item collection, victory conditions, defeat conditions, and final report.
* `Logbook`: Records the events of the simulation in `bitacora.txt`.
* `Reader`: Reads the `.txt` files and creates the world, dragons, objects, villagers, and hunter.
* `World`: Stores all regions and controls the hunter's current location.
* `Region`: Represents a location in the world. A region can contain dragons, objects, villagers, and connections.
* `Hunter`: Represents the main character of the simulation.
* `Dragon`: Base class for all dragon types.
* `Villager`: Represents merchants that sell items to the hunter.

---

## Design Pattern Used

### Factory Method

The project uses the Factory Method pattern in `DragonFactory`.

`DragonFactory` creates the correct dragon subtype depending on the type read from `dragons.txt`.

Example dragon types:

```txt
fire
poison
ice
hydra
```

This avoids creating dragons directly inside `Reader` and keeps dragon creation centralized.

---

### Template / Generic Container

The project uses a generic container through `List<T>`.

This allows the same list structure to store different types of objects.

Examples:

```cpp
List<Region*>
List<Dragon*>
List<Object*>
List<Villager*>
```

This helps avoid repeating container logic for every class type.

---

### Inheritance and Polymorphism

The project uses inheritance and polymorphism to represent different game entities.

Examples:

```txt
Dragon -> FireDragon, PoisonDragon, IceDragon, HydraDragon
Object -> Weapon, Potion, Armor
Entity -> Character, Villager
```

This allows the simulation to work with base-class pointers while still using the behavior of each specific subtype.

---

## Input Files

The project requires a `data/` folder with the following files:

```txt
regions.txt
dragons.txt
objects.txt
villagers.txt
hunter.txt
```

These files define the map, enemies, items, villagers, and initial hunter stats.
**Note**: This `data/` folder must be located in the cmake-build-debug folder for the program to run correctly.
---

## Output Files

The program generates the following files:

```txt
logbook.txt
final_report.txt
```

`logbook.txt` stores the turn-by-turn log of the simulation.

`final_report.txt` stores the final result of the adventure.

---

## Simulation Rules

* The simulation runs automatically.
* Movement, damage, and purchases can include randomness.
* The hunter moves between regions using the connections defined in `regions.txt`.
* The hunter can collect weapons from regions.
* Potions and armor are bought from villagers.
* Dragons are loaded from `dragons.txt`.
* The final enemy is the Hydra.
* The game ends when the hunter dies or the Hydra is defeated.

---

## Summary

Dragon's Lair combines file reading, object-oriented programming, inheritance, polymorphism, templates, and design patterns to simulate an automatic fantasy adventure.

The project separates responsibilities between classes, making the code easier to organize, extend, and test.
