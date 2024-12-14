
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char username[30];
    char password[30];
} User;

typedef struct {
    int id;
    char name[50];
    float price;
    int available;
} MenuItem;

typedef struct {
    int orderId;
    int itemId;
    int quantity;
} Order;

typedef struct {
    int tableId;
    int reserved;
} Table;


void signUp();
void login();
void placeOrder();
void addItem();
void deleteItem();
void makePayment();
void viewDailyOperations();
void generateSalesReport();
void manageUsers();
void manageInventory();
void updateItemAvailability();
void applyDiscount();
void addTip();
void reserveTable();


User users[100];
MenuItem menu[100];
Order orders[100];
Table tables[20];
int userCount = 0;
int menuCount = 0;
int orderCount = 0;
int tableCount = 10;
int loggedInUser = -1;

int main() {

    for (int i = 0; i < tableCount; i++) {
        tables[i].tableId = i + 1;
        tables[i].reserved = 0;
    }

    int choice;
    while (1) {
        printf("\nRestaurant Management System\n");
        if (loggedInUser == -1) {
            printf("\n********** Welcome to Management system **********\n");
            printf("1. Sign Up\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: signUp(); break;
                case 2: login(); break;
                case 3: exit(0);
                default: printf("Invalid choice. Please try again.\n");
            }
        } else {
            printf("----------------------------------------------\n");
            printf("1. Place Order\n");
            printf("2. Add Item to Menu\n");
            printf("3. Delete Item from Menu\n");
            printf("4. Make Payment\n");
            printf("5. View Daily Operations\n");
            printf("6. Generate Sales Report\n");
            printf("7. Manage Users\n");
            printf("8. Manage Inventory\n");
            printf("9. Update Item Availability\n");
            printf("10. Apply Discount\n");
            printf("11. Add Tip\n");
            printf("12. Reserve Table\n");
            printf("13. Show Table Availability\n");

            printf("14. clearMenu\n");
            printf("15. showDailySpecials Menu\n");
            printf("16. Logout\n");
            printf("__________________________________\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: placeOrder(); break;
                case 2: addItem(); break;
                case 3: deleteItem(); break;
                case 4: makePayment(); break;
                case 5: viewDailyOperations(); break;
                case 6: generateSalesReport(); break;
                case 7: manageUsers(); break;
                case 8: manageInventory(); break;
                case 9: updateItemAvailability(); break;
                case 10: applyDiscount(); break;
                case 11: addTip(); break;
                case 12: reserveTable(); break;
                case 13: showTableAvailability(); break;
                case 14: clearMenu(); break;
                case 16: loggedInUser = -1; break;
                case 15: showDailySpecials();break;
                default: printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}




void addItem() {
    MenuItem newItem;
    printf("Enter item ID: ");
    scanf("%d", &newItem.id);
    printf("Enter item name: ");
    scanf("%s", newItem.name);
    printf("Enter item price: ");
    scanf("%f", &newItem.price);
    newItem.available = 1;

    menu[menuCount++] = newItem;
    printf("Item added to menu successfully.\n");
}

void deleteItem() {
    int id;
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == id) {
            menu[i] = menu[menuCount - 1]; // Replace with last item
            menuCount--;
            printf("Item deleted from menu successfully.\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void updateItemAvailability() {
    int id, availability;
    printf("Enter item ID to update: ");
    scanf("%d", &id);
    printf("Enter new availability (1 for available, 0 for unavailable): ");
    scanf("%d", &availability);

    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == id) {
            menu[i].available = availability;
            printf("Item availability updated successfully.\n");
            return;
        }
    }
    printf("Item not found.\n");
}
void showMenu() {
    printf("Menu:\n");
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].available) {
            printf("ID: %d | Name: %s | Price: %.2f\n", menu[i].id, menu[i].name, menu[i].price);
        }
    }
}

void placeOrder() {
    int orderId, itemId, quantity, moreItems;
    printf("Enter order ID: ");
    scanf("%d", &orderId);

    do {
        showMenu(); // Display the menu before placing an order
        printf("Enter item ID: ");
        scanf("%d", &itemId);
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        // Add order details
        Order newOrder = {orderId, itemId, quantity};
        orders[orderCount++] = newOrder;

        printf("Do you want to order more items? (1 for Yes, 0 for No): ");
        scanf("%d", &moreItems);
    } while (moreItems == 1);

    printf("Order placed successfully.\n");
}




void makePayment() {
    int orderId;
    float amount = 0, tip, total;
    printf("Enter order ID for payment: ");
    scanf("%d", &orderId);

    // Calculate amount for the entire order
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            for (int j = 0; j < menuCount; j++) {
                if (menu[j].id == orders[i].itemId) {
                    amount += menu[j].price * orders[i].quantity;
                }
            }
        }
    }

    printf("Total amount (excluding tip): %.2f\n", amount);
    printf("Enter tip amount: ");
    scanf("%f", &tip);
    total = amount + tip;
    printf("Total amount to be paid (including tip): %.2f\n", total);

    // Mark the order as paid (assuming a simple representation)
    printf("Payment completed for Order ID: %d\n", orderId);
}

void viewDailyOperations() {
    printf("Daily Operations Overview:\n");
    // List all orders
    for (int i = 0; i < orderCount; i++) {
        printf("Order ID: %d, Item ID: %d, Quantity: %d\n", orders[i].orderId, orders[i].itemId, orders[i].quantity);
    }
}

void generateSalesReport() {
    float totalSales = 0;
    for (int i = 0; i < orderCount; i++) {
        for (int j = 0; j < menuCount; j++) {
            if (menu[j].id == orders[i].itemId) {
                totalSales += menu[j].price * orders[i].quantity;
            }
        }
    }
    printf("Total Sales: %.2f\n", totalSales);
}

void manageUsers() {
    printf("Manage Users:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Username: %s\n", users[i].username);
    }
}

void manageInventory() {
    printf("Manage Inventory:\n");
    for (int i = 0; i < menuCount; i++) {
        printf("Item ID: %d, Name: %s, Available: %d\n", menu[i].id, menu[i].name, menu[i].available);
    }
}

void applyDiscount() {
    int id;
    float discount;
    printf("Enter item ID to apply discount: ");
    scanf("%d", &id);
    printf("Enter discount percentage: ");
    scanf("%f", &discount);

    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == id) {
            menu[i].price -= (menu[i].price * discount / 100);
            printf("Discount applied successfully.\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void addTip() {
    int orderId;
    float tip;
    printf("Enter order ID to add tip: ");
    scanf("%d", &orderId);
    printf("Enter tip amount: ");
    scanf("%f", &tip);

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {

            printf("Tip added to order successfully.Thank You..\n");
            return;
        }
    }
    printf("Order not found.\n");
}
void reserveTable() {
    int tableId;
    printf("Enter table ID to reserve: ");
    scanf("%d", &tableId);

    if (tableId > 0 && tableId <= tableCount) {
        if (tables[tableId - 1].reserved == 0) {
            tables[tableId - 1].reserved = 1;
            printf("Table %d reserved successfully.\n", tableId);
        } else {
            printf("Table %d is already reserved.\n", tableId);
        }
    } else {
        printf("Invalid table ID.\n");
    }
}
void showTableAvailability() {
    printf("Table Availability:\n");
    for (int i = 0; i < tableCount; i++) {
        printf("Table %d: %s\n", tables[i].tableId, tables[i].reserved ? "Reserved" : "Available");
    }
}


void login() {
    char username[30], password[30];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Authenticate user from file
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char fileUsername[30], filePassword[30];
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) == 0 && strcmp(filePassword, password) == 0) {
            printf("Login successful.\n");
            loggedInUser = userCount;
            User newUser;
            strcpy(newUser.username, fileUsername);
            strcpy(newUser.password, filePassword);
            users[userCount++] = newUser;
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Invalid credentials.\n");
}


void signUp() {
    User newUser;
    int userExists;
    do {
        userExists = 0; // Reset flag for each new username attempt
        printf("Enter username: ");
        scanf("%s", newUser.username);

        // Check if username already exists
        FILE *file = fopen("users.txt", "r");
        if (file == NULL) {
            // Create the file if it does not exist
            file = fopen("users.txt", "w");
            if (file == NULL) {
                printf("Error creating file!\n");
                return;
            }
            fclose(file);
            file = fopen("users.txt", "r");
        }

        if (file != NULL) {
            char fileUsername[30], filePassword[30];
            while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
                if (strcmp(fileUsername, newUser.username) == 0) {
                    userExists = 1;
                    printf("Username already exists. Please choose a different username.\n");
                    break;
                }
            }
            fclose(file);
        }
    } while (userExists);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    // Save new user to file
    FILE *file = fopen("users.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", newUser.username, newUser.password);
        fclose(file);
    } else {
        printf("Error opening file for writing!\n");
        return;
    }

    // Add new user to users array
    users[userCount++] = newUser;
    printf("User registered successfully.\n");
}

void clearMenu() {
    menuCount = 0;
    printf("Menu cleared successfully.\n");
}
void showDailySpecials() {
    printf("\nToday's Specials:\n");
    printf("1. Kacci- 299 taka\n");
    printf("2. Beef khicuri- 250 taka\n");
    printf("3. Special lacci- 199 taka\n");
}
