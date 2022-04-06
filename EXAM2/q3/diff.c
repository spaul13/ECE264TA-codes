  char direction[4] = {NORTH, SOUTH, WEST, EAST};
  MazePos steps[4] = {
      {.xpos = curpos.xpos, .ypos = curpos.ypos - 1}, // NORTH
      {.xpos = curpos.xpos, .ypos = curpos.ypos + 1}, // SOUTH
      {.xpos = curpos.xpos - 1, .ypos = curpos.ypos}, // WEST
      {.xpos = curpos.xpos + 1, .ypos = curpos.ypos}  // EAST
  };