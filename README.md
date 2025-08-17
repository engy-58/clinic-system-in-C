# Hospital Management System

A simple C-based Hospital Management System for managing clinic operations, including user and admin functionalities.

## Features

- User and Admin login
- Patient registration and management
- Appointment scheduling
- Clinic system executable

## Project Structure

```
Hospital Management System/
├── Makefile
├── README.md
├── build/
│   └── clinic_system.exe
├── include/
│   ├── admin.h
│   ├── defs.h
│   ├── STD_TYPES.h
│   └── user.h
├── src/
│   ├── admin.c
│   ├── main.c
│   └── user.c
```

## Build Instructions

1. Open a terminal in the project directory.
2. Run the following command to build the project:
   ```
   make
   ```
3. The executable will be generated in the `build/` directory.

## Usage

Run the executable:

```
./build/clinic_system.exe
```

## Requirements

- GCC or compatible C compiler
- Make utility


## License

This project is licensed under the MIT License.