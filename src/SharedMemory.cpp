/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** SharedMemory
*/

#include "../include/SharedMemory.hpp"

SharedMemory::SharedMemory(int size):_size(size)
{
    _fcnt = new CEncapsulate();
}

SharedMemory::~SharedMemory()
{
}

char *SharedMemory::CreateSharedMemory(std::string filename, int nb, char *str)
{
    key_t key = ftok(filename.c_str(), nb);
    int shm_id = shmget(key, _size, 0666 | IPC_CREAT);
    str = (char *)shmat(shm_id, (void *) 0, 0);

    _fcnt->my_memset(str, 0, _size);
    return (str);
}

char *SharedMemory::OpenSharedMemory(std::string filename, int nb, char *str)
{
    key_t key = ftok(filename.c_str(), nb);
    int shm_id = shmget(key, _size, 0666 | IPC_CREAT);
    str = (char *)shmat(shm_id, (void *) 0, 0);

    return (str);
}

char *SharedMemory::ReadSharedMemory(key_t key)
{
    int shm_id = shmget(key, _size, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shm_id, (void *) 0, 0);

    return (str);
}

void SharedMemory::WriteSharedMemory(key_t key, std::string to_write)
{
    int shm_id = shmget(key, _size, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shm_id, (void *) 0, 0);

    for (size_t i = 0; i < to_write.size(); i++) {
        str[i] = to_write.at(i);
    }
}

void SharedMemory::DetachSharedMemory(key_t key)
{
    int shm_id = shmget(key, _size, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shm_id, (void *) 0, 0);

    shmdt(str);
}

void SharedMemory::DestroySharedMemory(char *str, int shm_id)
{
    shmdt(str);
    shmctl(shm_id, IPC_RMID, NULL);
}