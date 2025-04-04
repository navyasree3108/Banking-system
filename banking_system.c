#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Account Information
typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

// Function to create a new account
void createAccount() {
    Account acc;
    FILE *file = fopen("accounts.dat", "ab");
    
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    acc.balance = 0;
    
    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

// Function to deposit money
void deposit() {
    int accNum;
    float amount;
    FILE *file = fopen("accounts.dat", "rb+"), *temp;
    Account acc;
    
    if (!file) {
        printf("No accounts found!\n");
        return;
    }
    
    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);
    
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            acc.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            printf("Amount Deposited Successfully!\n");
            fclose(file);
            return;
        }
    }
    
    printf("Account not found!\n");
    fclose(file);
}

// Function to withdraw money
void withdraw() {
    int accNum;
    float amount;
    FILE *file = fopen("accounts.dat", "rb+"), *temp;
    Account acc;
    
    if (!file) {
        printf("No accounts found!\n");
        return;
    }
    
    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);
    
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, file);
                printf("Amount Withdrawn Successfully!\n");
            } else {
                printf("Insufficient balance!\n");
            }
            fclose(file);
            return;
        }
    }
    
    printf("Account not found!\n");
    fclose(file);
}

// Function to check balance
void checkBalance() {
    int accNum;
    FILE *file = fopen("accounts.dat", "rb");
    Account acc;
    
    if (!file) {
        printf("No accounts found!\n");
        return;
    }
    
    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Account Holder: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            fclose(file);
            return;
        }
    }
    
    printf("Account not found!\n");
    fclose(file);
}

// Main function
int main() {
    int choice;
    
    do {
        printf("\nBanking System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    
    return 0;
}
