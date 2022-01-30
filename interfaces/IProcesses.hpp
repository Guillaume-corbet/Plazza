/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IProcesses
*/

#ifndef IPROCESSES_HPP_
#define IPROCESSES_HPP_

template <typename T>
class IProcesses {
    public:
        virtual ~IProcesses() = default;
        virtual T my_fork() = 0;

    protected:
    private:
};

#endif /* !IPROCESSES_HPP_ */