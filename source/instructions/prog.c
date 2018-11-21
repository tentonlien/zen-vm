//
// Created by Tenton on 11/15/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/instruction_list.h"
#include "../../header/global_value.h"

extern double timer_stop();
extern double storeTime;

void zen_ins_prog() {
    // End current process (Exit Program)
    if (operand_1 == 0) {
        // Output time cost information
        if (storeTime >= 0) {
            timer_stop();
        }
        exit((int)operand_2);
    }

    // Create new process
    else if (operand_2 == 1) {

    }
}