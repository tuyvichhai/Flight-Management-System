#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// =================================================================
// 1. DATA STRUCTURES & MODELS
// =================================================================

// Structure for Flight
struct Flight {
    string flightCode;
    string origin;
    string destination;
    string date;
    string time;
    string status; // "Scheduled", "Delayed", "Cancelled"
    int totalSeats = 60;
    int bookedSeats = 0;
};

// Structure for Passenger
struct Passenger {
    string id;
    string name;
    string passport;
    string phone;
    vector<string> flightHistory;
};

// Structure for Booking
struct Booking {
    string referenceCode; 
    string passengerName; 
    string flightNumber;  
    string bookingDate;   
    string status; // "Active", "Cancelled"
};

// Structure for Seat
struct Seat {
    string seatNumber;
    string seatClass; // "Business" or "Economy"
    bool isBooked;
};

// Structure for Payment
struct Payment {
    string paymentID;
    string bookingID;
    string passengerName;
    double amount;
    string method;
    string status;
};

// Structure for E-Ticket
struct ETicket {
    string ticketID;
    string bookingID;
    string passengerName;
    string flightNo;
    string from;
    string to;
    string date;
    string time;
    string seat;
};

// =================================================================
// 2. GLOBAL DATA STORAGE
// =================================================================
vector<Flight> flights = {
    {"ZA101", "Phnom Penh", "Bangkok", "2026-10-15", "08:30 AM", "Scheduled", 60, 12},
    {"ZA102", "Phnom Penh", "Singapore", "2026-10-16", "02:00 PM", "Scheduled", 60, 25}
};

vector<Passenger> passengers = {
    {"P001", "Sok Dara", "N123456", "012345678", {"ZA101"}}
};

vector<Booking> bookingList = {
    {"BKM101", "Sok Dara", "ZA101", "2026-09-12", "Active"},
    {"BKM102", "Chan Srey", "ZA102", "2026-09-15", "Active"}
};

vector<Seat> seats = {
    {"1A", "Business", false},
    {"1B", "Business", false},
    {"2A", "Economy",  false},
    {"2B", "Economy",  false}
};

vector<Payment> payments;
vector<ETicket> tickets;

// =================================================================
// 3. FUNCTION DECLARATIONS
// =================================================================

// Menus
void showMainMenu();
void flightManagementMenu();
void passengerManagementMenu();
void bookingManagementMenu();
void seatManagementMenu();
void paymentManagementMenu();
void reportsMenu();

// Module 1: Flight Functions
void viewAllFlights();
void searchFlights();
void addNewFlight();
void editFlightSchedule();
void updateFlightStatus();

// Module 2: Passenger Functions
void viewAllPassengers();
void registerPassenger();
void searchPassengerByPassport();
void viewPassengerHistory();

// Module 3: Booking Functions
void createNewBooking();
void viewAllActiveBookings();
void searchBookingByReferenceCode();
void modifyBookingDatesOrFlight();
void cancelBooking();

// Module 4: Seat Functions
void traverseSeats();
void searchSeat();
void insertSeat();
void deleteSeat();
void updateSeat();

// Module 5: Payment & E-Ticketing Functions
void processPayment();
void generateETicket();
void viewPaymentHistory();
string generatePaymentID();
string generateTicketID();

// Module 6: Reports & Analytics Functions
void dailyMonthlyRevenueReport();
void flightOccupancyRate();
void popularDestinationsReport();

// =================================================================
// 4. MAIN FUNCTION
// =================================================================
int main() {
    int choice;
    do {
        showMainMenu();
        cout << "Select an option (0-6): ";
        cin >> choice;

        switch (choice) {
            case 1: flightManagementMenu(); break;
            case 2: passengerManagementMenu(); break;
            case 3: bookingManagementMenu(); break;
            case 4: seatManagementMenu(); break;
            case 5: paymentManagementMenu(); break;
            case 6: reportsMenu(); break;
            case 0:
                cout << "\nThank you! You have exited the system successfully.\n";
                break;
            default:
                cout << "\nInvalid selection! Please choose a number between 0 and 6.\n";
        }
    } while (choice != 0);

    return 0;
}

// =================================================================
// MAIN MENU
// =================================================================
void showMainMenu() {
    cout << "\n==================== MAIN MENU ====================\n";
    cout << "[1] Flight Management\n";
    cout << "[2] Passenger Management\n";
    cout << "[3] Booking System\n";
    cout << "[4] Seat Selection & Allocation\n";
    cout << "[5] Payment & E-Ticketing\n";
    cout << "[6] Reports & Analytics\n";
    cout << "[0] Exit System\n";
    cout << "===================================================\n";
}

// =================================================================
// [1] FLIGHT MANAGEMENT MODULE
// =================================================================
void flightManagementMenu() {
    int subChoice;
    do {
        cout << "\n--- [1] Flight Management ---\n";
        cout << "[1.1] View All Flights\n";
        cout << "[1.2] Search Flights\n";
        cout << "[1.3] Add New Flight\n";
        cout << "[1.4] Edit Flight Schedule\n";
        cout << "[1.5] Cancel/Update Flight Status\n";
        cout << "[0]   Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1: viewAllFlights(); break;
            case 2: searchFlights(); break;
            case 3: addNewFlight(); break;
            case 4: editFlightSchedule(); break;
            case 5: updateFlightStatus(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (subChoice != 0);
}

void viewAllFlights() {
    cout << "\n--- All Flight List ---\n";
    if (flights.empty()) {
        cout << "No flight records found.\n";
        return;
    }
    cout << left << setw(10) << "Code" << setw(15) << "Origin" << setw(15) << "Destination" 
         << setw(15) << "Date" << setw(12) << "Time" << setw(12) << "Status" << endl;
    cout << string(80, '-') << endl;

    for (const auto& f : flights) {
        cout << left << setw(10) << f.flightCode << setw(15) << f.origin << setw(15) << f.destination 
             << setw(15) << f.date << setw(12) << f.time << setw(12) << f.status << endl;
    }
}

void searchFlights() {
    string dest;
    cout << "\nEnter destination to search: ";
    cin.ignore();
    getline(cin, dest);

    bool found = false;
    cout << "\nSearch Results for: " << dest << endl;
    for (const auto& f : flights) {
        if (f.destination == dest) {
            cout << "- Code: " << f.flightCode << " | From: " << f.origin 
                 << " | Date: " << f.date << " | Time: " << f.time << " | Status: " << f.status << endl;
            found = true;
        }
    }
    if (!found) cout << "No flights found traveling to " << dest << ".\n";
}

void addNewFlight() {
    Flight newF;
    cout << "\n--- Add New Flight ---\n";
    cout << "Enter Flight Code (e.g. ZA103): "; cin >> newF.flightCode;
    cout << "Enter Origin: "; cin.ignore(); getline(cin, newF.origin);
    cout << "Enter Destination: "; getline(cin, newF.destination);
    cout << "Enter Date (YYYY-MM-DD): "; cin >> newF.date;
    cout << "Enter Time (e.g. 10:30 AM): "; cin.ignore(); getline(cin, newF.time);
    newF.status = "Scheduled";

    flights.push_back(newF);
    cout << "=> New flight added successfully!\n";
}

void editFlightSchedule() {
    string code;
    cout << "\nEnter Flight Code to edit: ";
    cin >> code;

    for (auto& f : flights) {
        if (f.flightCode == code) {
            cout << "Enter new date (YYYY-MM-DD): "; cin >> f.date;
            cout << "Enter new time: "; cin.ignore(); getline(cin, f.time);
            cout << "=> Schedule updated successfully!\n";
            return;
        }
    }
    cout << "Flight code not found!\n";
}

void updateFlightStatus() {
    string code;
    cout << "\nEnter Flight Code: ";
    cin >> code;

    for (auto& f : flights) {
        if (f.flightCode == code) {
            cout << "Select new Status (1: Scheduled, 2: Delayed, 3: Cancelled): ";
            int st;
            cin >> st;
            if (st == 1) f.status = "Scheduled";
            else if (st == 2) f.status = "Delayed";
            else if (st == 3) f.status = "Cancelled";
            else { cout << "Invalid choice!\n"; return; }
            
            cout << "=> Status updated successfully!\n";
            return;
        }
    }
    cout << "Flight code not found!\n";
}

// =================================================================
// [2] PASSENGER MANAGEMENT MODULE
// =================================================================
void passengerManagementMenu() {
    int subChoice;
    do {
        cout << "\n--- [2] Passenger Management ---\n";
        cout << "[2.1] View All Passengers\n";
        cout << "[2.2] Register New Passenger\n";
        cout << "[2.3] Search Passenger by Passport/ID\n";
        cout << "[2.4] View Passenger Flight History\n";
        cout << "[0]   Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1: viewAllPassengers(); break;
            case 2: registerPassenger(); break;
            case 3: searchPassengerByPassport(); break;
            case 4: viewPassengerHistory(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (subChoice != 0);
}

void viewAllPassengers() {
    cout << "\n--- All Passengers List ---\n";
    if (passengers.empty()) {
        cout << "No passenger records found.\n";
        return;
    }
    cout << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Passport" << setw(15) << "Phone" << endl;
    cout << string(60, '-') << endl;

    for (const auto& p : passengers) {
        cout << left << setw(8) << p.id << setw(20) << p.name << setw(15) << p.passport << setw(15) << p.phone << endl;
    }
}

void registerPassenger() {
    Passenger newP;
    cout << "\n--- Register New Passenger ---\n";
    cout << "Enter Passenger ID: "; cin >> newP.id;
    cout << "Enter Name: "; cin.ignore(); getline(cin, newP.name);
    cout << "Enter Passport Number: "; cin >> newP.passport;
    cout << "Enter Phone Number: "; cin >> newP.phone;

    passengers.push_back(newP);
    cout << "=> New passenger registered successfully!\n";
}

void searchPassengerByPassport() {
    string key;
    cout << "\nEnter Passport Number or Passenger ID: ";
    cin >> key;

    bool found = false;
    for (const auto& p : passengers) {
        if (p.passport == key || p.id == key) {
            cout << "\n[Passenger Details Found]\n";
            cout << "ID: " << p.id << endl;
            cout << "Name: " << p.name << endl;
            cout << "Passport: " << p.passport << endl;
            cout << "Phone: " << p.phone << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "No passenger found with this Passport/ID.\n";
}

void viewPassengerHistory() {
    string id;
    cout << "\nEnter Passenger ID to view history: ";
    cin >> id;

    for (const auto& p : passengers) {
        if (p.id == id) {
            cout << "\nFlight history for " << p.name << ":\n";
            if (p.flightHistory.empty()) {
                cout << "- No flight history available.\n";
            } else {
                for (const auto& fCode : p.flightHistory) {
                    cout << "- Flight: " << fCode << endl;
                }
            }
            return;
        }
    }
    cout << "Passenger ID not found!\n";
}

// =================================================================
// [3] BOOKING SYSTEM MODULE
// =================================================================
void bookingManagementMenu() {
    int subChoice;
    while (true) {
        cout << "\n============================================\n";
        cout << "         [3] Booking System                 \n";
        cout << "============================================\n";
        cout << "[3.1] Create New Booking\n";
        cout << "[3.2] View All Active Bookings\n";
        cout << "[3.3] Search Booking by Reference Code\n";
        cout << "[3.4] Modify Booking Dates/Flight\n";
        cout << "[3.5] Cancel Booking\n";
        cout << "[0] Back to Main Menu\n";
        cout << "--------------------------------------------\n";
        cout << "Select a submenu option: ";
        cin >> subChoice;

        if (subChoice == 0) break;

        switch (subChoice) {
            case 1: createNewBooking(); break;
            case 2: viewAllActiveBookings(); break;
            case 3: searchBookingByReferenceCode(); break;
            case 4: modifyBookingDatesOrFlight(); break;
            case 5: cancelBooking(); break;
            default: cout << "\nInvalid choice! Please select again.\n";
        }
    }
}

void createNewBooking() {
    Booking newBooking;
    cout << "\n--- [3.1] Create New Booking ---\n";
    cout << "Enter Reference Code: "; cin >> newBooking.referenceCode;
    cin.ignore(); 
    cout << "Enter Passenger Name: "; getline(cin, newBooking.passengerName);
    cout << "Enter Flight Number: "; cin >> newBooking.flightNumber;
    cout << "Enter Date (YYYY-MM-DD): "; cin >> newBooking.bookingDate;
    newBooking.status = "Active"; 

    bookingList.push_back(newBooking);
    cout << "\nBooking created successfully!\n";
}

void viewAllActiveBookings() {
    cout << "\n--- [3.2] Active Bookings List ---\n";
    bool hasActive = false;
    
    for (const auto& b : bookingList) {
        if (b.status == "Active") {
            cout << "-----------------------------------------\n";
            cout << "Reference Code: " << b.referenceCode << endl;
            cout << "Passenger Name: " << b.passengerName << endl;
            cout << "Flight Number : " << b.flightNumber << endl;
            cout << "Booking Date  : " << b.bookingDate << endl;
            cout << "Status        : " << b.status << endl;
            hasActive = true;
        }
    }
    if (!hasActive) {
        cout << "No active booking records found.\n";
    }
    cout << "-----------------------------------------\n";
}

void searchBookingByReferenceCode() {
    string searchCode;
    cout << "\n--- [3.3] Search Booking by Reference Code ---\n";
    cout << "Enter Reference Code: "; cin >> searchCode;
    
    bool found = false;
    for (const auto& b : bookingList) {
        if (b.referenceCode == searchCode) {
            cout << "\nBooking Details Found:\n";
            cout << "Passenger Name: " << b.passengerName << "\nFlight Number : " << b.flightNumber 
                 << "\nBooking Date  : " << b.bookingDate << "\nStatus        : " << b.status << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "No booking records found with Reference Code " << searchCode << ".\n";
}

void modifyBookingDatesOrFlight() {
    string searchCode;
    cout << "\n--- [3.4] Modify Booking Dates/Flight ---\n";
    cout << "Enter Reference Code to modify: "; cin >> searchCode;
    
    for (auto& b : bookingList) {
        if (b.referenceCode == searchCode && b.status == "Active") {
            cout << "\nCurrent Details -> Flight: " << b.flightNumber << " | Date: " << b.bookingDate << endl;
            cout << "Enter New Flight Number: "; cin >> b.flightNumber;
            cout << "Enter New Date (YYYY-MM-DD): "; cin >> b.bookingDate;
            cout << "\nBooking updated successfully!\n";
            return;
        }
    }
    cout << "Booking code not found or booking has already been cancelled.\n";
}

void cancelBooking() {
    string searchCode;
    cout << "\n--- [3.5] Cancel Booking ---\n";
    cout << "Enter Reference Code to cancel: "; cin >> searchCode;
    
    for (auto& b : bookingList) {
        if (b.referenceCode == searchCode) {
            if (b.status == "Cancelled") {
                cout << "This booking is already cancelled.\n";
                return;
            }
            b.status = "Cancelled";
            cout << "\nBooking cancelled successfully!\n";
            return;
        }
    }
    cout << "Reference code not found.\n";
}

// =================================================================
// [4] SEAT SELECTION & ALLOCATION MODULE
// =================================================================
void seatManagementMenu() {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << " [4] Seat Selection & Allocation\n";
        cout << "========================================\n";
        cout << "1. Traversal (View All Seats)\n";
        cout << "2. Search Seat\n";
        cout << "3. Insertion (Add Seat)\n";
        cout << "4. Deletion (Remove Seat)\n";
        cout << "5. Update (Book/Unbook)\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: traverseSeats(); break;
            case 2: searchSeat(); break;
            case 3: insertSeat(); break;
            case 4: deleteSeat(); break;
            case 5: updateSeat(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 0);
}

void traverseSeats() {
    cout << "\n--- ALL SEATS (Traversal) ---\n";
    for (const auto& seat : seats) {
        cout << "Seat " << seat.seatNumber << " | Class: " << seat.seatClass 
             << " | Status: " << (seat.isBooked ? "Booked" : "Available") << "\n";
    }
}

void searchSeat() {
    string target;
    cout << "\nEnter seat number to search: ";
    cin >> target;

    for (size_t i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == target) {
            cout << "Found! Seat " << seats[i].seatNumber << " (" << seats[i].seatClass 
                 << ") at index " << i << "\n";
            return;
        }
    }
    cout << "Seat not found.\n";
}

void insertSeat() {
    Seat newSeat;
    cout << "\nEnter new seat number (e.g., 3A): ";
    cin >> newSeat.seatNumber;
    cout << "Enter class (Business/Economy): ";
    cin >> newSeat.seatClass;
    newSeat.isBooked = false;

    seats.push_back(newSeat);
    cout << "Seat " << newSeat.seatNumber << " added successfully!\n";
}

void deleteSeat() {
    string target;
    cout << "\nEnter seat number to delete: ";
    cin >> target;

    for (auto it = seats.begin(); it != seats.end(); ++it) {
        if (it->seatNumber == target) {
            seats.erase(it);
            cout << "Seat " << target << " deleted successfully!\n";
            return;
        }
    }
    cout << "Seat not found.\n";
}

void updateSeat() {
    string target;
    cout << "\nEnter seat number to update booking status: ";
    cin >> target;

    for (auto& seat : seats) {
        if (seat.seatNumber == target) {
            seat.isBooked = !seat.isBooked;
            cout << "Seat " << target << " updated! New status: " 
                 << (seat.isBooked ? "Booked" : "Available") << "\n";
            return;
        }
    }
    cout << "Seat not found.\n";
}

// =================================================================
// [5] PAYMENT & E-TICKETING MODULE
// =================================================================
void paymentManagementMenu() {
    int choice;
    do {
        cout << "\n====================================\n";
        cout << "   [5] PAYMENT & E-TICKETING        \n";
        cout << "====================================\n";
        cout << "1. Process Booking Payment\n";
        cout << "2. Generate E-Ticket / Boarding Pass\n";
        cout << "3. View Payment History\n";
        cout << "0. Back to Main Menu\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: processPayment(); break;
            case 2: generateETicket(); break;
            case 3: viewPaymentHistory(); break;
            case 0: cout << "Returning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 0);
}

string generatePaymentID() {
    return "PAY" + to_string(payments.size() + 1);
}

string generateTicketID() {
    return "TKT" + to_string(tickets.size() + 1);
}

void processPayment() {
    cout << "\n====================================\n";
    cout << "        PROCESS BOOKING PAYMENT     \n";
    cout << "====================================\n";

    Payment p;
    int methodChoice;

    cout << "Enter Booking ID: ";
    cin >> p.bookingID;
    cin.ignore();

    cout << "Enter Passenger Name: ";
    getline(cin, p.passengerName);

    cout << "Enter Ticket Price ($): ";
    cin >> p.amount;

    cout << "\nSelect Payment Method:\n";
    cout << "1. Cash\n2. ABA Pay\n3. Credit/Debit Card\n4. Wing\n";
    cout << "Choose: ";
    cin >> methodChoice;

    switch (methodChoice) {
        case 1: p.method = "Cash"; break;
        case 2: p.method = "ABA Pay"; break;
        case 3: p.method = "Credit/Debit Card"; break;
        case 4: p.method = "Wing"; break;
        default: cout << "Invalid payment method!\n"; return;
    }

    p.paymentID = generatePaymentID();
    p.status = "PAID";
    payments.push_back(p);

    cout << "\nPayment Successful!\n";
    cout << "Payment ID : " << p.paymentID << endl;
    cout << "Booking ID : " << p.bookingID << endl;
    cout << "Amount     : $" << fixed << setprecision(2) << p.amount << endl;
    cout << "Method     : " << p.method << endl;
    cout << "Status     : " << p.status << endl;
}

void generateETicket() {
    cout << "\n====================================\n";
    cout << "        GENERATE E-TICKET           \n";
    cout << "====================================\n";

    ETicket t;
    cout << "Enter Booking ID: "; cin >> t.bookingID;
    cin.ignore();
    cout << "Passenger Name: "; getline(cin, t.passengerName);
    cout << "Flight Number: "; getline(cin, t.flightNo);
    cout << "From: "; getline(cin, t.from);
    cout << "To: "; getline(cin, t.to);
    cout << "Flight Date: "; getline(cin, t.date);
    cout << "Flight Time: "; getline(cin, t.time);
    cout << "Seat Number: "; getline(cin, t.seat);

    t.ticketID = generateTicketID();
    tickets.push_back(t);

    cout << "\n====================================\n";
    cout << "          E-TICKET / BOARDING PASS  \n";
    cout << "====================================\n";
    cout << "Ticket ID      : " << t.ticketID << endl;
    cout << "Booking ID     : " << t.bookingID << endl;
    cout << "Passenger      : " << t.passengerName << endl;
    cout << "Flight         : " << t.flightNo << endl;
    cout << "From           : " << t.from << endl;
    cout << "To             : " << t.to << endl;
    cout << "Date           : " << t.date << endl;
    cout << "Time           : " << t.time << endl;
    cout << "Seat           : " << t.seat << endl;
    cout << "Status         : CONFIRMED\n";
    cout << "====================================\n";
}

void viewPaymentHistory() {
    cout << "\n====================================\n";
    cout << "           PAYMENT HISTORY          \n";
    cout << "====================================\n";

    if (payments.empty()) {
        cout << "No payment history found.\n";
        return;
    }

    for (size_t i = 0; i < payments.size(); i++) {
        cout << "\nPayment #" << i + 1 << endl;
        cout << "Payment ID : " << payments[i].paymentID << endl;
        cout << "Booking ID : " << payments[i].bookingID << endl;
        cout << "Passenger  : " << payments[i].passengerName << endl;
        cout << "Amount     : $" << fixed << setprecision(2) << payments[i].amount << endl;
        cout << "Method     : " << payments[i].method << endl;
        cout << "Status     : " << payments[i].status << endl;
        cout << "------------------------------------\n";
    }
}

// =================================================================
// [6] REPORTS & ANALYTICS MODULE
// =================================================================
void reportsMenu() {
    int choice;
    do {
        cout << "\n=====================================\n";
        cout << "   [6] Reports & Analytics           \n";
        cout << "=====================================\n";
        cout << "[6.1] Daily/Monthly Revenue Report\n";
        cout << "[6.2] Flight Occupancy Rate\n";
        cout << "[6.3] Popular Destinations Report\n";
        cout << "[0] Back to Main Menu\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dailyMonthlyRevenueReport(); break;
            case 2: flightOccupancyRate(); break;
            case 3: popularDestinationsReport(); break;
            case 0: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void dailyMonthlyRevenueReport() {
    cout << "\n--- Daily/Monthly Revenue Report ---\n";
    double totalRevenue = 0;
    for (const auto& p : payments) {
        if (p.status == "PAID") {
            totalRevenue += p.amount;
        }
    }
    cout << "Total Transactions : " << payments.size() << endl;
    cout << "Total Revenue Collected : $" << fixed << setprecision(2) << totalRevenue << endl;
}

void flightOccupancyRate() {
    cout << "\n--- Flight Occupancy Rate ---\n";
    if (flights.empty()) {
        cout << "No flight data available.\n";
        return;
    }
    for (const auto& f : flights) {
        double rate = (static_cast<double>(f.bookedSeats) / f.totalSeats) * 100.0;
        cout << "Flight: " << f.flightCode << " | Dest: " << f.destination 
             << " | Booked: " << f.bookedSeats << "/" << f.totalSeats 
             << " | Occupancy Rate: " << fixed << setprecision(2) << rate << "%\n";
    }
}

void popularDestinationsReport() {
    cout << "\n--- Popular Destinations Report ---\n";
    if (bookingList.empty()) {
        cout << "No booking data available.\n";
        return;
    }
    
    for (const auto& f : flights) {
        int count = 0;
        for (const auto& b : bookingList) {
            if (b.flightNumber == f.flightCode && b.status == "Active") {
                count++;
            }
        }
        cout << "Destination: " << f.destination << " (Flight " << f.flightCode << ") - Active Bookings: " << count << endl;
    }
}