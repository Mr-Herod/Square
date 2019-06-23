
#include "windows.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#include <own.h>
#define Aplay 49
#define Mplay 50
#define EXIT  51
#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77
#define GO_ON 0
#define STOP 1
#define LAST_LINE 27
#define MAX 10000
#define DEFAULT -1

void draw_square();//
void draw_map();//
void draw_menu();//
void start_game();//
void over_game();//
int  check_game();//
void win_game();
void move_square();//
void check_line();//
int  check_boundary();
void change_dir(int);//
void define_square();//
int  choice, sq1, sq2 = 0;
int  sq[7][4][2], base[MAX][2], base_num, line[26], dir, dir_tmp, score = 0;

void goto_xy(SHORT x, SHORT y)      //调用系统接口实现移动光标位置
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

int main(int argc, char *argv[])
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
	start_game();
	while(choice != EXIT)
	{
		move_square();
	}

}

void start_game()
{
	srand((unsigned)time(NULL));
	base_num = 0;
	draw_menu();
	if (choice != EXIT)
	{
		draw_map();
		draw_square();
	}
}

void draw_menu()
{

	system("CLS");
	system("color 3F");
	printf("\
 ******************************************************************************\n\
 *                                                                            *\n\
 *                            1、Auto play                                    *\n\
 *                                                                            *\n\
 *                            2、Mannual play                                 *\n\
 *                                                                            *\n\
 *                            3、Exit                                         *\n\
 *                                                                            *\n\
 ******************************************************************************");
//	while (1) {
		choice = _getch();
		dir=_getch();
//		printf("%d  %d\n", choice,dir);
//		getchar();
//	}
}

void draw_map()
{
	int tmp;
	system("CLS");
	printf("*******祝大家中秋节快乐*******\n");
	for (tmp = 0; tmp <= 26;tmp++)
		printf("*                            *\n");
	printf("*******祝大家中秋节快乐*******");
	goto_xy(34,4);
	printf("next:");
	goto_xy(34, 10);
	printf("score:");
	goto_xy(39, 12);
	printf("000");
	goto_xy(34, 16);
	printf("speed level:");
	goto_xy(39, 18);
	printf(" 10");
}

void define_square()
{
	sq[0][0][0] = 13;	//  ##
	sq[0][0][1] = 1;	//  ##
	sq[0][1][0] = 14;
	sq[0][1][1] = 1;
	sq[0][2][0] = 14;
	sq[0][2][1] = 2;
	sq[0][3][0] = 13;
	sq[0][3][1] = 2;

	sq[1][0][0] = 12;   //  ####
	sq[1][0][1] = 1;
	sq[1][1][0] = 13;
	sq[1][1][1] = 1;
	sq[1][2][0] = 14;
	sq[1][2][1] = 1;
	sq[1][3][0] = 15;
	sq[1][3][1] = 1;

	sq[2][0][0] = 13;	//  ###
	sq[2][0][1] = 1;	//  #
	sq[2][1][0] = 14;
	sq[2][1][1] = 1;
	sq[2][2][0] = 15;
	sq[2][2][1] = 1;
	sq[2][3][0] = 13;
	sq[2][3][1] = 2;

	sq[3][0][0] = 13;	// ###
	sq[3][0][1] = 1;	//   #
	sq[3][1][0] = 14;
	sq[3][1][1] = 1;
	sq[3][2][0] = 15;
	sq[3][2][1] = 1;
	sq[3][3][0] = 15;
	sq[3][3][1] = 2;

	sq[4][0][0] = 13;	//  #
	sq[4][0][1] = 1;	//  ##
	sq[4][1][0] = 14;	//   #
	sq[4][1][1] = 2;
	sq[4][2][0] = 14;
	sq[4][2][1] = 3;
	sq[4][3][0] = 13;
	sq[4][3][1] = 2;

	sq[5][0][0] = 13;	 //  #
	sq[5][0][1] = 3;	 // ##
	sq[5][1][0] = 14;    // #
	sq[5][1][1] = 1;
	sq[5][2][0] = 14;
	sq[5][2][1] = 2;
	sq[5][3][0] = 13;
	sq[5][3][1] = 2;

	sq[6][0][0] = 13;    //  ###
	sq[6][0][1] = 1;     //   #
	sq[6][1][0] = 14;
	sq[6][1][1] = 1;
	sq[6][2][0] = 14;
	sq[6][2][1] = 2;
	sq[6][3][0] = 15;
	sq[6][3][1] = 1;
}

void draw_square()
{
	define_square();
	dir_tmp = 0;
	if (sq2 == DEFAULT)
		sq1 = rand() % 7;
	else
	{

		sq1 = sq2;
		goto_xy(sq[sq2][0][0] + 27, sq[sq2][0][1] + 4);
		printf(" ");
		goto_xy(sq[sq2][1][0] + 27, sq[sq2][1][1] + 4);
		printf(" ");
		goto_xy(sq[sq2][2][0] + 27, sq[sq2][2][1] + 4);
		printf(" ");
		goto_xy(sq[sq2][3][0] + 27, sq[sq2][3][1] + 4);
		printf(" ");
	}

	goto_xy(sq[sq1][0][0],sq[sq1][0][1]);
	printf("#");
	goto_xy(sq[sq1][1][0],sq[sq1][1][1]);
	printf("#");
	goto_xy(sq[sq1][2][0],sq[sq1][2][1]);
	printf("#");
	goto_xy(sq[sq1][3][0],sq[sq1][3][1]);
	printf("#");
	sq2 = rand() % 7;

	goto_xy(sq[sq2][0][0]+27, sq[sq2][0][1]+4);
	printf("#");
	goto_xy(sq[sq2][1][0]+27, sq[sq2][1][1]+4);
	printf("#");
	goto_xy(sq[sq2][2][0]+27, sq[sq2][2][1]+4);
	printf("#");
	goto_xy(sq[sq2][3][0]+27, sq[sq2][3][1]+4);
	printf("#");
//	getchar();
}

void move_square()
{
	if (check_game() == GO_ON)
	{
		int tmp;
		for (tmp = 0; tmp < 80; tmp++)
		{
			Sleep(2);
			if (_kbhit() == 1)
			{
				_getch();
				dir = _getch();
				change_dir(dir);
			}
			else if (dir == DOWN)
				break;
		}

			goto_xy(sq[sq1][0][0], sq[sq1][0][1]++);
			printf(" ");
			goto_xy(sq[sq1][1][0], sq[sq1][1][1]++);
			printf(" ");
			goto_xy(sq[sq1][2][0], sq[sq1][2][1]++);
			printf(" ");
			goto_xy(sq[sq1][3][0], sq[sq1][3][1]++);
			printf(" ");
			goto_xy(sq[sq1][0][0], sq[sq1][0][1]);
			printf("#");
			goto_xy(sq[sq1][1][0], sq[sq1][1][1]);
			printf("#");
			goto_xy(sq[sq1][2][0], sq[sq1][2][1]);
			printf("#");
			goto_xy(sq[sq1][3][0], sq[sq1][3][1]);
			printf("#");


	}
	else
	{

		dir = 0;
		if (base[base_num - 4][1] == 1 || base[base_num - 3][1] == 1 || base[base_num - 2][1] == 1 || base[base_num - 1][1] == 1)
            over_game();
		else
		{
			check_line();
			draw_square();
		}
	}

}

int check_game()
{
	int tmp;
	if (base_num == 0)
	{
		if (sq[sq1][0][1] == LAST_LINE || sq[sq1][1][1] == LAST_LINE || sq[sq1][2][1] == LAST_LINE || sq[sq1][3][1] == LAST_LINE)
		{
			base[base_num][0] =sq[sq1][0][0];
			base[base_num++][1] = sq[sq1][0][1];
			base[base_num][0] = sq[sq1][1][0];
			base[base_num++][1] = sq[sq1][1][1];
			base[base_num][0] = sq[sq1][2][0];
			base[base_num++][1] = sq[sq1][2][1];
			base[base_num][0] = sq[sq1][3][0];
			base[base_num++][1] = sq[sq1][3][1];
			return  STOP;
		}
		else
			return GO_ON;
	}
		for (tmp = 0; tmp < base_num;tmp++)
			if (   (sq[sq1][0][1]+1 == base[tmp][1] && sq[sq1][0][0] == base[tmp][0]) \
				|| (sq[sq1][1][1]+1 == base[tmp][1] && sq[sq1][1][0] == base[tmp][0]) \
				|| (sq[sq1][2][1]+1 == base[tmp][1] && sq[sq1][2][0] == base[tmp][0]) \
				|| (sq[sq1][3][1]+1 == base[tmp][1] && sq[sq1][3][0] == base[tmp][0])\
				|| sq[sq1][0][1] == LAST_LINE || sq[sq1][1][1] == LAST_LINE || sq[sq1][2][1] == LAST_LINE || sq[sq1][3][1] == LAST_LINE)
			{
				base[base_num][0] = sq[sq1][0][0];
				base[base_num++][1] = sq[sq1][0][1];
				base[base_num][0] = sq[sq1][1][0];
				base[base_num++][1] = sq[sq1][1][1];
				base[base_num][0] = sq[sq1][2][0];
				base[base_num++][1] = sq[sq1][2][1];
				base[base_num][0] = sq[sq1][3][0];
				base[base_num++][1] = sq[sq1][3][1];
				return  STOP;
			}
				return GO_ON;
}

void check_line()
{
	int tmp,tmp2;
	for (tmp = 0; tmp <=27;tmp++)
		line[tmp] = 0;
	for (tmp = 0; tmp < base_num;tmp++)
	{
		for (tmp2 = 3;tmp2 <= 27;tmp2++)
		{
			if (base[tmp][1] == tmp2)
				line[tmp2 - 1]++;
		}
	}
	for (tmp = 3; tmp <= 27;tmp++)
	{
		if (line[tmp] == 28)
		{
			int base_copy[MAX][2], tmp3;
			score += 10;
			goto_xy(40, 12);
			printf("%d", score);
			for (tmp2 = 0, tmp3 = 0; tmp2 < base_num;tmp2++)
			{
				if (base[tmp2][1] == (tmp + 1))
				{
					goto_xy(base[tmp2][0], base[tmp2][1]);
					printf(" ");
				}
				else
				{
					base_copy[tmp3][0] = base[tmp2][0];
					base_copy[tmp3][1] = base[tmp2][1];
					tmp3++;
				}
			}
			for (tmp2 = 0;tmp2 < base_num - 28; tmp2++)
			{
				base[tmp2][0] = base_copy[tmp2][0];
				base[tmp2][1] = base_copy[tmp2][1];
			}

			base_num -= 28;

			for (tmp2 = 0,tmp3 = 0;tmp2 < base_num; tmp2++)
			{
				if (base[tmp2][1] <= tmp)
				{
					base_copy[tmp3][0] = base[tmp2][0];
					base_copy[tmp3][1] = base[tmp2][1];
					tmp3++;
					++base[tmp2][1];
				}
			}
			for (tmp2 = 0; tmp2 < tmp3;tmp2++)
			{
				goto_xy(base_copy[tmp2][0], base_copy[tmp2][1]);
				printf(" ");
			}
			for (tmp2 = 0;tmp2 < base_num; tmp2++)
			{
				goto_xy(base[tmp2][0], base[tmp2][1]);
				printf("#");
			}
		}
	}
}

int check_boundary()
{
	int tmp;
	if (sq[sq1][0][1] >= LAST_LINE || sq[sq1][1][1] >= LAST_LINE || sq[sq1][2][1] >= LAST_LINE || sq[sq1][3][1] >= LAST_LINE\
		|| sq[sq1][0][1] <= 0 || sq[sq1][1][1] <= 0 || sq[sq1][2][1] <= 0 || sq[sq1][3][1] <= 0\
		|| sq[sq1][0][0] <= 0 || sq[sq1][1][0] <= 0 || sq[sq1][2][0] <= 0 || sq[sq1][3][0] <= 0\
		|| sq[sq1][0][0] >= 29 || sq[sq1][1][0] >= 29 || sq[sq1][2][0] >= 29 || sq[sq1][3][0] >= 29\
		)
		return STOP;
	for (tmp = 0; tmp < base_num;tmp++)
		if ((sq[sq1][0][1] == base[tmp][1] && sq[sq1][0][0] == base[tmp][0]) \
			|| (sq[sq1][1][1] == base[tmp][1] && sq[sq1][1][0] == base[tmp][0])\
			|| (sq[sq1][2][1] == base[tmp][1] && sq[sq1][2][0] == base[tmp][0])\
			|| (sq[sq1][3][1] == base[tmp][1] && sq[sq1][3][0] == base[tmp][0]))
			return STOP;
	return GO_ON;
}

void change_dir(int dir)
{
	int tmp;
	goto_xy(sq[sq1][0][0], sq[sq1][0][1]);
	printf(" ");
	goto_xy(sq[sq1][1][0], sq[sq1][1][1]);
	printf(" ");
	goto_xy(sq[sq1][2][0], sq[sq1][2][1]);
	printf(" ");
	goto_xy(sq[sq1][3][0], sq[sq1][3][1]);
	printf(" ");
		if (dir == LEFT)
		{
			sq[sq1][0][0] -= 1;
			sq[sq1][1][0] -= 1;
			sq[sq1][2][0] -= 1;
			sq[sq1][3][0] -= 1;
			if (check_boundary() == STOP)
			{
				sq[sq1][0][0] += 1;
				sq[sq1][1][0] += 1;
				sq[sq1][2][0] += 1;
				sq[sq1][3][0] += 1;
			}
		}
		else if (dir == RIGHT)
		{
			sq[sq1][0][0] += 1;
			sq[sq1][1][0] += 1;
			sq[sq1][2][0] += 1;
			sq[sq1][3][0] += 1;
			if (check_boundary() == STOP)
			{
				sq[sq1][0][0] -= 1;
				sq[sq1][1][0] -= 1;
				sq[sq1][2][0] -= 1;
				sq[sq1][3][0] -= 1;
			}
		}
		else if (dir == UP)
		{
			if (sq1 == 1 && dir_tmp==0)
			{
				sq[sq1][0][0] += 2;sq[sq1][0][1] -= 3;
				sq[sq1][1][0] += 1;sq[sq1][1][1] -= 2;
				sq[sq1][2][0] -= 0;sq[sq1][2][1] -= 1;
				sq[sq1][3][0] -= 1;sq[sq1][3][1] -= 0;
				dir_tmp=1;

				if (check_boundary() == STOP)
				{
					sq[sq1][0][0] -= 2;sq[sq1][0][1] += 3;
					sq[sq1][1][0] -= 1;sq[sq1][1][1] += 2;
					sq[sq1][2][0] -= 0;sq[sq1][2][1] += 1;
					sq[sq1][3][0] += 1;sq[sq1][3][1] += 0;
					dir_tmp = 0;
				}
			}
			else if (sq1 == 1 && dir_tmp == 1)
			{
				sq[sq1][0][0] -= 2;sq[sq1][0][1] += 3;
				sq[sq1][1][0] -= 1;sq[sq1][1][1] += 2;
				sq[sq1][2][0] -= 0;sq[sq1][2][1] += 1;
				sq[sq1][3][0] += 1;sq[sq1][3][1] += 0;
				dir_tmp = 0;
				if (check_boundary() == STOP)
				{
					sq[sq1][0][0] += 2;sq[sq1][0][1] -= 3;
					sq[sq1][1][0] += 1;sq[sq1][1][1] -= 2;
					sq[sq1][2][0] -= 0;sq[sq1][2][1] -= 1;
					sq[sq1][3][0] -= 1;sq[sq1][3][1] -= 0;
					dir_tmp = 1;
				}

			}
			else if (sq1 == 4 && dir_tmp == 0)
			{
				sq[sq1][0][0] += 2;
                sq[sq1][2][1] -= 2;
				dir_tmp = 1;

					if (check_boundary() == STOP)
					{
						sq[sq1][0][0] -= 2;
						sq[sq1][2][1] += 2;
						dir_tmp = 0;
					}
			}
			else if (sq1 == 4 && dir_tmp == 1)
			{
				sq[sq1][0][0] -= 2;
				sq[sq1][2][1] += 2;
				dir_tmp = 0;

					if (check_boundary() == STOP)
					{
						sq[sq1][0][0] += 2;
						sq[sq1][2][1] -= 2;
						dir_tmp = 1;
					}

			}
			else if (sq1 == 5 && dir_tmp == 0)
			{
				sq[sq1][0][1] -= 2;
				sq[sq1][3][0] += 2;
				dir_tmp = 1;

					if (check_boundary() == STOP)
					{
						sq[sq1][0][1] += 2;
						sq[sq1][3][0] -= 2;
						dir_tmp = 0;
					}
			}
			else if (sq1 == 5 && dir_tmp == 1)
			{
			sq[sq1][0][1] += 2;
			sq[sq1][3][0] -= 2;
			dir_tmp = 0;

				if (check_boundary() == STOP)
				{
					sq[sq1][0][1] -= 2;
					sq[sq1][3][0] += 2;
					dir_tmp = 1;
				}
			}
			else if (sq1 == 6 && dir_tmp == 0)
			{
				sq[sq1][3][0] -= 1;sq[sq1][3][1] -= 1;
				dir_tmp = 1;
				if (check_boundary() == STOP)
				{
					sq[sq1][3][0] += 1;sq[sq1][3][1] += 1;
					dir_tmp = 0;
				}
			}
			else if (sq1 == 6 && dir_tmp == 1)
			{
				sq[sq1][2][0] += 1;sq[sq1][2][1] -= 1;
				dir_tmp = 2;
				if (check_boundary() == STOP)
				{
					sq[sq1][2][0] -= 1;sq[sq1][2][1] += 1;
					dir_tmp = 1;
				}
			}
			else if (sq1 == 6 && dir_tmp == 2)
			{
			    sq[sq1][0][0] += 1;sq[sq1][0][1] += 1;
		    	dir_tmp = 3;
		    	if (check_boundary() == STOP)
		    	{
				sq[sq1][0][0] -= 1;sq[sq1][0][1] -= 1;
				dir_tmp = 2;
		    	}
			}
			else if (sq1 == 6 && dir_tmp == 3)
			{
			sq[sq1][3][0] += 1;sq[sq1][3][1] += 1;
			sq[sq1][0][0] -= 1;sq[sq1][0][1] -= 1;
			sq[sq1][2][0] -= 1;sq[sq1][2][1] += 1;
			dir_tmp = 0;
			if (check_boundary() == STOP)
			{
				sq[sq1][3][0] -= 1;sq[sq1][3][1] -= 1;
				sq[sq1][0][0] += 1;sq[sq1][0][1] += 1;
				sq[sq1][2][0] += 1;sq[sq1][2][1] -= 1;
				dir_tmp = 3;
			}
			}
			else if (sq1 == 2 && dir_tmp == 0)
			{
				sq[sq1][3][0] += 2;
				sq[sq1][0][0] += 2;sq[sq1][0][1] += 2;
				dir_tmp = 1;
				if (check_boundary() == STOP)
				{
					sq[sq1][3][0] -= 2;
					sq[sq1][0][0] -= 2;sq[sq1][0][1] -= 2;
					dir_tmp = 0;
				}
			}
			else if (sq1 == 2 && dir_tmp == 1)
			{
				sq[sq1][1][1] += 1;
				sq[sq1][0][0] -= 2;sq[sq1][0][1] -= 1;
				dir_tmp = 2;
				if (check_boundary() == STOP)
				{
					sq[sq1][1][1] -= 1;
					sq[sq1][0][0] += 2;sq[sq1][0][1] += 1;
					dir_tmp = 1;
				}

            }
			else if (sq1 == 2 && dir_tmp == 2)
			{
				sq[sq1][2][0] -= 2;
				sq[sq1][3][0] -= 2;sq[sq1][3][1] -= 2;
				dir_tmp = 3;
				if (check_boundary() == STOP)
				{
					sq[sq1][2][0] += 2;
					sq[sq1][3][0] += 2;sq[sq1][3][1] += 2;
					dir_tmp = 2;
				}
			}
			else if (sq1 == 2 && dir_tmp == 3)
			{
				sq[sq1][2][0] += 2;
				sq[sq1][0][1] -= 1;
				sq[sq1][1][1] -= 1;
				sq[sq1][3][1] += 2;
				dir_tmp = 0;
				if (check_boundary() == STOP)
				{
					sq[sq1][2][0] -= 2;
					sq[sq1][0][1] += 1;
					sq[sq1][1][1] += 1;
					sq[sq1][3][1] -= 2;
					dir_tmp = 3;
				}
			}
			else if (sq1 == 3 && dir_tmp == 0)
			{
			sq[sq1][1][1] += 1;
			sq[sq1][0][0] += 2;sq[sq1][0][1] -= 1;
			dir_tmp = 1;
			if (check_boundary() == STOP)
			{
				sq[sq1][1][1] -= 1;
				sq[sq1][0][0] -= 2;sq[sq1][0][1] += 1;
				dir_tmp = 0;
			}
			}
			else if (sq1 == 3 && dir_tmp == 1)
			{
			sq[sq1][2][0] -= 2;sq[sq1][2][1] += 1;
			sq[sq1][0][0] -= 2;sq[sq1][0][1] += 1;
			dir_tmp = 2;
			if (check_boundary() == STOP)
			{
				sq[sq1][2][0] += 2;sq[sq1][2][1] -= 1;
				sq[sq1][0][0] += 2;sq[sq1][0][1] -= 1;
				dir_tmp = 1;
			}

			}
			else if (sq1 == 3 && dir_tmp == 2)
			{
			sq[sq1][1][1] -= 1;
			sq[sq1][3][0] -= 2;sq[sq1][3][1] += 1;
			dir_tmp = 3;
			if (check_boundary() == STOP)
			{
				sq[sq1][1][1] += 1;
				sq[sq1][3][0] -= 2;sq[sq1][3][1] -= 1;
				dir_tmp = 2;
			}
			}
			else if (sq1 == 3 && dir_tmp == 3)
			{
			sq[sq1][2][0] += 2;sq[sq1][2][1] -= 1;
			sq[sq1][3][0] += 2;sq[sq1][3][1] -= 1;
			dir_tmp = 0;
			if (check_boundary() == STOP)
			{
				sq[sq1][2][0] -= 2;sq[sq1][2][1] += 1;
				sq[sq1][3][0] -= 2;sq[sq1][3][1] += 1;
				dir_tmp = 3;
			}
			}
		}

		goto_xy(sq[sq1][0][0], sq[sq1][0][1]); 		printf("#");
		goto_xy(sq[sq1][1][0], sq[sq1][1][1]);		printf("#");
		goto_xy(sq[sq1][2][0], sq[sq1][2][1]);		printf("#");
		goto_xy(sq[sq1][3][0], sq[sq1][3][1]);		printf("#");

}

void over_game()
{
	goto_xy(10, 13);
	printf("Game over!!!");
	getchar();
	start_game();
}
