#include <stdio.h>
#include "../include/user.h"
#include "../include/defs.h"
#include "../include/admin.h"

void userMenu(void) {
    u8 choice;
    
    printf("user mode\n");
    
    while(1) {
        printf("user menu:\n");
        printf("1. view patient\n");
        printf("2. view reservations\n");
        printf("3. back\n");
        printf("choice: ");
        
        choice = GetUserInput();
        
        switch(choice) {
            case 1:
                viewPatient();
                break;
            case 2:
                viewReservations();
                break;
            case 3:
                return; 
            default:
                printf("invalid\n");
        }
    }
}

void viewPatient(void) {
    u16 id;
    u8 index;
    
    printf("view patient\n");
    printf("enter patient id: ");
    id = GetUserInput();
    
    index = FindPatientById(id);
    if(index == 255) {
        printf("patient not found\n");
        return;
    }
    
    printf("patient info:\n");
    printf("id: %d\n", patients[index].id);
    printf("name: %s\n", patients[index].name);
    printf("age: %d\n", patients[index].age);
    printf("gender: %c\n", patients[index].gender);
}

void viewReservations(void) {
    u8 found = 0;
    u8 index;
    
    printf("today reservations:\n");
    
    for(u8 i = 0; i < MAX_SLOTS; i++) {
        if(reservations[i].isReserved) {
            found = 1;
            index = FindPatientById(reservations[i].patientId);
            
            printf("slot %d: ", i + 1);
            showSlotTime(i + 1);
            printf("\n");
            
            if(index != 255) {
                printf("patient id: %d\n", patients[index].id);
                printf("name: %s\n", patients[index].name);
            } else {
                printf("patient id: %d\n", reservations[i].patientId);
            }
            printf("\n");
        }
    }
    
    if(!found) {
        printf("no reservations\n");
    }
}

void showSlotTime(u8 slot) {
    switch(slot) {
        case 1:
            printf("2:00 PM to 2:30 PM");
            break;
        case 2:
            printf("2:30 PM to 3:00 PM");
            break;
        case 3:
            printf("3:00 PM to 3:30 PM");
            break;
        case 4:
            printf("4:00 PM to 4:30 PM");
            break;
        case 5:
            printf("4:30 PM to 5:00 PM");
            break;
        default:
            printf("invalid slot");
    }
}
