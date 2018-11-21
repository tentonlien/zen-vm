/* ZenVM v0.1
 * Last Modified: 10/5/2018
 * Bytecode Interpreter of Zen Programming Language
 * Zenlang: An interpreted language created at 8:28 PM, 4/26/2018.
 * Copyright Tenton Lien. All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../header/global_value.h"
#include "../header/instruction_list.h"

#define magic_number 0x214e455a
#define bytecode_version 1

unsigned int* bytecode_stream;
unsigned long long bytecode_pointer;

struct data_unit* create_data_seg(struct data_unit* data_seg) {
    // Allocate memory for data segment
    data_seg = malloc((bytecode_stream[bytecode_pointer]) * 16);
    bytecode_pointer ++;
    unsigned int constant_amount = bytecode_stream[bytecode_pointer];
    bytecode_pointer ++;

    // Write Constant into global data segment
    for (int i = 0; i < constant_amount; i ++) {
        unsigned int constant_type = bytecode_stream[bytecode_pointer];
        data_seg[i].type = constant_type;
        bytecode_pointer ++;

        // Literal variables
        if (constant_type < 2) {
            unsigned long long* constant_value = (unsigned long long*)(bytecode_stream + bytecode_pointer);
            data_seg[i].value = *constant_value;
            bytecode_pointer += 2;
        }

        // Reference variables
        else {
            unsigned int array_size = bytecode_stream[bytecode_pointer];
            data_seg[i].length = array_size;
            bytecode_pointer ++;

            unsigned int heap_size = bytecode_stream[bytecode_pointer];
            bytecode_pointer ++;

            unsigned int* new_heap;
            new_heap = malloc(heap_size * 4);
            
            for (int k = 0; k < heap_size; k ++) {
                new_heap[k] = bytecode_stream[bytecode_pointer];
                bytecode_pointer ++;
            }
            switch (constant_type) {
                case 0x02: data_seg[i].value = (unsigned char*)new_heap; break;
                case 0x03: data_seg[i].value = (unsigned short*)new_heap; break;
                case 0x04: data_seg[i].value = new_heap; break;
                case 0x05: data_seg[i].value = (unsigned long long*)new_heap; break;
                case 0x06: data_seg[i].value = (float*)new_heap; break;
                case 0x07: data_seg[i].value = (double*)new_heap; break;
                default:   break;
            }
        }
    }
    return data_seg;
}

void global_handler() {
    // Check magic number
    if ((bytecode_stream[bytecode_pointer]) == magic_number) {
        bytecode_pointer ++;

    } else {
        printf("Error: Invalid Zen executable file.\n");
        exit(0);
    }

    // Check bytecode version
    if (bytecode_stream[bytecode_pointer] != bytecode_version) {
        printf("Error: Unsupported bytecode version. ZenVM Version %d is required.\n", bytecode_stream[bytecode_pointer]);
        exit(0);
    } else {
        bytecode_pointer ++;
    }

    // Allocate memory for public stack
    stack_size = bytecode_stream[bytecode_pointer];
    stack_table = malloc(bytecode_stream[bytecode_pointer] * 8);
    bytecode_pointer ++;

    // Allocate memory for global data segment
    global_data_seg = create_data_seg(global_data_seg);
}

void local_handler() {
    unsigned int subroutine_amount = bytecode_stream[bytecode_pointer];
    subroutines = malloc(sizeof(struct subroutine) * subroutine_amount);
    bytecode_pointer ++;

    for (unsigned int i = 0; i < subroutine_amount; i ++) {
        subroutines[i].data_seg = create_data_seg(subroutines[i].data_seg);

        // Create instruction segment
        unsigned int ins_amount = bytecode_stream[bytecode_pointer];
        unsigned int* ins_seg = malloc(4 * ins_amount);
        subroutines[i].ins_seg = ins_seg;
        bytecode_pointer ++;

        for (unsigned int k = 0; k < ins_amount; k ++) {
            ins_seg[k] = bytecode_stream[bytecode_pointer];
            bytecode_pointer ++;
        }
    }
    
    execute(subroutines[0]);
}


int execute(struct subroutine sub) {
    local_data_seg = sub.data_seg;
    ip = 0;  // Instruction pointer

    while (1) {
        unsigned char opcode = (sub.ins_seg[ip] & 0xFF000000) >> 24;
        operand_1 = (sub.ins_seg[ip] & 0x00FF0000) >> 16;
        operand_2 = (sub.ins_seg[ip] & 0x0000FF00) >> 8;
        operand_3 = (sub.ins_seg[ip] & 0x000000FF);

        switch (opcode) {
            case 0x00: zen_ins_mov(); break;
            case 0x01: zen_ins_glob(); break;
            case 0x02: zen_ins_xchg(); break;
            case 0x03: zen_ins_push(); break;
            case 0x04: zen_ins_pop(); break;

            case 0x10: zen_ins_add(); break;
            case 0x11: zen_ins_inc(); break;
            case 0x12: zen_ins_sub(); break;
            case 0x13: zen_ins_dec(); break;
            case 0x14: zen_ins_cmp(); break;
            case 0x15: zen_ins_mul(); break;
            case 0x16: zen_ins_div(); break;

            case 0x20: zen_ins_and(); break;
            case 0x21: zen_ins_or(); break;
            case 0x22: zen_ins_not(); break;

            case 0x30: zen_ins_call(); break;
            case 0x31: return 0;  // zen__ins_ret
            case 0x32: zen_ins_loop(); break;
            case 0x33: zen_ins_jmp(); break;
            case 0x34: zen_ins_je(); break;
            case 0x35: zen_ins_jne(); break;
            case 0x36: zen_ins_jg(); break;
            case 0x37: zen_ins_jl(); break;
            case 0x38: zen_ins_jge(); break;
            case 0x39: zen_ins_jle(); break;

            case 0x40: zen_ins_prog(); break;
            case 0x41: zen_ins_sys(); break;
            case 0x42: zen_ins_cons(); break;
            case 0x43: zen_ins_file(); break;
            case 0x44: zen_ins_net(); break;
        
            default:
                printf("Error: Invalid instruction: 0x%x\n", opcode);
                exit(1);
        }
        ip ++;
    }
}

double storeTime = -1;

int timer_start() {
    struct timespec timeStamp;
    timespec_get(&timeStamp, TIME_UTC);
    storeTime = (long long)timeStamp.tv_sec + (double)timeStamp.tv_nsec / 1000000000;
    return 0;
}

void timer_stop() {
    struct timespec timeStamp;
    timespec_get(&timeStamp, TIME_UTC);
    double currentTime = (long long)timeStamp.tv_sec + (double)timeStamp.tv_nsec / 1000000000;
    printf("\n");
    for(int _count = 0; _count < 40; _count ++) {
        printf("-");
    }
    printf("\nProcess exited after %lf seconds\n", currentTime - storeTime);
}


int main(int argc, char* argv[]) {
    if (argc == 2 && argv[1][0] != '-') {}

    // If retrieving no args
    else if (argc == 1) {
        printf("zvm [-options] *.zef\n");
        return 0;
    }

    // Return version info
     else if (strcmp(argv[1], "-version") == 0) {
        printf("Zen VM version %d\nCopyright 2018 Tenton Lien. All Rights Reserved.\n", bytecode_version);
        return 0;
    }

    // Calculate the executing time
    else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        argv[1] = argv[2];
        timer_start();
    }
    
    else {
        printf("Invalid argument. Type -help for more info.\n");
        return 0;
    }

    FILE *fp;
    long long bytecode_length;

    if ((fp = fopen(argv[1],"rb")) == NULL) {
        printf("Error: Load bytecode file failed...\n");
        return 0;

    } else {
        // Load the bytecode into bytecode_stream
        fseek(fp,0,SEEK_END);
        bytecode_length = ftell(fp);
        bytecode_stream = malloc(bytecode_length);
        fseek(fp,0,SEEK_SET);
        fread(bytecode_stream,sizeof(char),bytecode_length,fp);
        fclose(fp);
    }

    global_handler();  // Set global parameters
    local_handler();
    free(bytecode_stream);
    return 0;
}