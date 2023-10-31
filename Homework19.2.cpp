// Homework19.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Observers.h"

class Observable {
private:
    std::vector<std::weak_ptr<Observer>> observers_;
public:
    void AddObserver(std::weak_ptr<Observer> observer) {
        observers_.push_back(observer);
    }
    void warning(const std::string& message) const {
        for (auto observer : observers_) {
            if (auto str_ptr = observer.lock()) {
                str_ptr->onWarning(message);
            }
        }
    }
    void error(const std::string& message) const {
        for (auto observer : observers_) {
            if (auto str_ptr = observer.lock()) {
                str_ptr->onError(message);
            }
        }
    }
    void fatalError(const std::string& message) const {
        for (auto observer : observers_) {
            if (auto str_ptr = observer.lock()) {
                str_ptr->onFatalError(message);
            }
        }
    }
};

int main()
{
    std::shared_ptr<Observer> sobsW(new ObserverWarn());
    std::weak_ptr<Observer> obsW(sobsW);
    
    std::shared_ptr<Observer> sobsE(new ObserverErr());
    std::weak_ptr<Observer> obsE(sobsE);

    std::shared_ptr<Observer> sobsFE(new ObserverFatErr());
    std::weak_ptr<Observer> obsFE(sobsFE);

    Observable obsl;
    obsl.AddObserver(obsW);
    obsl.AddObserver(obsE);
    obsl.AddObserver(obsFE);
    obsl.warning("small crash");
    obsl.error("medium crash");
    obsl.fatalError("big boom");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
