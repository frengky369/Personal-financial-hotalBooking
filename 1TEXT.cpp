#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits> // for numeric_limits
using namespace std;

const int NUM_ROOMS = 4;
const double PRICES[NUM_ROOMS] = { 350.0, 500.0, 800.0, 1200.0 };
const string ROOMS[NUM_ROOMS] = { "Single", "Deluxe", "Executive", "Presidential" };

const int SILVER = 300, GOLD = 500, DIAMOND = 1200;
const double BREAKFAST_PRICE = 20.0; // price per night for non-members

// enter a integer , array [min, max]
int getValidInt(int min, int max) {
    int value;
    while (true) {
        if (cin >> value && value >= min && value <= max) {
            return value; // if valid, return it
        }
        cout << "Invalid input! Please enter a number between "
            << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getValidString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin >> ws, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Try again." << endl;
        }
        else {
            return input;
        }
    }
}

bool isDigits(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string getValidNumber(const string& prompt, int length) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin >> ws, input);
        if ((int)input.size() != length || !isDigits(input)) {
            cout << "Invalid input. Must be exactly " << length << " digits." << endl;
        }
        else {
            return input;
        }
    }
}

string getValidPassword(const string& prompt, int minLength) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin >> ws, input);
        if ((int)input.size() < minLength) {
            cout << "Password must be at least " << minLength << " characters long." << endl;
        }
        else {
            return input;
        }
    }
}

//  enter Y/N
char getYesNo() {
    char c;
    while (true) {
        if (cin >> c) {
            c = toupper(c);
            if (c == 'Y' || c == 'N') return c;
        }
        cout << "Invalid input! Please enter Y or N: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getRoomChoice() {
    char type;
    while (true) {
        cin >> type;
        type = tolower(type);
        int index = type - 'a';
        if (index >= 0 && index < NUM_ROOMS) {
            return index; // valid choice,return index
        }
        cout << "Invalid choice! Please enter a-d: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// get member level
string getLevel(int points) {
    if (points >= DIAMOND) return "Diamond";
    else if (points >= GOLD) return "Gold";
    else if (points >= SILVER) return "Silver";
    return "Normal";
}

// discount rate
double getDiscount(string level) {
    if (level == "Diamond") return 0.85; // 15% off
    else if (level == "Gold") return 0.90; // 10% off
    else if (level == "Silver") return 0.95; // 5% off
    return 1.0; // Normal - no discount
}

// room booking function
void makeBooking(int nights[], int breakfasts[], int points) {
    char type;
    int numOfNight;
    bool another = true;

    do {
        system("cls");
        cout << "========================================================" << endl;
        cout << "|||||||| |||||\\   /|||||\\   /|||||\\  / \\    / \\  " << endl;
        cout << "||       ||  ||  ||     || ||     || || \\  / ||  " << endl;
        cout << "||||||   ||/|  ||     || ||     || ||  \\/  ||" << endl;
        cout << "||       ||  \\\\  ||     || ||     || ||      || " << endl;
        cout << "|||||||| ||   \\\\  \\|||||/   \\|||||/  ||      ||  " << endl;
        cout << "========================================================" << endl;
        cout << "\nROOM TYPE" << endl;
        for (int i = 0; i < NUM_ROOMS; i++) {
            cout << char('a' + i) << ". " << ROOMS[i] << " (RM" << PRICES[i] << " PER NIGHT)" << endl;
        }
        cout << "---------------------------------------------------" << endl;
        cout << "Choose a room type (a-d): ";
        int index = getRoomChoice();

        //enter number of nights 
        cout << "Enter number of nights: ";
        numOfNight = getValidInt(1, 365);

        nights[index] += numOfNight;

        // ask if want breakfast
        cout << "Do you want breakfast included? (Y/N): ";
        char breakfastChoice = getYesNo();
        if (breakfastChoice == 'Y') {
            string level = getLevel(points);
            if (level == "Normal") {
                cout << "\nBreakfast added (RM" << BREAKFAST_PRICE << " per night)." << endl;
                breakfasts[index] += numOfNight; // charge only for non-members
            }
            else {
                cout << "\nBreakfast added for FREE (Member benefit)." << endl;
            }
        }

        cout << "===================================================" << endl;
        cout << "Booking successful!" << endl;
        cout << "===================================================" << endl;
        cout << "\nMake another booking? (Y/N): ";
        char ans = getYesNo();
        another = (ans == 'Y');

    } while (another);
}

// review function
void viewBooking(const int nights[], const int breakfasts[]) {
    double total = 0;
    system("cls");
    cout << "\nBooking Summary:" << endl;
    cout << "===================================================" << endl;
    for (int i = 0; i < NUM_ROOMS; i++) {
        if (nights[i] > 0) {
            double roomCost = nights[i] * PRICES[i];
            double breakfastCost = breakfasts[i] * BREAKFAST_PRICE;
            cout << ROOMS[i] << " : " << nights[i]
                << " nights (RM" << fixed << setprecision(2) << roomCost << ")";
            if (breakfasts[i] > 0) {
                cout << " + Breakfast (RM" << breakfastCost << ")";
            }
            cout << endl;
            total += roomCost + breakfastCost;
        }
    }
    cout << "===================================================" << endl;
    if (total > 0) cout << "Total cost (before discount): RM" << total << endl;
    else cout << "No booking yet!" << endl;
    system("pause");
}

// cancel booking
void cancelBooking(int nights[], int breakfasts[]) {
    char choice;
    bool another = true;

    do {
        system("cls");
        cout << "Cancel Booking Menu:" << endl;
        double total = 0;
        cout << "\nBooking Summary:" << endl;
        cout << "===================================================" << endl;
        for (int i = 0; i < NUM_ROOMS; i++) {
            if (nights[i] > 0) {
                double roomCost = nights[i] * PRICES[i];
                double breakfastCost = breakfasts[i] * BREAKFAST_PRICE;
                cout << ROOMS[i] << " : " << nights[i]
                    << " nights (RM" << fixed << setprecision(2) << roomCost << ")";
                if (breakfasts[i] > 0) {
                    cout << " + Breakfast (RM" << breakfastCost << ")";
                }
                cout << endl;
                total += roomCost + breakfastCost;
            }
        }
        cout << "===================================================" << endl;
        if (total > 0) cout << "Total cost (before discount): RM" << total << endl;
        else cout << "No booking yet!" << endl;
        for (int i = 0; i < NUM_ROOMS; i++) {
            cout << char('a' + i) << ". Cancel " << ROOMS[i] << endl;
        }
        cout << "e. Cancel ALL" << endl;
        cout << "Choose option: ";
        cin >> choice;
        choice = tolower(choice);

        if (choice >= 'a' && choice <= 'd') {
            int index = choice - 'a';
            nights[index] = 0;
            breakfasts[index] = 0;
            cout << ROOMS[index] << " booking canceled!" << endl;
        }
        else if (choice == 'e') {
            for (int i = 0; i < NUM_ROOMS; i++) {
                nights[i] = 0;
                breakfasts[i] = 0;
            }
            cout << "All bookings canceled!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

        cout << "Cancel another booking? (Y/N): ";
        char ans = getYesNo();
        another = (ans == 'Y');
    } while (another);
}

// payment function
int payment(int nights[], int breakfasts[], int points) {
    double total = 0;
    for (int i = 0; i < NUM_ROOMS; i++) {
        total += nights[i] * PRICES[i];
        total += breakfasts[i] * BREAKFAST_PRICE;
    }
    if (total == 0) {
        system("cls");
        cout << "===========================" << endl;
        cout << "\nNo booking to pay!" << endl;
        cout << "Please try again . ";
        system("pause");
        return points;
    }

    string level = getLevel(points);
    double discountRate = getDiscount(level);
    double finalAmount = total * discountRate;
    system("cls");
    cout << "\n===== PAYMENT SUMMARY =====" << endl;
    cout << "Current Member Level : " << level << endl;
    cout << "Total before discount: RM" << total << endl;
    cout << "Discount applied (" << (1 - discountRate) * 100 << "%)" << endl;
    cout << "Final Amount to Pay : RM" << finalAmount << endl;

    // calculate the points earned
    points += (int)finalAmount;
    cout << "Points earned: " << (int)finalAmount << endl;
    cout << "New Points Balance: " << points << endl;
    cout << "New Member Level: " << getLevel(points) << endl;
    cout << "===========================" << endl;

    cout << "Please choose payment method:" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Online Banking" << endl;
    cout << "3. E-Wallet" << endl;
    cout << "Enter choice (1-3): ";
    int paymentChoice = getValidInt(1, 3);

    string username, password;

    switch (paymentChoice) {
    case 1:
        cout << "\n--- Credit Card Payment ---" << endl;
        username = getValidNumber("Enter 16-digit Credit Card Number: ", 16);
        password = getValidNumber("Enter 3-digit CVV: ", 3);
        break;
    case 2:
        cout << "\n--- Online Banking ---" << endl;
        username = getValidString("Enter Bank Account Username: ");
        password = getValidPassword("Enter Password (min 6 characters): ", 6);
        break;
    case 3:
        cout << "\n--- E-Wallet Payment ---" << endl;
        username = getValidString("Enter E-Wallet ID: ");
        password = getValidNumber("Enter 6-digit PIN: ", 6);
        break;
    }
    system("cls");
    cout << "\n Payment details received securely." << endl;
    cout << "(For security, details are not displayed here.)" << endl;
    cout << "\n========================================================" << endl;
    cout << "||||||\\   ||||  ||      ||" << endl;
    cout << "||    ||   ||   ||      ||" << endl;
    cout << "||||||||   ||   ||      ||" << endl;
    cout << "||    ||   ||   ||____  ||_" << endl;
    cout << "||||||/   ||||  || |_|" << endl;
    cout << "========================================================" << endl;
    cout << "Points earned: " << (int)finalAmount << endl;
    cout << "New Points Balance: " << points << endl;
    cout << "New Member Level: " << getLevel(points) << endl;
    cout << "===========================" << endl;
    cout << "Current Member Level\tTotal before discount\tDiscount applied\tFinal Amount to Pay  " << endl;
    cout << level << "\t\t\tRM" << total << "\t\t\t" << (1 - discountRate) * 100 << "%\t\t\tRM" << finalAmount << endl;
    // clear bookings after payment
    for (int i = 0; i < NUM_ROOMS; i++) {
        nights[i] = 0;
        breakfasts[i] = 0;
    }

    system("pause");
    return points;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}


int main() {
    int nights[NUM_ROOMS] = { 0 };
    int breakfasts[NUM_ROOMS] = { 0 };
    int points = 0;
    bool valid;
    string name;

    // enter name
    do {
        valid = true;
        system("cls");
        cout << "========================================================" << endl;
        cout << "|||||||| |||||\\   /|||||\\   /|||||\\  / \\    / \\  " << endl;
        cout << "||       ||  ||  ||     || ||     || || \\  / ||  " << endl;
        cout << "||||||   ||/|  ||     || ||     || ||  \\/  ||" << endl;
        cout << "||       ||  \\\\  ||     || ||     || ||      || " << endl;
        cout << "|||||||| ||   \\\\  \\|||||/   \\|||||/  ||      ||  " << endl;
        cout << "========================================================" << endl;
        cout << "Welcome to the Hotel Booking System!!!" << endl;
        cout << "Please enter your name: ";
        getline(cin, name);
        name = trim(name);
        if (name.empty()) {
            cout << "Name cannot be empty. Please try again." << endl;
            valid = false;
            system("pause");
        }
        else {
            for (char c : name) {
                if (isdigit((unsigned char)c)) {
                    cout << "Name can only contain letters and spaces. Please try again." << endl;
                    valid = false;
                    system("pause");
                    break;
                }
            }
        }
    } while (!valid);

    int menu;
    bool loop = true;
    while (loop) {
        system("cls");
        cout << "Welcome, " << name << "! (Points: " << points << ", Level: " << getLevel(points) << ")" << endl;
        cout << "========================================================" << endl;
        cout << "|||||||| |||||\\   /|||||\\   /|||||\\  / \\    / \\  " << endl;
        cout << "||       ||  ||  ||     || ||     || || \\  / ||  " << endl;
        cout << "||||||   ||/|  ||     || ||     || ||  \\/  ||" << endl;
        cout << "||       ||  \\\\  ||     || ||     || ||      || " << endl;
        cout << "|||||||| ||   \\\\  \\|||||/   \\|||||/  ||      ||  " << endl;
        cout << "========================================================" << endl;
        cout << "\n1. Make a booking" << endl;
        cout << "2. View my booking" << endl;
        cout << "3. Cancel booking" << endl;
        cout << "4. Payment" << endl;
        cout << "5. Member Info" << endl;
        cout << "6. Exit" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Enter choice: ";
        menu = getValidInt(1, 6);

        switch (menu) {
        case 1: makeBooking(nights, breakfasts, points); break;
        case 2: viewBooking(nights, breakfasts); break;
        case 3: cancelBooking(nights, breakfasts); break;
        case 4: points = payment(nights, breakfasts, points); break;
        case 5:
            system("cls");
            cout << "\nHi, " << name << "! (Points: " << points << ", Level: " << getLevel(points) << ")" << endl;
            cout << "========================================================" << endl;
            cout << "Member Info:" << endl;
            cout << "Current Points: " << points << endl;
            cout << "Member Level: " << getLevel(points) << endl;
            cout << "--------------------------------------------------------" << endl;
            cout << "1 point = RM 1.00" << endl;
            cout << "Point >= 300 --> Level Silver" << endl;
            cout << "Point >= 500 --> Level Gold" << endl;
            cout << "Point >= 1200 --> Level Diamond" << endl;
            cout << "========================================================" << endl;
            system("pause");
            break;
        case 6:
            cout << "========================================================" << endl;
            cout << "Thanks for using! Goodbye." << endl;
            loop = false;
            break;
        }
    }
    return 0;
}