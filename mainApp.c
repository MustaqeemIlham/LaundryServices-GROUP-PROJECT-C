#include <stdio.h>
#include <float.h>

#define MAX_CUSTOMERS 100

struct Customer {
    char name[50];
    int customerId;
    char phoneNumber[20];
    char laundryType[10];
    char clothType[10];
    int quantity;
    float charge;
};

float calculateCharge(struct Customer *customer) {
    float charge = 0.0;

    if (strcmp(customer->laundryType, "Dry") == 0) {
        if (strcmp(customer->clothType, "Blazer") == 0) {
            charge = 10.0;
        } else if (strcmp(customer->clothType, "Coat") == 0) {
            charge = 9.0;
        } else if (strcmp(customer->clothType, "Jacket") == 0) {
            charge = 9.0;
        } else if (strcmp(customer->clothType, "Melayu") == 0) {
            charge = 8.0;
        } else if (strcmp(customer->clothType, "Kurung") == 0) {
            charge = 8.0;
        }

    } else if (strcmp(customer->laundryType, "Normal") == 0) {
        charge = 2.5;
    }

    return charge * customer->quantity;
}

void addCustomer(struct Customer *customers, int *numCustomers) {
    if (*numCustomers >= MAX_CUSTOMERS) {
        printf("Maximum number of customers reached.\n");
        return;
    }

    printf("\nCustomer %d:\n", *numCustomers + 1);

    printf("Name: ");
    scanf(" %[^\n]s", customers[*numCustomers].name);

    customers[*numCustomers].customerId = *numCustomers + 1;

    printf("Phone Number: ");
    scanf(" %[^\n]s", customers[*numCustomers].phoneNumber);

    printf("Laundry Type (Dry/Normal): ");
    scanf(" %[^\n]s", customers[*numCustomers].laundryType);

    if (strcmp(customers[*numCustomers].laundryType, "Dry") == 0) {
        printf("Cloth Type (Kurung,Melayu,Blazer,Jacket,Coat ): ");
        scanf(" %[^\n]s", customers[*numCustomers].clothType);
    }
    else {
        strcpy(customers[*numCustomers].clothType, "Normal");
    }

    printf("Quantity: ");
    scanf("%d", &customers[*numCustomers].quantity);

    customers[*numCustomers].charge = calculateCharge(&customers[*numCustomers]);

    (*numCustomers)++;
}

void displayCustomers(struct Customer *customers, int numCustomers) {
    if (numCustomers == 0) {
        printf("No customers found.\n");
        return;
    }

    printf("\nCustomer Details:\n");
    printf("-------------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-12s | %-10s | %-6s | %-10s | %-10s |\n", "ID", "Name", "Phone Number", "Laundry", "Cloth", "Quantity", "Charge");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < numCustomers; i++) {
        customers[i].charge = calculateCharge(&customers[i]);

        printf("| %-4d | %-20s | %-12s | %-10s | %-6s | %-10d | $%-9.2f |\n",
               customers[i].customerId,
               customers[i].name,
               customers[i].phoneNumber,
               customers[i].laundryType,
               customers[i].clothType,
               customers[i].quantity,
               customers[i].charge);
    }

    printf("-------------------------------------------------------------------\n");
}

int findCustomerIndex(struct Customer *customers, int numCustomers, int customerId) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].customerId == customerId) {
            return i;
        }
    }

    return -1;
}

void updateCustomer(struct Customer *customers, int numCustomers) {
    int customerId;
    printf("Enter Customer ID to update: ");
    scanf("%d", &customerId);

    int customerIndex = findCustomerIndex(customers, numCustomers, customerId);
    if (customerIndex == -1) {
        printf("Customer with ID %d not found.\n", customerId);
        return;
    }

    printf("\nUpdating Customer %d:\n", customerIndex + 1);

    printf("Name: ");
    scanf(" %[^\n]s", customers[customerIndex].name);

    printf("Phone Number: ");
    scanf(" %[^\n]s", customers[customerIndex].phoneNumber);

    printf("Customer with ID %d updated successfully.\n", customerId);
}

void deleteCustomer(struct Customer *customers, int *numCustomers) {
    int customerId;
    printf("Enter Customer ID to delete: ");
    scanf("%d", &customerId);

    int customerIndex = findCustomerIndex(customers, *numCustomers, customerId);
    if (customerIndex == -1) {
        printf("Customer with ID %d not found.\n", customerId);
        return;
    }

    for (int i = customerIndex; i < *numCustomers - 1; i++) {
        customers[i] = customers[i + 1];
    }

    (*numCustomers)--;
    printf("Customer with ID %d deleted successfully.\n", customerId);
}

void displayTotalDryCleaningCharges(struct Customer *customers, int numCustomers) {
    float totalCharge = 0.0;

    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].laundryType, "Dry") == 0) {
            totalCharge += calculateCharge(&customers[i]);
        }
    }

    printf("Total charges for dry cleaning services: $%.2f\n", totalCharge);
}

void displayHighestAndLowestCharges(struct Customer *customers, int numCustomers) {
    float highestCharge = -FLT_MAX;
    float lowestCharge = FLT_MAX;
    int highestIndex = -1;
    int lowestIndex = -1;

    for (int i = 0; i < numCustomers; i++) {
        customers[i].charge = calculateCharge(&customers[i]);

        if (customers[i].charge > highestCharge) {
            highestCharge = customers[i].charge;
            highestIndex = i;
        }

        if (customers[i].charge < lowestCharge) {
            lowestCharge = customers[i].charge;
            lowestIndex = i;
        }
    }

    if (highestIndex != -1 && lowestIndex != -1) {
        printf("Customer with the highest charge:\n");
        printf("Name: %s\n", customers[highestIndex].name);
        printf("Customer ID: %d\n", customers[highestIndex].customerId);
        printf("Phone Number: %s\n", customers[highestIndex].phoneNumber);
        printf("Laundry Type: %s\n", customers[highestIndex].laundryType);
        if (strcmp(customers[highestIndex].laundryType, "Dry") == 0) {
            printf("Cloth Type: %s\n", customers[highestIndex].clothType);
        }
        printf("Quantity: %d\n", customers[highestIndex].quantity);
        printf("Charge: $%.2f\n", customers[highestIndex].charge);

        printf("\nCustomer with the lowest charge:\n");
        printf("Name: %s\n", customers[lowestIndex].name);
        printf("Customer ID: %d\n", customers[lowestIndex].customerId);
        printf("Phone Number: %s\n", customers[lowestIndex].phoneNumber);
        printf("Laundry Type: %s\n", customers[lowestIndex].laundryType);
        if (strcmp(customers[lowestIndex].laundryType, "Dry") == 0) {
            printf("Cloth Type: %s\n", customers[lowestIndex].clothType);
        }
        printf("Quantity: %d\n", customers[lowestIndex].quantity);
        printf("Charge: $%.2f\n", customers[lowestIndex].charge);
    } else {
        printf("No customers found.\n");
    }
}

void searchCustomer(struct Customer *customers, int numCustomers) {
    int customerId;
    printf("Enter Customer ID to search: ");
    scanf("%d", &customerId);

    int customerIndex = findCustomerIndex(customers, numCustomers, customerId);
    if (customerIndex == -1) {
        printf("Customer with ID %d not found.\n", customerId);
        return;
    }

    customers[customerIndex].charge = calculateCharge(&customers[customerIndex]);

    printf("\nCustomer Details:\n");
    printf("Name: %s\n", customers[customerIndex].name);
    printf("Customer ID: %d\n", customers[customerIndex].customerId);
    printf("Phone Number: %s\n", customers[customerIndex].phoneNumber);
    printf("Laundry Type: %s\n", customers[customerIndex].laundryType);
    if (strcmp(customers[customerIndex].laundryType, "Dry") == 0) {
        printf("Cloth Type: %s\n", customers[customerIndex].clothType);
    }
    printf("Quantity: %d\n", customers[customerIndex].quantity);
    printf("Charge: $%.2f\n", customers[customerIndex].charge);
}

int main() {
    struct Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;
    int choice;

    do {
        printf("\nPEARL SERVICE CUSTOMER MANAGEMENT SYSTEM:\n");
        printf("1. Add Customer\n");
        printf("2. Display Customers\n");       //display all
        printf("3. Update Customer\n");        //update
        printf("4. Delete Customer\n");         //delete
        printf("5. Display Total Charges for Dry Cleaning Services\n");     //display
        printf("6. Display Highest and Lowest Customer Charges\n");         //display highest lowest
        printf("7. Search Customer\n");     //search
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer(customers, &numCustomers);
                break;
            case 2:
                displayCustomers(customers, numCustomers);
                break;
            case 3:
                updateCustomer(customers, numCustomers);
                break;
            case 4:
                deleteCustomer(customers, &numCustomers);
                break;
            case 5:
                displayTotalDryCleaningCharges(customers, numCustomers);
                break;
            case 6:
                displayHighestAndLowestCharges(customers, numCustomers);
                break;
            case 7:
                searchCustomer(customers, numCustomers);
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}
