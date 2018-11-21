//
// Created by tentonlien on 5/25/18.
//

#ifndef ZENVM_EXECUTEMODULE_H
#define ZENVM_EXECUTEMODULE_H

// Transfer Instructions
void zen_ins_mov();
void zen_ins_glob();
void zen_ins_xchg();
void zen_ins_push();
void zen_ins_pop();

// Arithmetic Instructions
void zen_ins_add();
void zen_ins_inc();
void zen_ins_sub();
void zen_ins_dec();
void zen_ins_cmp();
void zen_ins_mul();
void zen_ins_div();
void zen_ins_sqrt();

// Logic Instructions
void zen_ins_and();
void zen_ins_or();
void zen_ins_not();
void zen_ins_xor();
void zen_ins_shl();
void zen_ins_shr();
void zen_ins_sal();
void zen_ins_sar();
void zen_ins_rol();
void zen_ins_ror();

// Control Instructions
void zen_ins_call();
void zen_ins_ret();
void zen_ins_loop();
void zen_ins_jmp();
void zen_ins_je();
void zen_ins_jne();
void zen_ins_jg();
void zen_ins_jl();
void zen_ins_jge();
void zen_ins_jle();

void zen_ins_prog();
void zen_ins_sys();
void zen_ins_cons();
void zen_ins_file();
void zen_ins_net();


#endif //ZENVM_EXECUTEMODULE_H