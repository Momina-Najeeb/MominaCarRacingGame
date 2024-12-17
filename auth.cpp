#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User{
    private:
    string username;
    string password;

    public:
    bool signup(string uname, string pass){
        ofstream file("users.txt", ios::app);
        if(file.is_open()){
            file<<uname << " " << pass << " 0 0\n";    // username, password, highscore, money
            file.close();
            return true;
        }
        return false;
    }

    bool login(string uname, string pass){
        ifstream file("users.txt");
        if(!file.is_open()){
            cout<<"❗Unable to open file"<<endl;
            return false;
        }
        string u, p;
        while(file >> u >> p){
            if(u==uname && p==password){
                username=uname;
                password=pass;
                file.close();
                return true;
            }
        }
        cout<<"❗Error: User not found or incorrect password! "<<endl;
        file.close();
        return false;
    }
};

struct Node{
    string content;
    Node* next;

    Node(string val){
        content=val;
        next=NULL;
    }
};

class Track {
private:
Node* head;

public:
Track() {
    head = NULL;
}

void addNode(string content) {
    Node* newNode = new Node(content);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayTrack() {
    Node* temp = head;
    int position = 1;
    while (temp) {
        cout << "Position " << position++ << ": " << temp->content << endl;
        temp = temp->next;
    }
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

    // Method to display car selection menu based on player rank
    void carSelection(int rank) {
        cout << "========================================================" << endl;
        cout << "                    🏎️CAR COLLECTION🏎️" << endl;
        cout << "========================================================" << endl;
        cout << endl;
        cout << "Select Your Car:" << endl;
        cout << endl;

        // Best cars for ranks greater than or equal to 10
        if (rank >= 10) {
            cout << "Best Cars for High Ranking Players:" << endl;
            Car car1("Bugatti Veyron Super Sport", 410, 1200);  // High speed and power
            car1.car_display();
            Car car2("Koenigsegg Agera RS", 450, 1160);
            car2.car_display();
            Car car3("Ferrari LaFerrari", 350, 950);
            car3.car_display();
        }
        // Better cars for ranks greater than or equal to 5 but less than 10
        else if (rank >= 5) {
            cout << "Better Cars for Mid Ranking Players:" << endl;
            Car car4("Porsche 911 Turbo S", 330, 640);  // Moderate speed and power
            car4.car_display();
            Car car5("Nissan GT-R", 315, 565);
            car5.car_display();
            Car car6("Mercedes-AMG GT", 318, 523);
            car6.car_display();
        }
        // Good cars for ranks less than 5
        else {
            cout << "Good Cars for Lower Ranking Players:" << endl;
            Car car7("Chevrolet Camaro SS", 250, 455);  // Basic speed and power
            car7.car_display();
            Car car8("Ford Mustang GT", 250, 450);
            car8.car_display();
            Car car9("Toyota Supra", 270, 335);
            car9.car_display();
        }
    }
};

void updateUser(string uname, int newScore, int money) {
    ifstream inFile("users.txt");
    if (!inFile) {
        cout << "Error opening users.txt file!" << endl;
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        cout << "Error opening temp.txt file!" << endl;
        return;
    }

    string u, p;
    int score, cash;

    while (inFile >> u >> p >> score >> cash) {
        if (u == uname) {
            score = max(score, newScore);
            cash += money;
        }
        outFile << u << " " << p << " " << score << " " << cash << "\n";
    }

    inFile.close();
    outFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}

// You can implement a similar BST for players, sorting based on score
struct PlayerNode {
    string username;
    int score;
    PlayerNode* left;
    PlayerNode* right;

    PlayerNode(string u, int s) : username(u), score(s), left(nullptr), right(nullptr) {}
};

PlayerNode* insertPlayerBST(PlayerNode* root, const string& username, int score) {
    if (root == nullptr) {
        return new PlayerNode(username, score);
    }

    if (score < root->score) {
        root->left = insertPlayerBST(root->left, username, score);
    } else {
        root->right = insertPlayerBST(root->right, username, score);
    }
    return root;
}

void inorderPlayerBST(PlayerNode* root) {
    if (root != nullptr) {
        inorderPlayerBST(root->left);
        cout << root->username << " | Score: " << root->score << "\n";
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
    ifstream file("users.txt");
    if (!file) {
        cout << "❗ Unable to open file!" << endl;
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
        if (leftarray[i].money > rightarray[j].money) { // Sorting in descending order
            arr[k] = leftarray[i];
            i++;
        } else {
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
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);

        Merge(arr, left, mid, right);
    }
}

// Display Leaderboard based on Money
void displayMoneyLeaderboard(Player players[], int count) {
    MergeSort(players, 0, count - 1);

    cout << "============ LEADERBOARD (MONEY) ============\n";
    cout << "Username      Money\n"; 
    for (int i = 0; i < count; i++) {
        cout << players[i].username << "          $" << players[i].money << "\n";
    }
}




int main(){
    return 0;


    
}



