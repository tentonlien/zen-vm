//
// Created by Tenton on 11/15/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "../zenvm.h"
#include "../instructions.h"

extern double timer_stop();
extern double storeTime;

void zen_ins_prog() {
    // End current process (Exit Program)
    if (operand_1 == 0) {
        // Output time cost information
        if (storeTime >= 0) {
            timer_stop();
        }
        //printf("%ld %d", (operand_2 << 8) + operand_3  , operand_3);
        
        exit((int)((operand_2 << 8)+ operand_3));
    }

    // Create new process
    else if (operand_2 == 1) {

    }
}