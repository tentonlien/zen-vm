//
// Created by Tenton on 5/12/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../header/instruction_list.h"
#include "../../header/global_value.h"


void zen_ins_add() {
    //global_data_seg[dst_operand].value += src_operand_value.value;
}


void zen_ins_inc() {
    //global_data_seg[dst_operand].value ++;
}


void zen_ins_sub() {
    //global_data_seg[dst_operand].value -= src_operand_value.value;
}


void zen_ins_dec() {
    //global_data_seg[dst_operand].value --;
}


void zen_ins_cmp() {
    long long _long;
    //_long = global_data_seg[dst_operand].value - src_operand_value.value;

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
    //global_data_seg[dst_operand].value *= src_operand_value.value;
}


void zen_ins_div() {
    //global_data_seg[dst_operand].value /= src_operand_value.value;
}


void zen_ins_sqrt() {
    // TODO
}