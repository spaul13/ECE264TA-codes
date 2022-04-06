bool depthFirstSolve(Maze *m, MazePos curpos, char *path, int step) {
  // Base case 1. if curpos is at the end, append \0 to the path,
  //   return true
  if (atEnd(curpos, m)) {
    path[step] = '\0';
    return true;
  }
  // Base case 2. if curpos is invalid (wall, out of bounds, or
  //   already visited) return false
  if (!inBounds(curpos, m)
    || hitWall(curpos, m)
    || isVisited(curpos, m)) {
    return false;
  }
  
  // inductive case: check each possible direction from curpos
  char direction[4] = {NORTH, SOUTH, EAST, WEST};
  MazePos steps[4] = {
      {.xpos = curpos.xpos, .ypos = curpos.ypos - 1}, // NORTH
      {.xpos = curpos.xpos, .ypos = curpos.ypos + 1}, // SOUTH
      {.xpos = curpos.xpos + 1, .ypos = curpos.ypos}, // EAST
      {.xpos = curpos.xpos - 1, .ypos = curpos.ypos}  // WEST
  };

  for (int i = 0; i < 4; i++) {
    // Try to make a move and see if it's successful
    if (depthFirstSolve(m, steps[i], path, step + 1)) {
      // If successful, record this step in the path
      path[step] = direction[i];
      return true;
    }
  }
  
  // Set this square to visited ** THIS IS A BUG **
  m->maze[curpos.ypos][curpos.xpos].visited = true;
  
  // If no move is successful, return false
  return false;
}
