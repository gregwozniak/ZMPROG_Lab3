// Zadanie 1: Wzorzec Adapter
#include <iostream>
#include <cmath>
//#include <string>

// Klasa RobotStary
class RobotStary {
public:
    virtual void idzDo(double x, double y) = 0;
};

// Klasa RobotNowy
class RobotNowy {
public:
    void idzDo(double kat, double odleglosc) {
        std::cout << "RobotNowy: Przemieszczam sie do punktu (" << kat << " stopni, " << odleglosc << " jednostek) w ukladzie biegunowym.\n";
    }
};

// Klasa AdapterRobota
class AdapterRobota : public RobotStary {
private:
    RobotNowy* robotNowy;
    double currentX = 0.0;
    double currentY = 0.0;

    // Funkcja do konwersji wspolrzednych
    void przeliczNaBiegunowe(double x, double y, double& kat, double& odleglosc) {
        odleglosc = std::sqrt(x * x + y * y);
        kat = std::atan2(y, x) * 180 / M_PI; // Konwersja na stopnie
    }

public:
    AdapterRobota(RobotNowy* nowyRobot) : robotNowy(nowyRobot) {}

    void idzDo(double x, double y) override {
        double deltaX = x - currentX;
        double deltaY = y - currentY;
        double kat, odleglosc;
        przeliczNaBiegunowe(deltaX, deltaY, kat, odleglosc);
        robotNowy->idzDo(kat, odleglosc);
        currentX = x;
        currentY = y;
    }
};

// Funkcja testujaca
void testAdapter() {
    RobotNowy robotNowy;
    AdapterRobota adapter(&robotNowy);

    std::cout << "Test adaptera:\n";
}

// Funkcja obslugujaca wpisywanie wspolrzednych
void interactWithAdapter() {
    RobotNowy robotNowy;
    AdapterRobota adapter(&robotNowy);

    double x, y;
    std::cout << "Wpisz wspolrzedne prostokatne X Y oddzielona spacja: ";
    while (std::cin >> x >> y) {
        adapter.idzDo(x, y);
        std::cout << "Wpisz kolejne wspólrzedne prostokatne X Y oddzielone spacja: ";
    }
    std::cout << "Koniec interakcji z robotem.\n";
}

int main() {
    testAdapter();
    interactWithAdapter();
    return 0;
}

