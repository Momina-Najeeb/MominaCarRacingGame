#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
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



class Car {
    string name;
    int speed;  
    int power;  
public:
    
Car(string n, int s, int p) {
    name = n;
    speed = s;
    power = p;
}

    // Method to display car details
    void car_display() {
        cout << "Car name: " << name << " | Speed: " << speed << " km/h | Power: " << power << " HP" << endl;
    }

// Modify the CarSelection to show cars based on high score
void carSelection(int score) {
    cout << "========================================================" << endl;
    cout << "                    CAR COLLECTION" << endl;
    cout << "========================================================" << endl;
    cout << endl;
    cout << "Select Your Car:" << endl;
    cout << endl;

    // Show Elite Cars for high scores above 20
    if(score > 20) {
        cout << "Elite Cars for High Scorers:" << endl;
        Car car1("Bugatti Veyron Super Sport", 410, 1200);  // High speed and power
        car1.car_display();
        Car car2("Koenigsegg Agera RS", 450, 1160);
        car2.car_display();
        Car car3("Ferrari LaFerrari", 350, 950);
        car3.car_display();

        // Provide numbers for selection
        cout << "1. Bugatti Veyron Super Sport" << endl;
        cout << "2. Koenigsegg Agera RS" << endl;
        cout << "3. Ferrari LaFerrari" << endl;
    }
    // Show Mid-tier Cars for scores between 10 and 20
    else if(score > 10) {
        cout << "Mid-tier Cars for Moderate Scorers:" << endl;
        Car car4("Porsche 911 Turbo S", 330, 640);  // Moderate speed and power
        car4.car_display();
        Car car5("Nissan GT-R", 315, 565);
        car5.car_display();
        Car car6("Mercedes-AMG GT", 318, 523);
        car6.car_display();

        // Provide numbers for selection
        cout << "1. Porsche 911 Turbo S" << endl;
        cout << "2. Nissan GT-R" << endl;
        cout << "3. Mercedes-AMG GT" << endl;
    }
    // Show Basic Cars for scores below or equal to 10
    else {
        cout << "Basic Cars for Lower Scorers:" << endl;
        Car car7("Chevrolet Camaro SS", 250, 455);  // Basic speed and power
        car7.car_display();
        Car car8("Ford Mustang GT", 250, 450);
        car8.car_display();
        Car car9("Toyota Supra", 270, 335);
        car9.car_display();

        // Provide numbers for selection
        cout << "1. Chevrolet Camaro SS" << endl;
        cout << "2. Ford Mustang GT" << endl;
        cout << "3. Toyota Supra" << endl;
    }

    // Ask for car selection by number
    cout << endl;
    cout << "Enter the number of the car you wish to select: ";
    int carChoice;
    cin >> carChoice;

    string selectedCar;
    switch (carChoice) {
        case 1:
            selectedCar = (score > 20) ? "Bugatti Veyron Super Sport" : (score > 10) ? "Porsche 911 Turbo S" : "Chevrolet Camaro SS";
            break;
        case 2:
            selectedCar = (score > 20) ? "Koenigsegg Agera RS" : (score > 10) ? "Nissan GT-R" : "Ford Mustang GT";
            break;
        case 3:
            selectedCar = (score > 20) ? "Ferrari LaFerrari" : (score > 10) ? "Mercedes-AMG GT" : "Toyota Supra";
            break;
        default:
            cout << "Invalid selection!" << endl;
            return;
    }

    cout << "You have selected: " << selectedCar << ". Let's begin the race!" << endl;
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
    cout << "Welcome to the Car Racing Game!" << endl;
    cout << "This is an exciting game where you race against the computer to reach the finish line first." << endl;
    cout << "Avoid obstacles to earn money and increase your score." << endl;

    User user;
    string username, password;

    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Exit" << endl;
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
        cout << "Exiting game." << endl;
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
                Car car("", 0, 0); // Temporary car object, since carSelection doesn't rely on a specific car
                car.carSelection(score);  // Show car selection based on high score
                break;  // Exit the loop once we find the user
            }
        }
        file.close();

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



