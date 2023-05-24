#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **env;
} vars_t;

void add_key(vars_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

void add_key(vars_t *vars) {
    unsigned int i = 0;
    while (vars->env[i] != NULL) {
        i++;
    }
    char **newenv = realloc(vars->env, sizeof(char *) * (i + 2));
    if (newenv == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    vars->env = newenv;
    vars->env[i] = add_value(vars->av[1], vars->av[2]);
    vars->env[i + 1] = NULL;
}

char **find_key(char **env, char *key) {
    unsigned int i = 0;
    unsigned int len = strlen(key);
    while (env[i] != NULL) {
        if (strncmp(key, env[i], len) == 0 && env[i][len] == '=') {
            return &env[i];
        }
        i++;
    }
    return NULL;
}

char *add_value(char *key, char *value) {
    size_t len1 = strlen(key);
    size_t len2 = strlen(value);
    char *new = malloc(len1 + len2 + 2);
    if (new == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(new, key);
    new[len1] = '=';
    strcpy(new + len1 + 1, value);
    return new;
}

int _atoi(char *str) {
    int num = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return -1;
        }
        num = num * 10 + (*str - '0');
        str++;
    }
    return num * sign;
}

