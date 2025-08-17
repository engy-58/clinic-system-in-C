#ifndef DEFS_H
#define DEFS_H

#include "STD_TYPES.h"

#define MAX_PATIENTS 100
#define MAX_NAME_LENGTH 50
#define DEFAULT_PASSWORD 1234
#define MAX_PASSWORD_ATTEMPTS 3
#define MAX_SLOTS 5

typedef enum {
    SLOT_2_TO_2_30 = 1,
    SLOT_2_30_TO_3,
    SLOT_3_TO_3_30,
    SLOT_4_TO_4_30,
    SLOT_4_30_TO_5
} TimeSlot;


typedef struct {
    u16 id;
    u8 name[MAX_NAME_LENGTH];
    u8 age;
    u8 gender; // 'M' for male, 'F' for female
    u8 isActive; 
} Patient;

typedef struct {
    u16 patientId;
    TimeSlot slot;
    u8 isReserved;
} Reservation;


extern Patient patients[MAX_PATIENTS];
extern Reservation reservations[MAX_SLOTS];
extern u8 patientCount;


void DisplayMessage(const u8* message);
void ClearScreen(void);
u16 GetUserInput(void);
void InitializeSystem(void);
u8 FindPatientById(u16 id);

#endif // DEFS_H