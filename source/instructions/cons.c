//
// Created by Tenton on 11/15/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../header/instruction_list.h"
#include "../../header/global_value.h"

// INT 10H : Input
void cons_input() {
    
    union {
        long long _int;
        double _float;
        char _string[100];
    } var;

    switch(operand_2) {
        case 0x00:  // int
            scanf("%lld", &var._int);
            local_data_seg[operand_3].value = var._int;
            break;

        case 0x01:  // float
            scanf("%lf", &var._float);
            local_data_seg[operand_3].value = var._float;
            break;

        case 0x02:  // char
            scanf("%c", &var._int);
            local_data_seg[operand_3].value = var._int;
            break;

        case 0x03:  // string
            scanf("%s", var._string);
            local_data_seg[operand_3].value = var._string;
            break;

        default:
            printf("\nError: Invalid argument \"0x%llx\" for INT 10H in AX register.\n", operand_2);
            exit(0);
    }
    
}

// INT 11H : Output
void cons_output() {
    switch(operand_2) {
        case 0x00:  // int
            printf("%lld", local_data_seg[operand_3].value);
            break;

        case 0x01:  // float
            printf("%lf", local_data_seg[operand_3].value);
            break;

        case 0x02:  // char
            printf("%c", local_data_seg[operand_3].value);
            break;

        case 0x03:  // string
            printf("%s", (char*)(local_data_seg[operand_3].value));
            break;

        case 0x04:  // space
            printf(" ");
            break;

        case 0x05:  // string
            printf("\n");
            break;

        default:
            printf("\nError: Invalid argument \"0x%llx\" for INT 10H in AX register.\n", operand_2);
            exit(0);
    }
}


// INT 12H : Clear screen
void cons_clear() {
    
}

void zen_ins_cons() {
    switch(operand_1) {
        case 0x00: cons_input(); break;
        case 0x01: cons_output(); break;
        case 0x02: break;
        default: break;
    }
}