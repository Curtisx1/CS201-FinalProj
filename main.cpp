#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "vendor.h"
using namespace std;

int main() {
    vector<Vendor> vendors;
    vector<AuditedVendor> auditedVendors;

    Vendor vendorManager; // Create an object to manage vendors
    vendorManager.loadVendorsFromFile(vendors, "vendors.csv"); // Load vendors once at the start

    int choice;

    while (true) {
        cout << "Overland Park Farmer's Market" << endl;
        cout << "   Vendor Audit System" << endl;
        cout << "============================" << endl;
        cout << "    Main Menu" << endl;
        cout << "    1. Start Audit\n    2. New Vendor\n    3. View Vendors\n    4. Delete Vendor\n    5. View Past Audits\n    6. Individual Audit Report\n    7. Exit\n    Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Starts the whole vendor audit
            AuditedVendor::startAudit(vendors, auditedVendors);
            break;
        case 2: // Adds a new vendor, prompts for a vendor name (business name), generates a sequential ID number
            vendorManager.addNewVendor(vendors);
            break;
        case 3: // Generates a vendor list, prints to console
            vendorManager.viewVendors(vendors);
            break;
        case 4: // Deletes a vendor from the vector, prompts for vendor ID to delete
            vendorManager.deleteVendor(vendors);
            break;
        case 5: // Generates a list of past audits, ordered by date, lists the vendor and vendor ID
            vendorManager.viewPastAudits();
            break;
        case 6: // View an audit report of an individual vendor
            vendorManager.fullAuditReport(vendors);
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
