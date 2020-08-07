//
//  9P-functions.c
//  9P
//
//  Created by Rainor Vigneault on 12/14/19.
//  Copyright © 2019 Rainor Vigneault. All rights reserved.
//

#include "9P-functions.h"

void display_plate(double heat_plate[8][6], double heater1, double heater2, int which_time){
    int i;
    int j;
    if (which_time == 0)
        printf("#### INITIAL PLATE ####\n");
    else
        (printf("#### PLATE %d ####\n", which_time));
    printf("                                   %4.2lf\n", heater1);
    for (i = 0; i < 8; i++){
        if(i != 4)
            printf("          --------------------------------------------------------------\n");
        else
            printf("  %4.2lf   -------------------------------------------------------------   %4.2lf\n", heater1, heater2);
        for (j = 0; j < 6; j++){
                if (j == 0)
                    printf("          ||  %4.2lf |", heat_plate[i][j]);
                else if (j == 5)
                    printf("|  %4.2lf ||\n", heat_plate[i][j]);
                else
                    printf("|  %4.2lf |", heat_plate[i][j]);
            }
        }
    printf("          --------------------------------------------------------------\n");
    printf("                                   %4.2lf\n", heater2);
}

void initialize_plate(double cell_temp[8][6], double temp1, double temp2){
    int i;
    int j;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 6; j++){
            if ((i < 4 && j < 3) || (i >= 4 && j >= 3))
                cell_temp[i][j] = temp1;
            else
                cell_temp[i][j] = temp2;
        }
    return;
}

int update_plate(double cell_temp[8][6], double heater1, double heater2, double crit, int flag_init){
    int i, j, flag = flag_init;
    double diff_of_temps = 0;
    double previous_heat_plate[8][6];
    for (i = 0; i < 8; i++)
        for (j = 0; j < 6; j++)
            previous_heat_plate[i][j] = cell_temp[i][j];
    
    for (i = 0; i < 8; i++)
        for (j = 0; j < 6; j++){
            if (i == 0 && j == 0){
                
                cell_temp[i][j] = (previous_heat_plate[i][j + 1] + previous_heat_plate[i + 1][j] + heater1 * 2) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
               
            }
                else if (i == 0 && j != 0 && j != 5){
            
                cell_temp[i][j] = (previous_heat_plate[i][j + 1] + previous_heat_plate[i + 1][j] + previous_heat_plate[i][j - 1] + heater1) / 4.0;
                   diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                   if (diff_of_temps <= crit)
                       flag++;
                    
                }
                   else if (i == 0 && j == 5){

                cell_temp[i][j] = (previous_heat_plate[i + 1][j] + previous_heat_plate[i][j - 1] + heater2 + heater1) / 4.0;
                       diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                       if (diff_of_temps <= crit)
                           flag++;
                       
                   }
            else if ((i != 0 && i != 7) && j == 0){

                           cell_temp[i][j] = (previous_heat_plate[i + 1][j] + previous_heat_plate[i][j + 1] + previous_heat_plate[i - 1][j] + heater1) / 4.0;
                                  diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                                  if (diff_of_temps <= crit)
                                      flag++;
        
                              }
            else if ((i != 0 && i != 7) && j == 5){
                cell_temp[i][j] = (previous_heat_plate[i + 1][j] + previous_heat_plate[i][j - 1] + previous_heat_plate[i - 1][j] + heater2) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
                
            }
                else if (i != 0 && i != 7 && j != 0 && j!= 5){
                
                cell_temp[i][j] = (previous_heat_plate[i - 1][j] + previous_heat_plate[i + 1][j] + previous_heat_plate[i][j - 1] + previous_heat_plate[i][j + 1]) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
               
                }
                else if (i == 7 && j == 0){
                
                cell_temp[i][j] = (previous_heat_plate[i][j + 1] + heater2 + previous_heat_plate[i - 1][j] + heater1 ) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
                
                }
                else if (i == 7 && j != 5){
               
                cell_temp[i][j] = (previous_heat_plate[i - 1][j] + previous_heat_plate[i][j + 1] + previous_heat_plate[i][j - 1] + heater2) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
            
                }
                else{
                
                cell_temp[i][j] = (previous_heat_plate[i - 1][j] + previous_heat_plate[i][j - 1] + heater2 * 2) / 4.0;
                diff_of_temps = fabs(cell_temp[i][j] - previous_heat_plate[i][j]) / previous_heat_plate[i][j];
                if (diff_of_temps <= crit)
                    flag++;
               
                }
        }
    return flag;
        }
    
           


double new_cell_temp (int i, int j, double arr1[8][6], double arr[8][6], double heater1, double heater2){
    
    if (i == 0 && j == 0){
    
    arr1[i][j] = (arr[i][j + 1] + arr[i + 1][j] + heater1 * 2) / 4.0;
    
}
    else if (i == 0 && j != 0 && j != 5){

    arr1[i][j] = (arr[i][j + 1] + arr[i + 1][j] + arr[i][j - 1] + heater1) / 4.0;
       
    }
       else if (i == 0 && j == 5){

    arr1[i][j] = (arr[i + 1][j] + arr[i][j - 1] + heater2 + heater1) / 4.0;
           
       }
    else if (i != 0 && i != 7 && j != 0 && j!= 5){
    
    arr1[i][j] = (arr[i - 1][j] + arr[i + 1][j] + arr[i][j - 1] + arr[i][j + 1]) / 4.0;
  
    }
    else if (i == 7 && j == 0){
    
    arr1[i][j] = (arr[i][j + 1] + heater2 + arr[i - 1][j] + heater1 ) / 4.0;
   
    }
    else if (i == 7 && j != 5){
   
    arr1[i][j] = (arr[i - 1][j] + arr[i][j + 1] + arr[i][j - 1] + heater2) / 4.0;
    
    }
    else{
    
    arr1[i][j] = (arr[i - 1][j] + arr[i][j - 1] + heater2 * 2) / 4.0;
   
    }
    return arr1[i][j];
}
