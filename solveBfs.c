// BFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"


bool isValidCell(Maze m, Item c, bool **visited) {
    return c.row >= 0 && c.row < MazeHeight(m) && c.col >= 0 && c.col < MazeWidth(m) && !MazeIsWall(m, c) && !visited[c.row][c.col];
}


bool solve(Maze m) {
    Item startVert = MazeGetStart(m);
    

    bool** visited = createBoolMatrix(MazeHeight(m), MazeWidth(m));
    struct cell** pred = createCellMatrix(MazeHeight(m), MazeWidth(m));
    
    Queue q = QueueNew();
    QueueEnqueue(q, startVert);

    MazeVisit(m, startVert);
    visited[startVert.row][startVert.col] = true;
    pred[startVert.row][startVert.col] = startVert;

    bool found = false;
    Item end;
    while (!QueueIsEmpty(q)) {
        
        Item v = QueueDequeue(q);
        
        if (MazeVisit(m, v)) {
            found = true;
            end = v;
            break;
        }

        Item u1 = { v.row + 1, v.col };
        Item d1 = { v.row - 1, v.col };
        Item l1 = { v.row, v.col - 1 };
        Item r1 = { v.row, v.col + 1 };


        if (isValidCell(m,u1,visited)) {
            visited[u1.row][u1.col] = true;
            pred[u1.row][u1.col] = v;
            QueueEnqueue(q, u1);
        }
        if (isValidCell(m,d1,visited)) {
            visited[d1.row][d1.col] = true;
            pred[d1.row][d1.col] = v;
            QueueEnqueue(q, d1);
        }
        if (isValidCell(m,l1,visited)) {
            visited[l1.row][l1.col] = true;
            pred[l1.row][l1.col] = v;
            QueueEnqueue(q, l1);
        }
        if (isValidCell(m,r1,visited)) {
            visited[r1.row][r1.col] = true;
            pred[r1.row][r1.col] = v;
            QueueEnqueue(q, r1);
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

