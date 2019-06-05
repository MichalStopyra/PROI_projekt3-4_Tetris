//
// Created by michal on 12.05.19.
//

#ifndef NODE_H
#define NODE_H

#include "Tetromino.h"


class Node
{
    Tetromino tetromino;
    Node* after;

public:
    Node(Node* n=nullptr );
    virtual ~Node();

    void setNode(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int blockSymbolCounter, int blockColorNumber);
    Node* get_after();

    Tetromino get_tetromino();


    friend class FifoQueue;
    template <typename T>
    friend class TheGame;
};


#endif //NODE_H
