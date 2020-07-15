# Lem_in

## Assignment

Write a program, named lem-in, which reads on standard input the map of an ant-farm and finds a solution to send all ants from start to end in as few turns as possible.
Each turn, each ant can move from one room to another adjacent room provided there's never more than one ant per room at any given time.
The ant-farm must be formatted as followed, else the program exits with an error statement :
- number of ants
- list of all rooms (rooms can have any name which doesn't start with an L)
- list of tubes to describe how the rooms are connected

The program prints the ant-farm then its solution, formatted as follows :
- each line = one turn
- L*ant_number* - room_the_ant_moves_to

## How to run it

`make`
`./lem-in < map`

Use `./generator --options > map` (generator runs on Linux) or use one of the maps in maps_valid
You can also run `./lem-in` and type the map on standard input

## Notions

- Antfarm stored as adjency table
- Hash table used for optimisation
- Shortest path algorithm (Djikstra)
- Max flow algorithm (Edmond-Karps)

## Bonus

`./script_test.sh` generates a series of maps, runs the program and compares the result with what the generator deems to be the best possible result
