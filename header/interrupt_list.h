//
// Created by Tenton on 6/23/2018.
//

#ifndef ZEN_VIRTUAL_MACHINE_INTERRUPT_LIST_H
#define ZEN_VIRTUAL_MACHINE_INTERRUPT_LIST_H

// System
void int_00h();  // Quit the program
void int_02h();  // System time

// IO
void int_10h();  // Input
void int_11h();  // Output
void int_12h();  // Clear screen
void int_13h();  // File info
void int_14h();  // Read File
void int_15h();  // Write File
void int_16h();  // Copy File
void int_17h();  // Move File
void int_18h();  // Delete File

// Network

// Thread

#endif //ZEN_VIRTUAL_MACHINE_INTERRUPT_LIST_H
