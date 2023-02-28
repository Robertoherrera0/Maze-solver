//  Roberto Herrera
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

class node {
 public:
  int x;
  int y;

  node() : x(0), y(0){};
  node(int y, int x) : y(y), x(x){};
  // vector of all possible children of each node
  std::vector<std::pair<int, int>> children = {
      {y, x - 1}, {y - 1, x}, {y, x + 1}, {y + 1, x}};
};

// copyright,
// https://www.geeksforgeeks.org/unordered-set-of-pairs-in-c-with-examples
struct hashFunction {
  size_t operator()(const std::pair<int, int> &x) const {
    return x.first * x.second;
  }
};

int main() {
  // Read the dimensions.
  std::vector<std::vector<int>> dist_matrix;
  int row, col;
  std::cin >> col >> row;
  // Fill the maze with INT_MAX.
  dist_matrix.resize(row, std::vector<int>(col, INT_MAX));

  // Read the maze, adding the walls as -1.
  std::cin.ignore();

  std::string r;
  for (int i = 0; i < row; i++) {
    std::getline(std::cin, r);
    for (int j = 0; j < col; j++) {
      if (r[j] == 'x') {
        dist_matrix[i][j] = -1;
      }
    }
  }

  // Read the target cell.

  int targetx, targety;
  std::cin >> targetx >> targety;

  std::queue<node> queue;
  std::unordered_set<std::pair<int, int>, hashFunction> visited; 
  // Start at the top-left, and do a BFS.
  dist_matrix[0][0] = 0;
  node n;
  queue.push(n);

  // O(N+E) N are nodes and E are edges
  while (!queue.empty()) {
    if (visited.find(std::make_pair(queue.front().y, queue.front().x)) ==
        visited.end()) {
      int x, y;
      for (int i = 0; i < queue.front().children.size(); i++) {
        x = queue.front().children[i].second;
        y = queue.front().children[i].first;

        // if children are in matrix and are not walls, calculate the distance
        if (x >= 0 && x < col && y >= 0 && y < row) {
          if (dist_matrix[y][x] != -1) {
            if (visited.find(std::make_pair(y, x)) == visited.end()) {
              dist_matrix[y][x] =
                  dist_matrix[queue.front().y][queue.front().x] + 1;
              node n(y, x);
              queue.push(n);
            }
          }
        }
      }
    }
    visited.insert(std::make_pair(queue.front().y, queue.front().x));
    queue.pop();
  }

  std::vector<std::vector<char>> solved_matrix;
  solved_matrix.resize(row, std::vector<char>(col, ' '));

  // Backtrack starting at the target.
  solved_matrix[targety][targetx] = 'o';

  // O(N+E) N are nodes and E are edges
  while (true) {
    node target(targety, targetx);

    for (int i = 0; i < target.children.size(); i++) {
      int x = target.children[i].second;
      int y = target.children[i].first;
      if (x >= 0 && x < col && y >= 0 && y < row) {
        if (dist_matrix[y][x] != -1) {
          if ((dist_matrix[targety][targetx] - dist_matrix[y][x]) == 1) {
            solved_matrix[y][x] = 'o';
            targetx = x;
            targety = y;
            break;
          }
        }
      }
    }

    if (targetx == 0 && targety == 0) {
      solved_matrix[0][0] = 'o';
      break;
    }
  }

  // Print the solved maze.
  // O(row*col)
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      std::cout << solved_matrix[i][j];
    }
    std::cout << "\n";
  }
}
