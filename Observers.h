#pragma once
#include <iostream>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {};
    virtual void onError(const std::string& message) {};
    virtual void onFatalError(const std::string& message) {};
};

class ObserverWarn : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "\nWarning! Warning! " << message << std::endl;
    }
};

class ObserverErr : public Observer {
public:
    void onError(const std::string& message) {
        std::ofstream errfile;
        errfile.open("ErrFile.txt");
        errfile << "Error! Error! " << message << std::endl;
        errfile.close();
    }
};

class ObserverFatErr : public Observer {
public:
    void onFatalError(const std::string& message) {
        std::ofstream fatErrfile;
        fatErrfile.open("fatErrFile.txt");
        fatErrfile << "Fatal Error! Fatal Error! " << message << std::endl;
        fatErrfile.close();
        std::cout << "\nFatal Error! Fatal Error! " << message << std::endl;
    }
};