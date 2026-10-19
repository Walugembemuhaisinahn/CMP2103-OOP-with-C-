#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base Class: Level 1
class Vehicle {
protected:
    string brand;
    int year;

public:
    Vehicle(string b, int y) : brand(b), year(y) {}

    // Virtual destructor for proper memory cleanup in polymorphic usage
    virtual ~Vehicle() {}

    // Virtual function for runtime polymorphism
    virtual void displayDetails() const {
        cout << "Brand: " << brand << endl;
        cout << "Year: " << year << endl;
    }

    // Getters and Setters
    string getBrand() const { return brand; }
    int getYear() const { return year; }
};

// Intermediate Class: Level 2 (Chained Inheritance)
class MotorVehicle : public Vehicle {
protected:
    string fuelType;

public:
    MotorVehicle(string b, int y, string fuel) 
        : Vehicle(b, y), fuelType(fuel) {}

    // Overriding the virtual function
    void displayDetails() const override {
        Vehicle::displayDetails(); // Call parent implementation
        cout << "Fuel Type: " << fuelType << endl;
    }

    string getFuelType() const { return fuelType; }
};

// Deeply Derived Class: Level 3 (Chained Inheritance)
class ElectricCar : public MotorVehicle {
private:
    int batteryCapacity; // in kWh

public:
    ElectricCar(string b, int y, string fuel, int battery) 
        : MotorVehicle(b, y, fuel), batteryCapacity(battery) {}

    // Overriding displayDetails at the third level of the chain
    void displayDetails() const override {
        MotorVehicle::displayDetails(); // Call intermediate implementation
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }

    int getBatteryCapacity() const { return batteryCapacity; }
};

int main() {
    // Demonstrating Polymorphism using a vector of Base Class pointers
    vector<Vehicle*> fleet;

    // Adding objects at different levels of the inheritance chain
    fleet.push_back(new Vehicle("Generic Model", 2018));
    fleet.push_back(new MotorVehicle("Toyota", 2021, "Petrol"));
    fleet.push_back(new ElectricCar("Tesla", 2023, "Electric", 85));

    cout << "=== VEHICLE FLEET DETAILS (POLYMORPHISM DEMO) ===" << endl << endl;

    // Dynamic Binding: Calling the correct displayDetails() for each object
    for (size_t i = 0; i < fleet.size(); ++i) {
        cout << "Vehicle #" << (i + 1) << ":" << endl;
        fleet[i]->displayDetails();
        cout << "-----------------------------------" << endl;
    }

    // Memory Cleanup
    for (Vehicle* v : fleet) {
        delete v;
    }
    fleet.clear();

    return 0;
}