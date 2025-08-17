#include <stdio.h>
#include <stdlib.h>
#include "../include/defs.h"
#include "../include/admin.h"
#include "../include/user.h"

Patient patients[MAX_PATIENTS];
Reservation reservations[MAX_SLOTS];
u8 patientCount = 0;

int main() {
    InitializeSystem();
    
    printf("clinic management system\n");
    printf("welcome\n");
    
    while(1) {
        u8 choice;
        printf("select mode:\n");
        printf("1. admin\n");
        printf("2. user\n");
        printf("3. exit\n");
        printf("choice: ");
        
        choice = GetUserInput();
        
        switch(choice) {
            case 1:
                if(login()) {
                    adminMenu();
                } else {
                    printf("access denied\n");
                    exit(0);
                }
                break;
            case 2:
                userMenu();
                break;
            case 3:
                printf("bye\n");
                exit(0);
            default:
                printf("invalid\n");
        }
    }
    
    return 0;
}


void InitializeSystem(void) {
    for(u8 i = 0; i < MAX_SLOTS; i++) {
        reservations[i].patientId = 0;
        reservations[i].slot = i + 1;
        reservations[i].isReserved = 0;
    }

    for(u8 i = 0; i < MAX_PATIENTS; i++) {
        patients[i].isActive = 0;
    }
}

u16 GetUserInput(void) {
    u16 input;
    while(scanf("%hu", &input) != 1) {
        printf("invalid input, try again: ");
        while(getchar() != '\n'); // clear input buffer
    }
    return input;
}

void DisplayMessage(const u8* message) {
    printf("%s\n", message);
}

void ClearScreen(void) {
    system("cls"); 
}

u8 FindPatientById(u16 id) {
    for(u8 i = 0; i < patientCount; i++) {
        if(patients[i].id == id && patients[i].isActive) {
            return i; 
        }
    }
    return 255;
}
