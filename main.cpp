#include <cstdio>
#include <cstring>
#include <cctype>

struct Cell {    int value;    int index;};
struct Node {    int x;    int y;    int succ;};


Cell spreadsheet[1000][1000];
Node node[1000000];

int n, m, t, num_node;


void Ejecutar(int x, int y, char* str) {

    if (str[0] != '=') {
        sscanf(str, "%d", &spreadsheet[x][y].value);
        spreadsheet[x][y].index = -1;
    }

    else {
        spreadsheet[x][y].index = num_node;
        int pos = 1;
        while (pos < strlen(str)){
            if (isalnum(str[pos])) {
                Node& new_node = node[num_node];
                new_node.x = 0;
                new_node.y = 0;
                while (isalpha(str[pos])) {
                    new_node.y = new_node.y * 26 + str[pos] - 'A' + 1;
                    pos++;}
                while (isdigit(str[pos])) {
                    new_node.x = new_node.x * 10 + str[pos] - '0';
                    pos++;}                            }
            node[num_node].succ = num_node + 1;
            ++num_node;
            ++pos;        }
        node[num_node - 1].succ = -1;    }
}


int Valor(int x, int y) {
    if (spreadsheet[x][y].index == -1) {
        return spreadsheet[x][y].value;}
    else {
        int sum = 0;
        int index = spreadsheet[x][y].index;
        while (index != -1) {
            sum += Valor(node[index].x, node[index].y);
            index = node[index].succ;        }
        spreadsheet[x][y].value = sum;
        spreadsheet[x][y].index = -1;
        return sum;} }


int main() {
    scanf("%d", &t);
    while (t--){
        num_node = 0;
        scanf("%d%d", &n, &m);
        getchar();
        for (int i = 1; i <= m; ++i){
            for (int j = 1; j <= n; ++j){
                char str[100];
                scanf("%s", str);
                Ejecutar(i, j, str);     }
            getchar();        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (spreadsheet[i][j].index != -1) {
                    Valor(i, j);
                }
            }        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n - 1; ++j) {
                printf("%d ", spreadsheet[i][j].value);}
            printf("%d\n", spreadsheet[i][n]);
        }
    }
    return 0;}


