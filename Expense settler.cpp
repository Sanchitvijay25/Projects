#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Structure to represent a transaction in the tree
struct Transaction {
    string from;
    string to;
    double amount;

    Transaction(string from, string to, double amount)
        : from(from), to(to), amount(amount) {}
};

class FindPath {
private:
    static vector<Transaction> transactionHistory; // To store transaction history

public:
    static void findPath(unordered_map<string, double>& details) {
        double Max_Value = max_element(details.begin(), details.end(),
            [](const auto& p1, const auto& p2) { return p1.second < p2.second; })->second;
        double Min_Value = min_element(details.begin(), details.end(),
            [](const auto& p1, const auto& p2) { return p1.second < p2.second; })->second;
        
        if (Max_Value != Min_Value) {
            auto Max_Key = getKeyFromValue(details, Max_Value);
            auto Min_Key = getKeyFromValue(details, Min_Value);
            double result = Max_Value + Min_Value;
            result = round(result, 1);
            
            if (result >= 0.0) {
                cout << Min_Key << " needs to pay " << Max_Key << ": " << round(abs(Min_Value), 2) << endl;
                details.erase(Max_Key);
                details.erase(Min_Key);
                details[Max_Key] = result;
                details[Min_Key] = 0.0;
                recordTransaction(Min_Key, Max_Key, abs(Min_Value));
            } else {
                cout << Min_Key << " needs to pay " << Max_Key << ": " << round(abs(Max_Value), 2) << endl;
                details.erase(Max_Key);
                details.erase(Min_Key);
                details[Max_Key] = 0.0;
                details[Min_Key] = result;
                recordTransaction(Min_Key, Max_Key, abs(Max_Value));
            }
            
            findPath(details);
        }
    }

    static void printTransactionHistory() {
        cout << "\nTransaction History:\n";
        for (const auto& transaction : transactionHistory) {
            cout << transaction.from << " pays " << transaction.to << " $" << transaction.amount << endl;
        }
    }

private:
    static string getKeyFromValue(const unordered_map<string, double>& hm, double value) {
        for (const auto& pair : hm) {
            if (pair.second == value) {
                return pair.first;
            }
        }
        return "";
    }
    
    static double round(double value, int places) {
        if (places < 0)
            throw invalid_argument("Places must be non-negative");
        
        double factor = pow(10, places);
        return std::round(value * factor) / factor;
    }

    static void recordTransaction(const string& from, const string& to, double amount) {
        transactionHistory.emplace_back(from, to, amount);
    }
};

// Initialize static member outside class definition
vector<Transaction> FindPath::transactionHistory;

int main() {
    // Number of members
    int numMembers;
    cout << "Enter number of members: ";
    cin >> numMembers;

    // Names of members
    vector<string> members(numMembers);
    cout << "Enter names of members:" << endl;
    for (int i = 0; i < numMembers; ++i) {
        cin >> members[i];
    }

    // Initialize details map
    unordered_map<string, double> details;
    for (const auto& member : members) {
        details[member] = 0.0;
    }

    // Number of transactions
    int numTransactions;
    cout << "Enter number of transactions: ";
    cin >> numTransactions;

    // Input transactions
    cout << "Enter transactions (payer amount splitType (0 for equal, 1 for unequal) numParticipants participant1 participant2 ...):" << endl;
    for (int i = 0; i < numTransactions; ++i) {
        string payer;
        double amount;
        int splitType;
        int numParticipants;
        cin >> payer >> amount >> splitType >> numParticipants;
        vector<string> participants(numParticipants);
        for (int j = 0; j < numParticipants; ++j) {
            cin >> participants[j];
        }

        if (splitType == 0) { // Equal split
            double splitAmount = amount / numParticipants;
            for (const auto& participant : participants) {
                details[participant] -= splitAmount;
            }
        } else { // Unequal split
            for (const auto& participant : participants) {
                double participantAmount;
                cin >> participantAmount;
                details[participant] -= participantAmount;
            }
        }
        details[payer] += amount;
    }

    // Find path to settle debts
    FindPath::findPath(details);

    // Print transaction history (tree)
    FindPath::printTransactionHistory();
    
}