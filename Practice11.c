#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//1.某个位置是不是地雷 mine_map ("1"表示是雷，"0"表示是雷)
//2.某个位置当前是翻开的还是未翻开的(show_map）
#define M_ROW 9
#define M_COL 9
#define M_Mine_Count 10
//表示每个位置是否雷，不能呈现给玩家
char mine_map[M_ROW][M_COL];
//表示每个位置是雷，呈现给玩家
char show_map[M_ROW][M_COL];
void Init(){

	//1.先对show_map初始化，每个位置都没翻开，把每个位置都填成*
	for (int row = 0; row < M_ROW; row++){
		for (int col = 0; col < M_COL; col++){
			show_map[row][col] = '*';
		}
	}
	//2.再对mine_map初始化，先把每个位置都设置为"0"
	//产生若干个随机数，把随机位置设置为"1"
	for (int row = 0; row < M_ROW; row++){
		for (int col = 0; col < M_COL; col++){
			mine_map[row][col] = '0';
		}
	}
	srand((unsigned int)time(0));
	int mine_count = 0;
	while (1){
		//产生随机数
		int row = rand() % M_ROW;
		int col = rand() % M_COL;
		if (mine_map[row][col] == '1'){
			continue;
		}
		mine_map[row][col] = '1';
		mine_count++;
		//产生雷
		if (mine_count >= M_Mine_Count){
			break;
		}
	}
}
void PrintMap(char the_map[M_ROW][M_COL]){
	for (int row = 0; row < M_ROW; row++){
		for (int col = 0; col < M_COL; col++){
			printf("%c", the_map[row][col]);
		}
		printf("\n");
	}
}
void Update(char mine_map[M_ROW][M_COL], char show_map[M_ROW][M_COL], int row, int col){
	//根据位置，判断这个位置周围位置有几个雷
	//表示雷的数量
	int count = 0;
	for (int r = row - 1; r <= row + 1; r++){
		for (int c = col - 1; c <= col + 1; c++){
			if (r == row&&c == col){
				continue;
			}
			if (r < 0 || r >= M_ROW || c < 0 || c >= M_COL){
				continue;
			}
			if (mine_map[r][c] == '1'){
				++count;
			}
		}
	}
	show_map[row][col] = '0' + count;
}
int main(){
	//1.初始化地图
	Init();
	int count = 0;
	while (1){
		//2.打印地图
		PrintMap(show_map);
		//3.让玩家输入一组坐标，表示要翻开的位置
		printf("请输入要翻开的位置(row,col):");
		int row = 0, col = 0;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= M_ROW || col < 0 || col >= M_COL){
			printf("您的输入有误，请重新输入\n");
			continue;
		}
		if (show_map[row][col] != '*'){
			printf("这个位置已经翻开，请重新输入\n");
			continue;
		}
		//4.判定是否游戏结束
		if (mine_map[row][col] == '1'){
			PrintMap(mine_map);
			printf("游戏结束\n");
			break;
		}
		//5.判定游戏是否胜利（翻开所有不是雷的格子）
		//用count表示已翻开不是雷的格子
		++count;
		if (count == M_ROW*M_COL - M_Mine_Count){
			PrintMap(mine_map);
			printf("你赢了\n");
			break;
		}
		//6.根据周围雷的情况，更新show_map
		Update(mine_map, show_map, row, col);
	}
	system("pause");
	return 0;
}
