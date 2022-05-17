#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GROUPS 30
#define MIN_STUDENTS 3
#define MAX_STUDENTS 35
#define MAX_CAND 4

// A simple function to check if a string is in an array of strings
int str_in_arr(char *arr, int width, int chr_size, char *str) {
    int success = 0;
    for (int i = 0; i < width; i++) {
        if ((strcmp(arr+(i*chr_size), str)) == 0) {
            success = 1;
            break;
        }
    }
    return success;
}

int main() {
    // List of all tutor groups
    char TUTOR_GROUPS[MAX_GROUPS][4] = {"7a","7b","7c","7d","7e","7f",
                                        "8a","8b","8c","8d","8e","8f",
                                        "9a","9b","9c","9d","9e","9f",
                                        "10a","10b","10c","10d","10e","10f",
                                        "11a","11b","11c","11d","11e","11f"
                                    };

    // Variable declarations
    char check[MAX_GROUPS][4];
    int index = 0;

    char cand_names[MAX_CAND][20];
    char tutor_name[4];
    int student_no;
    int cand_no;

    int counter;
    int tie_num;
    int no_votes[MAX_CAND];
    int no_abstaining;
    char vote_IDs[MAX_STUDENTS][6];
    int student_counter;
    char id[3];
    char voteID[6];
    int voting_check;
    int vote;

    int highest;
    int tie_list[MAX_CAND];
    int tie_index;
    char winners[30];

    double percentage;
    char temp[MAX_CAND][20];

    for (int count = 0; count < MAX_GROUPS; count++) {

        printf("Please enter a tutor group name: ");
        scanf("%s", &tutor_name);
        while (!(str_in_arr(&TUTOR_GROUPS[0][0], MAX_GROUPS, 4, tutor_name)) || (str_in_arr(&check[0][0], MAX_GROUPS, 4, tutor_name))) {
            if (str_in_arr(&check[0][0], MAX_GROUPS, 4, tutor_name)) {
                printf("This tutor group has already voted. Please enter a different tutor group: ");
                scanf("%s", &tutor_name);
            } else if (!(str_in_arr(&TUTOR_GROUPS[0][0], MAX_GROUPS, 4, tutor_name))) {
                printf("Please enter a valid tutor group name: ");
                scanf("%s", &tutor_name);
            }
        }
        strcpy(check[index], tutor_name);
        index++;

        printf("Please enter the number of students in the tutor group: ");
        scanf("%d", &student_no);
        while (student_no < MIN_STUDENTS || student_no > MAX_STUDENTS) {
            printf("Please enter a number between %d and %d: ", MIN_STUDENTS, MAX_STUDENTS);
            scanf("%d", &student_no);
        }

        printf("Please enter the number of candidates: ");
        scanf("%d", &cand_no);
        while (cand_no < 1 || cand_no > 4) {
            printf("Please enter the number of candidates: ");
            scanf("%d", &cand_no);
        }

        for (int i = 0;  i < cand_no; i++) {
            printf("Please enter candidate name: ");
            char name[20];
            scanf("%s", &name);
            strcpy(cand_names[i], name);
        }

        counter = 0;
        tie_num = 1;  // These variables are used for handling the event of a tie and terminating the loop
        while (tie_num > counter) {
            memset(no_votes, 0, sizeof(no_votes));  // Reset all vote counts
            no_abstaining = 0;
            student_counter = 0;

            // Allow each student to vote
            while (student_counter < student_no) {
                printf("\nPlease enter the last two digits of your vote number. For example, 05.\nEnter the last two digits of your vote number here: ");
                scanf("%s", &id);
                strcpy(voteID, tutor_name);
                strcat(voteID, id);

                if (!(str_in_arr(&vote_IDs[0][0], MAX_STUDENTS, 6, voteID))) {
                    printf("Your voting ID is %s\n", voteID);
                    strcpy(vote_IDs[student_counter], voteID);

                    printf("Are you voting? Type '1' if so, or '0' to abstain: ");
                    scanf("%d", &voting_check);

                    if (voting_check) {
                        for (int i = 0; i < cand_no; i++) {
                            printf("%d. %s\n", i+1, cand_names[i]);
                        }

                        printf("Please enter the index of the candidate you would like to vote for from the list above: ");
                        scanf("%d", &vote);
                        while (!((-1 < vote-1) && (vote-1 < cand_no))) {
                            printf("Please enter the candidate index from the list above: ");
                            scanf("%d", &vote);
                        }
                        no_votes[vote-1]++;

                    } else {
                        no_abstaining++;
                    }
                    student_counter++;

                } else {
                    printf("\nSorry, you have already voted. You will not be allowed to vote again.\n");
                }
            }

            // Get the winner of the elections
            // If there is a tie then the tie_num variable is incremented
            highest = -1;
            memset(tie_list, -1, sizeof(tie_list));
            tie_index = 0;
            for (int i = 0; i < cand_no; i++) {
                if (no_votes[i] > highest) {
                    for (int j = 0; j < 4; j++) {
                        tie_list[i] = -1;
                    }
                    tie_index = 0;
                    tie_list[tie_index] = i;
                    highest = no_votes[i];
                    strcpy(winners, cand_names[i]);
                    tie_num = 1;
                } else if (no_votes[i] == highest){
                    snprintf(winners, 30, "%s and %s", winners, cand_names[i]);
                    printf("%s\n", winners);
                    tie_index++;
                    tie_num++;
                    counter = 1;
                    tie_list[tie_index] = i;
                }
            }

            // Output all the details of the election
            printf("\nTutor Group Name:\n");
            printf("=================\n");
            printf("%s\n", tutor_name);
            printf("Number of votes for candidates:\n");
            printf("==============================\n");
            for (int i = 0; i < cand_no; i++) {
                percentage = ((double)no_votes[i]/(double)(student_no - no_abstaining)) *100;
                printf("%d. %s - %d - %f%% of students voted.\n", i+1, cand_names[i], no_votes[i], percentage);
            }
            printf("\nNumber of students who voted:\n");
            printf("=============================\n");
            printf("%d\n", student_no - no_abstaining);
            printf("Number of abstaining students:\n");
            printf("==============================\n");
            printf("%d\n", no_abstaining);

            // Condition to reset all voting variables for a re-election if there is a tie
            if (tie_num > 1) {
                printf("\nThere has been a tie between %s. The election will be run again.\n", winners);

                memcpy(&temp[0][0], &cand_names[0][0], sizeof(cand_names));
                for (int i = 0; i < tie_num; i++) {
                    strcpy(cand_names[i], temp[tie_list[i]]);
                }
                cand_no = tie_num;
                memset(vote_IDs, '\0', sizeof(vote_IDs));
                printf("\n====================================================\n");
                printf("Re-election will now commence against tied candidates\n");
                printf("====================================================\n");
            } else {
                printf("\nWinner of election:\n");
                printf("===================\n");
                printf("%s\n", winners); 
                tie_num = 0;
            }
            printf("\n====================================================================\n\n");
        }
    }

    return 0;
}