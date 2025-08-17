#include <stdio.h>
#include <string.h>
#include "../include/admin.h"
#include "../include/defs.h"

u8 login(void) {
    u16 pass;
    u8 tries = 0;
    
    printf("admin login\n");
    
    while(tries < MAX_PASSWORD_ATTEMPTS) {
        printf("password: ");
        pass = GetUserInput();
        
        if(pass == DEFAULT_PASSWORD) {
            printf("login ok\n");
            return 1; 
        } else {
            tries++;
            printf("wrong password. tries left: %d\n", MAX_PASSWORD_ATTEMPTS - tries);
        }
    }
    
    printf("max tries reached\n");
    return 0; 
}

void adminMenu(void) {
    u8 choice;
    
    while(1) {
        printf("admin menu:\n");
        printf("1. add patient\n");
        printf("2. edit patient\n");
        printf("3. reserve slot\n");
        printf("4. cancel reservation\n");
        printf("5. back\n");
        printf("choice: ");
        
        choice = GetUserInput();
        
        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                editPatient();
                break;
            case 3:
                reserveSlot();
                break;
            case 4:
                cancelReservation();
                break;
            case 5:
                return; 
            default:
                printf("invalid\n");
        }
    }
}

void addPatient(void) {
    if(patientCount >= MAX_PATIENTS) {
        printf("max patients reached\n");
        return;
    }
    
    Patient newPatient;
    u16 id;
    
    printf("add patient\n");
    printf("enter id: ");
    id = GetUserInput();
    
    if(FindPatientById(id) != 255) {
        printf("id already exists\n");
        return;
    }
    
    newPatient.id = id;
    newPatient.isActive = 1;
    
    printf("name: ");
    scanf(" %49[^\n]", newPatient.name); 
    
    printf("age: ");
    newPatient.age = GetUserInput();
    
    printf("gender (M/F): ");
    scanf(" %c", &newPatient.gender);
    
    patients[patientCount] = newPatient;
    patientCount++;
    
    printf("patient added\n");
}

void editPatient(void) {
    u16 id;
    u8 index;
    
    printf("edit patient\n");
    printf("enter id: ");
    id = GetUserInput();
    
    index = FindPatientById(id);
    if(index == 255) {
        printf("patient not found\n");
        return;
    }
    
    printf("current info:\n");
    printf("id: %d\n", patients[index].id);
    printf("name: %s\n", patients[index].name);
    printf("age: %d\n", patients[index].age);
    printf("gender: %c\n", patients[index].gender);
    
    printf("new info:\n");
    printf("name: ");
    scanf(" %49[^\n]", patients[index].name);
    
    printf("age: ");
    patients[index].age = GetUserInput();
    
    printf("gender (M/F): ");
    scanf(" %c", &patients[index].gender);
    
    printf("patient updated\n");
}

void reserveSlot(void) {
    u16 patientId;
    u8 slotChoice;
    u8 patientIndex;
    
    printf("reserve slot\n");
    showSlots();
    
    printf("enter patient id: ");
    patientId = GetUserInput();

    patientIndex = FindPatientById(patientId);
    if(patientIndex == 255) {
        printf("patient not found\n");
        return;
    }
    
    printf("enter slot (1-5): ");
    slotChoice = GetUserInput();
    
    if(slotChoice < 1 || slotChoice > MAX_SLOTS) {
        printf("invalid slot\n");
        return;
    }
    if(reservations[slotChoice - 1].isReserved) {
        printf("slot already taken\n");
        return;
    }
    reservations[slotChoice - 1].patientId = patientId;
    reservations[slotChoice - 1].isReserved = 1;
    
    printf("slot reserved\n");
    printf("patient %s assigned to: ", patients[patientIndex].name);
    DisplaySlotName(slotChoice);
    printf("\n");
}

void cancelReservation(void) {
    u16 patientId;
    u8 found = 0;
    
    printf("cancel reservation\n");
    printf("enter patient id: ");
    patientId = GetUserInput();
    for(u8 i = 0; i < MAX_SLOTS; i++) {
        if(reservations[i].patientId == patientId && reservations[i].isReserved) {
            reservations[i].patientId = 0;
            reservations[i].isReserved = 0;
            found = 1;
            printf("reservation cancelled\n");
            printf("slot ");
            DisplaySlotName(i + 1);
            printf(" now available\n");
            break;
        }
    }
    
    if(!found) {
        printf("no reservation found\n");
    }
}

void showSlots(void) {
    printf("available slots:\n");
    for(u8 i = 0; i < MAX_SLOTS; i++) {
        if(!reservations[i].isReserved) {
            printf("%d. ", i + 1);
            DisplaySlotName(i + 1);
            printf("\n");
        }
    }
}

void DisplaySlotName(TimeSlot slot) {
    switch(slot) {
        case SLOT_2_TO_2_30:
            printf("2:00 PM to 2:30 PM");
            break;
        case SLOT_2_30_TO_3:
            printf("2:30 PM to 3:00 PM");
            break;
        case SLOT_3_TO_3_30:
            printf("3:00 PM to 3:30 PM");
            break;
        case SLOT_4_TO_4_30:
            printf("4:00 PM to 4:30 PM");
            break;
        case SLOT_4_30_TO_5:
            printf("4:30 PM to 5:00 PM");
            break;
        default:
            printf("Invalid slot");
    }
}