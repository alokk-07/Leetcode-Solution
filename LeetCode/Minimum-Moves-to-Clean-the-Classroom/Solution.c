1#include <stdlib.h>
2#include <string.h>
3
4typedef struct {
5    int r, c;
6    int energy;
7    int mask;
8    int dist;
9} State;
10
11int minMoves(char** classroom, int classroomSize, int energy) {
12    int m = classroomSize;
13    int n = strlen(classroom[0]);
14
15    // Give every litter cell an ID from 0 to k-1
16    int id[20][20];
17    memset(id, -1, sizeof(id));
18
19    int sr = 0, sc = 0;
20    int k = 0;
21
22    for (int i = 0; i < m; i++) {
23        for (int j = 0; j < n; j++) {
24            if (classroom[i][j] == 'S') {
25                sr = i;
26                sc = j;
27            }
28            else if (classroom[i][j] == 'L') {
29                id[i][j] = k++;
30            }
31        }
32    }
33
34    int target = (1 << k) - 1;
35
36    // visited[r][c][energy][mask]
37    int totalStates = m * n * (energy + 1) * (1 << k);
38
39    unsigned char *visited =
40        (unsigned char*)calloc(totalStates, sizeof(unsigned char));
41
42    // Queue for BFS
43    State *queue =
44        (State*)malloc(totalStates * sizeof(State));
45
46    int front = 0;
47    int rear = 0;
48
49    // Starting state
50    int startIndex =
51        (((sr * n + sc) * (energy + 1) + energy) * (1 << k));
52
53    visited[startIndex] = 1;
54
55    queue[rear++] = (State){sr, sc, energy, 0, 0};
56
57    int dr[] = {-1, 1, 0, 0};
58    int dc[] = {0, 0, -1, 1};
59
60    while (front < rear) {
61        State cur = queue[front++];
62
63        // All litter collected
64        if (cur.mask == target) {
65            free(visited);
66            free(queue);
67            return cur.dist;
68        }
69
70        for (int d = 0; d < 4; d++) {
71            int nr = cur.r + dr[d];
72            int nc = cur.c + dc[d];
73
74            // Outside grid
75            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
76                continue;
77
78            // Obstacle
79            if (classroom[nr][nc] == 'X')
80                continue;
81
82            // Moving costs 1 energy
83            if (cur.energy == 0)
84                continue;
85
86            int newEnergy = cur.energy - 1;
87            int newMask = cur.mask;
88
89            // Collect litter
90            if (classroom[nr][nc] == 'L') {
91                newMask |= (1 << id[nr][nc]);
92            }
93
94            // Reset energy
95            if (classroom[nr][nc] == 'R') {
96                newEnergy = energy;
97            }
98
99            int index =
100                (((nr * n + nc) * (energy + 1) + newEnergy)
101                 * (1 << k)) + newMask;
102
103            if (!visited[index]) {
104                visited[index] = 1;
105
106                queue[rear++] =
107                    (State){nr, nc, newEnergy, newMask, cur.dist + 1};
108            }
109        }
110    }
111
112    free(visited);
113    free(queue);
114
115    return -1;
116}
117