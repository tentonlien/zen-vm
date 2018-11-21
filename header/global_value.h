//
// Created by tentonlien on 5/25/18.
//

#ifndef ZENVM_GLOBALVALUE_H
#define ZENVM_GLOBALVALUE_H

struct data_unit {
    unsigned int type;
    unsigned int length;
    unsigned long long value;
};

struct subroutine {
    struct data_unit* data_seg;
    unsigned int* ins_seg;
};

int execute(struct subroutine);

unsigned int stack_size;

struct data_unit* stack_table;
struct data_unit* global_data_seg;
struct subroutine* subroutines;

struct data_unit* local_data_seg;


unsigned char flag_register;
unsigned short stack_pointer;
unsigned long long base_pointer;
unsigned int ip;
unsigned int last_ip;

unsigned long long operand_1;
unsigned long long operand_2;
unsigned long long operand_3;

#endif //ZENVM_GLOBALVALUE_H