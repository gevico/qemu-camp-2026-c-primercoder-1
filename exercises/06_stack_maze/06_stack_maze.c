#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};
int vis[MAX_ROW][MAX_COL] = {0};
int path[MAX_COL * MAX_ROW][2];
int pathlen = -1;
void dfs(int i, int j, int len)
{
	path[len][0] = i;
	path[len][1] = j;
	if(i==4 && j==4) {
		pathlen = len+1;
		return;
	}
	vis[i][j] = 1;
	if(i-1>=0 && !vis[i-1][j] && !maze[i-1][j]) dfs(i-1, j, len+1);
	if(pathlen>=0) return;
	if(i+1<MAX_ROW && !vis[i+1][j] && !maze[i+1][j]) dfs(i+1, j, len+1);
	if(pathlen>=0) return;
	if(j-1>=0 && !vis[i][j-1] && !maze[i][j-1]) dfs(i, j-1, len+1);
	if(pathlen>=0) return;
	if(j+1<MAX_COL && !vis[i][j+1] && !maze[i][j+1]) dfs(i, j+1, len+1);
	if(pathlen>=0) return;
	vis[i][j] = 0; 
}

int main(void)
{
	// TODO: 在这里添加你的代码
    dfs(0, 0, 0);
	for(int i=pathlen-1;i>=0;i--) {
		printf("(%d, %d)\n", path[i][0], path[i][1]);
	}
	return 0;
}