
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
#define MAX_MOVIES 10
#define MAX_MOVIE_NAME 50
#define MAX_USER_NAME 50
// Define constants
        #define MAX_MALL_AREAS 100


// Constants
#define NUM_FLOORS 10
FILE *FC;
FILE *abt;
// Enum to represent the state of the elevator
enum ElevatorState
{
    IDLE,
    MOVING_UP,
    MOVING_DOWN
};

// Simulated biometric data (fingerprints) for two users
char user1Fingerprint[10] = "User1Fp";
char user2Fingerprint[10] = "User2Fp";

// Function to verify the fingerprint
bool verifyFingerprint(char *enteredFingerprint, char *storedFingerprint)
{
    return (strcmp(enteredFingerprint, storedFingerprint) == 0);
}

// Elevator structure
struct Elevator
{
    int currentFloor;
    enum ElevatorState state;
};

// Structure to represent a product
struct Product
{
    char name[50];
    float price;
};

// Structure to represent an item in the shopping cart
struct CartItem
{
    struct Product product;
    int quantity;
};

struct order
{
    char name[50];
    int order_number;
    int number_of_food;
    int cost;
} p[10000];
int order_count = 0, served_count = 0, waiting_now = 0;

typedef struct
{
    char name[MAX_MOVIE_NAME];
    int availableSeats;
    float price;
} Movie;

typedef struct
{
    char username[MAX_USER_NAME];
    int tickets;
    float totalCost;
} User;

Movie movies[MAX_MOVIES];
User currentUser;
int numMovies = 0;

struct list
{
    char author[20];
    char title[30];
    float price;
    struct
    {
        char month[10];
        int year;
    } date;
    char publisher[10];
    int quantity;
};

// Structures to represent mall areas and equipment
struct MallArea {
    char name[50];
    int numLights;
    int numHVAC;
};

struct Equipment {
    char name[50];
    int powerConsumption;
};

struct Move
{
    int row, col;
};

char player = 'x', opponent = 'o';
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}
void aboutUs()
{

    abt = fopen("Name.txt", "w");
    fprintf(abt, "\t\t** TEAM **\n");
    fprintf(abt, "\t\tTeesha Dhiman  \t23103334\n");
    fprintf(abt, "\t\tPoonam         \t23103306\n");
    fprintf(abt, "\t\tVipanshu Mittal\t23103324\n");
    fprintf(abt, "\t\tAvinash Umrao  \t23103316\n");
    fclose(abt);
}
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (isMovesLeft(board) == false)
        return 0;
    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = player;
                    int val = minimax(board, depth + 1, !isMax);
                    if (val > best)
                    {
                        best = val;
                    }
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '_')
                {
                    board[i][j] = opponent;
                    int val = minimax(board, depth + 1, !isMax);
                    if (val < best)
                    {
                        best = val;
                    }
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

struct Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// Function to calculate total energy consumption
int calculateEnergyConsumption(struct MallArea mall[], int numAreas, struct Equipment equipment[],
                               int numEquipment)
{
    int totalEnergy = 0;
    for (int i = 0; i < numAreas; i++)
    {
        int areaEnergy = 0;
        for (int j = 0; j < mall[i].numLights; j++)
        {
            areaEnergy += equipment[j].powerConsumption;
        }
        for (int j = mall[i].numLights; j < mall[i].numLights + mall[i].numHVAC; j++)
        {
            areaEnergy += equipment[j].powerConsumption;
        }
        totalEnergy += areaEnergy;
    }
    return totalEnergy;
}

int order()
{
    int n, in, qu;
    printf("please enter your name: ");
    gets(p[order_count].name);
    p[order_count].order_number = 10000 + order_count;
    // item();
    p[order_count].number_of_food = n;
    p[order_count].cost = 0;
    p[order_count].number_of_food = 0;

level:
    printf("How many items you want to order? ");
    scanf("%d", &n);

    getchar();
    while (n--)
    {
        printf("\nEnter chosen item code\n");
        scanf("%d", &in);
        getchar();
        switch (in)
        {
        case 11:
        {
            printf("Enter the size of burger: 1. 200 gm  2. 300 gm\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (130 * qu);

            else
                p[order_count].cost += (180 * qu);
            break;
        }
        case 12:
        {
            printf("Enter the size of Chicken Pizza: 1. 12 inch  2. 14 inch  3. 16 inch\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (750 * qu);

            else if (i == 2)
                p[order_count].cost += (975 * qu);

            else
                p[order_count].cost += (1250 * qu);

            break;
        }
        case 13:
        {
            printf("Enter the amount of chicken: 1. 1 pcs  2. 4 pcs  3. 10 pcs\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (85 * qu);

            else if (i == 2)
                p[order_count].cost += (320 * qu);

            else
                p[order_count].cost += (790 * qu);

            break;
        }
        case 14:
        {
            printf("Enter the size of grilled chicken: 1. quarter  2. half  3. full\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (70 * qu);

            else if (i == 2)
                p[order_count].cost += (140 * qu);

            else
                p[order_count].cost += (250 * qu);

            break;
        }
        case 15:
        {
            printf("Enter the size of Noodles: 1. half  2. full\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (130 * qu);

            else
                p[order_count].cost += (250 * qu);

            break;
        }
        case 16:
        {
            printf("Enter the size of pasta: 1. half  2. full\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (120 * qu);

            else
                p[order_count].cost += (240 * qu);

            break;
        }
        case 17:
        {
            printf("250 ml of OREO SHAKE\n");

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;
            p[order_count].cost += (180 * qu);
            break;
        }
        case 18:
        {
            printf("250 ml of Cold Coffee\n");

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;
            p[order_count].cost += (65 * qu);
            break;
        }
        case 19:
        {
            printf("250 ml of Cappuccino\n");

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;
            p[order_count].cost += (70 * qu);
            break;
        }
        case 20:
        {
            printf("Enter the size of Coke: 1. 250 ml  2. 500 ml\n");
            int i;
            scanf("%d", &i);
            getchar();

            printf("Please enter the quantity: ");
            scanf("%d", &qu);
            getchar();

            p[order_count].number_of_food += qu;

            if (i == 1)
                p[order_count].cost += (20 * qu);

            else
                p[order_count].cost += (30 * qu);
            break;
        }
        default:
        {
            printf("Invalid selection try again\n");
            n++;
        }
        }
    }
    char temp;
    printf("Do you want to order anything else?(y/n)\n ");
    scanf("%c", &temp);
    if (temp == 'y' || temp == 'Y')
        goto level;
    printf("\nNumber of food ordered %d\n", p[order_count].number_of_food);
    printf("\nThank you %s for your order. Your bill is Rupees %d.\nPlease wait while we prepare the food.\n\n", p[order_count].name, p[order_count].cost);
    order_count++;
}
void receive()
{
    if (order_count == 0)
    {
        printf("Please order first\n");
    }

    else if (served_count == order_count)
    {
        printf("All order served\n");
    }

    printf("Order no. %d by %s is ready\n", p[served_count].order_number, p[served_count].name);
    printf("Enjoy your meal\n\n");
    served_count++;
}
int display()

{

    printf("Total order taken: %d\n", (order_count));
    printf("Total number of order served %d\n", served_count);
    printf("Number of Currently waiting to be served: %d\n", (order_count - served_count));
    printf("Currently preparing food for order no. %d\n\n", p[served_count].order_number);
}
void items()
{
    printf("Hello");
    char str[100];
    FC = fopen("Food Court.txt", "r");
    while (fgets(str, 100, FC) != NULL)
    {
        printf("%s\n", str);
    }
    fclose(FC);
}

// Function to move the elevator
void moveElevator(struct Elevator *elevator, int targetFloor)
{
    if (targetFloor > elevator->currentFloor)
    {
        printf("Elevator is moving up...\n");
        elevator->state = MOVING_UP;
        while (elevator->currentFloor < targetFloor)
        {
            elevator->currentFloor++;
            printf("Current floor: %d\n", elevator->currentFloor);
        }
        printf("Elevator has arrived at floor %d\n", elevator->currentFloor);
    }
    else if (targetFloor < elevator->currentFloor)
    {
        printf("Elevator is moving down...\n");
        elevator->state = MOVING_DOWN;
        while (elevator->currentFloor > targetFloor)
        {
            elevator->currentFloor--;
            printf("Current floor: %d\n", elevator->currentFloor);
        }
        printf("Elevator has arrived at floor %d\n", elevator->currentFloor);
    }
    elevator->state = IDLE;
}

void initializeMovies()
{
    // Initialize movie data
    strcpy(movies[0].name, "Movie 1");
    movies[0].availableSeats = 100;
    movies[0].price = 1000.0;

    strcpy(movies[1].name, "Movie 2");
    movies[1].availableSeats = 80;
    movies[1].price = 1200.0;

    numMovies = 2;
}

void displayMovies()
{
    printf("Available Movies:\n");
    for (int i = 0; i < numMovies; i++)
    {
        printf("%d. %s - Price: Rs.%.2f - Seats: %d\n", i + 1, movies[i].name, movies[i].price,
               movies[i].availableSeats);
    }
    printf("\n");
}

int bookTickets(int movieIndex, int numTickets)
{
    if (movieIndex >= 0 && movieIndex < numMovies)
    {
        if (movies[movieIndex].availableSeats >= numTickets)
        {
            movies[movieIndex].availableSeats -= numTickets;
            currentUser.tickets = numTickets;
            currentUser.totalCost = numTickets * movies[movieIndex].price;
            return 1;
            // Booking successful
        }
        else
        {
            printf("Insufficient seats available.\n");
            return 0;
            // Booking failed
        }
    }
    else
    {
        printf("Invalid movie selection.\n");
        return 0;
        // Booking failed
    }
}

void header()
{

    printf(" \n\t\t\t|    :-WELCOME TO:- JIIT Book Store    |\n");
}

// to search the book in the list

int search(struct list table[], char c1[], char c2[], int n);

// to get the input string

void get(char string[]);

void get(char string[])
{
    char c;
    int i = 0;
    do
    {
        c = getchar();
        string[i++] = c;
    } while (c != '\n');
    string[i - 1] = '\0';
}

int search(struct list table[], char c1[], char c2[], int n)

{
    int i;
    for (i = 0; i < n; i++)
        if (strcmp(c1, table[i].title) == 0 && strcmp(c2, table[i].author) == 0)
            return (i);
    return (-1);
}

int evaluate(char b[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2])
        {
            if (b[row][0] == player)
                return +10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col])
        {
            if (b[0][col] == player)
                return +10;

            else if (b[0][col] == opponent)
                return -10;
        }
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
    }
    return 0;
}

void showBoard(char board[][SIDE])
{
    printf("\n\n");
    printf("\t\t\t %c | %c | %c \n", board[0][0],
           board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0],
           board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0],
           board[2][1], board[2][2]);
}

void showInstructions()
{
    printf("\t\t\t Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below "
           "and play\n\n");

    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");

    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

void initialise(char board[][SIDE], int moves[])
{
    srand(time(NULL));
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    }
    for (int i = 0; i < SIDE * SIDE; i++)
        moves[i] = i;

    for (int i = 0; i < SIDE * SIDE; i++)
    {
        int randIndex = rand() % (SIDE * SIDE);
        int temp = moves[i];
        moves[i] = moves[randIndex];
        moves[randIndex] = temp;
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won !!\nBetter luck next time.\n");
    else
        printf("Congratulations YOU won !!\n");
}

int rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
    }
    return 0;
}

int columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }
    return 0;
}

int diagonalCrossed(char board[][SIDE])
{
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') || (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;

    return 0;
}

int gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];
    initialise(board, moves);
    showInstructions();

    int moveIndex = 0, x, y;

    while (!gameOver(board) && moveIndex != SIDE * SIDE)
    {
        if (whoseTurn == COMPUTER)
        {
            char tempBoard[3][3];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == 'X')
                    {
                        tempBoard[i][j] = 'x';
                    }
                    else if (board[i][j] == 'O')
                    {
                        tempBoard[i][j] = 'o';
                    }
                    else
                    {
                        tempBoard[i][j] = '_';
                    }
                }
            }
            struct Move thisMove = findBestMove(tempBoard);
            x = thisMove.row;
            y = thisMove.col;
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in cell %d %d\n",
                   COMPUTERMOVE, x, y);
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            int move;
            printf("Enter your move (1-9): ");
            scanf("%d", &move);
            if (move < 1 || move > 9)
            {
                printf("Invalid input! Please enter a "
                       "number between 1 and 9.\n");
                continue;
            }
            x = (move - 1) / SIDE;
            y = (move - 1) % SIDE;
            if (board[x][y] == ' ')
            {
                board[x][y] = HUMANMOVE;
                showBoard(board);
                moveIndex++;
                if (gameOver(board))
                {
                    declareWinner(HUMAN);
                    return;
                }
                whoseTurn = COMPUTER;
            }
            else
            {
                printf("Cell %d is already occupied. Try "
                       "again.\n",
                       move);
            }
        }
    }
    if (!gameOver(board) && moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn);
    }
}

int main()

{
    char nm[50];
    aboutUs();
    abt = fopen("Name.txt", "r");
    while (fgets(nm, 50, abt) != NULL)
    {
        printf("%s\n", nm);
    }
    fclose(abt);

    printf(" 1 -> FOOD COURT \n 2 -> LIFTS, ELEVATORS & ESCALATORS \n 3 -> DIGITALOZATION OF KIOSKS \n 4 -> MOVIE BOOKING \n 5 -> BOOK CORNER \n 6 -> FINANCIAL MANAGEMENT \n 7 -> ENERGY MAINTENANCE \n 8 -> BIOMETRICS \n 9 -> GAMING ZONE \n");
    int z;
    printf("Enter your choice :\n");
    scanf("%d", &z);
    if (z == 1)
    {
        FC = fopen("Food court.txt", "w");
        fprintf(FC, "..................................MENU....................................\n");

        fprintf(FC, "Item Code#   Description-------------------Size--------------------Price(Rs.)\n");

        fprintf(FC, "[11]---------Burger---------------------200/300 gm------------------130/180\n");
        fprintf(FC, "[12]---------Chicken Pizza--------------12/14/16 inch---------------750/975/1250\n");
        fprintf(FC, "[13]---------Fried Chicken--------------1/4/10 pcs-----------------85/320/790\n");
        fprintf(FC, "[14]---------Grilled Chicken------------quarter/half/full----------70/140/250\n");
        fprintf(FC, "[15]---------Noodles--------------------Half/Full------------------130/250\n");
        fprintf(FC, "[16]---------Pasta----------------------Half/Full------------------120/240\n");
        fprintf(FC, "[17]---------Oreo Shake-----------------250 ml----------------------180\n");
        fprintf(FC, "[18]---------Cold Coffee----------------250 ml----------------------65\n");
        fprintf(FC, "[19]---------Cappuccino-----------------250 ml----------------------70\n");
        fprintf(FC, "[20]---------Coke-----------------------250/500 ml------------------20/30\n\n");
        fclose(FC);
        printf("\t\t     Welcome To JIIT food court\n");
        items();
        while (1)
        {
            printf("1. Order\n2. Serve\n3. Display \n4. Thankyou for visiting us.\n");

            int in;

            scanf("%d", &in);
            getchar();
            switch (in)
            {
            case 1:
            {
                order();
                break;
            }
            case 2:
            {
                receive();
                break;
            }
            case 3:
            {
                display();

                break;
            }

            case 4:
            {
                system("COLOR 2");
                printf("Thankyou\n");
                return 0;
            }
            }
        }
    }

    if (z == 2)
    {
        struct Elevator elevator;
        elevator.currentFloor = 1;
        elevator.state = IDLE;

        int targetFloor;
        bool inEmergency = false;

        while (true)
        {
            printf("Enter the target floor (1-%d): ", NUM_FLOORS);
            if (scanf("%d", &targetFloor) != 1 || targetFloor < 1 || targetFloor > NUM_FLOORS)
            {
                printf("Invalid input. Please enter a valid floor number.\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
                continue;
            }

            if (inEmergency)
            {
                printf("Elevator is in emergency mode. Cannot take requests.\n");
                continue;
            }

            if (elevator.state != IDLE)
            {
                printf("Elevator is currently in use. Please wait for it to arrive.\n");
                continue;
            }

            moveElevator(&elevator, targetFloor);

            // Check for emergency situation
            printf("Is there an emergency situation? (1 for yes, 0 for no): ");
            if (scanf("%d", &inEmergency) != 1)
            {
                printf("Invalid input. Assuming no emergency.\n");
                inEmergency = 0;
            }
        }
    }

    if (z == 3)
    {
        // Sample product data
        struct Product products[] = {
            {"Shirt", 1600},
            {"Jeans", 2400},
            {"Shoes", 6000},
            {"Hat", 800},
        };

        // Shopping cart to store selected items
        struct CartItem cart[10];
        int cartSize = 0;

        while (1)
        {
            printf("===== Mall Shopping System =====\n");
            printf("Available Products:\n");

            for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++)
            {
                printf("%d. %s - Rs.%.2f\n", i + 1, products[i].name, products[i].price);
            }

            printf("A. Add to Cart\n");
            printf("C. View Cart\n");
            printf("P. Process Payment\n");
            printf("Q. Quit\n");

            printf("Enter your choice: ");
            char choice;
            scanf(" %c", &choice);

            if (choice == 'Q' || choice == 'q')
            {
                break;
            }

            switch (choice)
            {
            case 'A':
            case 'a':
            {
                int productNumber;
                printf("Enter the product number to add to the cart: ");
                scanf("%d", &productNumber);

                if (productNumber >= 1 && productNumber <= sizeof(products) / sizeof(products[0]))
                {
                    int quantity;
                    printf("Enter the quantity: ");
                    scanf("%d", &quantity);

                    if (cartSize < 10)
                    {
                        struct CartItem item;
                        item.product = products[productNumber - 1];
                        item.quantity = quantity;
                        cart[cartSize++] = item;
                        printf("%d %s(s) added to your cart.\n", quantity, item.product.name);
                    }
                    else
                    {
                        printf("Cart is full. Proceed to payment or remove items from the cart.\n");
                    }
                }
                else
                {
                    printf("Invalid product number.\n");
                }
                break;
            }
            case 'C':
            case 'c':
                printf("===== Shopping Cart =====\n");
                for (int i = 0; i < cartSize; i++)
                {
                    struct CartItem item = cart[i];
                    printf("%d. %s x%d - Rs.%.2f\n", i + 1, item.product.name, item.quantity,
                           item.product.price * item.quantity);
                }
                break;
            case 'P':
            case 'p':
            {
                float totalBill = 0;
                for (int i = 0; i < cartSize; i++)
                {
                    struct CartItem item = cart[i];
                    totalBill += item.product.price * item.quantity;
                }
                printf("===== Payment Summary =====\n");
                printf("Total Bill: Rs.%.2f\n", totalBill);
                printf("Thank you for shopping with us! Please proceed to make a payment.\n");
                // You can add payment processing logic here.
                break;
            }
            default:
                printf("Invalid choice. Please select a valid option.\n");
            }
        }
    }
    if (z == 4)
    {
        initializeMovies();

        printf("Welcome to the Movie Ticket Booking System\n");

        while (1)
        {
            printf("1. Display Available Movies\n");
            printf("2. Book Tickets\n");
            printf("3. Exit\n");

            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                displayMovies();
                break;

            case 2:
                displayMovies();
                int movieChoice, numTickets;
                printf("Enter the movie number you want to book: ");
                scanf("%d", &movieChoice);
                printf("Enter the number of tickets: ");
                scanf("%d", &numTickets);

                if (bookTickets(movieChoice - 1, numTickets))
                {
                    printf("Booking successful!\n");
                    printf("Total Cost: Rs.%.2f\n", currentUser.totalCost);
                }
                else
                {
                    printf("Booking failed. Please try again.\n");
                }
                break;

            case 3:
                printf("Thank you for using the Movie Ticket Booking System.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    if (z == 5)
    {
        int index, no_of_record;
        char title[30], author[20];
        char responce[10], quantity[10];
        struct list book[] =
            {
                {"Ritche", "C Language", 245.00, "May", 1977, "PHI", 15},
                {"A S Hornby", "Oxford Advanced Dictionary", 550.00, "Jan", 2001, "OUP", 20},
                {"Ivor Horton", "Beginning Java", 527.50, "Nov", 2012, "WILEY", 15},
                {"Dr. B.V. Raju", "Finite Automata", 225.00, "Oct", 2010, "TMH", 10},
                {"Kochan", "Programming in C", 275.50, "july", 1983, "hayden", 25},
                {"Rajiv Mall", "Software Engineering", 310.00, "Jun", 2011, "TMH", 20},
                {"Balagurusamy", "Basic", 268.00, "Jan", 1984, "TMH", 20},
                {"Andrew S. Tanenbaum", "Computer Networks", 420.00, "Aug", 2009, "TMH", 15},
                {"Balagurusamy", "COBOL", 260.00, "Dec", 1988, "Macmillan", 25},
                {"Godbole & Kahate", "Web Technologies", 340.00, "Sep", 2012, "TMH", 20}};
        // calculate how many book in our list
        no_of_record = sizeof(book) / sizeof(struct list);
        do
        {
            system("cls");
            header();
        printf("\n\n\n\n\t:- ENTER THE TITLE AND AUTHOR OF THE BOOK WHICH YOU WANT TO PURCHASE :- \n"); 
        printf("\n\n\t:- TITLE :-"); 
        get(title); 
        printf("\n\n\t:- AUTHOR :-"); 
        get(author); 
        index=search(book,title,author,no_of_record); 
        if(index !=-1) 
        {
                printf("\n\n YOUR DESIRE BOOK AVAILBLE IN THE STOCK.\n\n");
                printf("[AUTHOR]   [TITLE]   [PRICE]   [MONTH]   [YEAR]   [PUBLISHER]\n");
                printf("-------------------------------------------------------------");
                printf("\n%s  %s  %.2f  %s   %d   %s \n\n ",book[index].author,book[index].title,book[index].price,book[index].date.month,book[index].date.year,     book[index].publisher);
                printf("\n\n ENTER THE NUMBER OF COPIES:");
                get(quantity);

                if (atoi(quantity) <= book[index].quantity)
            printf("\n\nCOST OF THE %d COPIES IS=%.2f\n ",atoi(quantity),book[index].price*atoi(quantity)); 
            else 
            printf("\n REQUIRED COPIES NOT IN THE STOCK \n\n"); 
        } 
        else 
        printf("\n YOUR DESIRED BOOK IS NOT IN THE STOCK.\n\n"); 
        printf("\n DO YOU WANT TO PURCHASE ANY OTHER BOOK ? (Y/N):"); 
        get(responce);
        }

        while (responce[0] == 'y' || responce[0] == 'y');
        printf("\n\n THANK YOU....!!!!\n");
        printf("www.i-world-tech.blogspot.in\n\n\n");
    }
    if (z == 6)
    {
        float totalSales = 0;
        float totalExpenses = 0;

        while (1)
        {
            int choice;
            float amount;

            printf("Mall Financial Management System\n");
            printf("1. Enter Sales\n");
            printf("2. Enter Expenses\n");
            printf("3. Calculate Daily Profit\n");
            printf("4. Exit\n");
            printf("Select an option: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter sales amount: Rs.");
                scanf("%f", &amount);
                totalSales += amount;
                printf("Sales recorded: Rs.%.2f\n", amount);
                break;
            case 2:
                printf("Enter expense amount: Rs.");
                scanf("%f", &amount);
                totalExpenses += amount;
                printf("Expenses recorded: Rs.%.2f\n", amount);
                break;
            case 3:
                printf("Daily Profit: Rs.%.2f\n", totalSales - totalExpenses);
                break;
            case 4:
                printf("Exiting the Financial Management System\n");
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
            }
        }
    }
    if (z == 7)
    {
    int calculateEnergyConsumption(struct MallArea mall[], int numAreas, struct Equipment equipment[], int numEquipment);
    struct MallArea mall[MAX_MALL_AREAS];
    struct Equipment equipment[MAX_MALL_AREAS * 2]; 
    // Assuming each area has lights and HVAC units

    int numAreas, numEquipment;

    // Input number of mall areas and equipment
    printf("Enter the number of mall areas: ");
    scanf("%d", &numAreas);
    printf("Enter the number of equipment (lights and HVAC): ");
    scanf("%d", &numEquipment);

    // Input mall area details
    for (int i = 0; i < numAreas; i++) {
        printf("Enter the name of mall area %d: ", i + 1);
        scanf("%s", mall[i].name);
        printf("Enter the number of lights in %s: ", mall[i].name);
        scanf("%d", &mall[i].numLights);
        printf("Enter the number of HVAC units in %s: ", mall[i].name);
        scanf("%d", &mall[i].numHVAC);
    }

    // Input equipment details
    for (int i = 0; i < numEquipment; i++) {
        printf("Enter the name of equipment %d: ", i + 1);
        scanf("%s", equipment[i].name);
        printf("Enter the power consumption (in watts) of %s: ", equipment[i].name);
        scanf("%d", &equipment[i].powerConsumption);
    }

    // Calculate and display total energy consumption
    int totalEnergy = calculateEnergyConsumption(mall, numAreas, equipment, numEquipment);
    printf("Total Energy Consumption: %d watts\n", totalEnergy);

    }
    if (z == 8)
    {
        char enteredFingerprint[10];
        int attempts = 3;

        while (attempts > 0)
        {
            printf("Place your fingerprint on the sensor: ");
            scanf("%s", enteredFingerprint);

            if (verifyFingerprint(enteredFingerprint, user1Fingerprint))
            {
                printf("Welcome, User 1!\n");
                break;
            }
            else if (verifyFingerprint(enteredFingerprint, user2Fingerprint))
            {
                printf("Welcome, User 2!\n");
                break;
            }
            else
            {
                attempts--;
                if (attempts > 0)
                {
                    printf("Fingerprint verification failed. You have %d attempts remaining.\n", attempts);
                }
                else
                {
                    printf("Fingerprint verification failed. Access denied.\n");
                }
            }
        }
    }
    if (z == 9)
    {
        playTicTacToe(COMPUTER);
    }
    return 0;
}
