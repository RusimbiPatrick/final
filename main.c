#include <stdio.h>

struct Customer {
    char name[50];
    char month[10];
    char day[10];
    char year[5];  // Changed to allow for the null terminator in the year string
    int days;
    int rate;
};

// Function to create a customer and record information
struct Customer createCustomer() {
    struct Customer customer;
    printf("Enter Customer name: ");
    scanf("%s", customer.name);
    printf("Enter Month of Arrival: ");
    scanf("%s", customer.month);
    printf("Enter Day of Arrival: ");
    scanf("%s", customer.day);
    printf("Enter Year of Arrival: ");
    scanf("%s", customer.year);
    printf("Enter Number of days: ");
    scanf("%d", &customer.days);
    printf("Enter Daily rate: ");
    scanf("%d", &customer.rate);
    return customer;
}

// Function to record data from users and store them in a file
void recordData(FILE *file, int numCustomers) {
    struct Customer customer;
    for (int i = 0; i < numCustomers; i++) {
        customer = createCustomer();
        fprintf(file, "%s %s %s %s %d %d\n", customer.name, customer.month, customer.day, customer.year, customer.days, customer.rate);
    }
}

// Function to display all customers
void displayCustomers(FILE *file) {
    struct Customer customer;
    rewind(file);
    printf("\nAll Customers:\n");
    printf("--------------------------------------------------\n");
    while (fscanf(file, "%s %s %s %s %d %d", customer.name, customer.month, customer.day, customer.year, &customer.days, &customer.rate) != EOF) {
        printf("Customer: %s Arrival Date: %s %s %s Number of Days: %d Daily Rate: %d\n", customer.name, customer.month, customer.day, customer.year, customer.days, customer.rate);
    }
    printf("--------------------------------------------------\n");
}

// Function to display customers per month and total amount collected each month
void displayCustomersPerMonth(FILE *file) {
    struct Customer customer;
    rewind(file);
    int monthTotal[12] = {0};  // Initialize an array to store the total amount for each month

    printf("\nCustomers per month and total amount collected each month:\n");
    printf("--------------------------------------------------\n");

    while (fscanf(file, "%s %s %s %s %d %d", customer.name, customer.month, customer.day, customer.year, &customer.days, &customer.rate) != EOF) {
        int monthIndex;

        // Convert month string to an index (assuming 1-12 for January-December)
        sscanf(customer.month, "%d", &monthIndex);

        // Display customer information
        printf("Customer: %s Arrival Date: %s %s %s Number of Days: %d Daily Rate: %d\n",
               customer.name, customer.month, customer.day, customer.year, customer.days, customer.rate);

        // Accumulate the total amount for the corresponding month
        monthTotal[monthIndex - 1] += (customer.days * customer.rate);
    }

    printf("--------------------------------------------------\n");

    // Display the total amount collected for each month
    printf("Total amount collected each month:\n");
    for (int i = 0; i < 12; i++) {
        printf("Month %d: $%d\n", i + 1, monthTotal[i]);
    }
}

int main() {
    FILE *file;
    int numCustomers;

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Record Data\n");
        printf("2. Display All customers\n");
        printf("3. Display Customers per month and total amount collected each month\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                file = fopen("customers.txt", "w");
                if (file == NULL) {
                    printf("Error opening file for writing.\n");
                    return 1;
                }
                printf("Enter the number of Customers: ");
                scanf("%d", &numCustomers);
                recordData(file, numCustomers);
                fclose(file);
                break;
            case 2:
                file = fopen("customers.txt", "r");
                if (file == NULL) {
                    printf("Error opening file for reading.\n");
                    return 1;
                }
                displayCustomers(file);
                fclose(file);
                break;
            case 3:
                file = fopen("customers.txt", "r");
                if (file == NULL) {
                    printf("Error opening file for reading.\n");
                    return 1;
                }
                displayCustomersPerMonth(file);
                fclose(file);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
