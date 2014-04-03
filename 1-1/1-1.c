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
	memset(winner,0x00, sizeof(winner));
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
	
	//for ( j = 0 ; j < total ; j ++ )
	//{
		start = k;//�ʱ�ȭ.
		while(1)//1ȸ Winner Tree�� ����Ѵ�.
		{
			
			if(start == 1)
			{
				//tree[0] = winner[1];//���� ���ڸ� 0���� �ִ´�.
				//fprintf(out, "%d ", **tree[0]);
				//(*tree[0])++;//���� ���� �ִ� content[x]�� �ּҸ� �÷� �״��� ���� Winner Tree�� �����ϵ��� �Ѵ�.

				//���� 1-1�� ó�� ������ loser tree�� ��� 4, 5, 6, 7�� ���� ���ʴ�� ����Ͻÿ�. �� ����.
				for ( j = 4 ; j <= 7 ; j ++ )
				{
					fprintf(out, "%d ", **tree[j]);
				}
				break;
			}
			for ( i = start ; i < (start * 2) ; i += 2 )//level���� �����Ѵ�.
			{
				if(**tree[i] == NULL)//NULL�� �Էµ� ���κ��̸� �� content[x] RUN������ �������� �ʰ� ������ �������������� �ö󰣴�.
				{
					tree[i/2] = tree[i+1];
				}
				else if(**tree[i+1] == NULL)
				{
					tree[i/2] = tree[i];					
				}
				
				if( i >= k) //���� ���ڿ� ���ڰ� �������� ���� leaf node������ ó��..
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
				else//�ӽ÷� ����� ���� ���� �߿��� �ٽ� ���ڸ� ������ ���ڴ� �ӽ� tree�� ���ڴ� ��� tree��.
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
		
			start /= 2;//�� level, parent level�� �ö󰣴�.
		}
	//}

	
	

	free(tree);
	free(contents);
	free(winner);
	fclose(fin);
	fclose(out);
}