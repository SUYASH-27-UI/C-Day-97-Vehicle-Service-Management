#include <stdio.h>

#define MAX 100

struct Vehicle {
    int id;
    char owner[50];
    char vehicle[50];
    char service[50];
    float cost;
};

struct Vehicle records[MAX];
int count = 0;

int findVehicle(int id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) {
            return i;
        }
    }

    return -1;
}

void loadRecords() {
    FILE *file = fopen("vehicles.txt", "r");

    if (file == NULL) {
        return;
    }

    while (count < MAX &&
           fscanf(file, "%d %49s %49s %49s %f",
                  &records[count].id,
                  records[count].owner,
                  records[count].vehicle,
                  records[count].service,
                  &records[count].cost) == 5) {
        count++;
    }

    fclose(file);
}

void saveRecords() {
    FILE *file = fopen("vehicles.txt", "w");

    if (file == NULL) {
        printf("Error saving records!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %s %.2f\n",
                records[i].id,
                records[i].owner,
                records[i].vehicle,
                records[i].service,
                records[i].cost);
    }

    fclose(file);
}

void addVehicle() {
    if (count >= MAX) {
        printf("Storage full!\n");
        return;
    }

    struct Vehicle v;

    printf("Enter Vehicle ID: ");
    if (scanf("%d", &v.id) != 1 || v.id <= 0) {
        printf("Invalid ID!\n");
        return;
    }

    if (findVehicle(v.id) != -1) {
        printf("Vehicle ID already exists!\n");
        return;
    }

    printf("Enter Owner Name (one word): ");
    scanf("%49s", v.owner);

    printf("Enter Vehicle Name (one word): ");
    scanf("%49s", v.vehicle);

    printf("Enter Service Type (one word): ");
    scanf("%49s", v.service);

    printf("Enter Service Cost: ");
    if (scanf("%f", &v.cost) != 1 ||
        v.cost < 0) {
        printf("Invalid cost!\n");
        return;
    }

    records[count] = v;
    count++;

    saveRecords();

    printf("Service record added successfully!\n");
}

void displayRecords() {
    if (count == 0) {
        printf("No service records found.\n");
        return;
    }

    printf("\n--- Vehicle Service Records ---\n");

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", records[i].id);
        printf("Owner: %s\n", records[i].owner);
        printf("Vehicle: %s\n", records[i].vehicle);
        printf("Service: %s\n", records[i].service);
        printf("Cost: Rs. %.2f\n", records[i].cost);
    }
}

void searchVehicle() {
    int id;

    printf("Enter Vehicle ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findVehicle(id);

    if (index == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    printf("Owner: %s\n", records[index].owner);
    printf("Vehicle: %s\n", records[index].vehicle);
    printf("Service: %s\n", records[index].service);
    printf("Cost: Rs. %.2f\n", records[index].cost);
}

void updateCost() {
    int id;

    printf("Enter Vehicle ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findVehicle(id);

    if (index == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    float cost;

    printf("Enter New Service Cost: ");

    if (scanf("%f", &cost) != 1 || cost < 0) {
        printf("Invalid cost!\n");
        return;
    }

    records[index].cost = cost;

    saveRecords();

    printf("Service cost updated!\n");
}

void deleteRecord() {
    int id;

    printf("Enter Vehicle ID to delete: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findVehicle(id);

    if (index == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        records[i] = records[i + 1];
    }

    count--;

    saveRecords();

    printf("Record deleted successfully!\n");
}

int main() {
    int choice;

    loadRecords();

    while (1) {
        printf("\n===== VEHICLE SERVICE SYSTEM =====\n");
        printf("1. Add Vehicle\n");
        printf("2. Display Records\n");
        printf("3. Search Vehicle\n");
        printf("4. Update Service Cost\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addVehicle();
                break;

            case 2:
                displayRecords();
                break;

            case 3:
                searchVehicle();
                break;

            case 4:
                updateCost();
                break;

            case 5:
                deleteRecord();
                break;

            case 6:
                printf("Program closed.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
