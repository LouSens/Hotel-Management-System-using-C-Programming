#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definitions
typedef struct {
    char username[50];
    char password[50];
    char role[20];
    
} User;

typedef struct {
    char name[50];
    char email[50];
    char phone[15];
} Customer;

typedef struct {
    char type[50];
    int capacity;
    float price;
    int totalRooms;
    int availableRooms;
} Accommodation;

char currentUser[50]; // Global variable to store the current user

// Function prototypes
void registerUser();
int login(char *role);
void recordAccommodation();
void viewCustomers();
void viewAccommodations();
void completeCustomerInfo(const char*currentUser);
void viewAccommodationsForCustomer();
void bookAccommodation();
void editAccommodation();
void viewBill();
void adminMenu();
void employeeMenu();
void customerMenu();
void waitForEnter();
void resetData();


// Utility functions
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


int main() {
    int choice;
    char role[20];
    
    while (1) {
        clearScreen();
        printf("Hotel Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (login(role)) {
                    if (strcmp(role, "admin") == 0) {
                        adminMenu();
                    } else if (strcmp(role, "employee") == 0) {
                        employeeMenu();
                    } else if (strcmp(role, "customer") == 0) {
                        customerMenu(currentUser); // Pass the global currentUser
                    }
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
                waitForEnter();
        }
    }
    return 0;
}


void registerUser() {
    User newUser;
    FILE *file;
    clearScreen();
    printf("Register\n");
    // Open the file for reading to check for duplicate usernames
    while (1) {
        printf("Enter username: ");
        scanf(" %[^\n]", newUser.username); // Read string including spaces
        getchar(); // Clear buffer after reading
        int isDuplicate = 0; // Flag to check duplication
        file = fopen("users.txt", "r");
        if (file != NULL) {
            char tempUsername[50], tempPassword[50], tempRole[20];
            while (fscanf(file, "%s %s %s", tempUsername, tempPassword, tempRole) != EOF) {
                if (strcmp(tempUsername, newUser.username) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }
            fclose(file);
        }
        if (isDuplicate) {
            printf("Username already exists! Please try a different username.\n");
        } else {
            break; // Username is unique
        }
    }
    // Get the password
    while (1) {
        printf("Enter password: ");
        scanf(" %[^\n]", newUser.password); // Read string including spaces
        getchar(); // Clear buffer after reading

        if (strlen(newUser.password) < 6) {
            printf("Password must be at least 6 characters long. Please try again.\n");
        } else {
            break; // Valid password
        }
    }
    // Validate role input
    while (1) {
        printf("Enter role (admin/employee/customer): ");
        scanf(" %[^\n]", newUser.role);
        getchar(); // Clear buffer after reading

        if (strcmp(newUser.role, "admin") == 0 || strcmp(newUser.role, "employee") == 0 || strcmp(newUser.role, "customer") == 0) {
            break; // Valid role entered
        } else {
            printf("Invalid role! Please enter 'admin', 'employee', or 'customer'.\n");
        }
    }
    // Append the new user to the file
    file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s %s %s\n", newUser.username, newUser.password, newUser.role);
    fclose(file);

    printf("User registered successfully!\n");
    waitForEnter();
}




int login(char *role) {
    extern char currentUser[50]; 
    char username[50], password[50];
    char fileUsername[50], filePassword[50], fileRole[20];
    FILE *file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file. Ensure users are registered.\n");
        return 0;
    }

    clearScreen();
    printf("Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    getchar(); // Consume newline character
    printf("Enter password: ");
    scanf("%s", password);
    getchar(); // Consume newline character

    // Check credentials
    while (fscanf(file, "%s %s %s", fileUsername, filePassword, fileRole) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            strcpy(role, fileRole);  // Pass role back to main
            strcpy(currentUser, username);  // Store current user globally
            fclose(file);
            printf("Login successful as %s!\n", role);
            waitForEnter();
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password.\n");
    waitForEnter();
    return 0;
}



void recordAccommodation() {
    Accommodation acc;
    clearScreen();
    printf("Record Accommodation\n");
    printf("Enter accommodation type: ");
    scanf("%s", acc.type);
    printf("Enter capacity: ");
    scanf("%d", &acc.capacity);
    getchar();
    if (acc.capacity <= 0) {
        printf("Invalid capacity! Must be greater than 0.\n");
        waitForEnter();  // Pause to display the error message
        return;
    }
    printf("Enter price per night: ");
    scanf("%f", &acc.price);
    getchar();
    if (acc.price <= 0) {
        printf("Invalid price! Must be greater than 0.\n");
        waitForEnter();  // Pause to display the error message
        return;
    }
    printf("Enter total number of rooms: ");
    scanf("%d", &acc.totalRooms);
    getchar();
    if (acc.totalRooms <= 0) {
        printf("Invalid total room count! Must be greater than 0.\n");
        waitForEnter();  // Pause to display the error message
        return;
    }
    printf("Enter available rooms: ");
    scanf("%d", &acc.availableRooms);
    getchar();
    if (acc.availableRooms < 0 || acc.availableRooms > acc.totalRooms) {
        printf("Invalid available room count! Must be between 0 and total rooms.\n");
        waitForEnter();  // Pause to display the error message
        return;
    }
    FILE *file = fopen("accommodations.txt", "a");
    if (!file) {
        perror("Error saving accommodation data");
        waitForEnter();  // Pause to display the error message
        return;
    }

    fprintf(file, "%s %d %.2f %d %d\n", acc.type, acc.capacity, acc.price, acc.totalRooms, acc.availableRooms);
    fclose(file);

    printf("Accommodation recorded successfully!\n");
    waitForEnter();  // Pause to display success message
}

void viewCustomers() {
    FILE *file = fopen("customer_info.txt", "r");
    if (!file) {
        printf("No customer records found!\n");
        waitForEnter();
        return;
    }

    Customer customer;
    int hasData = 0;
    
    while (fscanf(file, "%s %s %s", customer.name, customer.email, customer.phone) != EOF) {
        hasData = 1;
        printf("Customer List:\n");
        printf("---------------------------------------------\n");
        printf("| %-15s | %-10s | %-10s |\n", "Name", "Email", "Phone");
        printf("---------------------------------------------\n");
        printf("| %-15s | %-10s | %-10s |\n", customer.name, customer.email, customer.phone);
        printf("---------------------------------------------\n");
    }
    fclose(file);

    if (!hasData) {
        printf("No customer records found in the system!\n");
    }

    waitForEnter();
}

void viewAccommodations(const char *context) {
    FILE *file = fopen("accommodations.txt", "r");
    if (!file) {
        printf("No accommodation records found!\n");
        waitForEnter();
        return;
    }

    Accommodation acc;
    int totalRooms, availableRooms;
    int hasData = 0; // Initialize the hasData flag

    if (strcmp(context, "admin") == 0) {
        printf("Accommodation List:\n");
    } else if (strcmp(context, "customer") == 0) {
        printf("Available Accommodations:\n");
    }

    printf("----------------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-10s |\n", "Type", "Capacity", "Price", "Available");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%s %d %f %d %d", acc.type, &acc.capacity, &acc.price, &acc.totalRooms, &acc.availableRooms) == 5) {
        hasData = 1; // Set the flag when a record is successfully read
        printf("| %-15s | %-10d | %-10.2f | %-10d |\n", acc.type, acc.capacity, acc.price, acc.availableRooms);
    }

    fclose(file);

    if (!hasData) {
        printf("No accommodations available in the system!\n");
    }

    waitForEnter();
}

void completeCustomerInfo(const char *currentUser) {
    Customer customer; // Create a Customer structure to hold the information
    FILE *file = fopen("customer_info.txt", "a"); // Open file in append mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Prompt for customer information
    printf("Enter your name: ");
    scanf(" %[^\n]s", customer.name); // Read the name, including spaces
    getchar();
    printf("Enter your email: ");
    scanf("%s", customer.email); // Read the email
    getchar();
    printf("Enter your phone number: ");
    scanf("%s", customer.phone); // Read the phone number
    getchar();

    // Save the username and customer information to the file
    fprintf(file, "%s %s %s\n", customer.name, customer.email, customer.phone);
    fclose(file);

    printf("Information saved successfully!\n");
    waitForEnter(); // Wait for user input before continuing
}

void bookAccommodation() {
    extern char currentUser[50]; // Use the global currentUser variable
    FILE *accFile = fopen("accommodations.txt", "r");
    if (!accFile) {
        printf("No accommodation records found! Please add accommodations first.\n");
        waitForEnter();
        return;
    }

    Accommodation acc;
    char type[50];
    int found = 0, booked = 0;

    // Display available accommodations
    printf("----------------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-10s |\n", "Type", "Capacity", "Price", "Available");
    printf("----------------------------------------------------------\n");

    while (fscanf(accFile, "%s %d %f %d %d", acc.type, &acc.capacity, &acc.price, &acc.totalRooms, &acc.availableRooms) == 5) {
        printf("| %-15s | %-10d | %-10.2f | %-10d |\n", acc.type, acc.capacity, acc.price, acc.availableRooms);
    }
    fclose(accFile);

    printf("----------------------------------------------------------\n");
    printf("Enter accommodation type to book (or type 'exit' to cancel): ");
    scanf("%s", type);

    if (strcmp(type, "exit") == 0) {
        printf("Booking process canceled.\n");
        waitForEnter();
        return;
    }

    // Open files for reading and updating
    accFile = fopen("accommodations.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!accFile || !tempFile) {
        perror("Error handling files");
        waitForEnter();
        return;
    }

    while (fscanf(accFile, "%s %d %f %d %d", acc.type, &acc.capacity, &acc.price, &acc.totalRooms, &acc.availableRooms) == 5) {
        if (strcmp(type, acc.type) == 0) {
            found = 1;
            if (acc.availableRooms > 0) {
                acc.availableRooms--;
                FILE *billFile = fopen("bills.txt", "a");
                if (!billFile) {
                    perror("Error opening bills file");
                    fclose(accFile);
                    fclose(tempFile);
                    return;
                }
                fprintf(billFile, "%s %s %.2f\n", currentUser, acc.type, acc.price);
                fclose(billFile);

                printf("Booking successful for %s at %.2f per night! Remaining Rooms: %d\n", acc.type, acc.price, acc.availableRooms);
                waitForEnter();
                booked = 1;
            } else {
                printf("No available rooms for %s! Please choose another type.\n", acc.type);
                 waitForEnter();
            }
        }
        fprintf(tempFile, "%s %d %.2f %d %d\n", acc.type, acc.capacity, acc.price, acc.totalRooms, acc.availableRooms);
    }

    fclose(accFile);
    fclose(tempFile);

    remove("accommodations.txt");
    rename("temp.txt", "accommodations.txt");

    if (!found) {
        printf("Invalid accommodation type! Please try again.\n");
         waitForEnter();
    }

    if (!booked) {
        printf("No booking was made. Please try again.\n");
         waitForEnter();
    }

    waitForEnter();
}




void viewBill(const char *username) {
    currentUser[strcspn(currentUser, "\n")] = 0;
    FILE *billFile = fopen("bills.txt", "r");
    if (!billFile) {
        printf("Error opening bills file or no bills available.\n");
        waitForEnter();
        return;
    }

    char fileUsername[50], accommodationType[50];
    float price;
    int found = 0;

    clearScreen();
    printf("Bills for %s:\n", username);
    printf("------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s |\n", "Accommodation", "Price", "User");
    printf("------------------------------------------------\n");

    while (fscanf(billFile, "%s %s %f", fileUsername, accommodationType, &price) == 3) {
        if (strcmp(username, fileUsername) == 0) {
            found = 1;
            printf("| %-20s | %-10.2f | %-10s |\n", accommodationType, price, username);
        }
    }
    fclose(billFile);

    if (!found) {
        printf("No bills found for this user.\n");
    }
    printf("------------------------------------------------\n");
    waitForEnter();
}




void adminMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("Admin Menu\n");
        printf("1. Record Accommodation\n");
        printf("2. View Customers\n");
        printf("3. View Accommodations\n");
        printf("4. Edit Accommodation\n");
        printf("5. Reset All Data\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                recordAccommodation();
                break;
            case 2:
                viewCustomers();
                break;
            case 3:
                viewAccommodations("admin");
                break;
            case 4:
                editAccommodation(); 
                break;
            case 5:
                resetData();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice!\n");
                waitForEnter();
        }
    }
}


void resetData() {
    int confirm;

    printf("Are you sure you want to reset all data? This action cannot be undone.\n");
    printf("Enter 1 to confirm, 0 to cancel: ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        // Open files in write mode to clear their content
        FILE *file;

        file = fopen("customers.txt", "w");
        if (file) fclose(file);

        file = fopen("accommodations.txt", "w");
        if (file) fclose(file);

        file = fopen("bills.txt", "w");
        if (file) fclose(file);

        printf("All data has been reset successfully!\n");
    } else {
        printf("Data reset canceled.\n");
    }
    waitForEnter();
}


void employeeMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("Employee Menu\n");
        printf("1. View Customer Information\n");
        printf("2. View Accommodation Information\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                viewCustomers();
                break;
            case 2:
                viewAccommodations("admin");
                break;
            case 3:
                return;
            default:
                printf("Invalid choice!\n");
                waitForEnter();
        }
    }
}

void customerMenu(const char*currentUser) {
    int choice;
    while (1) {
        clearScreen();
        printf("Customer Menu\n");
        printf("1. Complete Your Information\n");
        printf("2. View Accommodation Information\n");
        printf("3. Book Accommodation\n");
        printf("4. View Bill Information\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                completeCustomerInfo(currentUser);
                break;
            case 2:
                viewAccommodations("customer");
                break;
            case 3:
                bookAccommodation(currentUser);
                break;
            case 4:
                viewBill(currentUser);
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
                waitForEnter();
        }
    }
}



void editAccommodation() {
    FILE *file = fopen("accommodations.txt", "r");
    if (!file) {
        perror("Error opening accommodations file");
        waitForEnter();
        return;
    }

    Accommodation accList[100];
    int count = 0;

    while (fscanf(file, "%s %d %f %d %d", accList[count].type, 
                  &accList[count].capacity, &accList[count].price, 
                  &accList[count].totalRooms, &accList[count].availableRooms) == 5) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No accommodations available to edit!\n");
        waitForEnter();
        return;
    }

    printf("Available Accommodations:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Type: %s, Capacity: %d, Price: %.2f, Total Rooms: %d, Available: %d\n",
               i + 1, accList[i].type, accList[i].capacity, accList[i].price,
               accList[i].totalRooms, accList[i].availableRooms);
    }

    int choice;
    printf("Enter the number of the accommodation to edit (0 to cancel): ");
    scanf("%d", &choice);
    if (choice == 0) {
        printf("Edit canceled.\n");
        waitForEnter();
        return;
    }

    if (choice < 1 || choice > count) {
        printf("Invalid choice!\n");
        waitForEnter();
        return;
    }

    int index = choice - 1;
    printf("Editing accommodation: %s\n", accList[index].type);

    printf("Enter new capacity (current: %d): ", accList[index].capacity);
    scanf("%d", &accList[index].capacity);
    if (accList[index].capacity < 0) {
        printf("Invalid capacity value!\n");
        return;
    }

    printf("Enter new price (current: %.2f): ", accList[index].price);
    scanf("%f", &accList[index].price);
    if (accList[index].price <= 0) {
        printf("Invalid price value!\n");
        return;
    }

    printf("Enter total rooms (current: %d): ", accList[index].totalRooms);
    scanf("%d", &accList[index].totalRooms);
    if (accList[index].totalRooms < 0) {
        printf("Invalid room count!\n");
        return;
    }

    printf("Enter available rooms (current: %d): ", accList[index].availableRooms);
    scanf("%d", &accList[index].availableRooms);
    if (accList[index].availableRooms < 0 || accList[index].availableRooms > accList[index].totalRooms) {
        printf("Invalid available room count!\n");
        return;
    }

    file = fopen("accommodations.txt", "w");
    if (!file) {
        perror("Error saving accommodations file");
        waitForEnter();
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %.2f %d %d\n", accList[i].type, accList[i].capacity,
                accList[i].price, accList[i].totalRooms, accList[i].availableRooms);
    }
    fclose(file);

    printf("Accommodation updated successfully!\n");
    waitForEnter();
}


void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}



