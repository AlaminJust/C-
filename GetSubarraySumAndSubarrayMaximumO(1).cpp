/*input
5 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
17 18 19 20
5
1 1
2 2
3 3
4 4
5 4
*/
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

#define INF 1000000000

int N, M, A[1001][1001];
int ColumnSum[1001][1001], Sum[1001][1001];
int Table[11][11][1100][1100], n, m;

int LogBase2(int x)
{
	if (x == 1 && x < 2)
		return 0;
	if (x >=2 && x < 4)
		return 1;
	if (x >= 4 && x < 8)
		return 2;
	if (x >= 8 && x < 16)
		return 3;
	if (x >= 16 && x < 32)
		return 4;
	if (x >= 32 && x < 64)
		return 5;
	if (x >= 64 && x < 128)
		return 6;
	if (x >= 128 && x < 256)
		return 7;
	if (x >= 256 && x < 512)
		return 8;
	if (x >= 512 && x < 1024)
		return 9;
	return 10;
}

void PreComputeSum()
{
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++)
		{
			ColumnSum[i][j] = 0;
			Sum[i][j] = 0;
		}

	for (int j = 1; j <= M; j++)
		for (int i = 1; i <= N; i++)
			ColumnSum[i][j] = ColumnSum[i-1][j] + A[i][j];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			Sum[i][j] = Sum[i][j-1] + ColumnSum[i][j];
}

int RangeSumQuery(int x1, int y1, int x2, int y2)
{
	return Sum[x2][y2] - Sum[x2][y1-1] - Sum[x1-1][y2] + Sum[x1-1][y1-1];
}

void PreComputeMax()
{
	int n = LogBase2(N) + 1;
	int m = LogBase2(M) + 1;
	int i1, j1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			i1 = 1<<i;
			j1 = 1<<j;
			for (int x = 1; x <= (N - i1 + 1); x++)
				for (int y = 1; y <= (M - j1 + 1); y++)
				{
					int y1 = 1<<j-1;
					int x1 = 1<<i-1;
					if (i == 0 && j == 0)
						Table[i][j][x][y] = A[x][y];
					else if (i == 0)
						Table[i][j][x][y] = max(Table[i][j-1][x][y], Table[i][j-1][x][y + y1]);
					else if (j == 0)
						Table[i][j][x][y] = max(Table[i-1][j][x][y], Table[i-1][j][x + x1][y]);
					else
						Table[i][j][x][y] = max(Table[i-1][j-1][x][y], max(Table[i-1][j-1][x][y + y1], max(Table[i-1][j-1][x + x1][y], Table[i-1][j-1][x + x1][y + y1])));
				}
		}
	}
}

int RangeMaxQuery(int x1, int y1, int x2, int y2)
{
	int l_x = x2 - x1 + 1,
		l_y = y2 - y1 + 1,
		k_x = LogBase2(l_x),
		k_y = LogBase2(l_y),
		k_x1 = 1<<k_x,
		k_y1 = 1<<k_y;

	return max(Table[k_x][k_y][x1][y1], max(Table[k_x][k_y][x1 + l_x - k_x1][y1], max(Table[k_x][k_y][x1][y1 + l_y - k_y1], Table[k_x][k_y][x1 + l_x - k_x1][y1 + l_y - k_y1])));
}

int CHSQARR(int a, int b)
{
	int x1, x2, y1, y2, Ans = INF;

	for (x1 = 1; x1 <= N - a + 1; x1++)
		for (y1 = 1; y1 <= M - b + 1; y1++)
		{
			x2 = x1 + a - 1;
			y2 = y1 + b - 1;
			Ans = min(Ans, a*b*RangeMaxQuery(x1, y1, x2, y2) - RangeSumQuery(x1, y1, x2, y2));
		}

	return Ans;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &A[i][j]);

	PreComputeSum();
	PreComputeMax();

	int Q, a, b;
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", CHSQARR(a, b));
	}
	return 0;
}
