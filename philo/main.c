#include "philo.h"

void

int main(int argc, char **argv)
{
    t_input data;

    if (argc == 5 || argc == 6)
    {
        if (parse(&data, argv) < 0)
            error_exit("Incorrect input");
        init_data(&data);
        philosophize(&data);
        cleanup(&data);
    }
    else
        error_exit("Incorrect input");
    return (0);
}
