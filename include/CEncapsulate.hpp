/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** CEncapsulate
*/

#ifndef CENCAPSULATE_HPP_
#define CENCAPSULATE_HPP_

#include <string>
#include <cstring>
#include <sys/time.h>

class CEncapsulate {
    public:
        CEncapsulate();
        ~CEncapsulate();
        int my_strchr(std::string str, char c);
        char *my_strcat(char *str1, const char *str2);
        char *my_strcpy(char *str1, const char *str2);
        char *my_strdup(char *str);
        void *my_memset(void *obj, char c, size_t size);
        void checkDelay(struct timeval *now);

    protected:
    private:
};

#endif /* !CENCAPSULATE_HPP_ */