#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int action = 0;
int *p_action = &action;

bool app_open = true;

struct songs {
    char name[100];
    char artist[100];
    int year_released;
    struct songs *next;
};

struct songs *playlist = NULL;

struct songs *add_to_playlist(struct songs *list, char name[], char artist[], int year_released) {
 struct songs *new_node;
    new_node = malloc(sizeof(struct songs));
    if (new_node == NULL) {
        printf("Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    strcpy(new_node->artist, artist);
    new_node->year_released = year_released;
    new_node->next = list;
    return new_node;
}

// struct songs *search_playlist(struct songs *list, char target[]) {
//     struct songs *current;
//
//     for (current = list; current != NULL; current = current->next) {
//         if (current->name == target) {
//             return current;
//         }
//         else {
//             return NULL;
//         }
//     }
// }

struct songs *remove_from_playlist(struct songs *list, char name[]) {
    struct songs *current, *previous;
    char temp_target[100] = "";
    strcpy(temp_target, name);
    char temp_possible_target[100] = "";
    for (int x = 0; x < sizeof(temp_target); x++) {
        temp_target[x] = toupper(temp_target[x]);
    }
    for (current = list, previous = NULL;
     current != NULL;
     previous = current, current = current->next)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
                list = current->next;
            else
                previous->next = current->next;

            free(current);
            return list;
        }
    }

    return list;
}

void print_playlist(struct songs *playlist)
{
    struct songs *current = playlist;
        while (current != NULL) {
            printf(" %s - %s (%d)\n", current->name, current->artist, current->year_released);

            current = current->next;
        }
}

void ready_actions() {
    char input[3] = "0";
    printf("What would you like to do?\n");
    printf("Press 1 to Add a Song\n");
    printf("Press 2 to Remove a Song\n");
    printf("Press 3 to Print Playlist\n");
    fgets(input, 3, stdin);
    *p_action = input[0] - '0';
}

int main() {
    while (app_open) {
        ready_actions();
        if (*p_action == 1) {
            char new_song_name[100] = "";
            printf("Enter song name: ");
            fgets(new_song_name, 100, stdin);
            char new_artist[100] = "";
            printf("Enter artist: ");
            fgets(new_artist, 100, stdin);
            char new_year_released[6] = "";
            printf("Enter year released: ");
            fgets(new_year_released, sizeof(new_year_released), stdin);
            int new_year_released_index = atoi(new_year_released);
            playlist = add_to_playlist(playlist, new_song_name, new_artist, new_year_released_index);
        }
        else if (*p_action == 2) {
            char target_song[100] = "";
            printf("What song would you like to remove?");
            print_playlist(playlist);
            fgets(target_song, 100, stdin);
            playlist = remove_from_playlist(playlist,target_song);
        }
        else if (*p_action == 3) {
            printf("Welcome to your Playlist!\n");
            print_playlist(playlist);
        }
        else {
            app_open = false;
        }
    }
    return 0;
}