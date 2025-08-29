#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//sanehaKumari_16401012022
#define MAX 1000

void createAndWriteFile(char *filename) {
    FILE *file;
    char content[MAX];

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    getchar(); // Clear buffer
    printf("Enter content to write into the file:\n");
    fgets(content, MAX, stdin);
    fprintf(file, "%s", content);

    fclose(file);
    printf("File created and content written successfully.\n");
}

void readFile(char *filename) {
    FILE *file;
    char ch;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading! File might not exist.\n");
        return;
    }

    printf("\nContents of the file:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void appendToFile(char *filename) {
    FILE *file;
    char content[MAX];

    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file for appending! File might not exist.\n");
        return;
    }

    getchar(); // Clear buffer
    printf("Enter content to append into the file:\n");
    fgets(content, MAX, stdin);
    fprintf(file, "%s", content);

    fclose(file);
    printf("Content appended successfully.\n");
}

void deleteFile(char *filename) {
    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
        filename[0] = '\0';  // Clear the filename
    } else {
        printf("Unable to delete the file. It may not exist.\n");
    }
}

int countOccurrences(const char *str, const char *word) {
    int count = 0;
    const char *temp = str;

    while ((temp = strstr(temp, word)) != NULL) {
        count++;
        temp += strlen(word);
    }

    return count;
}

void searchInFile(char *filename) {
    FILE *file;
    char fileContent[MAX * 10];
    char searchWord[100];

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for searching! File might not exist.\n");
        return;
    }

    fread(fileContent, sizeof(char), sizeof(fileContent), file);
    fclose(file);

    getchar(); // Clear buffer
    printf("Enter the word or phrase to search: ");
    fgets(searchWord, sizeof(searchWord), stdin);
    searchWord[strcspn(searchWord, "\n")] = '\0'; // Remove newline

    int occurrences = countOccurrences(fileContent, searchWord);
    printf("'%s' occurred %d times in the file.\n", searchWord, occurrences);
}

int main() {
    char filename[50];
    int choice;

    printf("Enter the filename: ");
    scanf("%s", filename);

    do {
        printf("\n--- File Handling Menu ---\n");
        printf("1. Create and Write to File\n");
        printf("2. Read File\n");
        printf("3. Append to File\n");
        printf("4. Delete File\n");
        printf("5. Search in File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (filename[0] == '\0' && choice != 1 && choice != 6) {
            printf("No valid file to operate on. Please restart the program.\n");
            continue;
        }

        switch (choice) {
            case 1:
                createAndWriteFile(filename);
                break;
            case 2:
                readFile(filename);
                break;
            case 3:
                appendToFile(filename);
                break;
            case 4:
                deleteFile(filename);
                printf("Do you want to continue? (y/n): ");
                char ch;
                getchar(); // clear buffer
                scanf("%c", &ch);
                if (ch == 'n' || ch == 'N') {
                    choice = 6; // force exit
                }
                break;
            case 5:
                searchInFile(filename);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
