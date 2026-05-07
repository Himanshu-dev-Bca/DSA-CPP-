#include <iostream>
#include <string>
using namespace std;

class Hospital
{
private:
    int patientID[100];
    string patientName[100];
    int totalPatients;

public:
    // Constructor
    Hospital()
    {
        totalPatients = 0;
    }

    // Function to add patient records
    void addPatient()
    {
        int n;

        cout << "Enter number of patients: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter Patient ID: ";
            cin >> patientID[totalPatients];

            cin.ignore();

            cout << "Enter Patient Name: ";
            getline(cin, patientName[totalPatients]);

            totalPatients++;
        }

        cout << "\nPatient records added successfully.\n";
    }

    // Function to display all patients
    void displayPatients()
    {
        if (totalPatients == 0)
        {
            cout << "\nNo patient records found.\n";
            return;
        }

        cout << "\n--- Patient Records ---\n";

        for (int i = 0; i < totalPatients; i++)
        {
            cout << "Patient ID   : " << patientID[i] << endl;
            cout << "Patient Name : " << patientName[i] << endl;
            cout << "---------------------------\n";
        }
    }

    // Linear Search
    void linearSearch()
    {
        int key;
        bool found = false;

        cout << "\nEnter Patient ID to search: ";
        cin >> key;

        for (int i = 0; i < totalPatients; i++)
        {
            if (patientID[i] == key)
            {
                cout << "\nPatient Found using Linear Search\n";
                cout << "Patient ID   : " << patientID[i] << endl;
                cout << "Patient Name : " << patientName[i] << endl;

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\nPatient not found.\n";
        }
    }

    // Sort records for Binary Search
    void sortPatients()
    {
        for (int i = 0; i < totalPatients - 1; i++)
        {
            for (int j = 0; j < totalPatients - i - 1; j++)
            {
                if (patientID[j] > patientID[j + 1])
                {
                    // Swap IDs
                    int tempID = patientID[j];
                    patientID[j] = patientID[j + 1];
                    patientID[j + 1] = tempID;

                    // Swap Names
                    string tempName = patientName[j];
                    patientName[j] = patientName[j + 1];
                    patientName[j + 1] = tempName;
                }
            }
        }
    }

    // Binary Search
    void binarySearch()
    {
        if (totalPatients == 0)
        {
            cout << "\nNo patient records available.\n";
            return;
        }

        sortPatients();

        int key;
        cout << "\nEnter Patient ID to search: ";
        cin >> key;

        int low = 0;
        int high = totalPatients - 1;
        bool found = false;

        while (low <= high)
        {
            int mid = (low + high) / 2;

            if (patientID[mid] == key)
            {
                cout << "\nPatient Found using Binary Search\n";
                cout << "Patient ID   : " << patientID[mid] << endl;
                cout << "Patient Name : " << patientName[mid] << endl;

                found = true;
                break;
            }
            else if (patientID[mid] < key)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        if (!found)
        {
            cout << "\nPatient not found.\n";
        }
    }
};

int main()
{
    Hospital h;

    int choice;

    do
    {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Patient Records\n";
        cout << "2. Display Patient Records\n";
        cout << "3. Linear Search\n";
        cout << "4. Binary Search\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            h.addPatient();
            break;

        case 2:
            h.displayPatients();
            break;

        case 3:
            h.linearSearch();
            break;

        case 4:
            h.binarySearch();
            break;

        case 5:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 5);

    return 0;
}
