//
// Created by michal on 12.05.19.
//

#include "FifoQueue.h"

FifoQueue::FifoQueue(Node* firstEl, Node* lastEl)
{
    first=firstEl;
    last=lastEl;
}

FifoQueue::~FifoQueue()
{
    Node* tmp = this->first;
    Node* tmpPrev;
    while(tmp){
        tmpPrev=tmp;
        tmp=tmp->after;
        delete tmpPrev;
    }
}


void FifoQueue::pushBack(Node* pAfter, int FIRSTCAGELOCX, int FIRSTCAGELOCY, int blockSymbolCounter, int blockColorNumber)
{
    Node* newEl=new Node;
    newEl->setNode(nullptr, FIRSTCAGELOCX, FIRSTCAGELOCY, blockSymbolCounter, blockColorNumber);

    if(first==nullptr || last==nullptr)
        first=last=newEl;
    else{
        last->after=newEl;
        last=newEl;
    }
}

void FifoQueue::popBack()
{
    Node* tmp = this->first;
    this->first=this->first->after;
    delete tmp;
}


int FifoQueue::sizeFifo()
{
    int nrOfEl=0;
    Node* tmp=this->first;
    while (tmp){
        ++nrOfEl;
        tmp=tmp->after; }
    delete tmp;
    return nrOfEl;
}
