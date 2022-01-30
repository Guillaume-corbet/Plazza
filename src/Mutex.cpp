/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Mutex
*/

#include "../include/Mutex.hpp"

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

std::mutex &Mutex::getLocker()
{
    return (_locker);
}

void Mutex::Lock()
{
    _locker.lock();
}

void Mutex::Unlock()
{
    _locker.unlock();
}

bool Mutex::isLock()
{
   return (_locker.try_lock());
}