#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
	int total, k, size;

	int ***tree;
	int ***winner;//���� ����� �ֱ� ���� �ӽ� �迭.
	int **contents;
	int i,j;
	int start;
	int x;

	FILE * fin = fopen("input.txt", "r");
	FILE * out = fopen("output.txt", "w");

	fscanf(fin, "%d %d", &total, &k);
	size = total / k;

	//int *tree[2*k] �� ����... 1���� ������ �迭..
	tree = (int ***)malloc(sizeof(int**) * (2*k));
	winner = (int ***)malloc(sizeof(int**) * (k));
	
	contents = (int**)malloc(sizeof(int*) * k);

	start = k;

	//���� ���� ������ �Է�..
	//contents[0], contents[1],... �� �ϳ��� run.
	//pointer�� �Ҷ����� contents[0]+1 �̷������� ����Ű�� �ȴ�....
	for ( i = 0 ; i < k ; i ++ )
	{
		contents[i] = (int*)malloc(sizeof(int)*(size+1));
		for ( j = 0 ; j < size ; j ++ )
		{
			fscanf(fin, "%d", &contents[i][j]);
		}
		contents[i][5] = NULL;//�߰��� ���� �˸��� ���� NULL�� �߰�.
	}

	for ( i = start ; i < start * 2 ; i ++ )
	{
		tree[i] = &contents[i-start];
	}
	
	for ( j = 0 ; j < total ; j ++ )
	{
		memset(winner,NULL, sizeof(winner));//�ӽ� �迭 �ʱ�ȭ.
		start = k;//�ʱ�ȭ.
		while(1)//1ȸ Winner Tree�� ����Ѵ�.
		{
			if(start == 1)
			{

				tree[0] = winner[1];//���� ���ڸ� 0���� �ִ´�.
				fprintf(out, "%d ", **tree[0]);
				(*tree[0])++;//���� ���� �ִ� content[x]�� �ּҸ� �÷� �״��� ���� Winner Tree�� �����ϵ��� �Ѵ�.
				break;
			}
			for ( i = start ; i < (start * 2) ; i += 2 )//level���� �����Ѵ�.
			{
				
				if( start == k)
				{
					if(**tree[i] == 0)//NULL�� �Էµ� ���κ��̸� �� content[x] RUN������ �������� �ʰ� ������ �������������� �ö󰣴�.
					{
						
						if(**tree[i+1] == 0)
						{
							**winner[i/2] = 999;
						}
						else
						{
							winner[i/2] = tree[i+1];
						}
					}
					else if(**tree[i+1] == 0)
					{
						if(**tree[i] == 0)
						{
							**winner[i/2] = 999;
						}
						else
						{
							winner[i/2] = tree[i];
						}
					}
					else if(**tree[i] > **tree[i+1])
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
				else
				{
					if(**winner[i] == 0)
					{
						if(**winner[i+1] == 0)
						{
							**winner[i/2] = 999;
						}
						else
						{
							winner[i/2] = winner[i+1];
						}
					}
					else if(**winner[i+1] == 0)
					{
						if(**winner[i] == 0)
						{
							**winner[i]  = 999;
						}
						else
						{
							winner[i/2] = winner[i];
						}
					}
					else if(**winner[i] < **winner[i+1])
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
			
			start /= 2;//�� level, parent level�� �ö󰣴�.
		}
		
	}

	
	

	free(tree);
	free(contents);
	free(winner);
	fclose(fin);
	fclose(out);
}