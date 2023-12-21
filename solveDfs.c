// DFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    Item startVert = MazeGetStart(m);


    bool** visited = createBoolMatrix(MazeHeight(m), MazeWidth(m));
    struct cell** pred = createCellMatrix(MazeHeight(m), MazeWidth(m));

    Stack s = StackNew();
    StackPush(s, startVert);

    MazeVisit(m, startVert);
    visited[startVert.row][startVert.col] = true;
    pred[startVert.row][startVert.col] = startVert;

    bool found = false;
    Item end;
    while (!StackIsEmpty(s)) {

        Item v = StackPop(s);

        if (MazeVisit(m, v)) {
            found = true;
            end = v;
            break;
        }

        Item u1 = { v.row + 1, v.col };
        Item d1 = { v.row - 1, v.col };
        Item l1 = { v.row, v.col - 1 };
        Item r1 = { v.row, v.col + 1 };


        if (u1.row >= 0 && u1.row < MazeHeight(m) && u1.col >= 0 && u1.col < MazeWidth(m) && !MazeIsWall(m, u1) && !visited[u1.row][u1.col]) {
            visited[u1.row][u1.col] = true;
            pred[u1.row][u1.col] = v;
            StackPush(s, u1);
        }
        if (d1.row >= 0 && d1.row < MazeHeight(m) && d1.col >= 0 && d1.col < MazeWidth(m) && !MazeIsWall(m, d1) && !visited[d1.row][d1.col]) {
            visited[d1.row][d1.col] = true;
            pred[d1.row][d1.col] = v;
            StackPush(s, d1);
        }
        if (l1.row >= 0 && l1.row < MazeHeight(m) && l1.col >= 0 && l1.col < MazeWidth(m) && !MazeIsWall(m, l1) && !visited[l1.row][l1.col]) {
            visited[l1.row][l1.col] = true;
            pred[l1.row][l1.col] = v;
            StackPush(s, l1);
        }
        if (r1.row >= 0 && r1.row < MazeHeight(m) && r1.col >= 0 && r1.col < MazeWidth(m) && !MazeIsWall(m, r1) && !visited[r1.row][r1.col]) {
            visited[r1.row][r1.col] = true;
            pred[r1.row][r1.col] = v;
            StackPush(s, r1);
        }

    }

    if (!found) {
        return false;
    }

    Item cur = end;
    while (!(cur.row == startVert.row && cur.col == startVert.col))
    {
        MazeMarkPath(m, cur);
        cur = pred[cur.row][cur.col];
    }
    MazeMarkPath(m, startVert);
    return true;
}

