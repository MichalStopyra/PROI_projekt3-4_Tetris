//
// Created by michal on 11.05.19.
//

#ifndef MAIN_CPP_TETROMINO_H
#define MAIN_CPP_TETROMINO_H

#define TETROMINO_TAB_SIZE 4
#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10


class Tetromino {

private:
    int blockSymbolCounter;
    int blockColorNumber;
    //enum symbol;
    int shape[TETROMINO_TAB_SIZE*TETROMINO_TAB_SIZE];
    int firstCageLocationx;
    int firstCageLocationy;

    static int field[FIELD_WIDTH*FIELD_HEIGHT];

public:
    Tetromino(int =0, int=0, int=0, int=0);


    virtual ~Tetromino();

    void set_variables (int FIRSTCAGELOCX, int FIRSTCAGELOCY, int BLOCKSYMBOLCOUNTER, int BLOCKCOLORNUMBER);

    int* get_shape();//usunalem const
    int get_firstCageLocationx() const;
    int get_firstCageLocationy() const;
    bool does_block_fit();
    void add_block_to_field();
    void rotate_block();
    void move_block(int newFirstCageLocationx, int newFirstCageLocationy);

    static int get_field_values(int i, int j);

    template <typename T>
    friend class TheGame;
    friend class Node;

};


#endif //MAIN_CPP_TETROMINO_H
