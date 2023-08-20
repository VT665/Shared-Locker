/*______________________________________________________*/
/*                                                      */
/*                 Shared Locker CPP                    */
/*                Vishnu Tejesh Movva                   */
/*                  Date:- 20/02/27                     */
/*______________________________________________________*/

#include <bits/stdc++.h>                                                // Including Header Files
using namespace std;



bool isPrime(long long int N) {
// Function to check whether the number is prime or not

    if (N <= 1)                                                         // Base Cases
        return false;
    if (N <= 3)
        return true;
    
    if (N % 2 == 0 || N % 3 == 0)                                       // Basic Check
        return false;

    for (int i = 5; i * i <= N; i = i + 6) {                            // Checking with other required numbers
        if (N % i == 0 || N % (i+2) == 0)                               // Returning false if a factor is found
            return false;
    }
    return true;
}


int kthRoot(long long int N, unsigned int k) {
//  Function to find the kth root of the integer N using pow function of std C++ lib

    float index = 1 / (float) k;                                        // Finding 1/k using type casting

    return (int) (pow(N, index));                                       // Converting in to int using type casting
}


void add_locker() {
// This function generate an entry in "config.txt" and user keys using given locker id, key and no of users

    string lockerId;                                                    // Declaring Varibles
    long long int L;
    unsigned int k;
    fstream file;

    cout << endl << "    Task: Add New Locker" << endl;                 // Taking input from user
    cout << "Enter Locker ID (5 chars): ";
    cin >> lockerId;
    cout << "Enter Locker key (upto 10 digits): ";
    cin >> L;
    cout << "Enter no.of Users of Locker: ";
    cin >> k;

    // Checking whether the entry is dupliclate or new
    file.open("config.txt", ios::in);                                   // Opening config.txt in input mode
    string line;
    while (getline(file, line)) {                                       // Iterating through every line
        line = line.substr(0, 5);                                       // Getting locker Id of the entry

        if (line == lockerId) {
            cout << endl << "   Locker is already occupied" << endl;
            cout << "Returning to Configure Menu... " << endl;
            return;                                                     // Returning if the entry is duplicate
        }
    }
    file.close();

    int l = kthRoot(L, k);                                              // Finding kth root of L

    // Finding k primes greater than kth root of L
    vector<int> primeArr(k);
    int i = 0;
    while (i < k) {
        // Pushing the number into the vector if it is a prime number
        if (isPrime(l)) {
            primeArr[i] = l;
            i++;
        }
        l++;                                                            // Moving on to next number
    }
    
    // Appending the desired content as an entry in to the "config.txt"
    file.open("config.txt", ios::app);                                 // Opening config.txt in input mode
    file << lockerId << "  " << k << "  ";
    for (int i = 0; i < k; i++) {                                       // Appending the primes into the file
        file << primeArr[i] << "  ";
    }
    file << endl;
    file.close();

    // Printing all user keys into std out
    cout << endl << "  User Keys :  ";
    int iter;
    for (int i = 0;  i < k;  i++) {                                     // Iterating through all the primes in primeArr
        iter = L % primeArr[i];                                         // Computing User key
        if (iter / 10 == 0)                                             // Adding Zeros to make user keys 4 digit
            cout << "000" << iter << "  ";
        else if (iter / 100 == 0)
            cout << "00" << iter << "  ";
        else if (iter / 1000 == 0)
            cout << "0" << iter << "  ";
        else
            cout << iter << "  ";
    }
    cout << endl;
    return;
}


void del_locker() {
// This function deletes corresponding entry from the text file "config.txt" after taking locker Id as input

    string lockerId, line, temp;                                        // Declaring variables
    bool flag;

    cout << endl << "    Task: Delete Locker" << endl;
    cout << "Enter Locker ID: ";
    cin >> lockerId;

    ifstream file;                                                      // Opening "config.txt"
    file.open("config.txt");
    
    ofstream temp_file;                                                 // creating a temp file
    temp_file.open("temp.txt");

    while (getline(file, line)) {                                       // Iterating through every line
        temp = line.substr(0, 5);                                       // Getting locker Id of the entry in "config.txt"

        if (temp != lockerId)                                           // Copying all entries except the entry to be deleted
            temp_file << line << endl;
        else                                                            // Turning on flag if a line is skipped
            flag = true;
    }

    temp_file.close();                                                  // Closing Files
    file.close();
    
    remove("config.txt");                                               // Removing original "config.txt"
    rename("temp.txt", "config.txt");                                   // Renaming temp file to "config.txt"

    if (flag)                                                           // Printing result of deletion to std out
        cout << endl << "Deletion Successful for " << lockerId << endl;
    else
        cout << endl << "No entry found for " << lockerId << endl;
    
    return;
}


void config() {
    // Menu Based Function
    int input;
    while (true) {
        cout << endl << "    Config Module" << endl;
        cout << "1: Add new locker" << endl;
        cout << "2: Delete locker" << endl;
        cout << "3: Return" << endl;
        cout << "Choose your Task (1/2/3) : ";
        cin >> input;

        if (input == 1) {
            add_locker();
            continue;
        }
        if (input == 2) {
            del_locker();
            continue;
        }
        if (input == 3) {
            cout << endl << "Returning to Main Menu" << endl;
            return;
        }

        cout << endl << "Invalid Input, Try again... " << endl;         // Error Input Handling
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void use() {
// This function regenerates the Locker Key from user Keys provided and the primes from the file "config.txt"
    string lockerId, line_lId, line;                                    // Declaring Variables
    ifstream file;
    bool flag;

    cout << endl << "    Use Module" << endl;
    cout << "Enter Locker Id: ";                                        // Taking locker Id from user input
    cin >> lockerId;

    file.open("config.txt");                                            // Opening "config.txt" in input mode

    flag = false;
    while (getline(file, line))                                         // Iterating through every line
    {
        line_lId = line.substr(0, 5);                                   // Getting locker Id of the entry
        if (line_lId == lockerId) {
        // Turning on flag and breaking loop if entry found
            flag = true;
            break;
        }
    }

    // Returning to Main Menu if no entry found with given locker Id
    if (!flag) {
        cout << endl << "No locker Entry found for " << lockerId << endl;
        return;
    }

    stringstream line_stream(line);                                     // Converting the line to string stream
    int k;

    line_stream >> line_lId >> k;                                       // Taking locker Id and 'k' from line string stream
    
    vector <int> primeArr(k);
    vector <int> user_keys(k);

    cout << endl << "    Enter User Keys" << endl;
    for (int j = 0;  j < k;  j++) {
        cout << "User Key " << j + 1 << " : ";
        cin >> user_keys[j];                                            // Taking User keys from std input
        line_stream >> primeArr[j];                                     // Taking primes from the line string stream
    }

    // Iterate through numbers starting from first prime
    int L = primeArr[0];
    while (true) {
        flag = true;
        for (int i = 0;  i < k;  i++) {
            // Check if the considered number gives 'i'th key with 'i'th prime
            if (L % primeArr[i] != user_keys[i]) {
                flag = false;
                break;
            }
        }
        if (flag)                                                       // If all k conditions were satisfied
            break;                                                      // The loop terminates
        else                                                            // If atleast one condition fail
            L++;                                                        // We check next number
    }
    
    cout << endl << "Locker Access Key for " << line_lId << " : " << L << endl;
    return;
}


int main() {
    // Menu Based Function
    cout << "Welcome to the Shared Locker CPP !!" << endl;
    int input;
    while (true) {
        cout << endl << "    MAIN MENU" << endl;
        cout << "1: CONFIG" << endl;
        cout << "2: USE" << endl;
        cout << "3: EXIT" << endl;
        cout << "Choose your Task (1/2/3) : ";
        cin >> input;

        if (input == 1) {
            config();
            continue;
        }
        if (input == 2) {
            use();
            continue;
        }
        if (input == 3) {
            cout << endl << "Exiting Program... " << endl;
            return 0;
        }

        cout << endl << "Invalid Input, Try Again... " << endl;         // Invalid Input Handling
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}