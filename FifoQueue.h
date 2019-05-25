//
// Created by michal on 12.05.19.
//

#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include "Tetromino.h"
#include "Node.h"

class FifoQueue {
    Node *first;
    Node *last;
public:
    FifoQueue(Node *f = nullptr, Node *l = nullptr);

    virtual ~FifoQueue();

//--------------METODY KLASY FIFOQUEUE------------------------------------

//Funkcja dodawania nowego klocka na koniec kolejki fifo
    void pushBack(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int blockSymbolCounter, int blockColorNumber);

//usuwanie elementu z poczatku listy
    void popBack();

//ilosc elementow w kolejce
    int sizeFifo();


friend class TheGame;
};
#endif //FIFOQUEUE_H
