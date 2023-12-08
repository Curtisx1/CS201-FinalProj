#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;


struct AuditRecord {
    vector<double> temperatures;
    vector<string> timesOfAudit;
    vector<string> foodTypes;
    vector<string> storageTypes;
    int numberOfViolations;

    // Constructor to initialize the struct
    AuditRecord(const vector<double>& temps, const vector<string>& times,
        const vector<string>& foods, const vector<string>& storages,
        int violations)
        : temperatures(temps), timesOfAudit(times), foodTypes(foods),
        storageTypes(storages), numberOfViolations(violations) {}
};


class Vendor {

private:
    int vendorId;
    string vendorName;
    vector<double> temperatures;
    int numberOfAudits;
    vector<string> foodTypes;
    vector<string> storageTypes;
    vector<AuditRecord> auditHistory;

public:
    int numberOfViolations;

    // Constructor
    Vendor() : vendorId(-1), vendorName("Unknown"), numberOfViolations(0), numberOfAudits(0) {}

    // Constructor
    Vendor(int id, const string& name)
        : vendorId(id), vendorName(name), numberOfViolations(0){}

    // Setters
    void setTemperatures(double temp) { temperatures.push_back(temp); }

    // Getters
    int getVendorId() const { return vendorId; }
    string getVendorName() const { return vendorName; }
    vector<double> getTemperatures() const { return temperatures; }

    void loadVendorsFromFile(vector<Vendor>& vendors, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string part;
            vector<string> parts;

            while (getline(ss, part, ',')) {
                parts.push_back(part);
            }

            if (parts.size() >= 2) {
                int id = stoi(parts[0]);
                string name = parts[1];
                name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
                Vendor vendor(id, name);
                vendors.push_back(vendor);
            }
        }
        file.close();
    }

    Vendor* findVendorById(vector<Vendor>& vendors, int id) {
        for (auto& vendor : vendors) {
            if (vendor.getVendorId() == id) {
                return &vendor;
            }
        }
        return nullptr;
    }

    void fullAuditReport(const vector<Vendor>& vendors) {
        int vendorId;
        cout << "Enter vendor ID for audit report: ";
        cin >> vendorId;

        auto it = find_if(vendors.begin(), vendors.end(), [vendorId](const Vendor& v) { return v.getVendorId() == vendorId; });
        if (it != vendors.end()) {
            cout << "Audit report for Vendor ID: " << vendorId << endl;

        }
        else {
            cout << "Vendor not found." << endl;
        }

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }

    void viewPastAudits() {
        cout << "Viewing past audits...\n";

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }

    void deleteVendor(vector<Vendor>& vendors) {
        int idToDelete;
        cout << "Enter vendor ID to delete: ";
        cin >> idToDelete;

        auto it = remove_if(vendors.begin(), vendors.end(), [idToDelete](const Vendor& v) { return v.getVendorId() == idToDelete; });
        if (it != vendors.end()) {
            vendors.erase(it, vendors.end());
            cout << "Vendor with ID " << idToDelete << " has been deleted." << endl;
        }
        else {
            cout << "Vendor not found." << endl;
        }

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }

    void viewVendors(const vector<Vendor>& vendors) {
        cout << "List of Vendors:\n";
        for (const auto& vendor : vendors) {
            cout << "ID: " << vendor.getVendorId() << ", Name: " << vendor.getVendorName() << endl;
        }

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }

    void addNewVendor(vector<Vendor>& vendors) {
        string vendorName;
        cout << "Enter vendor name (business name): ";
        cin.ignore();
        getline(cin, vendorName);

        int newId = vendors.empty() ? 1 : vendors.back().getVendorId() + 1;
        Vendor newVendor(newId, vendorName);
        vendors.push_back(newVendor);

        cout << "New vendor added with ID: " << newId << endl;

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }
};


// Derived Class
class AuditedVendor : public Vendor {
private:
    int vendorId;
    string vendorName;
    string lastAuditDate;

public:
    // Constructor
    AuditedVendor(int id, const string& name) : Vendor(), vendorId(id), vendorName(name) {}

    // Setters and getters for new properties
    void setLastAuditDate(const string& date) { lastAuditDate = date; }
    string getLastAuditDate() const { return lastAuditDate; }

    void setNumberOfViolations(int numViolations) {
        numberOfViolations = numViolations;
    }

    int getNumberOfViolations() const {
        return numberOfViolations;
    }

    static void startAudit(vector<Vendor>& vendors, vector<AuditedVendor>& auditedVendors) {
        if (vendors.size() < 5) {
            cout << "Not enough vendors to perform audit." << endl;
            return;
        }

        random_device rd;  // Obtain a random number from hardware
        mt19937 gen(rd()); // Seed the generator

        // Shuffle the vendors vector
        shuffle(vendors.begin(), vendors.end(), gen);

        cout << "Starting audit for 5 random vendors..." << endl;
        for (int i = 0; i < 5; ++i) {
            Vendor& selectedVendor = vendors[i];

            // Example: Collecting audit data for the selected vendor
            vector<double> temperatures;
            int numberOfViolations;
            vector<string> timesOfAudit;
            vector<string> foodTypes;
            vector<string> storageTypes;

            // Example: Getting input from the user (you can expand upon this as per your requirements)
            cout << "Auditing Vendor ID: " << selectedVendor.getVendorId() << ", Name: " << selectedVendor.getVendorName() << endl;

            // Get times of audit
            cout << "Enter times of audit (enter 'done' to stop)" << endl;
            cout << "Use the following format: 1:15PM" << endl;
            string time;
            while (cin >> time && time != "done") {
                timesOfAudit.push_back(time);
            }

            // Get food types
            cout << "Enter food types (enter 'done' to stop)" << endl;
            cout << "Options: Poultry, Beef, Dairy, Prepared" << endl;
            string foodType;
            while (cin >> foodType && foodType != "done") {
                foodTypes.push_back(foodType);
            }

            // Get storage types
            cout << "Enter storage types (enter 'done' to stop)" << endl;
            cout << "Options: Cooler, Open air, packaged, fridge" << endl;
            string storageType;
            while (cin >> storageType && storageType != "done") {
                storageTypes.push_back(storageType);
            }

            // Get temperatures
            cout << "Enter temperatures (enter -1 to stop)" << endl;
            cout << "Enter an integer, example: 35" << endl;
            double temp;

            while (true) {
                cin >> temp;
                if (cin.fail()) {
                    cin.clear(); // Clears the error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards the incorrect input
                    cout << "Invalid input. Please enter a numeric value." << endl;
                }
                else {
                    if (temp == -1) {
                        break; // Exit the loop if -1 is entered
                    }
                    temperatures.push_back(temp);
                }
            }

            // Record number of violations
            cout << "Enter number of violations: ";
            cin >> numberOfViolations;

            // Create an AuditedVendor object and add it to auditedVendors
            AuditedVendor audited(selectedVendor.getVendorId(), selectedVendor.getVendorName());
            // Set the audit data for the audited vendor
            audited.setNumberOfViolations(numberOfViolations);
            // Similarly set other audit data
            auditedVendors.push_back(audited);
        }

        cout << "Audit completed for 5 vendors." << endl;

        // Adding back feature
        char back;
        cout << "\nM: Return to main menu ";
        cin >> back;
        if (toupper(back) == 'M') {
            return; // This will return control to the main menu in the main function
        }
    }
};