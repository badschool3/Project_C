#include "base.h"

/* --------메인함수-------- */
int main(void)
{
	int check;
	system("clear");
	load_file();
	check=first_menu();
	if(check == 1)
		member_menu();
	else if(check == 2)
		admin_menu();
	save_file();
	return 0;
}
