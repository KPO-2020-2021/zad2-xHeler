#include "Examiner.h"

Examiner::Examiner() {}

Examiner::Examiner(std::string fileName) {

    std::fstream fs(fileName);
    if (!fs.good()) throw std::invalid_argument("[Error] Bad file!");

    ComplexExpression ce;
    Complex result;

    while(fs.peek() != -1) {
        fs >> ce;
        std::cout << "Podaj wynik operacji: " << ce << " = ";

        for (int i = 3; i > 0; i--) {
            try {
                std::cin >> result;
                i = 0;
            } catch (std::exception e){
                if (i == 1) throw std::invalid_argument("[Error] To much !");
                std::cout << "Wpisz jeszcze raz: " ;
            }
        }
        tasks++;
        if (ce.calculateExpression() == result) score++;
    }

    std::cout << "Koniec testu \n";
    std::cout << "Poprawne odpowiedzi: " << score << std::endl;
    std::cout << "Niepoprawne odpowiedzi: " << tasks - score << std::endl;
    std::cout << "Wynik procentowy: " << (score / tasks) * 100 << "% \n";

}