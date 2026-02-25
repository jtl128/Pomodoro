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
                start_pomodoro();
                break;
            case 2:
                add_interrupt();  // ✅ 已实现
                break;
            case 3:
                generate_report();  // ✅ 已实现
                break;
            case 4:
                show_motivation();  // ✅ 已实现
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

void start_pomodoro() {
    int work_minutes = 25;
    int elapsed = 0;
    int choice;
    
    current_pomodoro++;
    printf("\n+==========================================+\n");
    printf(" 🍅 第%d个番茄钟开始！专注25分钟\n", current_pomodoro);
    printf("+==========================================+\n");
    printf("💡 提示：专注期间可以按 'i' 记录打断，按 'p' 暂停\n\n");
    
    for(elapsed = 1; elapsed <= work_minutes; elapsed++) {
        clear_screen();
        print_banner();
        printf("\n+==========================================+\n");
        printf(" 🎯 正在专注中... 第%d个番茄钟\n", current_pomodoro);
        draw_progress_bar(elapsed, work_minutes);
        printf("\n⏰ 剩余时间: %d分钟\n", work_minutes - elapsed);
        printf("📝 按 'i' 记录打断 | 按 'p' 暂停\n");
        printf("+==========================================+\n");
        
        if(kbhit()) {
            int key = getch();
            if(key == 'i' || key == 'I') {
                add_interrupt();
            } else if(key == 'p' || key == 'P') {
                printf("\n⏸️  已暂停，按回车继续...");
                getchar(); 
                getchar();
            }
        }
        
        Sleep(1000);
    }
    
    printf("\n\n🔔 叮！25分钟专注完成！\n");
    Beep(523, 500);
    
    today_stats.total_pomodoros++;
    focus_minutes += work_minutes;
    
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

// ✅ 新增：记录打断原因
void add_interrupt() {
    int reason_code;
    char *reasons[] = {"📱 玩手机", "💭 走神发呆", "🌍 环境干扰", "💬 聊天", "📌 其他原因"};
    char other_reason[50];
    
    clear_screen();
    printf("\n+==========================================+\n");
    printf(" 📝 记录打断原因 (认识你的拖延)\n");
    printf("+==========================================+\n\n");
    
    printf("❓ 是什么打断了你的专注？\n");
    for(int i = 0; i < 5; i++) {
        printf("%d. %s\n", i+1, reasons[i]);
    }
    printf("\n👉 请选择 (1-5): ");
    scanf("%d", &reason_code);
    while(getchar() != '\n');
    
    char current_time[30];
    get_current_time(current_time);
    
    if(reason_code >= 1 && reason_code <= 5) {
        if(reason_code == 5) {
            printf("✏️  请输入其他原因: ");
            fgets(other_reason, sizeof(other_reason), stdin);
            other_reason[strcspn(other_reason, "\n")] = 0;
            strcpy(today_stats.interrupts[today_stats.interrupt_index].reason, other_reason);
        } else {
            strcpy(today_stats.interrupts[today_stats.interrupt_index].reason, reasons[reason_code-1] + 3);
        }
        
        today_stats.interrupts[today_stats.interrupt_index].pomodoro_count = current_pomodoro;
        strcpy(today_stats.interrupts[today_stats.interrupt_index].time_str, current_time);
        
        today_stats.interrupt_index++;
        today_stats.interrupt_count++;
        
        printf("\n✅ 已记录！认识问题是改变的第一步\n");
    } else {
        printf("\n❌ 无效选择\n");
    }
    
    printf("\n⏎ 按回车键继续...");
    getchar();
}

// ✅ 新增：生成专注力报告
void generate_report() {
    int i;
    int phone_count = 0, wander_count = 0, env_count = 0, chat_count = 0, other_count = 0;
    
    clear_screen();
    printf("\n+==========================================+\n");
    printf(" 📊 你的专注力分析报告\n");
    printf("+==========================================+\n\n");
    
    printf("📅 日期: %s\n", today_stats.date);
    printf("🍅 完成番茄钟: %d个\n", today_stats.total_pomodoros);
    printf("⏱️  专注总时长: %d分钟\n", focus_minutes);
    printf("⚠️  打断次数: %d次\n\n", today_stats.interrupt_count);
    
    if(today_stats.interrupt_count > 0) {
        printf("📈 打断原因分析:\n");
        for(i = 0; i < today_stats.interrupt_index; i++) {
            if(strstr(today_stats.interrupts[i].reason, "手机")) phone_count++;
            else if(strstr(today_stats.interrupts[i].reason, "走神")) wander_count++;
            else if(strstr(today_stats.interrupts[i].reason, "环境")) env_count++;
            else if(strstr(today_stats.interrupts[i].reason, "聊天")) chat_count++;
            else other_count++;
        }
        
        if(phone_count > 0) printf("   📱 手机干扰: %d次\n", phone_count);
        if(wander_count > 0) printf("   💭 走神发呆: %d次\n", wander_count);
        if(env_count > 0) printf("   🌍 环境干扰: %d次\n", env_count);
        if(chat_count > 0) printf("   💬 聊天干扰: %d次\n", chat_count);
        if(other_count > 0) printf("   📌 其他原因: %d次\n", other_count);
        
        if(today_stats.total_pomodoros > 0) {
            float ratio = (float)today_stats.interrupt_count / today_stats.total_pomodoros;
            if(ratio <= 0.5) today_stats.focus_score = 90;
            else if(ratio <= 1) today_stats.focus_score = 75;
            else if(ratio <= 2) today_stats.focus_score = 60;
            else today_stats.focus_score = 40;
        }
    } else {
        printf("⭐ 太棒了！今天零打断！\n");
        today_stats.focus_score = 100;
        strcpy(today_stats.best_time, "完美专注日");
    }
    
    printf("\n+==========================================+\n");
    printf("🎯 今日专注力评分: %d分\n", today_stats.focus_score);
    if(today_stats.focus_score >= 90) printf("🏆 卓越！你今天是专注大师！\n");
    else if(today_stats.focus_score >= 75) printf("👍 不错哦，保持这个节奏！\n");
    else if(today_stats.focus_score >= 60) printf("📈 及格啦，明天会更好！\n");
    else printf("💪 别灰心，记录问题是进步的开始！\n");
    
    printf("\n+==========================================+\n");
    printf("⏎ 按回车键返回主菜单...");
    getchar();
}

// ✅ 新增：显示动力语录
void show_motivation() {
    char *quotes[] = {
        "🌱 \"种一棵树最好的时间是十年前，其次是现在。\"",
        "🏃 \"你拖延的每一分钟，都在被别人超越。\"",
        "🍅 \"专注25分钟，休息5分钟，你可以征服任何任务。\"",
        "💪 \"今天不想跑，所以才去跑。\"",
        "🎯 \"自律给我自由。\"",
        "⚔️ \"番茄钟不是束缚，而是你对抗拖延的武器。\"",
        "🌟 \"每一个完成的番茄钟，都是向更好的自己迈进。\"",
        "🚀 \"开始行动，就已经打败了50%的人。\"",
        "✨ \"完成比完美更重要。\"",
        "🎨 \"你不是懒，只是需要一点方法。\""
    };
    
    int random_index = rand() % 10;
    
    clear_screen();
    printf("\n+==========================================+\n");
    printf(" 💪 今日动力加油站\n");
    printf("+==========================================+\n\n");
    printf("        %s\n\n", quotes[random_index]);
    printf("+==========================================+\n");
    printf("\n🍅 现在，开始你的第一个番茄钟吧！\n");
    printf("\n⏎ 按回车键返回...");
    getchar();
}

void save_to_file() {
    // 将在后续版本实现
}

void load_from_file() {
    // 将在后续版本实现
}