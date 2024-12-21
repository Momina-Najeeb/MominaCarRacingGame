#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;


class User {
private:
    string username;
    string password;

public:
    bool signup(string uname, string pass) {
        ofstream file("user.txt", ios::app);
        if(file.is_open()) {
            file << uname << " " << pass << " 0 0"<<endl; // username, password, highscore, money
            file.close();
            return true;
        }
        return false;
    }

    bool login(string uname, string pass) {
        ifstream file("user.txt");
        if(!file.is_open()) {
            cout << "Unable to open file" << endl;
            return false;
        }
        string u, p;
        while (file >> u >> p) {
            if(u == uname && p == pass) {
                username = uname;
                password = pass;
                file.close();
                return true;
            }
        }
        cout << "Error: User not found or incorrect password!" << endl;
        file.close();
        return false;
    }

    string getUsername() {
    return username;
    }
};


// Car class for cars attributes
class Car {
public:
    string name;
    int speed;
    int power;

    Car(string carName, int carSpeed, int carPower){
        name=carName;
        speed=carSpeed;
        power=carPower;
    }
       
    void display() const {
        cout << "Car Name: " << name << ", Speed: " << speed << " km/h, Power: " << power << " hp" << endl;
    }
};


// Node class for the linked list
class Node {
public:
    Car car;
    Node* next;

    Node(Car carData) : car(carData), next(NULL) {}
};


// Linked list class for storing cars and displaying them
class CarsLinkedList {
private:
    Node* head;

public:
    CarsLinkedList() : head(NULL) {}

    // Insert function for adding cars
    void insert(Car carData) {
        Node* newNode = new Node(carData);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void select(int score) {
        CarsLinkedList carList;
        int carChoice;

        // Displaying cars based on high scores of player
        if (score > 50) {
            cout << "Elite Cars for High Scorers:" << endl;
            carList.insert(Car("Bugatti Veyron Super Sport", 410, 1200));
            carList.insert(Car("Koenigsegg Agera RS", 450, 1160));
            carList.insert(Car("Ferrari LaFerrari", 350, 950));
        } else if (score > 20) {
            cout << "Mid-tier Cars for Moderate Scorers:" << endl;
            carList.insert(Car("Porsche 911 Turbo S", 330, 640));
            carList.insert(Car("Nissan GT-R", 315, 565));
            carList.insert(Car("Mercedes-AMG GT", 318, 523));
        } else {
            cout << "Basic Cars for Lower Scorers:" << endl;
            carList.insert(Car("Chevrolet Camaro SS", 250, 455));
            carList.insert(Car("Ford Mustang GT", 250, 450));
            carList.insert(Car("Toyota Supra", 270, 335));
        }

        // Display car options
        cout << "Car List:" << endl;
        carList.display();
        cout << "Choose your car for the game (Enter 1, 2, or 3): ";
        cin >> carChoice;

        // Validate and make the selected car available for gameplay
        Node* temp = carList.head;
        for (int i = 1; i < carChoice; i++) {
            if (temp != NULL) {
                temp = temp->next;
            }
        }

        if (temp != NULL) {
            cout << "You have selected the " << temp->car.name << endl;
        } else {
            cout << "Invalid choice, please select a valid car!" << endl;
        }
    }

    // Display function
    void display() const {
        if (head == NULL) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* temp = head;
        int index = 1;
        while (temp != NULL) {
            cout << index << ". ";
            temp->car.display();
            temp = temp->next;
            index++;
        }
    }

    // Destructor to free memory
    ~CarsLinkedList() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


void updateUser(string uname, int newScore, int money) {
    ifstream inFile("user.txt");
    if(!inFile) {
        cout << "Error opening user.txt file!" << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if(!outFile) {
        cout << "Error opening temp.txt file!" << endl;
        return;
    }

    string u, p;
    int score, cash;

    while (inFile >> u >> p >> score >> cash) {
        if(u == uname) {
            score = max(score, newScore);
            cash += money;
        }
        outFile << u << " " << p << " " << score << " " << cash << ""<<endl;
    }

    inFile.close();
    outFile.close();
    remove("user.txt");
    rename("temp.txt", "user.txt");
}

// Implementing BST to sort scores
struct PlayerNode {
    string username;
    int score;
    PlayerNode* left;
    PlayerNode* right;

    PlayerNode(string u, int s) : username(u), score(s), left(NULL), right(NULL) {}
};

PlayerNode* insertPlayerBST(PlayerNode* root, const string& username, int score) {
    if(root == NULL) {
        return new PlayerNode(username, score);
    }

    if(score < root->score) {
        root->left = insertPlayerBST(root->left, username, score);
    } else{
        root->right = insertPlayerBST(root->right, username, score);
    }
    return root;
}

void inorderPlayerBST(PlayerNode* root) {
    if(root != NULL) {
        inorderPlayerBST(root->left);
        cout << root->username << " | Score: " << root->score << ""<<endl;
        inorderPlayerBST(root->right);
    }
}

class Player {
public:
    string username;
    string password;
    int score;
    int money;
};

// Function to read players from file into an array
int readPlayersFromFile(Player players[], int maxPlayers) {
    ifstream file("user.txt");
    if(!file) {
        cout << "Unable to open file!" << endl;
        return 0;
    }

    string u, p;
    int score, money;
    int count = 0;

    while (file >> u >> p >> score >> money && count < maxPlayers) {
        players[count].username = u;
        players[count].password = p;
        players[count].score = score;
        players[count].money = money;
        count++;
    }

    file.close();
    return count;
}

// Merge sort function for sorting players in a leaderboard based on money
void Merge(Player arr[], int left, int mid, int right) {
    int leftsize = mid - left + 1;
    int rightsize = right - mid;

    Player leftarray[leftsize];
    Player rightarray[rightsize];

    for (int i = 0; i < leftsize; i++) {
        leftarray[i] = arr[left + i];
    }
    for (int j = 0; j < rightsize; j++) {
        rightarray[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < leftsize && j < rightsize) {
        if(leftarray[i].money > rightarray[j].money) { 
            arr[k] = leftarray[i];
            i++;
        } else{
            arr[k] = rightarray[j];
            j++;
        }
        k++;
    }

    while (i < leftsize) {
        arr[k] = leftarray[i];
        i++;
        k++;
    }
    while (j < rightsize) {
        arr[k] = rightarray[j];
        j++;
        k++;
    }
}

// Custom MergeSort for Player array
void MergeSort(Player arr[], int left, int right) {
    if(left < right) {
    int mid = left + (right - left) / 2;

    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);

    Merge(arr, left, mid, right);
    }
}

// Display Leaderboard based on Money
void displayMoneyLeaderboard(Player players[], int count) {
    MergeSort(players, 0, count - 1);

    cout << "============ LEADERBOARD (MONEY) ============"<<endl;
    cout << left << setw(20) << "Username" << setw(10) << "Money" << endl; 
    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << players[i].username << "$" << players[i].money << endl;
    }
}


void displayScoreLeaderboard(PlayerNode* root) {
    if(root != NULL) {
        displayScoreLeaderboard(root->right); // Right subtree for higher scores
        cout << left << setw(20) << root->username << setw(10) << root->score << endl;
        displayScoreLeaderboard(root->left);  // Left subtree for lower scores
    }
}

void gamePlay(string username) {
    srand(time(0));
    const int TRACK_LENGTH = 20;
    char track[TRACK_LENGTH];

    for (int i = 0; i < TRACK_LENGTH; i++) {
        track[i] = ' ';
    }

    int userPosition = 0;
    int computerPosition = 0;
    int obstaclePosition = rand() % TRACK_LENGTH;

    int score = 0;
    int money = 0;

    while (true) {
        system("cls"); // Change 'clear' to 'cls' for Windows

        track[userPosition] = 'u';
        track[computerPosition] = 'c';
        track[obstaclePosition] = 'x';

        for (int i = 0; i < TRACK_LENGTH; i++) {
            cout << track[i];
        }
        cout << endl;

        track[userPosition] = ' ';
        track[computerPosition] = ' ';
        track[obstaclePosition] = ' ';

        cout << "Press 'd' to move forward: ";
        char input;
        cin >> input;

        if (input == 'd') {
            userPosition++;
        } else {
            cout << "Invalid input!" << endl;
            continue;
        }

        computerPosition += rand() % 2;
        obstaclePosition = (obstaclePosition + 1) % TRACK_LENGTH;

        if (userPosition == TRACK_LENGTH - 1) {
            cout << "You win!" << endl;
            score += 10;
            money += 20;
            break;
        }

        if (computerPosition == TRACK_LENGTH - 1) {
            cout << "Computer wins!" << endl;
            break;
        }

        if (userPosition == obstaclePosition) {
            cout << "Game over! You hit an obstacle." << endl;
            break;
        }

        if (userPosition > obstaclePosition) {
            score += 2;
            money += 5;
        }
    }

    cout << "Your final score: " << score << endl;
    cout << "Your total money: $" << money << endl;
    updateUser(username, score, money);
}


//MAIN FUNTION
int main() {

        cout<<endl;
    cout << "=============================   Welcome to the Car Racing Game!   =============================" << endl;
    cout<<endl;
    cout << "Embark on a high-speed adventure as you race against the computer to claim victory and cross the finish line first."<<endl;
    cout << "But it's not just about speed. Master your reflexes to dodge tricky obstacles that stand in your way!" << endl;

    User user;
    string username, password;

    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Exit" << endl;
    cout<<"Enter your choice here: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (!user.login(username, password)) {
            cout << "Login failed. Exiting game." << endl;
            return 0;
        }
    }
    else if (choice == 2) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (!user.signup(username, password)) {
            cout << "Signup failed. Exiting game." << endl;
            return 0;
        }
        cout << "Signup successful! You can now log in." << endl;
        cout << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (!user.login(username, password)) {
            cout << "Login failed. Exiting game." << endl;
            return 0;
        }
    }
    else {
        cout<<endl;
        cout << "Exiting game." << endl;
        cout << "Have a nice day!" << endl;
        cout << "We hope to see you soon again!" << endl;
        return 0;
    }

    cout << endl;
    cout << "Welcome back " << user.getUsername() << "!" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Play" << endl;
    cout << "2. How to play" << endl;
    cout << "3. Leaderboard" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice here: ";

    int action;
    cin >> action;

    if (action == 1) {
    // Get the high score from the file and call car selection based on that
    ifstream file("user.txt");
    string u, p;
    int score, money;
    while (file >> u >> p >> score >> money) {
        if (u == username) {
            CarsLinkedList car; // Temporary car object, since carSelection doesn't rely on a specific car
            car.select(score);  // Show car selection based on high score
            
            
            break;  // Exit the loop once we find the user
        }
    }
    file.close();
    cout<<"Press any key to start the game ";
    getch();

    // Start the game
    gamePlay(username);
}

    else if (action == 2) {
        cout << endl;
        cout << "Here's how you will control your car movements: " << endl;
        cout << "Press 'a' to move left" << endl;
        cout << "Press 'd' to move right" << endl;
        cout << "Press 'w' to move up" << endl;
        cout << "Press 'x' to exit." << endl;
        cout << "Make sure to stay away from the obstacles denoted as x on the track. Hitting it will end the game and you will lose. Passing it successfully earns you two points and 5$ money!" << endl;
        cout << "Be the first one at the finish line to win! All the best!" << endl;
    }
    else if (action == 3) {
        const int MAX_PLAYERS = 100;
        Player players[MAX_PLAYERS];
        int count = readPlayersFromFile(players, MAX_PLAYERS);

        PlayerNode* root = NULL;
        for (int i = 0; i < count; i++) {
            root = insertPlayerBST(root, players[i].username, players[i].score);
        }

        if (count > 0) {
            // Displaying leaderboard for money
            displayMoneyLeaderboard(players, count);
            cout << endl;

            cout << "============ LEADERBOARD (SCORES) ============" << endl;
            cout << "Username      Score" << endl;
            // Displaying leaderboard for high-scores
            displayScoreLeaderboard(root);
        }
        else {
            cout << "No players found." << endl;
        }
    }
    else {
        cout << endl;
        cout << "Exiting game...." << endl;
        cout << "Have a nice day!" << endl;
        cout << "We hope to see you soon again!" << endl;
        cout << endl;
    }

    return 0;



}



