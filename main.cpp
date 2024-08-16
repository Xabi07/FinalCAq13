/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"
#include "string.h"
#include <cstdio>


DigitalOut myled(LED1);
//Serial pc(USBRX, USBTX);
UnbufferedSerial pc(USBTX, USBRX);      //added UnbufferedSerial to work for Mbed
//Serial dev(p9, p10);                  //commented out errorenous code
UnbufferedSerial dev(PC_6, PC_7);       //corrected pins names


char buff;                             //added char buff - to store the read data from serial port
void dev_recv(){
    while(dev.readable()){
        //pc.putc(dev.getc());          //commented out erronous code    
        dev.read(&buff,1);              //dev.read reads data to buff
        pc.write(&buff,1);              //pc.write writes the data read by dev.read
    }    
}

void pc_recv(){
    while(pc.readable()){
        //dev.putc(pc.getc());          //commented out erronous code   
        pc.read(&buff,1);              //pc.read reads data to buff
        dev.write(&buff,1);             //dev.write writes the data read by pc.read  
    }    
}

int main() {
    pc.baud(9600);
    //device1.baud(115200);         //commented out incorrect code
    dev.baud(9600);                 //corrected line above
    pc.attach(pc_recv);             //corrected erronous code pointed it pc_recv function
    dev.attach(dev_recv);           //corrected code and pointed dev.attach to fev_recv function
    printf("Hello!! \r\n");         //pc.printf removed it will not work with UnbufferedSerial
    
    while(1) {
        myled = 1;
        //wait(1);                  //removed wait(1) it will not work with Mbed
        ThisThread::sleep_for(1s);  //added a wait that works with MBED 
        myled = 0;
        //wait(1);                  //removed wait(1) it will not work with Mbed
        ThisThread::sleep_for(1s);  //added a wait that works with MBED
    }
}