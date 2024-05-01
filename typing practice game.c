#define _CRT_SECURE_NO_WARNINGS

// 필요한 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// 최대 단어 길이, 최대 목숨, 최대 플레이어 수를 상수로 정의
#define MAX_WORD_LENGTH 30
#define MAX_LIVES 5
#define MAX_PLAYERS 10

// 게임의 난이도를 나타내는 열거형 정의
typedef enum { EASY, MEDIUM, HARD } Difficulty;

// 플레이어 정보를 담는 구조체 정의
typedef struct {
    char name[50];
    int score;
    Difficulty difficulty;
} Player;

// 각 난이도별 게임 시간 및 점수를 배열로 정의
int difficulty_times[] = { 10, 15, 20 };
int difficulty_scores[] = { 1, 2, 3 };

// 쉬움, 중간, 어려움 난이도의 단어 목록을 초기화하는 함수
char* easy_words[MAX_WORD_LENGTH];
char* medium_words[MAX_WORD_LENGTH];
char* hard_words[MAX_WORD_LENGTH];
Player* ranking;

// 게임에 사용될 단어 목록을 초기화하는 함수
void initialize_word_list(char** word_list, char* words[]) {
    // 단어 리스트 초기화
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        word_list[i] = words[i];
    }
}
// 게임에 사용될 단어 목록을 초기화하는 함수
void initialize_words() {
    // 각 난이도에 해당하는 단어 목록 정의
    char* easy_word_list[MAX_WORD_LENGTH] = {
        "cat", "dog", "book", "tree", "ball", "sun", "moon", "star", "fire", "water",
        "apple", "banana", "orange", "flower", "music"
    };
    char* medium_word_list[MAX_WORD_LENGTH] = {
        "computer", "university", "restaurant", "championship", "environment", "keyboard",
        "internet", "programming", "mountain", "river", "elephant", "tiger", "lion",
        "giraffe", "ocean"
    };
    char* hard_word_list[MAX_WORD_LENGTH] = {
        "concatenation", "philosophy", "architecture", "microprocessor", "biotechnology",
        "telecommunication", "psychoanalysis", "interdisciplinary", "responsibility",
        "misinterpretation", "extraterrestrial", "quantum", "paradox", "phenomenon", "catastrophe"
    };

    // 단어 목록 초기화
    initialize_word_list(easy_words, easy_word_list);
    initialize_word_list(medium_words, medium_word_list);
    initialize_word_list(hard_words, hard_word_list);
}

// 랭킹 배열을 초기화하는 함수
void initialize_ranking() {
    // 랭킹 배열 동적 할당
    ranking = (Player*)malloc(MAX_PLAYERS * sizeof(Player));
    // 각 플레이어의 점수 초기화
    for (int i = 0; i < MAX_PLAYERS; i++) {
        ranking[i].score = 0;
    }
}

// 랭킹에 플레이어를 추가하는 함수
void add_to_ranking(char* name, int score, Difficulty difficulty) {
    // 점수에 따라 랭킹에 추가
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (ranking[i].score < score) {
            // 새로운 플레이어 정보를 랭킹에 삽입
            for (int j = MAX_PLAYERS - 1; j > i; j--) {
                ranking[j] = ranking[j - 1];
            }
            // 플레이어 정보 업데이트
            strcpy(ranking[i].name, name);
            ranking[i].score = score;
            ranking[i].difficulty = difficulty;
            break;
        }
    }
}

// 랭킹 배열을 메모리에서 해체하는 함수
void free_ranking() {
    // 랭킹 배열 메모리 해체
    free(ranking);
}

// 게임 시작 시 화면에 출력되는 시작 화면을 출력하는 함수
void print_intro() {
    // 화면 초기화
    system("cls");
    // 시작 화면 출력
    printf("\033[1;36m");
    printf("\n\t\t\t\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("\t\t\t\t\t\t|   타자 연습 게임   |\n");
    printf("\t\t\t\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("\033[0m");
    printf("\n\n\t\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");
    printf("\t\t\t\t\t\t    1. 게임 시작\n\n\n\n");
    printf("\t\t\t\t\t\t    2. 게임 방법\n\n\n\n");
    printf("\t\t\t\t\t\t    3. 랭킹 보기\n\n\n\n");
    printf("\t\t\t\t\t\t    4. 게임 종료\n\n");
    printf("\t\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n\n");
}

// 게임 방법을 출력하는 함수
void print_instructions() {
    // 화면 초기화
    system("cls");
    // 게임 방법 출력
    printf("\033[1;36m");
    printf("\n\t\t\t게임 방법\n\n");
    printf("\033[0m");
    printf("1. 게임 시작을 선택하면 플레이어 이름을 입력하고, 난이도를 선택할 수 있습니다.\n");
    printf("2. 단어가 화면에 표시되고, 정확하게 입력해야 합니다.\n");
    printf("3. 제한 시간 내에 정확하게 입력하면 점수가 증가하고, 틀리면 목숨이 감소합니다.\n");
    printf("4. 목숨이 모두 소진되거나 모든 단어를 완료하면 게임이 종료됩니다.\n");
    printf("5. 게임 종료 후 획득한 점수에 따라 랭킹이 업데이트됩니다.\n");
    printf("6. 게임 중에 'item'을 입력하면 아이템을 사용할 수 있습니다.\n");
    printf("\n아이템에 따른 세부정보:\n");
    printf("- 목숨 1개를 추가합니다.\n");
    printf("- 점수 2배를 얻습니다.\n");
    printf("\n난이도에 따른 세부 정보:\n");
    printf("- 쉬움 난이도: 목숨 5개, 제한 시간 10초, 점수 1점\n");
    printf("- 보통 난이도: 목숨 4개, 제한 시간 15초, 점수 2점\n");
    printf("- 어려움 난이도: 목숨 3개, 제한 시간 20초, 점수 3점\n");
    printf("\nEnter 키를 누르면 메뉴로 돌아갑니다...");
    getchar();
}

// 목숨 개수를 화면에 출력하는 함수
void print_hearts(int lives) {
    // 목숨 개수 출력
    printf("목숨: ");
    for (int i = 0; i < lives; i++) {
        printf("\033[1;31m♥ \033[0m");
    }
    printf("\n");
}

// 게임을 시작하는 함수
void game_start() {
    // 필요한 변수들 초기화
    int difficulty_index, lives, word_count;
    char** word_list;

    // 난이도 선택
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t난이도 선택 (1: 쉬움, 2: 보통, 3: 어려움) 1 ~ 3을 입력하세요.\n\t\t\t\t: ");
    scanf("%d", &difficulty_index);

    // 선택한 난이도에 따라 설정
    Difficulty difficulty;
    switch (difficulty_index) {
    case 1:
        word_list = easy_words;
        lives = MAX_LIVES;
        word_count = 15;
        difficulty = EASY;
        break;
    case 2:
        word_list = medium_words;
        lives = MAX_LIVES - 1;
        word_count = 15;
        difficulty = MEDIUM;
        break;
    case 3:
        word_list = hard_words;
        lives = MAX_LIVES - 2;
        word_count = 15;
        difficulty = HARD;
        break;
    default:
        printf("\t\t\t잘못된 입력입니다. 쉬움 난이도로 시작합니다.\n");
        word_list = easy_words;
        lives = MAX_LIVES;
        word_count = 15;
        difficulty = EASY;
    }

    // 플레이어 이름 입력
    char player_name[50];
    printf("\n\t\t\t\t플레이어 이름을 입력하세요: ");
    scanf("%49s", player_name);

    // 점수, 시간, 아이템 설정
    int score = 0;
    double total_time = 0;
    int has_item = 1;

    // 시드 값 설정
    srand(time(NULL));

    // 게임 루프
    for (int i = 0; i < word_count && lives > 0; i++) {
        // 랜덤 단어 선택
        int random_index = rand() % word_count;
        char* word = word_list[random_index];

        // 화면 초기화
        system("cls");
        // 게임 화면 출력
        printf("\033[1;36m");
        printf("\n\n\t\t\t\t\t\t타자 연습 게임\n\n\n\t\t\t");
        printf("\033[0m");
        printf("현재 난이도: %s\n\t\t\t", (difficulty == EASY) ? "쉬움" : ((difficulty == MEDIUM) ? "보통" : "어려움"));
        print_hearts(lives);
        printf("\t\t\t제한 시간: %ds\n", difficulty_times[difficulty_index - 1]);
        printf("\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");
        printf("\t\t\t\t\t\t    %s\t\t\t   \n", word);
        printf("\n\t\t\tㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
        printf("\t\t\t아이템(목숨 +1 또는 점수 2배) 사용 가능 여부: %s\n", has_item ? "가능" : "불가능");
        printf("\t\t\t현재 점수: %d\n", score);
        printf("\n\n\t\t\t\t\t\t입력: ");

        // 시작 시간 기록
        clock_t start_time = clock();
        char input[MAX_WORD_LENGTH];
        scanf("%s", input);
        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        total_time += elapsed_time;

        // 시간 초과 여부 확인
        if (elapsed_time > difficulty_times[difficulty_index - 1]) {
            printf("\t\t\t시간초과!");
            double time_difference = -(15.00 - elapsed_time);
            printf("\t\t\t\t    초과 시간: %.2f초\n", time_difference);
            lives--;
            printf("\n\t\t\tEnter 키를 누르면 계속합니다...");
            getchar();
            getchar();
            continue;
        }

        // 아이템 사용 여부 확인
        if (strcmp(input, "item") == 0 && has_item) {
            if (lives < MAX_LIVES) {
                printf("\t\t\t아이템 사용: 목숨을 1개 추가합니다!\n");
                lives++;
            }
            else {
                printf("\t\t\t아이템 사용: 점수를 2배로 받습니다!\n");
                score += 2;
            }
            has_item = 0;
        }
        // 단어 입력 확인
        else if (strcmp(input, word) == 0) {
            printf("\n\n\t\t\t정확합니다!");
            score += difficulty_scores[difficulty_index - 1];
        }
        // 틀린 입력 처리
        else {
            printf("\n\n\t\t\t틀렸습니다!");
            lives--;
        }
        printf("\t\t\t\t     소요 시간: %.2f초", elapsed_time);
        printf("\n\n\t\t\tEnter 키를 누르면 계속합니다...\n");
        getchar();
        getchar();
    }

    // 화면 초기화
    system("cls");
    // 게임 종료 화면 출력
    printf("\033[1;36m");
    printf("\n\n\t\t\t\t\t\t게임 종료\n\n\n");
    printf("\033[0m");
    // 랭킹에 플레이어 추가
    printf("\t\t\t\t\t최종 점수: %d, 총 소요 시간: %.2f초\n\n", score, total_time);
    add_to_ranking(player_name, score, difficulty);
    printf("\t\t\t\t\tEnter 키를 누르면 메뉴로 돌아갑니다...\n");
    getchar();
}

// 랭킹을 화면에 출력하는 함수
void show_ranking() {
    // 화면 초기화
    system("cls");
    printf("\033[1;36m");
    printf("\n\t\t\t랭킹\n\n");
    printf("\033[0m");

    printf("\033[1;33m");
    printf("%-5s %-20s %-10s %s\n", "순위", "이름", "점수", "난이도");
    printf("\033[0m");

    int empty = 1;

    // 랭킹 배열을 복사하여 정렬
    Player sorted_ranking[MAX_PLAYERS];
    memcpy(sorted_ranking, ranking, MAX_PLAYERS * sizeof(Player));

    // 점수가 높은 순으로 정렬
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = i + 1; j < MAX_PLAYERS; j++) {
            if (sorted_ranking[i].score < sorted_ranking[j].score) {
                Player temp = sorted_ranking[i];
                sorted_ranking[i] = sorted_ranking[j];
                sorted_ranking[j] = temp;
            }
        }
    }

    // 난이도가 동일한 경우에는 어려움, 보통, 쉬움 순으로 정렬
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = i + 1; j < MAX_PLAYERS; j++) {
            if (sorted_ranking[i].score == sorted_ranking[j].score && sorted_ranking[i].difficulty < sorted_ranking[j].difficulty) {
                Player temp = sorted_ranking[i];
                sorted_ranking[i] = sorted_ranking[j];
                sorted_ranking[j] = temp;
            }
        }
    }

    // 정렬된 랭킹 출력
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (sorted_ranking[i].score != 0) {
            printf("%-5d %-20s %-10d ", i + 1, sorted_ranking[i].name, sorted_ranking[i].score);
            switch (sorted_ranking[i].difficulty) {
            case HARD:
                printf("어려움\n");
                break;
            case MEDIUM:
                printf("보통\n");
                break;
            case EASY:
                printf("쉬움\n");
                break;
            }
            empty = 0;
        }
    }

    if (empty) {
        printf("기록이 없습니다.\n");
    }

    printf("\nEnter 키를 누르면 메뉴로 돌아갑니다...");
    getchar();
}

// 커서 모양을 설정하는 함수
void setcursortype(int c) {
    // 커서 정보 설정
    CONSOLE_CURSOR_INFO CurInfo;
    switch (c)
    {
    case 0:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case 1:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case 2:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    default:
        break;
    }
    // 커서 모양 설정
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 좌표를 이동하는 함수
void gotoxy(int x, int y) {
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

// 메인 함수
int main() {
    // 랭킹, 단어 초기화
    initialize_words();
    initialize_ranking();

    // 커서 설정
    setcursortype(0);

    int x = 70, y = 8;
    int key;
    print_intro();

    gotoxy(x, y);
    printf("◀");

    while (1) {
        key = _getch();
        gotoxy(x, y);
        printf(" ");

        if (key == 224) {
            key = _getch();
        }

        switch (key) {
        case (int)'w': case 72:
            if (y > 11) y -= 4;
            break;
        case (int)'s': case 80:
            if (y < 17) y += 4;
            break;
        case 13:
            if (y == 12) {
                print_instructions();
                print_intro();
                gotoxy(x, y);
                printf("◀");
            }
            else if (y == 8) {
                game_start();
                print_intro();
                gotoxy(x, y);
                printf("◀");
            }
            else if (y == 16) {
                show_ranking();
                print_intro();
                gotoxy(x, y);
                printf("◀");
            }
            else {
                printf("\n\n\n\t\t\t\t게임을 종료합니다.\n");
                free_ranking();
                return 0;
            }
        }

        gotoxy(x, y);
        printf("◀");
    }
    free_ranking();
    return 0;
}