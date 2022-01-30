/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** IThreads
*/

#ifndef ITHREADS_HPP_
#define ITHREADS_HPP_

template <class T, typename Q>
class IThreads {
    public:
        virtual ~IThreads() = default;
        virtual void create() = 0;
        virtual void run() = 0;

    protected:
        T *_lock;
        Q *_work;
};

#endif /* !ITHREADS_HPP_ */