/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** CondVar
*/

#include "../include/CondVar.hpp"

CondVar::CondVar()
{
}

CondVar::~CondVar()
{
}

void CondVar::wait(Mutex &mutex)
{
    std::mutex &mut = mutex.getLocker();
    std::unique_lock<std::mutex> locker{mut};
    _condVar.wait(locker);
}

void CondVar::wait(Mutex *mutex)
{
    std::mutex &mut = mutex->getLocker();
    std::unique_lock<std::mutex> locker{mut};
    _condVar.wait(locker);
}

void CondVar::notify_all()
{
    _condVar.notify_all();
}

void CondVar::notify_one()
{
    _condVar.notify_one();
}