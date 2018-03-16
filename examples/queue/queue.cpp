#include <Arduino.h>
#include <RAExecutionQueue.h>

/*
Simple example of RAExecutionQueue in action.  LEDs are connected to
pins 12 & 11 with 220ohm resisters and a button connected to pin 3
*/

// Create an execution queue
RAExecutionQueue appQueue;
// States for the LEDs
int state1 = 0;
int state2 = 0;

// Invert the state at pin 12 and write
void process1() {
    state1 = !state1;
    digitalWrite(12,state1);
}

// Invert the state at pin 11 and write
void process2() {
    state2 = !state2;
    digitalWrite(11,state2);
}

// If ID 1 is running, stop it.  If it's stopped, start it.
void process3() {
    appQueue.invertQueueItemRunning(1);
}

// Invert the running status of process id 0 via an interrupt on pin 3
void interrupt3() {
    appQueue.invertQueueItemRunning(0);
}

void setup() {
    // pinMode only used for the LEDs
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    // Add process1 to the queue and tell it to execute every 100 millis
    // The Queue is an array of RAQueueItem so the first number is the
    // position in the Vector so do these in order.
    appQueue.addProcess(0,process1,100);
    appQueue.addProcess(1,process2,50);
    // Checks the job 1's running status and inverts it.
    appQueue.addProcess(2,process3,300);
    // Add a process attached to interrupt pin 3
    appQueue.addHardwareInterrupt(3,interrupt3,RISING);
    // This sets a common start time for all queue items and sets them all to be processed.
    appQueue.start();
}

void loop() {
    // Process all of the jobs on the queue
    appQueue.processQueue();
}
