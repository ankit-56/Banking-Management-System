#include "ui_display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char name[50];
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

int main() {
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int opt, choice;
    char cont = 'y';
    float amount;

    while (1) {
        showWelcomeScreen();
        showMainMenu(); 

        printf("\nYour choice:\t");
        scanf("%d", &opt);

        // Register an Account
        if (opt == 1) {
            system("cls");
            printf("Enter your full name:\t");
            scanf(" %[^\n]", usr.name);
            printf("Enter your account number:\t");
            scanf("%s", usr.ac);
            printf("Enter your phone number:\t");
            scanf("%s", usr.phone);
            printf("Enter your new password:\t");
            scanf("%s", usr.password);
            usr.balance = 0;

            strcpy(filename, usr.phone);
            fp = fopen(strcat(filename, ".dat"), "w");
            if (fp == NULL) {
                printf("\nError creating account. Try again.");
                continue;
            }

            fwrite(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            printf("\n\nAccount successfully registered!\n");
        }

        // Login to an Account
        else if (opt == 2) {
            system("cls");
            printf("\nPhone number:\t");
            scanf("%s", phone);
            printf("Password:\t");
            scanf("%s", pword);

            strcpy(filename, phone);
            fp = fopen(strcat(filename, ".dat"), "r");

            if (fp == NULL) {
                printf("\nAccount not registered!\n");
                continue;
            }

            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            if (strcmp(pword, usr.password) == 0) {
                // UI-based login message
                showAccountUI(usr.name, usr.balance);

                cont = 'y';
                while (cont == 'y' || cont == 'Y') {
                    printf("\n===============================");
                    printf("\n        Banking Menu");
                    printf("\n===============================");
                    printf("\n1. Balance Inquiry");
                    printf("\n2. Deposit Cash");
                    printf("\n3. Withdraw Cash");
                    printf("\n4. Online Transfer");
                    printf("\n5. Change Password");
                    printf("\n6. Apply for Loan");
                    printf("\n7. Logout");

                    printf("\n\nYour choice:\t");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            showAccountUI(usr.name, usr.balance);
                            break;

                        case 2:
                            printf("\nEnter amount to deposit:\t");
                            scanf("%f", &amount);
                            usr.balance += amount;
                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nRs. %.2f deposited successfully!\n", amount);
                            showAccountUI(usr.name, usr.balance);
                            break;

                        case 3:
                            printf("\nEnter amount to withdraw:\t");
                            scanf("%f", &amount);
                            if (amount > usr.balance) {
                                printf("\nInsufficient balance!\n");
                            } else {
                                usr.balance -= amount;
                                fp = fopen(filename, "w");
                                fwrite(&usr, sizeof(struct user), 1, fp);
                                fclose(fp);
                                printf("\nRs. %.2f withdrawn successfully!\n", amount);
                                showAccountUI(usr.name, usr.balance);
                            }
                            break;

                        case 4:
                            printf("\nEnter recipient phone number:\t");
                            scanf("%s", phone);
                            printf("Enter amount to transfer:\t");
                            scanf("%f", &amount);

                            if (amount > usr.balance) {
                                printf("\nInsufficient balance!\n");
                            } else {
                                strcpy(filename, phone);
                                fp = fopen(strcat(filename, ".dat"), "r");
                                if (fp == NULL) {
                                    printf("\nRecipient account not found!\n");
                                } else {
                                    fread(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    usr1.balance += amount;
                                    fp = fopen(filename, "w");
                                    fwrite(&usr1, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    strcpy(filename, usr.phone);
                                    fp = fopen(strcat(filename, ".dat"), "w");
                                    usr.balance -= amount;
                                    fwrite(&usr, sizeof(struct user), 1, fp);
                                    fclose(fp);

                                    printf("\nRs. %.2f transferred successfully to %s!\n", amount, usr1.name);
                                    showAccountUI(usr.name, usr.balance);
                                }
                            }
                            break;

                        case 5:
                            printf("\nEnter your new password:\t");
                            scanf("%s", pword);
                            strcpy(usr.password, pword);
                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nPassword changed successfully!\n");
                            break;

                        case 6: {
                            printf("\n===== Loan Services =====");
                            printf("\n1. Home Loan");
                            printf("\n2. Gold Loan");
                            printf("\n3. Personal Loan");

                            printf("\n\nChoose loan type:\t");
                            int loanChoice;
                            scanf("%d", &loanChoice);

                            float loanAmount, rate, emi;
                            int years;

                            printf("\nEnter loan amount:\t");
                            scanf("%f", &loanAmount);
                            printf("Enter tenure (in years):\t");
                            scanf("%d", &years);

                            if (loanChoice == 1) rate = 8.5;
                            else if (loanChoice == 2) rate = 7.0;
                            else rate = 10.5;

                            emi = (loanAmount * rate * years) / 100 + loanAmount;

                            // Credit loan to user account
                            usr.balance += loanAmount;
                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);

                            //  UI-based loan info
                            showLoanInfo(loanAmount, 
                                (loanChoice == 1) ? "Home Loan" : 
                                (loanChoice == 2) ? "Gold Loan" : "Personal Loan");
                            printf("\nTotal Payable (after interest): Rs. %.2f", emi);
                            printf("\nMonthly EMI: Rs. %.2f", emi / (years * 12));
                            printf("\nUpdated Account Balance: Rs. %.2f\n", usr.balance);
                            break;
                        }

                        case 7:
                            printf("\nLogged out successfully!\n");
                            cont = 'n';
                            break;

                        default:
                            printf("\nInvalid option! Try again.\n");
                    }

                    if (choice != 7) {
                        printf("\nDo you want to continue transactions? [y/n]: ");
                        scanf(" %c", &cont);
                    }
                }
            } else {
                printf("\nInvalid password!\n");
            }
        }

        else if (opt == 3) {
            printf("\nThank you for using SBI Bank!\n");
            exit(0);
        }

        else {
            printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
