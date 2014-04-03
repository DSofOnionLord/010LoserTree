#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
	int total, k, size;

	int ***tree;
	int ***winner;//승자 결과를 넣기 위한 임시 배열.
	int **contents;
	int i,j;
	int start;
	int x;

	FILE * fin = fopen("input.txt", "r");
	FILE * out = fopen("output.txt", "w");

	fscanf(fin, "%d %d", &total, &k);
	size = total / k;

	//int *tree[2*k] 의 형식... 1차원 포인터 배열..
	tree = (int ***)malloc(sizeof(int**) * (2*k));
	winner = (int ***)malloc(sizeof(int**) * (k));
	memset(winner,0x00, sizeof(winner));
	contents = (int**)malloc(sizeof(int*) * k);

	start = k;

	//집어 넣을 내용을 입력..
	//contents[0], contents[1],... 이 하나의 run.
	//pointer을 할때에는 contents[0]+1 이런식으로 가리키게 된다....
	for ( i = 0 ; i < k ; i ++ )
	{
		contents[i] = (int*)malloc(sizeof(int)*(size+1));
		for ( j = 0 ; j < size ; j ++ )
		{
			fscanf(fin, "%d", &contents[i][j]);
		}
		contents[i][5] = NULL;//추가로 끝을 알리는 곳에 NULL을 추가.
	}

	for ( i = start ; i < start * 2 ; i ++ )
	{
		tree[i] = &contents[i-start];
	}
	
	//for ( j = 0 ; j < total ; j ++ )
	//{
		start = k;//초기화.
		while(1)//1회 Winner Tree를 계산한다.
		{
			
			if(start == 1)
			{
				//tree[0] = winner[1];//최종 승자를 0번에 넣는다.
				//fprintf(out, "%d ", **tree[0]);
				//(*tree[0])++;//최종 값이 있는 content[x]의 주소를 올려 그다음 값이 Winner Tree에 참가하도록 한다.

				//과제 1-1번 처음 구성된 loser tree의 노드 4, 5, 6, 7의 값을 차례대로 출력하시오. 를 수행.
				for ( j = 4 ; j <= 7 ; j ++ )
				{
					fprintf(out, "%d ", **tree[j]);
				}
				break;
			}
			for ( i = start ; i < (start * 2) ; i += 2 )//level마다 연산한다.
			{
				if(**tree[i] == NULL)//NULL이 입력된 끝부분이면 그 content[x] RUN단위는 진행하지 않고 상대방이 부전승형식으로 올라간다.
				{
					tree[i/2] = tree[i+1];
				}
				else if(**tree[i+1] == NULL)
				{
					tree[i/2] = tree[i];					
				}
				
				if( i >= k) //아직 승자와 패자가 가려지지 않은 leaf node에서의 처리..
				{
					if(**tree[i] > **tree[i+1])
					{
						tree[i/2] = tree[i];
						winner[i/2] = tree[i+1];
					}
					else if(**tree[i] <= **tree[i+1])
					{
						tree[i/2] = tree[i+1];
						winner[i/2] = tree[i];
					}
				}
				else//임시로 저장된 승자 값들 중에서 다시 승자를 가려서 승자는 임시 tree로 패자는 결과 tree로.
				{
					if(**winner[i] < **winner[i+1])
					{
						tree[i/2] = winner[i+1];
						winner[i/2] = winner[i];
					}
					else if(**winner[i] >= **winner[i+1])
					{
						tree[i/2] = winner[i];
						winner[i/2] = winner[i+1];
					}
				}

			}
		
			start /= 2;//윗 level, parent level로 올라간다.
		}
	//}

	
	

	free(tree);
	free(contents);
	free(winner);
	fclose(fin);
	fclose(out);
}