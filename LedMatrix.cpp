/*
 * LedMatrix.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: Karan Daryani
 */

#include "tasks.hpp"
#include "examples/examples.hpp"
#include "uart0.hpp"
#include <stdio.h>
#include "FreeRTOS.h"
#include "gpio.hpp"
#include "LabGPIO.hpp"
#include "utilities.h"
#include "string.h"
#include "time.h"
#include "LedMatrix.hpp"
#include "printf_lib.h"

int gamepace=100;

void LedMatrix::displayNumber(uint8_t row, uint8_t col, uint8_t number){
    switch(number){
        case 0:{
            if (row < 15){
                drawPixel(row,col,0x06); drawPixel(row+1,col,0x06); drawPixel(row+2,col,0x06); drawPixel(row+3,col,0x06);
                drawPixel(row+4,col,0x06); drawPixel(row,col+1,0x06); drawPixel(row+4,col+1,0x06); drawPixel(row,col+2,0x06);
                drawPixel(row+1,col+2,0x06); drawPixel(row+2,col+2,0x06); drawPixel(row+3,col+2,0x06); drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30); drawPixel(row+1,col,0x30); drawPixel(row+2,col,0x30); drawPixel(row+3,col,0x30);
                drawPixel(row+4,col,0x30); drawPixel(row,col+1,0x30); drawPixel(row+4,col+1,0x30); drawPixel(row,col+2,0x30);
                drawPixel(row+1,col+2,0x30); drawPixel(row+2,col+2,0x30); drawPixel(row+3,col+2,0x30); drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 1:{
            if (row < 15){
                drawPixel(row,col+1,0x06); drawPixel(row+1,col+1,0x06); drawPixel(row+1,col,0x06); drawPixel(row+2,col+1,0x06);
                drawPixel(row+3,col+1,0x06); drawPixel(row+4,col+1,0x06); drawPixel(row+4,col,0x06); drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col+1,0x30); drawPixel(row+1,col+1,0x30); drawPixel(row+1,col,0x30); drawPixel(row+2,col+1,0x30);
                drawPixel(row+3,col+1,0x30); drawPixel(row+4,col+1,0x30); drawPixel(row+4,col,0x30); drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 2:{
            if (row < 16){
                drawPixel(row,col,0x06); drawPixel(row,col+1,0x06); drawPixel(row,col+2,0x06); drawPixel(row+1,col+2,0x06);
                drawPixel(row+2,col+2,0x06); drawPixel(row+2,col+1,0x06); drawPixel(row+2,col,0x06); drawPixel(row+3,col,0x06);
                drawPixel(row+4,col,0x06); drawPixel(row+4,col+1,0x06); drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30); drawPixel(row,col+1,0x30); drawPixel(row,col+2,0x30); drawPixel(row+1,col+2,0x30);
                drawPixel(row+2,col+2,0x30); drawPixel(row+2,col+1,0x30); drawPixel(row+2,col,0x30); drawPixel(row+3,col,0x30);
                drawPixel(row+4,col,0x30); drawPixel(row+4,col+1,0x30); drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 3:{
            if (row < 16) {
                drawPixel(row,col,0x06); drawPixel(row+2,col,0x06); drawPixel(row+4,col,0x06); drawPixel(row,col+1,0x06); drawPixel(row+2,col+1,0x06);
                drawPixel(row+4,col+1,0x06); drawPixel(row,col+2,0x06); drawPixel(row+1,col+2,0x06); drawPixel(row+2,col+2,0x06);
                drawPixel(row+3,col+2,0x06); drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30); drawPixel(row+2,col,0x30); drawPixel(row+4,col,0x30); drawPixel(row,col+1,0x30); drawPixel(row+2,col+1,0x30);
                drawPixel(row+4,col+1,0x30); drawPixel(row,col+2,0x30); drawPixel(row+1,col+2,0x30); drawPixel(row+2,col+2,0x30);
                drawPixel(row+3,col+2,0x30); drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 4:{
            if (row < 16){
                drawPixel(row,col,0x06); drawPixel(row+1,col,0x06); drawPixel(row+2,col,0x06); drawPixel(row+2,col+1,0x06);
                drawPixel(row+2,col+2,0x06); drawPixel(row,col+2,0x06); drawPixel(row+1,col+2,0x06); drawPixel(row+3,col+2,0x06);
                drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30); drawPixel(row+1,col,0x30); drawPixel(row+2,col,0x30); drawPixel(row+2,col+1,0x30);
                drawPixel(row+2,col+2,0x30); drawPixel(row,col+2,0x30); drawPixel(row+1,col+2,0x30); drawPixel(row+3,col+2,0x30);
                drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 5:{
            if ( row < 16 ){
                drawPixel(row,col,0x06);drawPixel(row+1,col,0x06);drawPixel(row+2,col,0x06);drawPixel(row+4,col,0x06);
                drawPixel(row,col+1,0x06);drawPixel(row+2,col+1,0x06);drawPixel(row+4,col+1,0x06);drawPixel(row,col+2,0x06);
                drawPixel(row+2,col+2,0x06);drawPixel(row+3,col+2,0x06);drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30);drawPixel(row+1,col,0x30);drawPixel(row+2,col,0x30);drawPixel(row+4,col,0x30);
                drawPixel(row,col+1,0x30);drawPixel(row+2,col+1,0x30);drawPixel(row+4,col+1,0x30);drawPixel(row,col+2,0x30);
                drawPixel(row+2,col+2,0x30);drawPixel(row+3,col+2,0x30);drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 6:{
            if ( row < 16 ){
                drawPixel(row,col,0x06);drawPixel(row+1,col,0x06);drawPixel(row+2,col,0x06);drawPixel(row+3,col,0x06);
                drawPixel(row+4,col,0x06);drawPixel(row,col+1,0x06);drawPixel(row+2,col+1,0x06);drawPixel(row+4,col+1,0x06);
                drawPixel(row,col+2,0x06);drawPixel(row+2,col+2,0x06);drawPixel(row+3,col+2,0x06);drawPixel(row+4,col+2,0x06);}
            else{
                drawPixel(row,col,0x30);drawPixel(row+1,col,0x30);drawPixel(row+2,col,0x30);drawPixel(row+3,col,0x30);
                drawPixel(row+4,col,0x30);drawPixel(row,col+1,0x30);drawPixel(row+2,col+1,0x30);drawPixel(row+4,col+1,0x30);
                drawPixel(row,col+2,0x30);drawPixel(row+2,col+2,0x30);drawPixel(row+3,col+2,0x30);drawPixel(row+4,col+2,0x30);
            }
            break;
        }
        case 7:{
            if ( row < 16 ){
                drawPixel(row,col,0x06);drawPixel(row,col+1,0x06);drawPixel(row,col+2,0x06);drawPixel(row+4,col+1,0x06);
                drawPixel(row+1,col+2,0x06);drawPixel(row+2,col+2,0x06);drawPixel(row+3,col+1,0x06);}
            else {
                drawPixel(row,col,0x30);drawPixel(row,col+1,0x30);drawPixel(row,col+2,0x30);drawPixel(row+4,col+1,0x30);
                drawPixel(row+1,col+2,0x30);drawPixel(row+2,col+2,0x30);drawPixel(row+3,col+1,0x30);
            }
            break;
        }
        case 8:{
            if (row < 16){
                drawPixel(row,col,0x06);drawPixel(row+1,col,0x06);drawPixel(row+2,col,0x06);drawPixel(row+3,col,0x06);drawPixel(row+4,col+2,0x06);
                drawPixel(row+4,col,0x06);drawPixel(row,col+1,0x06);drawPixel(row+2,col+1,0x06);drawPixel(row+4,col+1,0x06);
                drawPixel(row,col+2,0x06);drawPixel(row+1,col+2,0x06);drawPixel(row+2,col+2,0x06);drawPixel(row+3,col+2,0x06);}
            else {
                drawPixel(row,col,0x30);drawPixel(row+1,col,0x30);drawPixel(row+2,col,0x30);drawPixel(row+3,col,0x30);drawPixel(row+4,col+2,0x30);
                drawPixel(row+4,col,0x30);drawPixel(row,col+1,0x30);drawPixel(row+2,col+1,0x30);drawPixel(row+4,col+1,0x30);
                drawPixel(row,col+2,0x30);drawPixel(row+1,col+2,0x30);drawPixel(row+2,col+2,0x30);drawPixel(row+3,col+2,0x30);
            }
            break;
        }
        case 9:{
            if (row < 16){
                drawPixel(row,col,0x06);drawPixel(row+1,col,0x06);drawPixel(row+2,col,0x06);drawPixel(row+4,col,0x06);
                drawPixel(row,col+1,0x06);drawPixel(row+2,col+1,0x06);drawPixel(row+4,col+1,0x06);drawPixel(row,col+2,0x06);
                drawPixel(row+1,col+2,0x06);drawPixel(row+2,col+2,0x06);drawPixel(row+3,col+2,0x06);drawPixel(row+4,col+2,0x06);}
            else {
                drawPixel(row,col,0x30);drawPixel(row+1,col,0x30);drawPixel(row+2,col,0x30);drawPixel(row+4,col,0x30);
                drawPixel(row,col+1,0x30);drawPixel(row+2,col+1,0x30);drawPixel(row+4,col+1,0x30);drawPixel(row,col+2,0x30);
                drawPixel(row+1,col+2,0x30);drawPixel(row+2,col+2,0x30);drawPixel(row+3,col+2,0x30);drawPixel(row+4,col+2,0x30);
            }
            break;
        }
    }
}

LabGPIO r1(1,19); LabGPIO g1(0,29); LabGPIO b1(1,22); LabGPIO r2(1,20); LabGPIO g2(0,30); LabGPIO b2(1,23);
LabGPIO addrA(1,28); LabGPIO addrB(1,29); LabGPIO addrC(1,30); LabGPIO addrD(1,31);
LabGPIO oe(2,1); LabGPIO clk(2,0); LabGPIO latch(0,26);

LedMatrix::LedMatrix(){

}

void LedMatrix::init(){
    addrA.setAsOutput(); addrB.setAsOutput(); addrC.setAsOutput(); addrD.setAsOutput();
    latch.setAsOutput(); oe.setAsOutput(); clk.setAsOutput();
    r1.setAsOutput(); g1.setAsOutput(); b1.setAsOutput();
    r2.setAsOutput(); g2.setAsOutput(); b2.setAsOutput();

    addrA.setLow(); addrB.setLow(); addrC.setLow(); addrD.setLow();
    latch.setLow(); oe.setHigh(); clk.setLow();
    r1.setLow(); g1.setLow(); b1.setLow();
    r2.setLow(); g2.setLow(); b2.setLow();
    puts("init complete \n");
}

void LedMatrix::setEn(bool set)
{
    if (set == 1){
        oe.setLow();
    }
    else{
        oe.setHigh();
    }
}

void LedMatrix::setLatch(bool set)
{
    if (set == 1){
        latch.setLow();
    }
    else{
        latch.setHigh();
    }
}

void LedMatrix::selRow(uint8_t row)
{
    if(row == 0){
        addrA.setLow();addrB.setLow();addrC.setLow();addrD.setLow();
    } else if (row == 1){
        addrA.setHigh();addrB.setLow();addrC.setLow();addrD.setLow();
    } else if (row == 2){
        addrA.setLow();addrB.setHigh();addrC.setLow();addrD.setLow();
    } else if (row == 3){
        addrA.setHigh();addrB.setHigh();addrC.setLow();addrD.setLow();
    } else if (row == 4){
        addrA.setLow();addrB.setLow();addrC.setHigh();addrD.setLow();
    }else if (row == 5){
        addrA.setHigh();addrB.setLow();addrC.setHigh();addrD.setLow();
    }else if (row == 6){
        addrA.setLow();addrB.setHigh();addrC.setHigh();addrD.setLow();
    }else if (row == 7){
        addrA.setHigh();addrB.setHigh();addrC.setHigh();addrD.setLow();
    }else if (row == 8){
        addrA.setLow();addrB.setLow();addrC.setLow();addrD.setHigh();
    }else if (row == 9){
        addrA.setHigh();addrB.setLow();addrC.setLow();addrD.setHigh();
    }else if (row == 10){
        addrA.setLow();addrB.setHigh();addrC.setLow();addrD.setHigh();
    }else if (row == 11){
        addrA.setHigh();addrB.setHigh();addrC.setLow();addrD.setHigh();
    }else if (row == 12){
        addrA.setLow();addrB.setLow();addrC.setHigh();addrD.setHigh();
    }else if (row == 13){
        addrA.setHigh();addrB.setLow();addrC.setHigh();addrD.setHigh();
    }else if (row == 14){
        addrA.setLow();addrB.setHigh();addrC.setHigh();addrD.setHigh();
    }else if (row == 15){
        addrA.setHigh();addrB.setHigh();addrC.setHigh();addrD.setHigh();
    }
}

void LedMatrix::shiftleft(){
    for(uint8_t col=0;col<31;col++)
    {
        obsarray[col] = obsarray[col+1]; //move all element to the left except first one
    }
    obsarray[31] = 0;
    delay_ms(gamepace);
}

void LedMatrix::rotateleft(){
    for(uint8_t row=0;row<32;row++){
        uint8_t temp = matrixbuf[row][0];
        for(uint8_t col=0;col<31;col++)
        {
            matrixbuf[row][col] = matrixbuf[row][col+1]; //move all element to the left except first one
        }
        matrixbuf[row][31] = temp;
    }
    delay_ms(gamepace);
}

void LedMatrix::drawPixel(uint8_t x, uint8_t y, uint8_t c) {
    uint8_t row = x;
    uint8_t col = y;
    uint8_t color = c;

    if(x<16){
        if(color & 0x1) matrixbuf [row][col] += 0x1;
        if(color & 0x2) matrixbuf [row][col] += 0x2;
        if(color & 0x4) matrixbuf [row][col] += 0x4;
    } else if (15<x && x<32){
        if(color & 0x8) matrixbuf [row][col] += 0x8;
        if(color & 0x10) matrixbuf [row][col] += 0x10;
        if(color & 0x20) matrixbuf [row][col] += 0x20;
    } else return;

}

void LedMatrix::updateDisplay(){

    generateObstacle();
    drawBird(birdRow,birdCol);


    for(uint8_t row=0;row<32;row++){

        setEn(false);
        setLatch(false);
        if (row < 16){
            selRow(row);
        } else if( 15 < row ){
            selRow(row-16);
        }
        for(uint8_t col=0;col<32;col++){
            if(matrixbuf[row][col] & 0x1)
                b1.setHigh();
            else
                b1.setLow();
            if(matrixbuf[row][col] & 0x2)
                g1.setHigh();
            else
                g1.setLow();
            if(matrixbuf[row][col] & 0x4)
                r1.setHigh();
            else
                r1.setLow();
            if(matrixbuf[row][col] & 0x8)
                b2.setHigh();
            else
                b2.setLow();
            if(matrixbuf[row][col] & 0x10)
                g2.setHigh();
            else
                g2.setLow();
            if(matrixbuf[row][col] & 0x20)
                r2.setHigh();
            else
                r2.setLow();

            clk.setHigh();clk.setLow();
        }
        setLatch(true); //move shift register contents into parallel output register
        setEn(true); //turn on display
        delay_us(250);
    }
    clearDisplay();
}

void LedMatrix::updateDisplay2(){

    for(uint8_t row=0;row<32;row++){

        setEn(false);
        setLatch(false);
        if (row < 16){
            selRow(row);
        } else if( 15 < row ){
            selRow(row-16);
        }
        for(uint8_t col=0;col<32;col++){
            if(matrixbuf[row][col] & 0x1)
                b1.setHigh();
            else
                b1.setLow();
            if(matrixbuf[row][col] & 0x2)
                g1.setHigh();
            else
                g1.setLow();
            if(matrixbuf[row][col] & 0x4)
                r1.setHigh();
            else
                r1.setLow();
            if(matrixbuf[row][col] & 0x8)
                b2.setHigh();
            else
                b2.setLow();
            if(matrixbuf[row][col] & 0x10)
                g2.setHigh();
            else
                g2.setLow();
            if(matrixbuf[row][col] & 0x20)
                r2.setHigh();
            else
                r2.setLow();

            clk.setHigh();clk.setLow();
        }
        setLatch(true); //move shift register contents into parallel output register
        setEn(true); //turn on display
        delay_us(250);
    }
    //clearDisplay();
}


void LedMatrix::generateObstacle(){
    for(uint8_t col=0;col<32;col++){
        if ( obsarray[col] != 0){
            uint8_t obsHeight = obsarray[col];
            for(uint8_t x=8 ;x<32;x++){
                if ((x == obsHeight))
                {
                    x+=4;
                } else{
                    if (x<16){
                        matrixbuf [x][col] += 0x7;
                    }
                    else {
                        matrixbuf [x][col] += 0x38;
                    }
                }
            }
        }
    }
}

void LedMatrix::drawObstacle(){
    if(birdRow != 0 && birdCol != 0){
        //srand(time(NULL));
        uint8_t obsHeight = rand()%18+9;
        printf("%u \n",obsHeight);
        obsarray[30] = obsHeight;
        obsarray[31] = obsHeight;
        delay_ms(gamepace*13);
    }
}

void LedMatrix::drawBird(uint8_t row, uint8_t col){
    if(birdRow != 0 && birdCol != 0){
        if(row<16){
            drawPixel(row,col,0x5);
            drawPixel(row,col-2,0x5);
        } else {
            drawPixel(row,col,0x28);
            drawPixel(row,col-2,0x28);
        }
        if( (row-1) < 16){
            drawPixel(row-1,col-1,0x5);
        } else {
            drawPixel(row-1,col-1,0x28);
        }
        if( (row+1) < 16){
            drawPixel(row+1,col-1,0x5);
        } else {
            drawPixel(row+1,col-1,0x28);
        }
    }
}

void LedMatrix::gameBird(){

    LabGPIO button(1,10);
    button.setAsInput();
    while(1){
        if(button.getLevel()){
            birdRow--;
            u0_dbg_printf("Jump Detected \n");
        }else
        {
            birdRow++;
            u0_dbg_printf("Fall \n");
        }
        delay_ms(200);
    }
}


bool LedMatrix::detectCollision(){

    // printf("Value of birdRow in detectCollision is : %d", birdRow);
    if( birdRow < 10 || birdRow > 29){
        birdRow = 0;
        birdCol = 0;
        cleanDisplay();
        for(int i=0;i<32;i++){
            obsarray[i] = 0;
        }
        return true;
    } else {
        for(int col=4; col<7; col++){
            for(int row=0; row<16; row++){

                if (matrixbuf[row][col] == 0x0C){
                    birdRow = 0;
                    birdCol = 0;
                    cleanDisplay();
                    for(int i=0;i<32;i++){
                        obsarray[i] = 0;
                    }
                    return true;
                }
                if (matrixbuf[row+16][col] == 0x60){
                    birdRow = 0;
                    birdCol = 0;
                    cleanDisplay();
                    for(int i=0;i<32;i++){
                        obsarray[i] = 0;
                    }
                    return true;
                }

            }
        }
    }
    return false;
}

void LedMatrix::displayScore(){
    bool printneeded = false;
    int temp = 1;
    if (obsarray[3] != 0){
        gamescore++;
        temp++;
        if (temp % 2 == 0){
            printneeded = true;
        }
    }
    score = gamescore/2;
    score_tens = score/10;
    score_units = score - (score_tens*10);
    printf("the score is : %d \n", score);
    if( printneeded == true ){
        for(int row=1;row<6;row++){
            for(int col=22;col<30;col++){
                matrixbuf[row][col] = 0;
            }
        }
        displayNumber(1,23,score_tens);
        displayNumber(1,27,score_units);
        printneeded = false;
    }
    delay_ms(gamepace);
}

void LedMatrix::startScreen(){
    //memcpy(matrixbuf, startScreen, sizeof(matrixbuf));
}

void LedMatrix::gameStart(){
    memcpy(matrixbuf, gameScreen, sizeof(matrixbuf));
    displayNumber(1,23,score_tens);
    displayNumber(1,27,score_units);
}

void LedMatrix::clearDisplay(){
    for(uint8_t row=8;row<32;row++){
        for(uint8_t col=0;col<32;col++)
        {
            matrixbuf[row][col] = 0;
        }
    }
}

void LedMatrix::cleanDisplay(){
    for(uint8_t row=0;row<32;row++){
        for(uint8_t col=0;col<32;col++)
        {
            matrixbuf[row][col] = 0;
        }
    }
}

void LedMatrix::gameOver(){
    memcpy(matrixbuf, GameOver, sizeof(matrixbuf));
    displayNumber(20,24,score_tens);
    displayNumber(20,28,score_units);
}
