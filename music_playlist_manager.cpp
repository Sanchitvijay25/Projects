#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

struct Node {
    char song[100];
    Node *next;
    Node *prev;
};

Node *top = nullptr;
Node *temp = nullptr;
Node *top1 = nullptr;
string playlistFileName; // Global variable to hold the playlist file name

void tofile(const char a[]) {
    ofstream f1(playlistFileName.c_str(), ios::out | ios::app);
    f1 << a << endl;
}

void add_node(Node *first) {
    char a[100];
    while (first->next != nullptr) {
        first = first->next;
    }
    first->next = new Node;
    first->next->prev = first;
    first = first->next;
    cout << "\nEnter Song name: ";
    cin.ignore(); // Clear input buffer
    cin.getline(a, 100);
    strcpy(first->song, a);
    tofile(a);
    first->next = nullptr;
}

void add_node_file(Node *first, const string &a) {
    while (first->next != nullptr) {
        first = first->next;
    }
    first->next = new Node;
    first->next->prev = first;
    first = first->next;
    strcpy(first->song, a.c_str());
    first->next = nullptr;
}

void delete_file(const char a[]) {
    ifstream f1(playlistFileName.c_str());
    ofstream f2("temp.txt");
    string line;
    bool found = false;

    while (getline(f1, line)) {
        if (strcmp(a, line.c_str()) != 0) {
            f2 << line << endl;
        } else {
            found = true;
        }
    }

    f1.close();
    f2.close();

    remove(playlistFileName.c_str());
    rename("temp.txt", playlistFileName.c_str());

    if (!found) {
        cout << "There is no song with the name you entered." << endl;
    } else {
        cout << "Song has been deleted." << endl;
    }
}

void del_node(Node *first, const char a[]) {
    while (first->next != nullptr) {
        if (strcmp(first->song, a) == 0) {
            Node *temp = first;
            first->prev->next = first->next;
            if (first->next != nullptr) {
                first->next->prev = first->prev;
            }
            delete temp;
            delete_file(a);
            cout << "Deleted song: " << a << endl;
            return;
        }
        first = first->next;
    }
    if (strcmp(first->song, a) == 0) {
        Node *temp = first;
        first->prev->next = nullptr;
        delete temp;
        delete_file(a);
        cout << "Deleted song: " << a << endl;
    } else {
        cout << "Song not found." << endl;
    }
}

void printlist(Node *first) {
    cout << "\nPlaylist Name: ";
    while (first->next != nullptr) {
        cout << first->song << endl;
        first = first->next;
    }
    cout << first->song << endl;
}

void count_nodes(Node *first) {
    int count = 0;
    while (first->next != nullptr) {
        first = first->next;
        count++;
    }
    count++;
    cout << "\nTotal songs: " << count << endl;
}

Node* del_pos(Node *pointer, int pos) {
    Node *prev1 = nullptr;
    Node *temp = nullptr;
    int i = 1;

    if (pos == 1) {
        temp = pointer;
        delete_file(temp->song);
        pointer = pointer->next;
        pointer->prev = nullptr;
        delete temp;
        cout << "\nThe list is updated. Use the display function to check.\n";
        return pointer;
    }

    Node *current = pointer;
    while (i < pos && current != nullptr) {
        prev1 = current;
        current = current->next;
        i++;
    }

    if (current == nullptr) {
        cout << "Position out of range." << endl;
        return pointer;
    }

    if (current->next == nullptr) {
        prev1->next = nullptr;
    } else {
        prev1->next = current->next;
        current->next->prev = prev1;
    }

    delete_file(current->song);
    delete current;

    cout << "\nThe list is updated. Use the display function to check.\n";
    return pointer;
}

void search1(Node *first) {
    char song[100];
    cout << "\nEnter song to be searched: ";
    cin.ignore(); // Clear input buffer
    cin.getline(song, 100);
    bool found = false;

    while (first != nullptr) {
        if (strcmp(first->song, song) == 0) {
            cout << "\n#Song Found" << endl;
            found = true;
            break;
        } else {
            first = first->next;
        }
    }
    if (!found) {
        cout << "\n#Song Not found" << endl;
    }
}

void create() {
    top = nullptr;
}

void push(const char data[]) {
    if (top == nullptr) {
        top = new Node;
        top->next = nullptr;
        strcpy(top->song, data);
    } else if (strcmp(top->song, data) != 0) {
        temp = new Node;
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

void display() {
    top1 = top;
    if (top1 == nullptr) {
        cout << "\n#NO recently played tracks.\n";
        return;
    }
    cout << "\n#Recently played tracks-\n";
    while (top1 != nullptr) {
        cout << top1->song << endl;
        top1 = top1->next;
    }
}

void play(Node *first) {
    char song[100];
    printlist(first);
    cout << "\nChoose song you wish to play: ";
    cin.ignore(); // Clear input buffer
    cin.getline(song, 100);
    bool found = false;

    while (first != nullptr) {
        if (strcmp(first->song, song) == 0) {
            cout << "\n=> Now Playing......" << song << endl;
            push(song);
            found = true;
            break;
        } else {
            first = first->next;
        }
    }
    if (!found) {
        cout << "\n#Song Not found" << endl;
    }
}

void recent() {
    display();
}

void topelement() {
    top1 = top;
    if (top1 == nullptr) {
        cout << "\n#NO last played tracks.\n";
        return;
    }
    cout << "\n=> Last Played Song - " << top->song << endl;
}

void sort(Node *&pointer) {
    Node *e = nullptr;
    bool swapped;

    do {
        swapped = false;
        Node *a = pointer;

        while (a->next != e) {
            Node *b = a->next;
            if (strcmp(a->song, b->song) > 0) {
                if (a == pointer) {
                    pointer = b;
                    a->next = b->next;
                    b->next = a;
                } else {
                    Node *prev_a = a->prev;
                    prev_a->next = b;
                    a->next = b->next;
                    b->next = a;
                    b->prev = prev_a;
                    a->prev = b;
                }
                swapped = true;
            }
            a = a->next;
        }
        e = a;
    } while (swapped);
}

void addplaylist(Node *start) {
    ifstream f1(playlistFileName.c_str());
    string line;

    while (getline(f1, line)) {
        add_node_file(start, line);
    }
    cout << "Playlist Added" << endl;
}

void del_search(Node *start) {
    char song[100];
    printlist(start);
    cout << "\nChoose song you wish to delete: ";
    cin.ignore(); // Clear input buffer
    cin.getline(song, 100);
    bool found = false;

    while (start != nullptr) {
        if (strcmp(start->song, song) == 0) {
            cout << "\n#Song Found" << endl;
            delete_file(start->song);
            if (start->prev != nullptr) start->prev->next = start->next;
            if (start->next != nullptr) start->next->prev = start->prev;
            delete start;
            found = true;
            break;
        } else {
            start = start->next;
        }
    }
    if (!found) {
        cout << "\n#Song Not found" << endl;
    }
}

void deletemenu(Node *start) {
    int choice;
    cout << "Which type of delete do you want?\n1. By Search\n2. By Position" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            del_search(start);
            break;
        case 2:
            int pos;
            cout << "Enter the position of the song to be deleted: ";
            cin >> pos;
            start = del_pos(start, pos);
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}

void clear_playlist(Node *start) {
    Node *current = start->next;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    start->next = nullptr;
    ofstream clearFile(playlistFileName.c_str(), ofstream::out | ofstream::trunc);
    cout << "\nPlaylist cleared successfully." << endl;
}

void add_two_playlists(Node *start1, Node *start2) {
    Node *current = start2->next;
    while (current != nullptr) {
        add_node_file(start1, current->song);
        current = current->next;
    }
    cout << "\nTwo playlists merged successfully." << endl;
}

void shuffle_playlist(Node *start) {
    // Count number of songs
    int count = 0;
    Node *current = start->next;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // Convert linked list to array for shuffling
    string *songs = new string[count];
    current = start->next;
    int i = 0;
    while (current != nullptr) {
        songs[i] = current->song;
        current = current->next;
        i++;
    }

    // Perform Fisher-Yates shuffle
    srand(time(0));
    for (int j = count - 1; j > 0; j--) {
        int k = rand() % (j + 1);
        swap(songs[j], songs[k]);
    }

    // Update linked list with shuffled array and file
    current = start->next;
    i = 0;
    ofstream f1(playlistFileName.c_str(), ios::out | ios::trunc);
    while (current != nullptr) {
        strcpy(current->song, songs[i].c_str());
        f1 << songs[i] << endl;
        current = current->next;
        i++;
    }

    delete[] songs;
    cout << "\nPlaylist shuffled successfully." << endl;
}

int main() {
    int choice;
    Node *start = new Node;
    cout << "\t\t\t**WELCOME**" << endl;
    cout << "\n**Please use '_' for space." << endl;
    cout << "\nEnter your playlist name: ";
    cin.ignore();
    cin.getline(start->song, 100);
    start->next = nullptr;
    start->prev = nullptr;

    char fileChoice;
    cout << "\nDo you want to add to an existing playlist file? (y/n): ";
    cin >> fileChoice;

    if (fileChoice == 'y' || fileChoice == 'Y') {
        cout << "\nEnter the name of the existing playlist file (with .txt extension): ";
        cin.ignore();
        getline(cin, playlistFileName);
    } else {
        cout << "\nEnter the name for the new playlist file (without extension): ";
        cin.ignore();
        getline(cin, playlistFileName);
        playlistFileName += ".txt"; // Append .txt extension to the file name
    }

    create();

    do {
        cout << "\n1. Add New Song\n2. Delete Song\n3. Display Entered Playlist\n4. Total Songs\n5. Search Song\n6. Play Song\n7. Recently Played List\n8. Last Played\n9. Sorted playlist\n10. Add From File\n11. Clear Playlist\n12. Add Two Playlists\n13. Shuffle Playlist\n14. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_node(start);
                break;
            case 2:
                char delSong[100];
                cout << "\nEnter song name to delete: ";
                cin.ignore(); // Clear input buffer
                cin.getline(delSong, 100);
                del_node(start, delSong);
                break;
            case 3:
                printlist(start);
                break;
            case 4:
                count_nodes(start);
                break;
            case 5:
                search1(start);
                break;
            case 6:
                play(start);
                break;
            case 7:
                recent();
                break;
            case 8:
                topelement();
                break;
            case 9:
                sort(start->next);
                printlist(start);
                break;
            case 10:
                addplaylist(start);
                break;
            case 11:
                clear_playlist(start);
                break;
            case 12: {
                Node *start2 = new Node;
                cout << "\nEnter your second playlist name: ";
                cin.ignore();
                cin.getline(start2->song, 100);
                start2->next = nullptr;
                start2->prev = nullptr;
                addplaylist(start2);
                add_two_playlists(start, start2);
                break;
            }
            case 13:
                shuffle_playlist(start);
                break;
            case 14:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 14);

    return 0;
}
