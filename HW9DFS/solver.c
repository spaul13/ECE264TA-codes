#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"

char * solveMaze(Maze * m) {
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	//base cases: 
	//1. if curpos is at the end, append \0 to the path, return true
	if (atEnd(curpos, m)) {
		path[step] = '\0';
		return true;
	}
	//2. if curpos is invalid (wall, out of bounds, or already visited)
	//   return false
	if (!squareOK(curpos, m)) {
		return false;
	}
	
	//Set this square to visited
	m->maze[curpos.ypos][curpos.xpos].visited = true;
	
	//inductive case: check each possible direction from curpos
	char direction[4] = {NORTH, SOUTH, EAST, WEST};
	MazePos steps[4] = {
		{.xpos = curpos.xpos, .ypos = curpos.ypos - 1}, //NORTH
		{.xpos = curpos.xpos, .ypos = curpos.ypos + 1}, //SOUTH
		{.xpos = curpos.xpos + 1, .ypos = curpos.ypos}, //EAST
		{.xpos = curpos.xpos - 1, .ypos = curpos.ypos}  //WEST
	};
	
	for (int i = 0; i < 4; i++) {
		//Try to make a move and see if it's successful
		
		if (depthFirstSolve(m, steps[i], path, step + 1)) {
			//If successful, record this step in the path
			path[step] = direction[i];
			printf("%d, %d\n", curpos.xpos, curpos.ypos);
			return true;
		}
	}
	//If no move is successful, return false
	return false;
}
