#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//1.ĳ��λ���ǲ��ǵ��� mine_map ("1"��ʾ���ף�"0"��ʾ����)
//2.ĳ��λ�õ�ǰ�Ƿ����Ļ���δ������(show_map��
#define M_ROW 9
#define M_COL 9
#define M_Mine_Count 10
//��ʾÿ��λ���Ƿ��ף����ܳ��ָ����
char mine_map[M_ROW][M_COL];
//��ʾÿ��λ�����ף����ָ����
char show_map[M_ROW][M_COL];
void Init(){

	//1.�ȶ�show_map��ʼ����ÿ��λ�ö�û��������ÿ��λ�ö����*
	for (int row = 0; row < M_ROW; row++){
		for (int col = 0; col < M_COL; col++){
			show_map[row][col] = '*';
		}
	}
	//2.�ٶ�mine_map��ʼ�����Ȱ�ÿ��λ�ö�����Ϊ"0"
	//�������ɸ�������������λ������Ϊ"1"
	for (int row = 0; row < M_ROW; row++){
		for (int col = 0; col < M_COL; col++){
			mine_map[row][col] = '0';
		}
	}
	srand((unsigned int)time(0));
	int mine_count = 0;
	while (1){
		//���������
		int row = rand() % M_ROW;
		int col = rand() % M_COL;
		if (mine_map[row][col] == '1'){
			continue;
		}
		mine_map[row][col] = '1';
		mine_count++;
		//������
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
	//����λ�ã��ж����λ����Χλ���м�����
	//��ʾ�׵�����
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
	//1.��ʼ����ͼ
	Init();
	int count = 0;
	while (1){
		//2.��ӡ��ͼ
		PrintMap(show_map);
		//3.���������һ�����꣬��ʾҪ������λ��
		printf("������Ҫ������λ��(row,col):");
		int row = 0, col = 0;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= M_ROW || col < 0 || col >= M_COL){
			printf("����������������������\n");
			continue;
		}
		if (show_map[row][col] != '*'){
			printf("���λ���Ѿ�����������������\n");
			continue;
		}
		//4.�ж��Ƿ���Ϸ����
		if (mine_map[row][col] == '1'){
			PrintMap(mine_map);
			printf("��Ϸ����\n");
			break;
		}
		//5.�ж���Ϸ�Ƿ�ʤ�����������в����׵ĸ��ӣ�
		//��count��ʾ�ѷ��������׵ĸ���
		++count;
		if (count == M_ROW*M_COL - M_Mine_Count){
			PrintMap(mine_map);
			printf("��Ӯ��\n");
			break;
		}
		//6.������Χ�׵����������show_map
		Update(mine_map, show_map, row, col);
	}
	system("pause");
	return 0;
}
