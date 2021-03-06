/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 *          FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *          @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include "tasks.hpp"
#include "examples/examples.hpp"
#include <sys/_stdint.h>
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

/**
 * The main() creates tasks or "threads".  See the documentation of scheduler_task class at scheduler_task.hpp
 * for details.  There is a very simple example towards the beginning of this class's declaration.
 *
 * @warning SPI #1 bus usage notes (interfaced to SD & Flash):
 *      - You can read/write files from multiple tasks because it automatically goes through SPI semaphore.
 *      - If you are going to use the SPI Bus in a FreeRTOS task, you need to use the API at L4_IO/fat/spi_sem.h
 *
 * @warning SPI #0 usage notes (Nordic wireless)
 *      - This bus is more tricky to use because if FreeRTOS is not running, the RIT interrupt may use the bus.
 *      - If FreeRTOS is running, then wireless task may use it.
 *        In either case, you should avoid using this bus or interfacing to external components because
 *        there is no semaphore configured for this bus and it should be used exclusively by nordic wireless.
 */

LabGPIO reset(1,9);
LedMatrix Matrix;
uint16_t delay = 200;
bool restart = false;

class gameStart: public scheduler_task
{
public:
    gameStart(uint8_t priority): scheduler_task("gameStart", 2048, priority){
        reset.setAsInput();
    }
    bool run(void *p)
    {
        if ( restart == true ){
            Matrix.gamescore = 0;
            Matrix.score = 0;
            Matrix.score_tens = 0;
            Matrix.score_units = 0;
            scheduler_task *updateDisplay= getTaskPtrByName("updateDisplay");
            if(NULL != updateDisplay){
                vTaskResume(updateDisplay->getTaskHandle());
            }
            scheduler_task *gameBird= getTaskPtrByName("gameBird");
            if(NULL != gameBird){
                vTaskResume(gameBird->getTaskHandle());
            }
            scheduler_task *drawObstacle= getTaskPtrByName("drawObstacle");
            if(NULL != drawObstacle){
                vTaskResume(drawObstacle->getTaskHandle());
            }
            scheduler_task *shiftLeft= getTaskPtrByName("shiftLeft");
            if(NULL != shiftLeft){
                vTaskResume(shiftLeft->getTaskHandle());
            }
            scheduler_task *displayScore= getTaskPtrByName("displayScore");
            if(NULL != displayScore){
                vTaskResume(displayScore->getTaskHandle());
            }
            scheduler_task *detectCollision= getTaskPtrByName("detectCollision");
            if(NULL != detectCollision){
                vTaskResume(detectCollision->getTaskHandle());
            }
            restart = false;
        }

        memcpy(Matrix.matrixbuf, Matrix.startscreen, sizeof(Matrix.matrixbuf));
        Matrix.updateDisplay2();
        if(reset.getLevel() == 1){
            Matrix.clearDisplay();
            Matrix.gameStart();
            printf("Suspended the task");
            Matrix.birdCol = 6;
            Matrix.birdRow = 14;
            suspend();
        }
        return true;
    }
};

class updateDisplayTask: public scheduler_task
{
public :
    updateDisplayTask(uint8_t priority): scheduler_task("updateDisplay", 2048, priority){
        }
        bool run(void *p)
        {
            Matrix.updateDisplay();
            return true;
        }
};

class shiftLeftTask: public scheduler_task
{
public :
    shiftLeftTask(uint8_t priority): scheduler_task("shiftLeft", 2048, priority){
        }
        bool run(void *p)
        {
            Matrix.shiftleft();
            delay_ms(delay);
            return true;
        }
};

class rotateLeftTask: public scheduler_task
{
public :
    rotateLeftTask(uint8_t priority): scheduler_task("rotateLeft", 2048, priority){
        }
        bool run(void *p)
        {
            Matrix.rotateleft();
            delay_ms(delay);
            return true;
        }
};

class drawObstacleTask: public scheduler_task
{
public :
    drawObstacleTask(uint8_t priority): scheduler_task("drawObstacle", 2048, priority){
        }
        bool run(void *p)
        {
            Matrix.drawObstacle();
            delay_ms(delay*13);
            return true;
        }
};

class gameBird: public scheduler_task
{
public :
    gameBird(uint8_t priority): scheduler_task("gameBird", 2048, priority){
        }
        bool run(void *p)
        {
            Matrix.gameBird();
            return true;
        }
};

class gameOver: public scheduler_task
{
public :
    gameOver(uint8_t priority): scheduler_task("gameOver", 2048, priority){
        }
        bool run(void *p)
        {
            for(int i = 0; i< 600; i++){
            Matrix.gameOver();
            Matrix.updateDisplay2();
            delay_ms(1);
            }
            restart = true;
            scheduler_task *gameStart= getTaskPtrByName("gameStart");
            if(NULL != gameStart){
                vTaskResume(gameStart->getTaskHandle());
            }
            delay_ms(1);
            return true;
        }
};

class detectCollision: public scheduler_task
{
public :
    detectCollision(uint8_t priority): scheduler_task("detectCollision", 2048, priority){
    }
    bool run(void *p)
    {
        bool result = 0;
        result = Matrix.detectCollision();
        if( result == 1 ){
            printf("Collison Detected \n");
            Matrix.updateDisplay2();
            scheduler_task *updateDisplay= getTaskPtrByName("updateDisplay");
            if(NULL != updateDisplay){
                vTaskSuspend(updateDisplay->getTaskHandle());
            }
            scheduler_task *gameBird= getTaskPtrByName("gameBird");
            if(NULL != gameBird){
                vTaskSuspend(gameBird->getTaskHandle());
            }
            scheduler_task *drawObstacle= getTaskPtrByName("drawObstacle");
            if(NULL != drawObstacle){
                vTaskSuspend(drawObstacle->getTaskHandle());
            }
            scheduler_task *shiftLeft= getTaskPtrByName("shiftLeft");
            if(NULL != shiftLeft){
                vTaskSuspend(shiftLeft->getTaskHandle());
            }
            scheduler_task *displayScore= getTaskPtrByName("displayScore");
            if(NULL != displayScore){
                vTaskSuspend(displayScore->getTaskHandle());
            }
            suspend();
        }
        delay_ms(delay);
        return true;
    }
};

class displayScore: public scheduler_task
{
public:
    displayScore(uint8_t priority): scheduler_task("displayScore", 2048, priority){
    }
    bool run(void *p)
    {
        Matrix.displayScore();
        delay_ms(delay);
        return true;
    }
};


int main(void)
{
    /**
     * A few basic tasks for this bare-bone system :
     *      1.  Terminal task provides gateway to interact with the board through UART terminal.
     *      2.  Remote task allows you to use remote control to interact with the board.
     *      3.  Wireless task responsible to receive, retry, and handle mesh network.
     *
     * Disable remote task if you are not using it.  Also, it needs SYS_CFG_ENABLE_TLM
     * such that it can save remote control codes to non-volatile memory.  IR remote
     * control codes can be learned by typing the "learn" terminal command.
     */
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));

    /* Consumes very little CPU, but need highest priority to handle mesh network ACKs */
    scheduler_add_task(new wirelessTask(PRIORITY_CRITICAL));

    /* Change "#if 0" to "#if 1" to run period tasks; @see period_callbacks.cpp */
    #if 0
    const bool run_1Khz = false;
    scheduler_add_task(new periodicSchedulerTask(run_1Khz));
    #endif

    /* The task for the IR receiver to "learn" IR codes */
    // scheduler_add_task(new remoteTask  (PRIORITY_LOW));

    /* Your tasks should probably used PRIORITY_MEDIUM or PRIORITY_LOW because you want the terminal
     * task to always be responsive so you can poke around in case something goes wrong.
     */

    /**
     * This is a the board demonstration task that can be used to test the board.
     * This also shows you how to send a wireless packets to other boards.
     */
    #if 0
        scheduler_add_task(new example_io_demo());
    #endif

    /**
     * Change "#if 0" to "#if 1" to enable examples.
     * Try these examples one at a time.
     */
    #if 0
        scheduler_add_task(new example_task());
        scheduler_add_task(new example_alarm());
        scheduler_add_task(new example_logger_qset());
        scheduler_add_task(new example_nv_vars());
    #endif

    /**
     * Try the rx / tx tasks together to see how they queue data to each other.
     */
    #if 0
        scheduler_add_task(new queue_tx());
        scheduler_add_task(new queue_rx());
    #endif

    /**
     * Another example of shared handles and producer/consumer using a queue.
     * In this example, producer will produce as fast as the consumer can consume.
     */
    #if 0
        scheduler_add_task(new producer());
        scheduler_add_task(new consumer());
    #endif

    /**
     * If you have RN-XV on your board, you can connect to Wifi using this task.
     * This does two things for us:
     *   1.  The task allows us to perform HTTP web requests (@see wifiTask)
     *   2.  Terminal task can accept commands from TCP/IP through Wifly module.
     *
     * To add terminal command channel, add this at terminal.cpp :: taskEntry() function:
     * @code
     *     // Assuming Wifly is on Uart3
     *     addCommandChannel(Uart3::getInstance(), false);
     * @endcode
     */
    #if 0
        Uart3 &u3 = Uart3::getInstance();
        u3.init(WIFI_BAUD_RATE, WIFI_RXQ_SIZE, WIFI_TXQ_SIZE);
        scheduler_add_task(new wifiTask(Uart3::getInstance(), PRIORITY_LOW));
    #endif

    #if 1
        Matrix.init();
        scheduler_add_task(new updateDisplayTask(PRIORITY_MEDIUM));
        scheduler_add_task(new gameStart(PRIORITY_HIGH));
        scheduler_add_task(new gameBird(PRIORITY_MEDIUM));
        scheduler_add_task(new drawObstacleTask(PRIORITY_MEDIUM));
        scheduler_add_task(new shiftLeftTask(PRIORITY_MEDIUM));
        scheduler_add_task(new displayScore(PRIORITY_MEDIUM));
        scheduler_add_task(new detectCollision(PRIORITY_MEDIUM));
        scheduler_add_task(new gameOver(PRIORITY_LOW));
        //scheduler_add_task(new rotateLeftTask(PRIORITY_LOW));
        scheduler_start();
    #endif

    scheduler_start(); ///< This shouldn't return
    return -1;
}
