#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define SPECIAL "!@#$%^&*"
/* ============ FUNCTION PROTOTYPES ============ */
void clearBuffer(void);
int checkPassword(char pwd[]);
void encryptPassword(char pwd[], char enc[]);
void saveToHistory(char pwd[]);
void showHistory(void);

/* ============ GLOBAL VARIABLES ============ */
char history[10][MAX];
int historyCount = 0;

/* ============ STUDENT 1: MAIN PROGRAM ============ */
void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char password[MAX];
    char encrypted[MAX];
    char choice;
    int isStrong = 0;
    
    printf("\n+-----------------------------------+\n");
    printf("¦    PASSWORD SECURITY SYSTEM        ¦\n");
    printf("¦         Group Project - 4          ¦\n");
    printf("+------------------------------------+\n");
    
    /* STUDENT 2: Loop until strong password */
    while(isStrong == 0) {
        printf("\n?? Enter password: ");
        fgets(password, MAX, stdin);
        password[strcspn(password, "\n")] = '\0';
        
        /* Check password strength */
        isStrong = checkPassword(password);
        
        /* If weak password - ask to rewrite */
        if(isStrong == 0) {
            printf("\n? WEAK PASSWORD! Please try again.\n");
            printf("------------------------------------\n");
        }
    }
    
    /* STUDENT 4: Save to history */
    saveToHistory(password);
    
    /* STUDENT 3: Ask for encryption */
    printf("\n?? Do you want to encrypt this password? (y/n): ");
    scanf("%c", &choice);
    clearBuffer();
    
    /* STUDENT 3: Encrypt if user says yes */
    if(choice == 'y' || choice == 'Y') {
        encryptPassword(password, encrypted);
        printf("\n------------------------------------\n");
        printf("? ENCRYPTION COMPLETE!\n");
        printf("------------------------------------\n");
        printf("Original : %s\n", password);
        printf("Encrypted: %s\n", encrypted);
        printf("------------------------------------\n");
        
        /* STUDENT 4: Save encrypted to history */
        saveToHistory(encrypted);
    } else {
        printf("\n? Password saved without encryption.\n");
    }
    
    /* STUDENT 4: Show history */
    showHistory();
    
    printf("\n?? Press Enter to exit...");
    getchar();
    return 0;
}

/* ============ STUDENT 2: PASSWORD CHECKER ============ */
int checkPassword(char pwd[]) {
    int len = strlen(pwd);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int i;
    int score = 0;
    int isStrong = 0;
    
    printf("\n------------------------------------\n");
    printf("     PASSWORD STRENGTH CHECKER\n");
    printf("------------------------------------\n");
    
    /* Check each character */
    for(i = 0; i < len; i++) {
        if(isupper(pwd[i])) hasUpper = 1;
        else if(islower(pwd[i])) hasLower = 1;
        else if(isdigit(pwd[i])) hasDigit = 1;
        else if(strchr(SPECIAL, pwd[i]) != NULL) hasSpecial = 1;
    }
    
    /* Display results */
    printf("Password    : %s\n", pwd);
    printf("Length      : %d characters ", len);
    if(len >= 8) printf("?\n"); else printf("? (need 8+)\n");
    
    printf("Uppercase   : %s ", hasUpper ? "Yes" : "No");
    if(hasUpper) printf("?\n"); else printf("?\n");
    
    printf("Lowercase   : %s ", hasLower ? "Yes" : "No");
    if(hasLower) printf("?\n"); else printf("?\n");
    
    printf("Numbers     : %s ", hasDigit ? "Yes" : "No");
    if(hasDigit) printf("?\n"); else printf("?\n");
    
    printf("Special     : %s ", hasSpecial ? "Yes" : "No");
    if(hasSpecial) printf("?\n"); else printf("?\n");
    
    /* Calculate score */
    if(len >= 8) score += 2;
    if(hasUpper) score += 2;
    if(hasLower) score += 2;
    if(hasDigit) score += 2;
    if(hasSpecial) score += 3;
    
    printf("------------------------------------\n");
    printf("Score       : %d/11\n", score);
    
    /* Final verdict */
    if(len >= 8 && hasUpper && hasLower && hasDigit && hasSpecial) {
        printf("STATUS      : ? STRONG PASSWORD!\n");
        isStrong = 1;
    } else {
        printf("STATUS      : ? WEAK PASSWORD!\n");
        printf("\n? MISSING REQUIREMENTS:\n");
        if(len < 8) printf("   • 8+ characters (currently %d)\n", len);
        if(!hasUpper) printf("   • Uppercase letter\n");
        if(!hasLower) printf("   • Lowercase letter\n");
        if(!hasDigit) printf("   • Number\n");
        if(!hasSpecial) printf("   • Special character (!@#$%%^&*)\n");
        isStrong = 0;
    }
    printf("------------------------------------\n");
    
    return isStrong;
}

/* ============ STUDENT 3: ENCRYPTION MODULE ============ */
void encryptPassword(char pwd[], char enc[]) {
    int i;
    int shift = 3;  /* Caesar cipher shift */
    
    for(i = 0; pwd[i] != '\0'; i++) {
        char c = pwd[i];
        
        /* Encrypt uppercase */
        if(c >= 'A' && c <= 'Z') {
            enc[i] = ((c - 'A' + shift) % 26) + 'A';
        }
        /* Encrypt lowercase */
        else if(c >= 'a' && c <= 'z') {
            enc[i] = ((c - 'a' + shift) % 26) + 'a';
        }
        /* Encrypt numbers */
        else if(c >= '0' && c <= '9') {
            enc[i] = ((c - '0' + shift) % 10) + '0';
        }
        /* Keep special characters */
        else {
            enc[i] = c;
        }
    }
    enc[i] = '\0';
}
/* ============ STUDENT 4: HISTORY MODULE ============ */
void saveToHistory(char pwd[]) {
    if(historyCount < 10) {
        strcpy(history[historyCount], pwd);
        historyCount++;
        printf("\n?? Password saved to history!\n");
    } else {
        printf("\n?? History full! Cannot save more passwords.\n");
    }
}
void showHistory(void) {
    int i;
    printf("\n------------------------------------\n");
    printf("        PASSWORD HISTORY\n");
    printf("------------------------------------\n");
    if(historyCount == 0) {
        printf("   No passwords saved yet.\n");
    } else {
        for(i = 0; i < historyCount; i++) {
            printf("   %d. %s\n", i+1, history[i]);
        }
    }
    printf("------------------------------------\n");
}
