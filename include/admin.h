#ifndef ADMIN_H
#define ADMIN_H

#include "defs.h"

u8 login(void);
void adminMenu(void);
void addPatient(void);
void editPatient(void);
void reserveSlot(void);
void cancelReservation(void);
void showSlots(void);
void DisplaySlotName(TimeSlot slot);

#endif