#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Parking
{
    char regNo[20];
    int entryTime;
    int occupied;
};

struct Parking p[10];
int max = 10;


void readLine(char str[], int size)
{
    int ch;

    if(fgets(str, size, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }

    if(strchr(str, '\n') == NULL)
    {
        
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    else
    {
        str[strcspn(str, "\n")] = '\0';
    }
}


int readInt()
{
    char line[50];
    int n;

    readLine(line, sizeof(line));

    if(sscanf(line, "%d", &n) != 1)
    {
        return -1;
    }

    return n;
}

/* Remove spaces and convert to uppercase: "hr 45 ds 8765" -> "HR45DS8765" */
void normalize(char str[])
{
    int i, j = 0;

    for(i = 0; str[i] != '\0'; i++)
    {
        if(!isspace((unsigned char)str[i]))
        {
            str[j] = toupper((unsigned char)str[i]);
            j++;
        }
    }

    str[j] = '\0';
}

void initialize()
{
    int i;

    for(i = 0; i < max; i++)
    {
        p[i].occupied = 0;
    }
}

int availableSpaces()
{
    int i, count = 0;

    for(i = 0; i < max; i++)
    {
        if(p[i].occupied == 0)
        {
            count++;
        }
    }

    return count;
}

/* Function to search vehicle */
int searchVehicle(char reg[])
{
    int i;

    for(i = 0; i < max; i++)
    {
        if(p[i].occupied == 1 &&
           strcmp(p[i].regNo, reg) == 0)
        {
            return i;
        }
    }

    return -1;
}

/* Vehicle Entry */
void vehicleEntry()
{
    char reg[20];
    int time;
    int i;
    int slot = -1;

    printf("\nEnter vehicle registration number: ");
    readLine(reg, sizeof(reg));
    normalize(reg);

    if(strlen(reg) == 0)
    {
        printf("Registration number cannot be empty!\n");
        return;
    }

    if(searchVehicle(reg) != -1)
    {
        printf("Vehicle is already parked!\n");
        return;
    }

    if(availableSpaces() == 0)
    {
        printf("Parking area is FULL!\n");
        return;
    }

    printf("Enter entry time (in hours, 0-23): ");
    time = readInt();

    if(time < 0 || time > 23)
    {
        printf("Invalid time!\n");
        return;
    }

    /* Find free slot */
    for(i = 0; i < max; i++)
    {
        if(p[i].occupied == 0)
        {
            slot = i;
            break;
        }
    }

    strcpy(p[slot].regNo, reg);
    p[slot].entryTime = time;
    p[slot].occupied = 1;

    printf("Vehicle %s entered successfully.\n", reg);
    printf("Parking slot: %d\n", slot + 1);
    printf("Available spaces: %d\n", availableSpaces());
}

/* Vehicle Exit */
void vehicleExit()
{
    char reg[20];
    int exitTime;
    int position;
    int duration;
    float fee;

    printf("\nEnter vehicle registration number: ");
    readLine(reg, sizeof(reg));
    normalize(reg);

    position = searchVehicle(reg);

    if(position == -1)
    {
        printf("Vehicle not found!\n");
        return;
    }

    printf("Enter exit time (in hours, 0-23): ");
    exitTime = readInt();

    if(exitTime < 0 || exitTime > 23)
    {
        printf("Invalid time!\n");
        return;
    }

    duration = exitTime - p[position].entryTime;

    if(duration < 0)
    {
        duration = duration + 24;
    }

    if(duration == 0)
    {
        duration = 1;
    }

    fee = duration * 20;

    printf("\n----- PARKING RECEIPT -----\n");
    printf("Vehicle Number : %s\n", p[position].regNo);
    printf("Entry Time     : %d:00\n", p[position].entryTime);
    printf("Exit Time      : %d:00\n", exitTime);
    printf("Duration       : %d hour(s)\n", duration);
    printf("Parking Fee    : Rs %.2f\n", fee);
    printf("---------------------------\n");

    p[position].occupied = 0;

    printf("Vehicle exited successfully.\n");
}

void displayAvailability()
{
    printf("\n----- PARKING STATUS -----\n");
    printf("Total Spaces     : %d\n", max);
    printf("Occupied Spaces  : %d\n", max - availableSpaces());
    printf("Available Spaces : %d\n", availableSpaces());
}

void vehicleStatus()
{
    char reg[20];
    int position;

    printf("\nEnter vehicle registration number: ");
    readLine(reg, sizeof(reg));
    normalize(reg);

    position = searchVehicle(reg);

    if(position == -1)
    {
        printf("Vehicle is NOT parked.\n");
    }
    else
    {
        printf("Vehicle is parked.\n");
        printf("Slot Number : %d\n", position + 1);
        printf("Entry Time  : %d:00\n", p[position].entryTime);
    }
}

void displayParking()
{
    int i;

    printf("\n----- PARKING LOT -----\n");

    for(i = 0; i < max; i++)
    {
        printf("Slot %d : ", i + 1);

        if(p[i].occupied == 1)
        {
            printf("%s\n", p[i].regNo);
        }
        else
        {
            printf("EMPTY\n");
        }
    }
}

int main()
{
    int choice;

    initialize();

    do
    {
        printf("\n================================");
        printf("\n   SMART CAMPUS PARKING SYSTEM");
        printf("\n================================");

        printf("\n1. Vehicle Entry");
        printf("\n2. Vehicle Exit");
        printf("\n3. Parking Availability");
        printf("\n4. Vehicle Status");
        printf("\n5. Display Parking Lot");
        printf("\n0. Exit");

        printf("\n\nEnter your choice: ");
        choice = readInt();

        switch(choice)
        {
            case 1:
                vehicleEntry();
                break;

            case 2:
                vehicleExit();
                break;

            case 3:
                displayAvailability();
                break;

            case 4:
                vehicleStatus();
                break;

            case 5:
                displayParking();
                break;

            case 0:
                printf("\nProgram terminated.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}
