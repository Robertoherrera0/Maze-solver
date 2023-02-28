# Instructions  

This project helps you practice writing a flood-fill algorithm to find the fastest path through a maze.

A flood-fill algorithm is comprised of two parts:

1. A modified BFS where a node is given a distance when it is reached where the distance is equal to 1 + the distance of the current node.
2. A backtracking algorithm that chooses the nearest node that has a distance one less than the current node.

See
[this slide deck](https://docs.google.com/presentation/d/1Nk9xGVUJyDl62a6kFExRsBWGFrdQtNqibXYXf0mHFGw/edit?usp=sharing)
for a visual of how a flood-fill algorithm works.

## Backtracking

While backtracking we prefer the directions in this order: left, up, right, down.

For example, if you have this map, where -1 is a wall, otherwise it is the distance. The start is the 1, and the end is the 5.

||||
|---|---|---|
|1|2|3|
|-1|3|4|
|-1|4|5|

The fastest path would be...

||||
|---|---|---|
|1|2||
||3||
||4|5|

Not...

||||
|---|---|---|
|1|2|3|
|||4|
|||5|

Because **left** is prioritized over **up**.

## Input / Output

First, two integers are given which are X and Y.

Second, Y rows of X characters are given.
A 'x' character indicates a wall in the maze that cannot be passed through. Any other character is an open space that can be passed through.

Third, two integers are given which are EndX and EndY and signify the coordinate of the end cell. The start cell is always (0, 0) starting from the top-left.

The program must output the shortest path using 'o' characters for cells on the path, and spaces for everything else.

### Example

Input

```
8 9
........
xxxxxxx.
........
.xxxxxxx
........
xxxxxxx.
........
.xxxxxxx
........
7 8
```

Output

```
oooooooo
       o
oooooooo
o       
oooooooo
       o
oooooooo
o       
oooooooo
```