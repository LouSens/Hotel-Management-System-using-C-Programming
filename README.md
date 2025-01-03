# Hotel Management System

## Overview
This project is a **Hotel Management System** implemented in C. It allows users to interact with the system in three roles: **Admin**, **Employee**, and **Customer**. Each role has specific functionalities to streamline hotel management, such as registering users, logging in, managing accommodations, viewing bills, and more.

## Features
### Admin Role
- Add, update, or delete accommodations.
- View all registered customers.

### Employee Role
- View accommodations.
- View all registered customers.

### Customer Role
- Complete personal information.
- View accommodation information.
- Book accommodations.
- View personal bills.

## File Structure
```
├── main.c                    # Main program file            
├── customer_info.txt         # Stores customer info (name, email, phone number)
├── accommodations.txt        # Stores accommodation details
├── bills.txt                 # Stores customer bill information
```

## How It Works
1. **Registration**:
   - Users can register with a username and password.
   - Role (Admin, Employee, or Customer) is assigned during registration.

2. **Login**:
   - Users log in by entering their credentials.
   - Based on the role, users are directed to their respective menus.

3. **Admin Menu**:
   - Admins can manage accommodations and view all customer information.

4. **Employee Menu**:
   - Employees can view accommodations, assist customers in booking accommodations, and handle billing information.

5. **Customer Menu**:
   - Customers can complete their personal information, view available accommodations, book accommodations, and view their bills.

## Key Functions
### `completeCustomerInfo()`
- Collects and stores the customer's name and username in `customer_info.txt`.

### `viewBill(const char *username)`
- Displays all bills for a specific customer by matching their username with records in `bills.txt`.

### `bookAccommodation()`
- Allows a customer to book an accommodation and saves the booking information in `bills.txt`.

## How to Run
1. **Compile the Program**:
   ```bash
   gcc AIT101AIT2409110.c customer.c -o HotelManagementSystem
   ```

2. **Run the Program**:
   ```bash
   ./HotelManagementSystem
   ```

3. **Follow the Instructions**:
   - Choose an option from the main menu (Register, Login, Exit).
   - Based on your role, interact with the system using the corresponding menu.

## Dependencies
- GCC compiler
- Basic knowledge of C file handling

## Sample Input/Output
### Customer Menu Example:
**Input:**
```
1. Complete Your Information
2. View Accommodation Information
3. Book Accommodation
4. View Bill Information
5. Logout
Enter your choice: 1
```
**Output:**
```
Enter name: John Doe
Information saved successfully!
```

## Contributing
Feel free to fork this repository, make changes, and submit a pull request. Any improvements to the code structure, functionality, or documentation are welcome.

## License
This project is licensed under the [MIT License](LICENSE).  
Copyright © 2024 David Kurniawan. All rights reserved.

