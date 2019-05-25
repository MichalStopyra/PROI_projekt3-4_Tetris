//
// Created by michal on 11.05.19.
//

#include "Tetromino.h"
#include<iostream>

#define TETROMINO_TAB_SIZE 4


Tetromino::Tetromino(int BLOCKSYMBOLCOUNTER, int BLOCKCOLORNUMBER, int FIRSTCAGELOCATIONX, int FIRSTCAGELOCATIONY):
    blockSymbolCounter(BLOCKSYMBOLCOUNTER), blockColorNumber(BLOCKCOLORNUMBER), firstCageLocationx(FIRSTCAGELOCATIONX), firstCageLocationy(FIRSTCAGELOCATIONY)
{
    for (int i=0; i<TETROMINO_TAB_SIZE; ++i){
        for(int j=0; j<TETROMINO_TAB_SIZE; ++j)
            shape[TETROMINO_TAB_SIZE*j+i]=0;
    }
}

int Tetromino::field[FIELD_WIDTH*FIELD_HEIGHT]={0};



Tetromino::~Tetromino(){ }



void Tetromino::set_variables (int FIRSTCAGELOCX, int FIRSTCAGELOCY, int BLOCKSYMBOLCOUNTER, int BLOCKCOLORNUMBER)
{
    firstCageLocationx=FIRSTCAGELOCX;
    firstCageLocationy=FIRSTCAGELOCY;
    blockSymbolCounter=BLOCKSYMBOLCOUNTER;
    blockColorNumber=BLOCKCOLORNUMBER;

    switch (blockSymbolCounter)
    {
        case 0: //'I'
            shape[1] = shape[5] = shape[9] = shape[13] = 1;
            break;
        case 1: //'T':
            shape[0] = shape[4] = shape[8] = shape[5] = 1;
            break;
        case 2: //'O':
            shape[0] = shape[4] = shape[1] = shape[5] = 1;
            break;
        case 3: //'L':
            shape[0] = shape[4] = shape[8] = shape[9] = 1;
            break;
        case 4: //'J':
            shape[1] = shape[5] = shape[9] = shape[8] = 1;
            break;
        case 5: //'S':
            shape[4] = shape[5] = shape[1] = shape[2] = 1;
            break;
        case 6: //'Z':
            shape[0] = shape[1] = shape[5] = shape[6] = 1;
            break;
        default:
            std::cout << "NIE MA TAKIEGO KLOCKA" << std::endl;
            break;
    }

}

int* Tetromino::get_shape() {
    return shape;}

int Tetromino::get_firstCageLocationx() const {
    return firstCageLocationx;}

int Tetromino::get_firstCageLocationy() const {
    return firstCageLocationy;}


int Tetromino::get_field_values(int i, int j) {
    return field[j*FIELD_WIDTH+i];}


bool Tetromino::does_block_fit()
{
    int blockInField;
    for (int py = 0; py < TETROMINO_TAB_SIZE; ++py) {
        for (int px = 0; px < TETROMINO_TAB_SIZE; ++px) {

            blockInField = (firstCageLocationy + py) * FIELD_WIDTH + (firstCageLocationx + px);

            if(this->shape[py*TETROMINO_TAB_SIZE+px]==1) {
                if (firstCageLocationx + px < 0 || firstCageLocationx + px >= FIELD_WIDTH)
                    return false;
                if (firstCageLocationy + py < 0 || firstCageLocationy + py >= FIELD_HEIGHT)
                    return false;
            }

            if (firstCageLocationx + px >= 0 && firstCageLocationx + px < FIELD_WIDTH) {
                if (firstCageLocationy + py >= 0 && firstCageLocationy + py < FIELD_HEIGHT) {

                    if (Tetromino::shape[py*TETROMINO_TAB_SIZE+px] == 1) {
                        if (Tetromino::field[blockInField] != 0)
                            return false;
                    }
                }

            }
        }
    }
    return true;
}


void Tetromino::add_block_to_field() {
    int blockInField;

        for (int py = 0; py < TETROMINO_TAB_SIZE; ++py) {
            for (int px = 0; px < TETROMINO_TAB_SIZE; ++px) {
                if (firstCageLocationx + px >= 0 && firstCageLocationx + px < FIELD_WIDTH) {
                    if (firstCageLocationy + py >= 0 && firstCageLocationy + py < FIELD_HEIGHT && this->shape[py*TETROMINO_TAB_SIZE+px]==1   ) {
                        blockInField = (firstCageLocationy + py) * FIELD_WIDTH + (firstCageLocationx + px);
                          Tetromino::field[blockInField] = this->shape[py * TETROMINO_TAB_SIZE + px];
                    }

                }
            }
        }
}

void Tetromino::rotate_block(){

    if(this->blockSymbolCounter!=2) {
        int tmpShapeTable[TETROMINO_TAB_SIZE * TETROMINO_TAB_SIZE];
        int tmpShapeTable2[TETROMINO_TAB_SIZE * TETROMINO_TAB_SIZE];

        for (int i = 0; i < TETROMINO_TAB_SIZE; ++i) {
            for (int j = 0; j < TETROMINO_TAB_SIZE; ++j)
                tmpShapeTable[TETROMINO_TAB_SIZE * i + TETROMINO_TAB_SIZE - j - 1] = this->shape[
                        TETROMINO_TAB_SIZE * j + i];
        }

        for (int i = 0; i < TETROMINO_TAB_SIZE * TETROMINO_TAB_SIZE; ++i) {
            tmpShapeTable2[i] = this->shape[i];
            this->shape[i] = tmpShapeTable[i];
        }

        if (!this->does_block_fit()) {
            for (int i = 0; i < TETROMINO_TAB_SIZE * TETROMINO_TAB_SIZE; ++i)
                this->shape[i] = tmpShapeTable2[i];
        }
    }
}

void Tetromino::move_block(int newFirstCageLocationx, int newFirstCageLocationy) {
    int tmpfirstx = this->firstCageLocationx;
    int tmpfirsty = this->firstCageLocationy;

    this->firstCageLocationx=newFirstCageLocationx;
    this->firstCageLocationy=newFirstCageLocationy;



   if(!does_block_fit()) {
        this->firstCageLocationx = tmpfirstx;
        this->firstCageLocationy = tmpfirsty;
    }

}