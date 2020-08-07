//
//  main.c
//  9P
//  This program prompts the user for a txt file with five numbers. The five numbers
//  are used to simulate the process of heat transfer in a square metal plate. There are
//  two values used to intitialize four quadrants of the plate to a certain temperature,
//  and two values used for the temperatures of heaters on the edges of the plate.
//  Created by Rainor Vigneault on 12/14/19.
//  Copyright © 2019 Rainor Vigneault. All rights reserved.
//

#include "9P-functions.h"

int main(int argc, const char * argv[]) {
    double heat_plate[8][6];
    double t1, t2;
    double h1, h2;
    double stab_crit;
   
    char filename[30];
    FILE *plata;
    printf("File name: ");
    scanf("\n%s", filename);
    plata = fopen(filename, "r");
    fscanf(plata,"%lf%lf%lf%lf%lf", &h1, &h2, &t1, &t2, &stab_crit);

    printf("HEATER/COOLER A TEMPERATURE: \t%4.2lf\nHEATER/COOLER B TEMPERATURE: \t%4.2lf\nINITIAL PLATE TEMPERATURE 1: \t%4.2lf\nINITIAL PLATE TEMPERATURE 2: \t%4.2lf\n\nSTABILIZE CRITERION: \t%4.2lf\n\n", h1, h2, t1, t2, stab_crit);
    initialize_plate(heat_plate, t1, t2);
    int i/*, j, k*/;
    int flag_initializer;
    int flag = 0;
    for (i = 0; flag != 48; i++){
        display_plate(heat_plate, h1, h2, 0);
        flag_initializer = 0;
        flag = update_plate(heat_plate, h1, h2, stab_crit, flag_initializer);
    }
    display_plate(heat_plate, h1, h2, i);
    printf("\nGoodbye");
    
    
    return 0;
}
