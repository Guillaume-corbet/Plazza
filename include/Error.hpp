/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <string>

class Error: public std::exception {
    public:
        Error(std::string const &message);
        ~Error();

    protected:
    private:
        std::string _message;
};

#endif /* !ERROR_HPP_ */