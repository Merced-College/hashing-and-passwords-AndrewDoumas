//Andrew Doumas
//3/18/25
//


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Hash function from ZyBooks
int HashString(const string& value) {
   int hashCode = 0;
   for (int character : value) {

       //helps reduce collisions
       char lower_case = tolower(character);
       if(lower_case == 'a' || lower_case == 'e' || lower_case == 'i' || lower_case == 'o' || lower_case == 'u' ){
          character *=-11;
       }
       if(lower_case == 't' || lower_case ==  'h' || lower_case ==  'r' || lower_case ==  'd' || lower_case ==  'l' || lower_case ==  'm' || lower_case ==  'n' || lower_case ==  's'){
           character *=97;
       }
       if(lower_case == 'b' || lower_case ==  'c' || lower_case == 'p' || lower_case ==  'f' || lower_case ==  'g' ){
           character *=41;
       }
      hashCode += character;
   }
    
   return (int)(hashCode & 0x7fffffff); // Ensure positive value
}

int main() {
    unordered_map<int, vector<string>> passwordTable; // Handles collisions using a vector
    ifstream passwordFile("10-million-password-list-top-10000.txt"); // Replace with the actual password file

    if (!passwordFile) {
        cerr << "Error: Password file not found!" << endl;
        return 1;
    }

    
    string password;
    cout << "Reading passwords and hashing...\n";
    int collisionCount = 0;
    while (getline(passwordFile, password)) {
        int hashValue = HashString(password);
        passwordTable[hashValue].push_back(password); // Store in vector to handle collisions
        
        if (passwordTable[hashValue].size() > 1) {
            collisionCount++; // Increment collision count
        }
    }
    passwordFile.close();
    //display total collisions
    // for(int i = 0; i < passwordTable.size(); i++){
    //     if(passwordTable[i].size() > 0){
    //         cout<<i <<": "<< passwordTable[i].size() << endl;
    //     }
    // }


    int count = 0;
    cout << "Non-empty buckets in ascending order:" << endl;
    for (const auto& [hashValue, passwords] : passwordTable) {
        if (!passwords.empty() && count<10) {
            count++;
                
            cout <<count<<" "<< "Hash: " << hashValue << ", Passwords: ";
            for (const string& pass : passwords) {
                cout << pass << " ";
            }
            cout << endl;
        }
    }
    
    //cout << "Size of passwordTable: " << passwordTable.size() << endl;
    //display total collisions
    cout << "Total number of collisions: " << collisionCount << endl;
    cout << "Hashing complete. Enter a hashed password to find the original: ";

    int userHash;
    while (true) {
        cout << "\nEnter hashed value (or -1 to exit): ";
        cin >> userHash;

        if (userHash == -1) break;

        if (passwordTable.find(userHash) != passwordTable.end()) {
            cout << "Possible original passwords:\n";
            for (const string& pass : passwordTable[userHash]) {
                cout << " - " << pass << endl;
            }
        } else {
            cout << "Password not found in database." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
