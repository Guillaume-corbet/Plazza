/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** CEncapsulate
*/

#include "../include/CEncapsulate.hpp"

CEncapsulate::CEncapsulate()
{
}

CEncapsulate::~CEncapsulate()
{
}

int CEncapsulate::my_strchr(std::string str, char c)
{
    const char *sto = str.c_str();
    const char *verif = strchr(sto, c);

    if (verif == NULL)
        return (-1);
    return (verif - sto);
}

char *CEncapsulate::my_strcat(char *str1, const char *str2)
{
    char *res = strcat(str1, str2);

    return (res);
}

char *CEncapsulate::my_strcpy(char *str1, const char *str2)
{
    char *res = strcpy(str1, str2);

    return (res);
}

char *CEncapsulate::my_strdup(char *str)
{
    char *res = strdup(str);

    return (res);
}

void *CEncapsulate::my_memset(void *obj, char c, size_t size)
{
    obj = memset(obj, c, size);

    return (obj);
}

void CEncapsulate::checkDelay(struct timeval *now)
{
    gettimeofday(now, NULL);
}