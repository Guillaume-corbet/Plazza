/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <map>
#include <vector>
#include <iostream>
#include "../interfaces/IMutex.hpp"

class Mutex: public IMutex<std::mutex> {
    public:
        Mutex();
        ~Mutex();
        std::mutex &getLocker();
        void Lock();
        void Unlock();
        bool isLock();

    protected:
    private:
        std::mutex _locker;
};

#endif /* !MUTEX_HPP_ */