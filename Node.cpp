//
// Created by michal on 12.05.19.
//

#include "Node.h"

Node::Node(Node* elAfter):
    after(elAfter){ }

Node::~Node(){ }


void Node::setNode(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int BLOCKSYMBOLCOUNTER, int BLOCKCOLORNUMBER)
{
    after=pAfter;
    tetromino.set_variables(FIRSTCAGELOCX, FIRSTCAGELOCY, BLOCKSYMBOLCOUNTER, BLOCKCOLORNUMBER);
}


Tetromino Node::get_tetromino() {
    return tetromino;}
