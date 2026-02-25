#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

// ========== 数据结构定义 ==========
typedef struct {
    char reason[20];
    int pomodoro_count;
    char time_str[20];
} InterruptRecord;

typedef struct {
    char date[11];
    int total_pomodoros;
    int interrupt_count;
    InterruptRecord interrupts[50];
    int interrupt_index;
    char best_time[20];
    int focus_score;
} DailyStats;

// 全局变量
DailyStats today_stats;
int current_pomodoro = 0;
int focus_minutes = 0;

// ========== 函数声明 ==========
void print_banner();
void print_menu();
void start_pomodoro();
void add_interrupt();
void generate_report();
void save_to_file();
void load_from_file();
void clear_screen();
void get_current_time(char *buffer);
void draw_progress_bar(int minutes, int total_minutes);
void show_motivation();

// ========== 主函数 ==========
int main() {
    int choice;
    
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // 初始化数据
    strcpy(today_stats.date, "2024-01-01");
    today_stats.total_pomodoros = 0;
    today_stats.interrupt_count = 0;
    today_stats.interrupt_index = 0;
    today_stats.focus_score = 0;
    strcpy(today_stats.best_time, "暂无数据");
    
    while(1) {
        clear_screen();
        print_banner();
        printf("\n📅 今天是: %s\n", today_stats.date);
        printf("🍅 今日已完成番茄钟: %d\n", today_stats.total_pomodoros);
        printf("⚠️  今日打断次数: %d\n\n", today_stats.interrupt_count);
        
        print_menu();
        printf("\n👉 请选择操作 (1-5): ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        
        switch(choice) {
            case 1:
                printf("\n🚧 功能开发中，敬请期待...\n");
                Sleep(1500);
                break;
            case 2:
                printf("\n🚧 功能开发中，敬请期待...\n");
                Sleep(1500);
                break;
            case 3:
                printf("\n🚧 功能开发中，敬请期待...\n");
                Sleep(1500);
                break;
            case 4:
                printf("\n🚧 功能开发中，敬请期待...\n");
                Sleep(1500);
                break;
            case 5:
                printf("\n✨ 感谢使用，再见！\n");
                printf("⏎ 按回车键退出...");
                getchar(); 
                exit(0);
            default:
                printf("\n❌ 输入错误，请重新选择！\n");
                Sleep(1500);
        }
    }
    
    return 0;
}

// ========== 函数实现 ==========
void print_banner() {
    printf("\n");
    printf("  +========================================+\n");
    printf("  |   🍅 拖延症终结者 - Pomodoro助手      |\n");
    printf("  |      \"25分钟改变拖延习惯\"             |\n");
    printf("  +========================================+\n");
}

void print_menu() {
    printf("  +------------------------------------+\n");
    printf("  |  🍅 1. 开始一个番茄钟              |\n");
    printf("  |  📝 2. 记录打断原因                |\n");
    printf("  |  📊 3. 生成专注力报告              |\n");
    printf("  |  💪 4. 获取今日动力                |\n");
    printf("  |  🚪 5. 退出程序                    |\n");
    printf("  +------------------------------------+\n");
}

void clear_screen() {
    system("cls");
}

void get_current_time(char *buffer) {
    // 临时实现
    strcpy(buffer, "2024-01-01 12:00:00");
}

void draw_progress_bar(int minutes, int total_minutes) {
    // 临时实现
    printf("\n⏳ 进度: %d/%d 分钟\n", minutes, total_minutes);
}

void start_pomodoro() {
    // 将在后续版本实现
}

void add_interrupt() {
    // 将在后续版本实现
}

void generate_report() {
    // 将在后续版本实现
}

void show_motivation() {
    // 将在后续版本实现
}

void save_to_file() {
    // 将在后续版本实现
}

void load_from_file() {
    // 将在后续版本实现
}