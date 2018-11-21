//
// Created by Tenton on 11/15/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../header/instruction_list.h"
#include "../../header/global_value.h"

void sys_time() {
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    // char* str = asctime(tm);
    // dx -> value = str;
 /*
    switch (operand_2) {
        case 0x00: dx -> value = asctime(tm); break;
        case 0x01: dx -> value = tm -> tm_sec; break;
        case 0x02: dx -> value = tm -> tm_min; break;
        case 0x03: dx -> value = tm -> tm_hour; break;
        case 0x04: dx -> value = tm -> tm_mday; break;
        case 0x05: dx -> value = tm -> tm_mon + 1; break;
        case 0x06: dx -> value = tm -> tm_year + 1900; break;
        case 0x07: dx -> value = tm -> tm_wday; break;
        case 0x08: dx -> value = tm -> tm_isdst; break;
        case 0x09: dx -> value = tm -> tm_gmtoff; break;
        case 0x0A: dx -> value = tm -> tm_zone; break;
        default:
            printf("Error: Invalid argument for INT 02H in AX register.\n");
    }
*/
}

void zen_ins_sys() {
    printf("sys\n");
}