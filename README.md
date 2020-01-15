# CityMap

Command-line tool for work with city maps. Implemented in C++ 17. Done as a homework project for the course on Data structures in programming at SU "Kliment Ohridski" FMI.

## Usage

### Prerequisites

- **CMake**: version 3.13 or higher

### Building the project

Run these commands while in the project directory:

```bash
cmake .
make
```

After that a **CityMap_cli** executable should be available in the src/CityMap_cli project folder.

## Usage

The available commands are as follows:

1. `open_map <file-name>` - Open a CityMap file.
2. `save` - Save the CityMap file.
3. `save_as <location>` - Save CityMap file to location.
4. `add <crossroad-name>` - Add a Crossroad to the city.
5. `add_road <from> <to> <weight>` - Add a Road.
6. `rm_road <from> <to>` - Remove a Road.
7. `has_path <from> <to>` - Is there a path from `from` to `to` in the city.
8. `show_paths <from> <to>` - Find top 3 shortest paths.
9. `close <crossroad-name>` - Close crossroad.
10. `open <crossroad-name>` - Open crossroad.
11. `cycle_from <crossroad-name>` - Check if there is a cycle in the city containing `crossroad-name`.
12. `tour` - Find if there is an Euler cycle in the city.
13. `reach_all <crossroad-name>` - Check if there is a path from `crossroad-name` to all other crossroads in the city.
14. `dead_ends` - Find all dead-ends in the city.
15. `loc` - Print current location.
16. `nbs` - Show neighbours to current location.
17. `change <crossroad-name>` - Change current location.
18. `move <crossroad-name>` - Change current location only if a path to `<crossroad-name>` exists.
19. `closed` - Show closed crossroads.
20. `exit` - Exit the program.

## Project Structure

The project is separated in to 4 main modules:
1. **CityMap_lib** - Core functionality regarding cities, crossroads, path-search, cycle-serach.
2. **CityMap_serialization** - Serialization functionality.
3. **CityMap_cli** - Command-line User Interface related functionality.
4. **CityMap_utils** - Often used Utility functions throughout the project.

### Third-party libraries used

- Catch 2 Testing framework - [Go to Github page](https://github.com/catchorg/catch2)
