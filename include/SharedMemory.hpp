/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** SharedMemory
*/

#ifndef SHAREDMEMORY_HPP_
#define SHAREDMEMORY_HPP_

#include <string>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "CEncapsulate.hpp"

class SharedMemory {
    public:
        SharedMemory(int size);
        ~SharedMemory();
        char *CreateSharedMemory(std::string filename, int nb, char *str);
        char *OpenSharedMemory(std::string filename, int nb, char *str);
        char *ReadSharedMemory(key_t key);
        void WriteSharedMemory(key_t key, std::string to_write);
        void DetachSharedMemory(key_t key);
        void DestroySharedMemory(char *str, int shm_id);

    protected:
    private:
        int _size;
        CEncapsulate *_fcnt;
};

#endif /* !SHAREDMEMORY_HPP_ */