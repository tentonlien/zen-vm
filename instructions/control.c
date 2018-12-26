//
// Created by Tenton on 5/12/2018.
//

#include <stdio.h>
#include "../zenvm.h"
#include "../instructions.h"

// All the control instructions only allow immediate as dst_operand



unsigned char sf_value() {
    return (flag_register & 0x80) >> 7;  // & 1000 0000
}

unsigned char zf_value() {
    return (flag_register & 0x40) >> 6;  // & 0100 0000
}

void zen_ins_call() {
}


void zen_ins_ret() {
    //ip = last_ip;
}


void zen_ins_loop() {
    global_data_seg[2].value --;
    if (global_data_seg[2].value > 0) {
        ip = operand_2;
        //ip = dst_operand_value.value;
    }
}


void zen_ins_jmp() {
    last_ip = ip;
    //ip = dst_operand_value.value;
}


void zen_ins_je() {
    if (zf_value() == 1) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}


void zen_ins_jne() {
    if (zf_value() == 0) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}


void zen_ins_jg() {
    if (sf_value() == 0) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}


void zen_ins_jl() {
    if (sf_value() == 1) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}


void zen_ins_jge() {
    if (zf_value() == 1 || sf_value() == 0) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}


void zen_ins_jle() {
    if (zf_value() == 1 || sf_value() == 1) {
        last_ip = ip;
        //ip = dst_operand_value.value;
    } else {
        ip ++;
    }
}