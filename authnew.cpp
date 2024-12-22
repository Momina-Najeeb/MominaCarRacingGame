#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

//User class for user authorization
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


// Node class for the linked list of cars
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
            cout<<endl;
            cout << "Elite Cars for High Scorers:" << endl;
            carList.insert(Car("Bugatti Veyron Super Sport", 410, 1200));
            carList.insert(Car("Koenigsegg Agera RS", 450, 1160));
            carList.insert(Car("Ferrari LaFerrari", 350, 950));
        } else if (score > 20) {
            cout<<endl;
            cout << "Mid-tier Cars for Moderate Scorers:" << endl;
            carList.insert(Car("Porsche 911 Turbo S", 330, 640));
            carList.insert(Car("Nissan GT-R", 315, 565));
            carList.insert(Car("Mercedes-AMG GT", 318, 523));
        } else {
            cout<<endl;
            cout << "Basic Cars for Lower Scorers:" << endl;
            carList.insert(Car("Chevrolet Camaro SS", 250, 455));
            carList.insert(Car("Ford Mustang GT", 250, 450));
            carList.insert(Car("Toyota Supra", 270, 335));
        }

        cout << "Car List:" << endl;
        carList.display();
        cout<<endl;
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

    // Display function for cars stored in Linked List
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

    // Destructor
    ~CarsLinkedList() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

const int TRACK_LENGTH = 50; // Fixed track length
const int TRACK_WIDTH = 5;  // Width of the track
const char OBSTACLE = 'X';

//Printing racing track
void printTrack(int userPos, int userLane, int compPos, int compLane, int obstaclePos, int obstacleLane) {
    system("cls");
    for (int i = 0; i < TRACK_WIDTH; i++) {
        for (int j = 0; j <= TRACK_LENGTH; j++) {
            if (j == userPos && i == userLane) {
                cout << "U"; // User's car
            } else if (j == compPos && i == compLane) {
                cout << "C"; // Computer's car
            } else if (j == obstaclePos && i == obstacleLane) {
                cout << OBSTACLE; // Obstacle
            } else {
                cout << "."; // Empty track
            }
        }
        cout << endl;
    }
}

//Updating players's stats
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

// MergeSort on Player array
void MergeSort(Player arr[], int left, int right) {
    if(left < right) {
    int mid = left + (right - left) / 2;

    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);

    Merge(arr, left, mid, right);
    }
}

// Displaying Money Leaderboard
void displayMoneyLeaderboard(Player players[], int count) {
    MergeSort(players, 0, count - 1);

    cout << "============ LEADERBOARD (MONEY) ============"<<endl;
    cout << left << setw(20) << "Username" << setw(10) << "Money" << endl; 
    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << players[i].username << "$" << players[i].money << endl;
    }
}

// Displaying Score Leaderboard
void displayScoreLeaderboard(PlayerNode* root) {
    if(root != NULL) {
        displayScoreLeaderboard(root->right); 
        cout << left << setw(20) << root->username << setw(10) << root->score << endl;
        displayScoreLeaderboard(root->left);  
    }
}


void gamePlay(string username){
    srand(time(0));

    int userPos = 0, compPos = 0;
    int userLane = TRACK_WIDTH / 2, compLane = TRACK_WIDTH / 2 + 1;
    int obstaclePos = rand() % TRACK_LENGTH; // Initial obstacle position
    int obstacleLane = rand() % TRACK_WIDTH; // Initial obstacle lane
    int score=0;
    int money=0;

    while (true) {
        // Move obstacle randomly sideways and forward/backward
        obstaclePos += rand() % 3 - 1;
        obstacleLane += rand() % 3 - 1;
        if (obstaclePos < 0) obstaclePos = 0;
        if (obstaclePos > TRACK_LENGTH) obstaclePos = TRACK_LENGTH;
        if (obstacleLane < 0) obstacleLane = 0;
        if (obstacleLane >= TRACK_WIDTH) obstacleLane = TRACK_WIDTH - 1;

        // Check for user input
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && userLane > 0) {
                userLane--;
            } else if (key == 'd' && userLane < TRACK_WIDTH - 1) {
                userLane++;
            } else if (key == 'w') {
                userPos++;
            }
        }

        // Move computer randomy froward
        compPos += rand() % 2;

        // Check collision with obstacle
        if (userPos == obstaclePos && userLane == obstacleLane) {
            cout << "You hit an obstacle! Game Over." << endl;
            break;
        }

        // Print the track
        printTrack(userPos, userLane, compPos, compLane, obstaclePos, obstacleLane);

        // Check for the winner
        if (userPos >= TRACK_LENGTH) {
            cout << "Congratulations! You win!" << endl;
            score+=5;
            money+=10;
            break;
        } else if (compPos >= TRACK_LENGTH) {
            cout << "Computer wins! Better luck next time." << endl;
            break;
        }

        updateUser(username, score, money);

        // Delay for smoother gameplay
        Sleep(100); 
    }
}

//MAIN FUNTION
int main() {

        cout<<endl;
    cout << "=============================_/'''|_  Welcome to the Car Racing Game!  _/'''|_ =============================" << endl;
    cout<<"                            |_.___._|                                 |_.___._|"<<endl;
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
            CarsLinkedList car; 
            car.select(score); 
            break;             
        }
    }
    file.close();
    cout<<"Press any key to start the game ";
    getch();

    //Start the game
    gamePlay(username);
    }

    else if (action == 2) {
    //Displaying How to Play of the game
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



