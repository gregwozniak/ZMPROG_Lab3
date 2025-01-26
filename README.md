# ZMPROG_Lab3
dwa programy wykonane wg instrukcji Lab3
ZMP_Lab3_zadanie1.cpp - realizuje wzorzec adapter
zasada działania:
- robot startuje z pozycji (0,0)
- program prosi o podanie dwóch współrzędnych X i Y oddzielonych spacją
- robot przesuwa się na wskazaną pozycję i informuje o niej w postaci współrzędnych biegunowych (kąt i odległość od środka układu)
- każde kolejne przesunięcie realizowane jest w stosunku do poprzedniej pozycji
- współrzędne biegunowe podawane są zawsze względem środka układu (pozycji startowej) czyli punktu (0,0)

ZMP_Lab3_zadanie1.cpp - realizuje wzorzec dekorator
zasada działania:
- metoda operacja informuje o tym, że robot porusza się
- program umożliwia dodanie oraz usunięcie jednej z trzech funkcji - kamera, czujnik, dzwiek
- te samą funkcję można dodać wielokrotnie
- dostepne są trzy polecenia - dodaj, usun i zakoncz
- polecenia dodaj i usun przyjmuja parametry w postaci nazwy wyposazenia do dodania
