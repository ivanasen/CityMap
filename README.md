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

1. `open <file-name>` - Open a CityMap file.
2. `save` - Save the CityMap file.
3. `saveAs <location>` - Save CityMap file to location.
4. `addCrossroad <crossroad-name>` - Add a Crossroad to the city.
5. `addRoad <from> <to> <weight>` - Add a Road.
6. `removeCrossroad <crossroad-name>` - Remove a Crossroad. (Not implemented)
7. `removeRoad <from> <to>` - Remove a Road.
8. `hasPath <from> <to>` - Is there a path from `from` to `to` in the city.
9. `findShortestPaths <from> <to>` - Find top 3 shortest paths.
10. `closeCrossroad <crossroad-name>` - Close crossroad.
11. `openCrossroad <crossroad-name>` - Open crossroad.
12. `hasCycleFrom <crossroad-name>` - Check if there is a cycle in the city containing `crossroad-name`.
13. `findEulerCycle` - Find if there is an Euler cycle in the city.
14. `canReachAllFrom <crossroad-name>` - Check if there is a path from `crossroad-name` to all other crossroads in the city.
15. `findDeadEnds` - Find all dead-ends in the city.
16. `currentLocation` - Print current location. (Not implemented)
17. `showNeighbours` - Show neighbours to `currentLocation` crossroad. (Not implemented)
18. `changeLocation <crossroad-name>` - Change `currentLocation` (Not implemented)
19. `moveLocation <crossroad-name>` - Change `currentLocation` printing the travelled path. (Not implemented)
20. `showClosed` - Show closed crossroads. (Not implemented)

### Third-party libraries used

- Catch 2 Testing framework - [Go to Github page](https://github.com/catchorg/catch2)
