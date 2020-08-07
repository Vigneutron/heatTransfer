//
//  9P-functions.h
//  9P
//
//  Created by Rainor Vigneault on 12/14/19.
//  Copyright © 2019 Rainor Vigneault. All rights reserved.
//

#include <stdio.h>
#include <math.h>


void initialize_plate(double cell_temp[8][6], double temp1, double temp2);

void display_plate(double heat_plate[8][6], double heater1, double heater2, int which_time);

int update_plate(double cell_temp[8][6], double heater1, double heater2, double crit, int flag_init);

double new_cell_temp (int i, int j, double arr1[8][6], double arr[8][6], double heater1, double heater2);
