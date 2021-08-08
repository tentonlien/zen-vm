//
// Created by Tenton on 5/12/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../zenvm.h"
#include "../instructions.h"


void zen_ins_add() {
    local_data_seg[operand_1].value = local_data_seg[operand_2].value + local_data_seg[operand_3].value;
}


void zen_ins_inc() {
    local_data_seg[operand_1].value ++;
}


void zen_ins_sub() {
    local_data_seg[operand_1].value = local_data_seg[operand_2].value - local_data_seg[operand_3].value;
}


void zen_ins_dec() {
    local_data_seg[operand_1].value --;
}


void zen_ins_cmp() {
    long long _long;

    unsigned char sf;  // flag_register & 0x80 & 1000 0000
    unsigned char zf;  // flag_register & 0x40 & 0100 0000
    
    if (_long == 0) {
        zf = 1;
    } else if (_long < 0) {
        sf = 1;
    }

    flag_register = (sf << 7) + (zf << 6);
}


void zen_ins_mul() {
    local_data_seg[operand_1].value = local_data_seg[operand_2].value * local_data_seg[operand_3].value;
}


void zen_ins_div() {
    //global_data_seg[dst_operand].value /= src_operand_value.value;
}


void zen_ins_sqrt() {
    // TODO
}