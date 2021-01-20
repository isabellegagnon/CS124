//
// Created by Isabelle Gagnon on 11/11/20.
//


#ifndef UNTITLED_CORONAVIRUS_H
#define UNTITLED_CORONAVIRUS_H

#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <cstdlib>

//Coronavirus Class
class Coronavirus {
private:
    std::string continent;
    double total_cases;
    double total_deaths;
    double total_tests_per_thousand;
    double population;

public:
    //Constructors
    Coronavirus() {
        continent = "null";
        total_cases = 0;
        total_deaths = 0;
        total_tests_per_thousand = 0;
        population = 0;
    }

    Coronavirus(std::string continent,
                double total_cases,
                double total_deaths,
                double total_tests_per_thousand,
                double population) {
        this->continent = continent;
        setTotal_cases(total_cases);
        setTotal_deaths(total_deaths);
        setTotal_tests_per_thousand(total_tests_per_thousand);
        setPopulation(population);
    }

    //Getters
    std::string getContinent() const {
        return continent;
    }

    double getTotal_cases() const {
        return total_cases;
    }

    double getTotal_deaths() const {
        return total_deaths;
    }

    double getTotal_tests_per_thousand() const {
        return total_tests_per_thousand;
    }

    double getPopulation() const {
        return population;
    }

    //Setters
    void setContinent(std::string continent) {
        this->continent = continent;
    }

    void setTotal_cases(double total_cases) {
        // check for negative (invalid) value
        if (total_cases < 0) {
            this->total_cases = 0;
        } else {
            this->total_cases = total_cases;
        }
    }

    void setTotal_deaths(double total_deaths) {
        // check for negative (invalid) value
        if (total_deaths < 0) {
            this->total_deaths = 0;
        } else {
            this->total_deaths = total_deaths;
        }
    }

    void setTotal_tests_per_thousand(double total_tests_per_thousand) {
        // check for negative (invalid) value
        if (total_tests_per_thousand < 0) {
            this->total_tests_per_thousand = 0;
        } else {
            this->total_tests_per_thousand = total_tests_per_thousand;
        }
    }

    void setPopulation(double population) {
        // check for negative (invalid) value
        if (population < 0) {
            this->population = 0;
        } else {
            this->population = population;
        }
    }


    //Read data from csv file and into the vector
    void readCovidDataFromFile(std::string filename, std::vector<Coronavirus> &coronavirus) {
        std::ifstream fIn;
        fIn.open("../" + filename);

        std::string header = "";
        if (fIn) {
            getline(fIn, header);
        }

        std::string continent = "";
        double total_cases = 0;
        double total_deaths = 0;
        double total_tests_per_thousand = 0;
        double population = 0;

        char comma = ',';
        char quote = '"';

        while (fIn && fIn.peek() != EOF) {

            //Read continent
            getline(fIn, continent, ',');


            //read total_cases
            fIn >> total_cases;
            //Check to see if stream is broken
            if (!fIn) {
                total_cases = 0;
                fIn.clear();
            }
            fIn >> comma;

            //read total_deaths
            fIn >> total_deaths;
            //Check to see if stream is broken
            if (!fIn) {
                total_deaths = 0;
                fIn.clear();
            }
            fIn >> comma;

            //read total_tests_per_thousand
            fIn >> total_tests_per_thousand;
            //Check to see if stream is broken
            if (!fIn) {
                total_tests_per_thousand = 0;
                fIn.clear();
            }
            fIn >> comma;

            //read population
            fIn >> population;
            //Check to see if stream is broken
            if (!fIn) {
                population = 0;
                fIn.clear();
            }

            //create coronavirus object and add to vector
            coronavirus.push_back(Coronavirus(continent, total_cases,
                                              total_deaths, total_tests_per_thousand, population));
        }

        fIn.close();
    }


    //Overloading
    friend bool operator == (const Coronavirus &c1, const Coronavirus &c2) {
        if (c1.getTotal_cases() == c2.getTotal_cases()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator < (const Coronavirus &c1, const Coronavirus &c2) {
        if (c1.getTotal_cases() < c2.getTotal_cases()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator > (const Coronavirus &c1, const Coronavirus &c2) {
        if (c1.getTotal_cases() > c2.getTotal_cases()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator <= (const Coronavirus &c1, const Coronavirus &c2) {
        if (c1.getTotal_cases() <= c2.getTotal_cases()) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator >= (const Coronavirus &c1, const Coronavirus &c2) {
        if (c1.getTotal_cases() >= c2.getTotal_cases()) {
            return true;
        } else {
            return false;
        }
    }

    friend std::ostream& operator << (std::ostream &o, const Coronavirus &vg) {
        o << vg.getTotal_cases() << std::endl;
        return o;
    }
};


#endif //UNTITLED_CORONAVIRUS_H
