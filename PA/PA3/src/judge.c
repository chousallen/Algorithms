#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

const char* input_file[] = {"./inputs/public_case_0.in", "./inputs/public_case_1.in", "./inputs/public_case_2.in",
                        "./inputs/public_case_3.in", "./inputs/public_case_4.in", "./inputs/public_case_5.in",
                        "./inputs/public_case_6.in", "./inputs/public_case_7.in", "./inputs/public_case_8.in"};
int type = 0;
int testcase = 0;
int adjM[10000][10000] = {};
int weightM[10000][10000] = {};
int went[10000] = {};
int p[10000] = {};
int undirected = 0;
int seed = -1;

int parse(char* argv[]) {
    if(strcmp(argv[1], "-c") == 0) {
        if(strcmp(argv[2], "UUW") == 0) {
            type = 0;
            return 0;
        }
        else if(strcmp(argv[2], "UW") == 0) {
            type = 1;
            return 0;
        }
        else if(strcmp(argv[2], "DW") == 0) {
            type = 2;
            return 0;
        }
        else if(strcmp(argv[2], "ALL") == 0) {
            type = 3;
            return 0;
        }
        else return -1;
    }
    else if(strcmp(argv[1], "-t") == 0) {
        testcase = (int)(argv[2][0] - '0');
        if(!((0 <= testcase && testcase <= 4) || (7 <= testcase && testcase <= 8))) {
            return -1;
        }
        else return 1;
    }
    else if(strcmp(argv[1], "-s") == 0) {
        sscanf(argv[2], "%d", &seed);
        return 2;
    }
    else return -1;
}

void usage() {
    printf("\"./judge -c <UUW/UW/DW/ALL>\" or \"./judge -t <0-8 except 5,6>\"\n");
    printf("Advanced: \"./judge -s <seed>\" for specific DW testcase\n");
}

void wrong_answer(long long int expect, long long int found) {
    printf("\033[0;31mWA: Not minimum (expect: %lld, found %lld)\033[0m\n", expect, found);
}

void invalid_edge(int v1, int v2, int w) {
    printf("\033[0;31mWA: Invalid edge (%d, %d, %d)\033[0m\n", v1, v2, w);
}

void result_unmatch(long long int answer, long long int truth) {
    printf("\033[0;31mWA: Provided sum doesn't match (provide: %lld, but in fact it's %lld)\033[0m\n", answer, truth);
}

void cycle_exist() {
    printf("\033[0;31mWA: Exist cycle(s)\033[0m\n");
}

int DFSAux(int index, int n) {
    went[index] = 1;
    for(int i = 0; i < n; i++) {
        if(adjM[index][i] == 1) {
            if(went[i] == 0) {
                p[i] = index;
                if(DFSAux(i, n) == -1) {
                    printf("%d\n", index);
                    return -1;
                }
            }
            else if(went[i] == 1) {
                if(!(i == p[index] && undirected)) {
                    printf("%d\n", index);
                    return -1;
                }
            }
        }
    }
    went[index] = 2;
    return 0;
}

int DFS(int n) {
    for(int i = 0; i < n; i++) {
        if(went[i] == 0) {
            if(DFSAux(i, n) == -1) {
                return -1;
            }
        }
    }
    return 0;
}

void clean_data(int n) {
    for(int i = 0; i < n; i++) {
        went[i] = 0;
        p[i] = -1;
        for(int j = 0; j < n; j++) {
            adjM[i][j] = 0;
            weightM[i][j] = 0;
        }
    }
}

void testcase0() {
    undirected = 0;
    printf("\033[0;33mPublic Case 0 (Directed Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[0], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[0], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        if(answer != 5) {
            wrong_answer(5, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPublic Case 0: Accepted.\033[0m\n");

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase1() {
    undirected = 1;
    printf("\033[0;33mPublic Case 1 (Undirected Unweighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[1], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[1], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
            adjM[v2][v1] = 1;
            weightM[v2][v1] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        if(answer != 21) {
            wrong_answer(21, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                adjM[v2][v1] = 0;
                weightM[v2][v1] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPublic Case 1: Accepted.\033[0m\n");

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase2() {
    undirected = 1;
    printf("\033[0;33mPublic Case 2 (Undirected Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[2], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[2], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
            adjM[v2][v1] = 1;
            weightM[v2][v1] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        if(answer != -3330) {
            wrong_answer(-3330, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                adjM[v2][v1] = 0;
                weightM[v2][v1] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPublic Case 2: Accepted.\033[0m\n");

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase3() {
    undirected = 0;
    printf("\033[0;33mPublic Case 3 (Directed Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[3], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[3], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        if(answer > 0) {
            printf("\033[0;31mPublic Case 3: Performance: %d.\033[0m\n", answer);
        }
        else if(answer > -20000) {
            printf("\033[0;34mPublic Case 3: Performance: %d.\033[0m\n", answer);
        }
        else {
            printf("\033[0;32mPublic Case 3: Performance: %d.\033[0m\n", answer);
        }

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase4() {
    undirected = 1;
    printf("\033[0;33mPublic Case 4 (Undirected Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[4], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[4], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
            adjM[v2][v1] = 1;
            weightM[v2][v1] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        if(answer != 0) {
            wrong_answer(0, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                adjM[v2][v1] = 0;
                weightM[v2][v1] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPublic Case 4: Accepted.\033[0m\n");

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase7() {
    undirected = 0;
    printf("\033[0;33mPublic Case 7 (Directed Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[7], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[7], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        if(answer > 0) {
            printf("\033[0;31mPublic Case 7: Performance: %d.\033[0m\n", answer);
        }
        else if(answer > -11000) {
            printf("\033[0;34mPublic Case 7: Performance: %d.\033[0m\n", answer);
        }
        else {
            printf("\033[0;32mPublic Case 7: Performance: %d.\033[0m\n", answer);
        }

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcase8() {
    undirected = 0;
    printf("\033[0;33mPublic Case 8 (Directed Weighted)\033[0m\n");
    if(fork() == 0) {
        execlp("./bin/cb", "cb", input_file[8], "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen(input_file[8], "r");
        char c;
        int n, m, v1, v2, w, che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        if(answer > 0) {
            printf("\033[0;31mPublic Case 8: Performance: %d.\033[0m\n", answer);
        }
        else if(answer > -70000) {
            printf("\033[0;34mPublic Case 8: Performance: %d.\033[0m\n", answer);
        }
        else {
            printf("\033[0;32mPublic Case 8: Performance: %d.\033[0m\n", answer);
        }

    clean:
        clean_data(n);
        fclose(fp);
        remove("./testout.out");
        return;
    }
}

void testcaseUUW(int num, int n, int m) {
    undirected = 1;
    srand(time(NULL));
    FILE* fp = fopen("./input", "w");
    char c;
    int v1, v2, w, che = 0;
    c = 'u';
    fprintf(fp, "%c\n", c);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", m);
    v1 = rand() % n;
    w = 1;
    for(v2 = 0; v2 < n; v2++) {
        if(v2 != v1) {
            fprintf(fp, "%d %d %d\n", v1, v2, w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
            adjM[v2][v1] = 1;
            weightM[v2][v1] = w;
        }
    }
    int edgeCount = n - 1;
    while(edgeCount != m) {
        for(v1 = 0; v1 < n; v1++) {
            for(v2 = 0; v2 < n; v2++) {
                if(v1 == v2 || adjM[v1][v2] == 1) continue;
                if(rand() % 5 > 1) {
                    fprintf(fp, "%d %d %d\n", v1, v2, w);
                    adjM[v1][v2] = 1;
                    weightM[v1][v2] = w;
                    adjM[v2][v1] = 1;
                    weightM[v2][v1] = w;
                    edgeCount++;
                    if(edgeCount == m) break;
                }
            }
            if(edgeCount == m) break;
        }
    }
    fprintf(fp, "0\n");
    fclose(fp);

    printf("\033[0;33mPrivate Case %d (Undirected Unweighted, n = %d, m = %d)\033[0m\n", num, n, m);
    if(fork() == 0) {
        alarm(60);
        execlp("./bin/cb", "cb", "./input", "./testout.out", (char*)0);
    }
    else {
        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        if(answer != (m - n + 1)) {
            wrong_answer(m - n + 1, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                adjM[v2][v1] = 0;
                weightM[v2][v1] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPrivate Case %d: Accepted.\033[0m\n", num);

    clean:
        clean_data(n);
        fclose(fp);
        remove("./input");
        remove("./testout.out");
        return;
    }
}

void testcaseUW(int num, int n, int m, int top) {
    undirected = 1;
    srand(time(NULL));
    FILE* fp = fopen("./input", "w");
    char c;
    int v1, v2, w;
    long long int trueAns = 0, che = 0;
    c = 'u';
    fprintf(fp, "%c\n", c);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", m);
    v1 = rand() % n;
    w = top;
    for(v2 = 0; v2 < n; v2++) {
        if(v2 != v1) {
            fprintf(fp, "%d %d %d\n", v1, v2, w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = top;
            adjM[v2][v1] = 1;
            weightM[v2][v1] = top;
        }
    }
    int edgeCount = n - 1;
    while(edgeCount != m) {
        for(v1 = 0; v1 < n; v1++) {
            for(v2 = 0; v2 < n; v2++) {
                if(v1 == v2 || adjM[v1][v2] == 1) continue;
                if(rand() % 5 > 1) {
                    w = rand() % (101 + top) - 100;
                    fprintf(fp, "%d %d %d\n", v1, v2, w);
                    adjM[v1][v2] = 1;
                    weightM[v1][v2] = w;
                    adjM[v2][v1] = 1;
                    weightM[v2][v1] = w;
                    trueAns += w;
                    edgeCount++;
                    if(edgeCount == m) break;
                }
            }
            if(edgeCount == m) break;
        }
    }
    fprintf(fp, "0\n");
    fclose(fp);

    printf("\033[0;33mPrivate Case %d (Undirected Weighted, n = %d, m = %d, top = %d)\033[0m\n", num, n, m, top);
    if(fork() == 0) {
        alarm(60);
        execlp("./bin/cb", "cb", "./input", "./testout.out", (char*)0);
    }
    else {
        wait(NULL);

        fp = fopen("./testout.out", "r");
        long long int answer;
        fscanf(fp, "%lld", &answer);
        if(answer != trueAns) {
            wrong_answer(trueAns, answer);
            goto clean;

        }
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                adjM[v2][v1] = 0;
                weightM[v2][v1] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        printf("\033[0;32mPrivate Case %d: Accepted.\033[0m\n", num);

    clean:
        clean_data(n);
        fclose(fp);
        remove("./input");
        remove("./testout.out");
        return;
    }
}

void testcaseDW(int num, int n, int m, int seed) {
    undirected = 0;
    // srand(seed);
    FILE* fp = fopen("./input", "w");
    char c;
    int v1, v2, w;
    long long int thres = 0, che = 0;
    c = 'd';
    fprintf(fp, "%c\n", c);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", m);
    v1 = rand() % n;
    w = (rand() % 201) - 100;
    for(v2 = 0; v2 < n; v2++) {
        if(v2 != v1) {
            if(rand() % 2 == 1) {
                fprintf(fp, "%d %d %d\n", v1, v2, w);
                adjM[v1][v2] = 1;
                weightM[v1][v2] = w;
            }
            else {
                fprintf(fp, "%d %d %d\n", v2, v1, w);
                adjM[v2][v1] = 1;
                weightM[v2][v1] = w;
            }
        }
    }
    int edgeCount = n - 1;
    while(edgeCount != m) {
        for(v1 = 0; v1 < n; v1++) {
            for(v2 = 0; v2 < n; v2++) {
                if(v1 == v2 || adjM[v1][v2] == 1) continue;
                if(rand() % 5 > 1) {
                    w = rand() % 201 - 100;
                    fprintf(fp, "%d %d %d\n", v1, v2, w);
                    adjM[v1][v2] = 1;
                    weightM[v1][v2] = w;
                    thres += w;
                    edgeCount++;
                    if(edgeCount == m) break;
                }
            }
            if(edgeCount == m) break;
        }
    }
    fprintf(fp, "0\n");
    fclose(fp);

    printf("\033[0;33mPrivate Case %d (Directed Weighted, seed = %d)\033[0m\n", num, seed);
    if(fork() == 0) {
        execlp("./bin/cb", "cb", "./input", "./testout.out", (char*)0);
    }
    else {
        FILE* fp = fopen("./input", "r");
        char c;
        int v1, v2, w;
        long long int che = 0;
        fscanf(fp, "%c", &c);
        fscanf(fp, "%d", &n);
        fscanf(fp, "%d", &m);
        for(int i = 0; i < m; i++) {
            fscanf(fp, "%d %d %d", &v1, &v2, &w);
            adjM[v1][v2] = 1;
            weightM[v1][v2] = w;
        }
        fclose(fp);

        wait(NULL);

        fp = fopen("./testout.out", "r");
        int answer;
        fscanf(fp, "%d", &answer);
        while(fscanf(fp, "%d %d %d", &v1, &v2, &w) != EOF) {
            if(adjM[v1][v2] != 1 || weightM[v1][v2] != w) {
                invalid_edge(v1, v2, w);
                goto clean;
            }
            else {
                adjM[v1][v2] = 0;
                weightM[v1][v2] = 0;
                che += w;
            }
        }
        if(che != answer) {
            result_unmatch(answer, che);
            goto clean;
        }
        if(DFS(n) == -1) {
            cycle_exist();
            goto clean;
        }
        if(answer > thres) {
            printf("\033[0;31mPrivate Case %d: Performance: %d.\033[0m\n", num, answer);
        }
        else {
            printf("\033[0;34mPrivate Case %d: Performance: %d.\033[0m\n", num, answer);
        }

    clean:
        clean_data(n);
        fclose(fp);
        remove("./input");
        remove("./testout.out");
        return;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        usage();
        return 0;
    }
    int va = parse(argv);
    if(va == -1) {
        usage();
        return 0;
    }
    else if(va == 0) {
        clean_data(10000);
        int cat1 = 0, cat2 = 0, cat3 = 0;
        if(type == 0) {
            testcase1();
            srand(time(NULL));
            cat1 = rand() % 10000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 20000000) cat2 = 20000000;
            testcaseUUW(1, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)));
            testcaseUUW(2, 10000, 9999);
            testcaseUUW(3, 10000, 20000000);
            testcaseUUW(4, 3, 2);
        }
        else if(type == 1) {
            testcase2();
            testcase4();
            cat1 = rand() % 10000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 20000000) cat2 = 20000000;
            cat3 = rand() % 201 - 100;
            testcaseUW(5, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(6, 10000, 9999, cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(7, 10000, 20000000, cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(8, 3, 2, cat3);
        }
        else if(type == 2) {
            testcase0();
            testcase3();
            testcase7();
            testcase8();

            srand(time(NULL));
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(9, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(10, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            sleep(1);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(11, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            sleep(1);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(12, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
        }
        else {
            testcase0();
            testcase1();
            testcase2();
            testcase3();
            testcase4();
            testcase7();
            testcase8();

            srand(time(NULL));
            cat1 = rand() % 10000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 20000000) cat2 = 20000000;
            testcaseUUW(1, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)));
            testcaseUUW(2, 10000, 9999);
            testcaseUUW(3, 10000, 20000000);
            testcaseUUW(4, 3, 2);

            cat1 = rand() % 10000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 20000000) cat2 = 20000000;
            cat3 = rand() % 201 - 100;
            testcaseUW(5, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(6, 10000, 9999, cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(7, 10000, 20000000, cat3);
            cat3 = rand() % 201 - 100;
            testcaseUW(8, 3, 2, cat3);
            
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(9, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(10, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            sleep(1);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(11, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
            sleep(1);
            seed = (rand() % 100);
            srand(seed);
            cat1 = rand() % 5000;
            cat2 = rand() % (cat1 * (cat1 - 1) / 2);
            if(cat2 > 10000) cat2 = 10000;
            testcaseDW(12, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
        }
    }
    else if(va == 1) {
        void (*testcases[9])(void) = {testcase0, testcase1, testcase2, testcase3, testcase4, NULL, NULL, testcase7, testcase8};
        testcases[testcase]();
    }
    else {
        srand(seed);
        int cat1 = rand() % 5000;
        int cat2 = rand() % (cat1 * (cat1 - 1) / 2);
        if(cat2 > 10000) cat2 = 10000;
        testcaseDW(10, cat1, (cat2 > (cat1 - 1) ? cat2 : (cat1 - 1)), seed);
    }
    return 0;
}