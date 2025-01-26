// Zadanie 2: Wzorzec Adapter
#include <iostream>
#include <memory>
//#include <string>

// Klasa bazowa Robot
class Robot {
public:
    virtual ~Robot() = default;
    virtual void operacja() const = 0;
    virtual std::shared_ptr<Robot> usunDekorator(const std::string& nazwa) {
        std::cout << "Nie mozna usunac podstawowego robota ani funkcji, ktorej nie ma.\n";
        return nullptr;
    }
    virtual std::string pobierzNazwe() const {
        return "RobotPodstawowy";
    }
};

// Klasa RobotPodstawowy (konkretny robot)
class RobotPodstawowy : public Robot {
public:
    void operacja() const override {
        std::cout << "Robot: porusza sie.\n";
    }
};

// Klasa abstrakcyjna RobotDekorator
class RobotDekorator : public Robot {
protected:
    std::shared_ptr<Robot> robot; // Wskazanie na dekorowanego robota

public:
    RobotDekorator(std::shared_ptr<Robot> robot) : robot(robot) {}
    virtual ~RobotDekorator() = default;

    virtual void operacja() const override {
        robot->operacja();
    }

    virtual std::shared_ptr<Robot> usunDekorator(const std::string& nazwa) override {
        if (pobierzNazwe() == nazwa) {
            return robot; // zwraca aktualny stan robota
        } else {
            robot = robot->usunDekorator(nazwa); // Usuwanie wskazanej funkcji
            return robot;
        }
    }
};

// Klasa dekoratora dodajaca kamere
class RobotZKamera : public RobotDekorator {
public:
    RobotZKamera(std::shared_ptr<Robot> robot) : RobotDekorator(robot) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Wyposazenie: Robot posiada kamere.\n";
    }
    std::string pobierzNazwe() const override {
        return "kamera";
    }
};

// Klasa dekoratora dodajaca czujnik temperatury
class RobotZCzujnikiemTemperatury : public RobotDekorator {
public:
    RobotZCzujnikiemTemperatury(std::shared_ptr<Robot> robot) : RobotDekorator(robot) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Wyposazenie: Robot posiada czujnik temperatury.\n";
    }
    std::string pobierzNazwe() const override {
        return "czujnik";
    }
};

// Klasa dekoratora dodajaca system dzwiekowy
class RobotZDzwiekiem : public RobotDekorator {
public:
    RobotZDzwiekiem(std::shared_ptr<Robot> robot) : RobotDekorator(robot) {}
    void operacja() const override {
        RobotDekorator::operacja();
        std::cout << "Wyposazenie: Robot posiada system dzwiekowy.\n";
    }
    std::string pobierzNazwe() const override {
        return "dzwiek";
    }
};

// Funkcja interakcji z uzytkownikiem - dodawanie i usuwanie wyposazenia za pomoca polecen
void dekorujRobota() {
    std::shared_ptr<Robot> robot = std::make_shared<RobotPodstawowy>();
    std::cout << "Robot podstawowy zostal stworzony.\n";

    std::string polecenie, parametr;
    while (true) {
        std::cout << "\nAktualny robot:\n";
        robot->operacja();

        std::cout << "\nDostepne polecenia:\n"
                  << "1. dodaj [nazwa_funkcji] (kamera, czujnik, dzwiek)\n"
                  << "2. usun [nazwa_funkcji]\n"
                  << "3. zakoncz\n"
                  << "Wpisz polecenie: ";
        std::cin >> polecenie;

        if (polecenie == "dodaj") {
            std::cin >> parametr;
            if (parametr == "kamera") {
                robot = std::make_shared<RobotZKamera>(robot);
                std::cout << "Dodano kamere do robota.\n";
            } else if (parametr == "czujnik") {
                robot = std::make_shared<RobotZCzujnikiemTemperatury>(robot);
                std::cout << "Dodano czujnik temperatury do robota.\n";
            } else if (parametr == "dzwiek") {
                robot = std::make_shared<RobotZDzwiekiem>(robot);
                std::cout << "Dodano system dzwiekowy do robota.\n";
            } else {
                std::cout << "Nieznana funkcja: " << parametr << ". Sprobuj ponownie.\n";
            }
        } else if (polecenie == "usun") {
            std::cin >> parametr;
            auto nowyRobot = robot->usunDekorator(parametr);
            if (nowyRobot) {
                robot = nowyRobot;
                std::cout << "Usunieto funkcje: " << parametr << " z robota.\n";
            }
        } else if (polecenie == "zakoncz") {
            std::cout << "Zakonczono dekorowanie robota.\n";
            break;
        } else {
            std::cout << "Nieznane polecenie. Sprobuj ponownie.\n";
        }
    }
}

int main() {
    dekorujRobota();
    return 0;
}
