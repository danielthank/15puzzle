#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
FILE *fin, *fout;
int pos[8][4] = {{15},{0},{1,2},{3,4},{5,6},{7,8},{9,10},{11,12,13,14}};
int cnt[8] = {1,1,2,2,2,2,2,4};
int go[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int map[16], ans[16], closest[16][8], h, idx, stack[100], top;
int abs(int x){return x>0?x:-x;}
bool check(int x, int y){return x>=0 && x<4 && y>=0 && y<4;}
int cal(int index, int num)
{
    int i, ans = 100;
    for(i=0; i<cnt[num]; i++)
    {
        int x=index/4, y=index%4;
        int xx=pos[num][i]/4, yy=pos[num][i]%4;
        int t=abs(x-xx) + abs(y-yy);
        if(t < ans) ans=t;
    }
    return ans;
}
void print()
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++) fprintf(fout, "%d ", map[i*4+j]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
}
int cal(int x, int y, int step, int ban)
{
    if(h==0) return 1;
    if(step+h > idx) return 0;
    int p = x*4+y;
    for(int i=0; i<4; i++)
    {
        if(i == ban) continue;
        int xx=x+go[i][0], yy=y+go[i][1];
        if(!check(xx,yy)) continue;
        int pp = xx*4 + yy;
        map[p] = map[pp];
        map[pp] = 0;
        h=h-closest[pp][map[p]] + closest[p][map[p]];
        int t = cal(xx, yy, step+1, i>=2 ? 5-i : 1-i);
        if(t)
        {
            stack[top++] = pp;
            print();
        }
        h=h+closest[pp][map[p]] - closest[p][map[p]];
        map[pp] = map[p];
        map[p] = 0;
        if(t) return t;
    }
    return 0;
}
int start(int x)
{
    char str[100];
    sprintf(str, "input_%d.txt", x);
    fin = fopen(str, "r");
    sprintf(str, "output_%d.txt", x);
    fout = fopen(str, "w");
    int i,j;
    for(i=0; i<16; i++) fscanf(fin, "%d", &map[i]), ans[i] = map[i];
    for(i=0; i<16; i++)
    {
        for(j=0; j<8; j++) closest[i][j] = cal(i, j);
    }
    h = 0;
    int start;
    for(i=0; i<16; i++)
    {
        if(map[i] == 0)
        {
            start=i;
            continue;
        }
        h+=closest[i][map[i]];
    }
    top = 0;
    for(idx=0; ;idx++)
    {
        printf("%d\n", idx);
        if(cal(start/4, start%4, 0, -1)) break;
    }
    fprintf(fout, "%d\n", idx);
    for(i = top-1; i>=0; i--) fprintf(fout, "%d %d\n", stack[i]/4+1, stack[i]%4+1);
    fclose(fin);
    fclose(fout);
}
int main()
{
    for(int x=1; x<=5; x++)
    {
        start(x);
        printf("%d finish\n", x);
    }
}
