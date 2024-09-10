#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;

public:
    Vehicle(string make, string model, int year)
        : make(make), model(model), year(year) {}

    virtual void displayInfo() const {
        cout << "Make: " << make << "\nModel: " << model << "\nYear: " << year << endl;
    }

    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
};

class Engine {
protected:
    int horsepower;
    double displacement;

public:
    Engine(int horsepower, double displacement)
        : horsepower(horsepower), displacement(displacement) {}

    int getHorsepower() const { return horsepower; }
    double getDisplacement() const { return displacement; }
};

class Car : public virtual Vehicle, public Engine {
    int numberOfDoors;

public:
    Car(string make, string model, int year, int horsepower, double displacement, int numberOfDoors)
        : Vehicle(make, model, year), Engine(horsepower, displacement), numberOfDoors(numberOfDoors) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Horsepower: " << horsepower << "\nDisplacement: " << displacement
            << "\nNumber of Doors: " << numberOfDoors << endl;
    }

    int getNumberOfDoors() const { return numberOfDoors; }
};

class Truck : public virtual Vehicle, public Engine {
    double loadCapacity;

public:
    Truck(string make, string model, int year, int horsepower, double displacement, double loadCapacity)
        : Vehicle(make, model, year), Engine(horsepower, displacement), loadCapacity(loadCapacity) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Horsepower: " << horsepower << "\nDisplacement: " << displacement
            << "\nLoad Capacity: " << loadCapacity << " tons" << endl;
    }

    double getLoadCapacity() const { return loadCapacity; }

    double calculateFuelConsumption(double speed, double cargoWeight) const {
        return (displacement / 10.0) * (1 + (cargoWeight / loadCapacity)) * speed / 100;
    }
};

class ElectricVehicle : public virtual Vehicle {
    double batteryCapacity;
    int range;

public:
    ElectricVehicle(string make, string model, int year, double batteryCapacity, int range)
        : Vehicle(make, model, year), batteryCapacity(batteryCapacity), range(range) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Battery Capacity: " << batteryCapacity << " kWh\nRange: " << range << " km" << endl;
    }

    double getBatteryCapacity() const { return batteryCapacity; }
    int getRange() const { return range; }
};

class ElectricCar : public ElectricVehicle, public Car {
public:
    ElectricCar(string make, string model, int year, int horsepower, double displacement, int numberOfDoors, double batteryCapacity, int range)
        : Vehicle(make, model, year),
        ElectricVehicle(make, model, year, batteryCapacity, range),
        Car(make, model, year, horsepower, displacement, numberOfDoors) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Horsepower: " << getHorsepower() << "\nDisplacement: " << getDisplacement()
            << "\nNumber of Doors: " << getNumberOfDoors()
            << "\nBattery Capacity: " << getBatteryCapacity() << " kWh\nRange: " << getRange() << " km" << endl;
    }
};

int main() {
    Car car("Toyota", "Corolla", 2021, 132, 1.8, 4);
    Truck truck("Ford", "F-150", 2020, 400, 5.0, 3.5);
    ElectricVehicle ev("Tesla", "Model S", 2022, 100, 600);
    ElectricCar eCar("Tesla", "Model 3", 2023, 283, 0.0, 4, 75, 500);

    vector<const Vehicle*> vehicles = { &car, &truck, &ev, &eCar };

    for (const Vehicle* vehicle : vehicles) {
        vehicle->displayInfo();
        cout << "\n" << endl;
    }

    const Truck constTruck("Volvo", "FH16", 2021, 700, 16.1, 40);
    cout << "Fuel Consumption at 80 km/h with 20 tons of cargo: "
        << constTruck.calculateFuelConsumption(80, 20) << " liters per 100 km" << endl;
}
