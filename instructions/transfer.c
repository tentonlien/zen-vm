//
// Created by Tenton on 6/26/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "../zenvm.h"
#include "../instructions.h"

void zen_ins_mov() {
    global_data_seg[operand_1].value = global_data_seg[operand_2].value;
}


void zen_ins_glob() {
    // printf("glob: %d %lld\n", operand_1, (operand_2 << 8) + operand_3);
    local_data_seg[operand_1] = global_data_seg[(operand_2 << 8) + operand_3];
}


void zen_ins_xchg() {
    struct data_unit swap;
    swap = global_data_seg[operand_1];
    local_data_seg[operand_1] = local_data_seg[operand_2];
    local_data_seg[operand_2] = swap;
}


void zen_ins_push() {
    if (stack_pointer >= stack_size) {
        printf("Error: Stack overflow.\n");
        exit(0);
    }
    stack_table[stack_pointer] = local_data_seg[operand_1];
    stack_pointer ++;
}


void zen_ins_pop() {
    if (stack_pointer <= 0) {
        printf("Error: Stack underflow.");
        exit(0);
    }
    local_data_seg[operand_1] = stack_table[stack_pointer - 1];
    stack_pointer --;
}