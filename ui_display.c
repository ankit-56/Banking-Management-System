#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    printf("\033[%dm", color);
#endif
}

void resetColor() {
#ifdef _WIN32
    setColor(7); // Default gray
#else
    printf("\033[0m");
#endif
}

void drawLine() {
    printf("============================================================\n");
}

void showWelcomeScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    setColor(11);  // Cyan
    drawLine();
    printf("                  WELCOME TO SBI ONLINE BANKING\n");
    drawLine();
    resetColor();
    printf("\n");
}

void showMainMenu() {
    setColor(14); // Yellow
    printf("1. Register an Account\n");
    printf("2. Login to an Account\n");
    printf("3. Exit\n");
    resetColor();
    drawLine();
}

void showAccountUI(char name[], float balance) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    setColor(10); // Green
    drawLine();
    printf("                 Account Dashboard - %s\n", name);
    drawLine();
    resetColor();

    setColor(14);
    printf("Current Balance: Rs. %.2f\n", balance);
    resetColor();

    drawLine();
}

void showLoanInfo(float loanAmount, char *loanType) {
    setColor(13); // Magenta
    printf("\n=============================================\n");
    printf("   Loan Type: %s\n", loanType);
    printf("   Loan Amount Approved: Rs. %.2f\n", loanAmount);
    printf("=============================================\n");
    resetColor();
}
