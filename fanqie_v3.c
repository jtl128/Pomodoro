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
    
    get_current_time(today_stats.date);
    today_stats.date[10] = '\0';
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
                start_pomodoro();  // ✅ 已实现
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
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void draw_progress_bar(int minutes, int total_minutes) {
    int i;
    int progress = (minutes * 50) / total_minutes;
    
    printf("\n⏳ 专注进度: [");
    for(i = 0; i < progress; i++) printf("█");
    for(i = progress; i < 50; i++) printf("░");
    printf("] %d/%d 分钟\n", minutes, total_minutes);
}

// ✅ 新增：完整的番茄钟功能
void start_pomodoro() {
    int work_minutes = 25;
    int elapsed = 0;
    int choice;
    
    current_pomodoro++;
    printf("\n+==========================================+\n");
    printf(" 🍅 第%d个番茄钟开始！专注25分钟\n", current_pomodoro);
    printf("+==========================================+\n");
    printf("💡 提示：专注期间可以按 'p' 暂停\n\n");
    
    // 工作时段
    for(elapsed = 1; elapsed <= work_minutes; elapsed++) {
        clear_screen();
        print_banner();
        printf("\n+==========================================+\n");
        printf(" 🎯 正在专注中... 第%d个番茄钟\n", current_pomodoro);
        draw_progress_bar(elapsed, work_minutes);
        printf("\n⏰ 剩余时间: %d分钟\n", work_minutes - elapsed);
        printf("+==========================================+\n");
        
        // 检查暂停
        if(kbhit()) {
            int key = getch();
            if(key == 'p' || key == 'P') {
                printf("\n⏸️  已暂停，按回车继续...");
                getchar(); 
                getchar();
            }
        }
        
        Sleep(1000);  // 演示用1秒
    }
    
    // 工作结束提醒
    printf("\n\n🔔 叮！25分钟专注完成！\n");
    Beep(523, 500);
    
    // 更新统计
    today_stats.total_pomodoros++;
    focus_minutes += work_minutes;
    
    // 休息时段
    printf("\n+==========================================+\n");
    printf(" ☕ 休息5分钟！站起来活动一下吧\n");
    printf("+==========================================+\n");
    
    Sleep(2000);
    
    printf("\n❓ 休息结束！准备开始下一个番茄钟？\n");
    printf("1. 继续下一个 🍅  2. 返回主菜单 🏠\n");
    printf("👉 请选择: ");
    scanf("%d", &choice);
    while(getchar() != '\n');
    
    if(choice == 1) {
        start_pomodoro();
    }
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