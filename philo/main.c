#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info;

	if (!right_input(argc, argv))
		return (1);
	init_info(&info, argv);

}