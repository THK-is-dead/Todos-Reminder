#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <unistd.h>

#define sw 1024
#define sh 600

int abcd;
int chng_ind;
int del_ind = -1;
int taskcount = 0;
int x = 255, y = 255, z = 255;
int bgi = 0;
int ringingtaskindex = 0;
bool musicstate = false;
typedef struct
{
    int dd;
    int mm;
    int yy;
    int h;
    int mi;
    int sec;
} systime;
systime pc;
FILE *fp;
FILE *fp2;

typedef struct
{
    char taskname[100];
    int year;
    int day;
    int month;
    int hour;
    int minute;
    // int taskstate = 0;
    char taskdetails[100];
    int taskstate = 0;

} task;
task tasklist[10];
typedef struct
{
    int oldbgi;
    int oldmsi;
    int oldst;
    int oldx, oldy, oldz;
} restoreold;
restoreold restore;

int i = 0, j = 0;
int st = 0;
char tempdate[50];
char temptime[50];
char tempo[10];
char *tmp = tempdate;
char *tmt = temptime;
int counterfordate = 0;
int counterfortime = 0;

void frontpage();
void AddRemoveTask();
void ChangeRingtone();
void ChangeBackground();
void showTaskDetails(int i);
void showTaskDetails2(int i);
void editTask(int taskIndex);
void Settings();
void Credits();
void inputTask();
void saveToFile();
void getFileSize();
void removeTask();
void tasknamelist();
void remindtimelist();
void biostimefetch();
void ringtone();
void taskshow();
void alarm();
void Alarmoff();
void statusshow();
void savesettings();
void fetchsettings();
void push();
void ringtonechk();
void saveandquit();
void biostimeprint();

void iDraw()
{
    // place your drawing codes here
    iClear();

    if (st == 0)
    {
        frontpage();
    }
    else if (st == 7)
    {
        // Draw the page to display task details
        showTaskDetails(abcd);
        biostimeprint();
    }
    if (st == 1)
    {
        inputTask();
        biostimeprint();
    }

    if (st == 6)
    {
        inputTask();
        biostimeprint();
    }

    if (st == 8)
    {
        inputTask();
        biostimeprint();
    }
    if (st == 9)
    {
        Alarmoff();
        biostimeprint();
    }

    if (st == 12)
    {
        inputTask();
        biostimeprint();
    }
    if (st == 10)
    {
        editTask(abcd);
        biostimeprint();
    }
    if (st == 16)
    {
        editTask(abcd);
        biostimeprint();
    }
    if (st == 18)
    {
        editTask(abcd);
        biostimeprint();
    }
    if (st == 112)
    {
        editTask(abcd);
        biostimeprint();
    }
}

void statusshow()
{
    for (int f = 0; f < taskcount; f++)
    {
        // iFilledCircle(120, 463 - 50 * (f + 1), 2);
        if (tasklist[f].taskstate == 0)
        {
            iSetColor(255, 255, 255);
            iText(700, 460 - 50 * (f + 2), "Not Done", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iSetColor(0, 255, 0);
            iText(720, 460 - 50 * (f + 2), "Done", GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
}
void inputTask()
{

    iShowBMP(0, 0, "eye.bmp");
    iSetColor(133, 84, 49);
    iFilledRectangle(830, 520, 180, 100);
    iSetColor(0, 0, 0);
    iFilledRectangle(27, 553, 70, 30);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 490, 200, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 440, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 390, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 340, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 290, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 240, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 190, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 140, 500, 40);
    // iFilledRectangle(195, 60, 500, 500);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(200, 500, "Enter Task Below: ", GLUT_BITMAP_TIMES_ROMAN_24);
    if (i != -1)
    {
        iText(200, 450, tasklist[i].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    iText(200, 400, "Enter Date: (format-dd/mm/yyyy)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 350, tempdate, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 300, "Enter Time: (format(24 hour clock)-hh:mm)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 250, temptime, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 200, "Enter Description: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 150, tasklist[i].taskdetails, GLUT_BITMAP_TIMES_ROMAN_24);
}

void editTask(int taskIndex)
{

    iShowBMP(0, 0, "eye.bmp");
    iSetColor(133, 84, 49);
    iFilledRectangle(830, 520, 180, 100);
    iSetColor(0, 0, 0);
    iFilledRectangle(27, 553, 70, 30);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 490, 200, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 440, 200, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 390, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 340, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 290, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 240, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 190, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 140, 500, 40);
    // iFilledRectangle(195, 60, 500, 500);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(200, 500, "Edit Task Below: ", GLUT_BITMAP_TIMES_ROMAN_24);
    if (taskIndex != -1)
    {
        iText(200, 450, tasklist[taskIndex].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    iText(200, 400, "Enter New Date: (format-dd/mm/yyyy)", GLUT_BITMAP_TIMES_ROMAN_24);
    // snprintf(tempdate, 20, "%d/%d/%d", tasklist[taskIndex].day, tasklist[taskIndex].month, tasklist[taskIndex].year);
    iText(200, 350, tempdate, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 300, "Enter New Time: (format(24 hour clock)-hh:mm)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 250, temptime, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 200, "Enter New Description: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 150, tasklist[taskIndex].taskdetails, GLUT_BITMAP_TIMES_ROMAN_24);
}

void alarm()
{
    biostimefetch();
    for (int i = 0; i < taskcount; i++)
    {
        if (tasklist[i].taskstate == 0 && pc.h == tasklist[i].hour && pc.mi == tasklist[i].minute && pc.dd == tasklist[i].day && pc.mm == tasklist[i].month && pc.yy == tasklist[i].year && pc.sec == 0 && tasklist[i].taskstate == 0)
        {
            musicstate = true;
            tasklist[i].taskstate = 1;
            ringingtaskindex = i;
            st = 9;
            ringtone();
            break;
        }
    }
}
void Alarmoff()
{

    showTaskDetails2(ringingtaskindex);
    // iShowBMP(0, 0, "cop.bmp");
    iSetColor(133, 84, 49);
    iFilledRectangle(830, 520, 180, 100);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(70, 85, 95);
    iFilledRectangle(315, 290, 250, 180);
    iSetColor(0, 0, 0);
    iText(325, 450, "Turn off Reminder for:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(325, 400, " -> 5 minutes", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(325, 350, " -> 10 minutes", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(325, 300, " -> Indefinitely", GLUT_BITMAP_TIMES_ROMAN_24);
}

void frontpage()
{
    iShowBMP(0, 0, "add.bmp");
    iSetColor(133, 84, 49);
    iFilledRectangle(830, 520, 180, 100);
    // iSetColor(0, 0, 0);
    // iFilledRectangle(28, 555, 70, 30);
    // iSetColor(255, 255, 255);
    // iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(28, 219, 249);

    iFilledRectangle(380, 470, 200, 40);
    iSetColor(28, 250, 49);
    iSetColor(255, 84, 49);
    iFilledRectangle(380, 400, 150, 40);
    iSetColor(0, 0, 0);
    iText(425, 480, "Add Task", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(415, 410, "Tasks: ", GLUT_BITMAP_TIMES_ROMAN_24);

    // Display all added tasks
    for (int f = 0; f < taskcount; f++)
    {
        iSetColor(50, 50, 50);
        iFilledRectangle(395, 350 - 50 * f, 410, 40);
        iSetColor(255, 255, 255);
        char taskIndex[3];
        itoa(f + 1, taskIndex, 10);
        iText(400, 360 - 50 * f, taskIndex, GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledCircle(415, 363 - 50 * f, 2);
        iText(430, 360 - 50 * f, tasklist[f].taskname, GLUT_BITMAP_TIMES_ROMAN_24);

        // Add "Remove" and "Mark as Done" options
        iSetColor(280, 0, 0); // Red color for remove task option
        iText(600, 360 - 50 * f, "Remove", GLUT_BITMAP_TIMES_ROMAN_24);
        // if (tasklist[f].taskstate == 0)
        // {
        //     iSetColor(255, 255, 255); // Green color for mark as done option
        //     //iText(660, 360 - 50 * f, "Mark as Done", GLUT_BITMAP_TIMES_ROMAN_24);
        //     iFilledCircle(760, 365 - 50 * f, 10); // Circle for mark as done
        // }
        // else
        // {
        //     iSetColor(0, 255, 0); // Green color for mark as done option
        //     // iText(660, 360 - 50 * f, "Mark as Done", GLUT_BITMAP_TIMES_ROMAN_24);
        //     iFilledCircle(760, 365 - 50 * f, 10); // Circle for mark as done
        // }
    }
    statusshow();
    iSetColor(255, 255, 255);
    biostimeprint();
}

void saveToFile()
{
    fp = fopen("tasks.bin", "w");
    for (int p = 0; p < taskcount; p++)
    {
        fwrite(&tasklist[p], sizeof(task), 1, fp);
    }
    fclose(fp);
}
void getFileSize()
{
    fseek(fp, 0L, SEEK_END);
    unsigned int long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    i = size / sizeof(task);
    taskcount = i;
}

void fetchtask()
{
    fp = fopen("tasks.bin", "r");
    if (fp)
    {
        getFileSize();
        for (int p = 0; p < i; p++)
        {
            fread(&tasklist[p], sizeof(task), 1, fp);
        }
        fclose(fp);
    }
}
void showTaskDetails(int i)
{
    iShowBMP(0, 0, "ops.bmp");
    iSetColor(100, 100, 255);
    iFilledRectangle(440, 490, 160, 40);
    // iSetColor(55,55,55);
    iSetColor(133, 84, 49);
    iFilledRectangle(340, 230, 380, 210);
    iSetColor(200, 150, 50);
    iFilledRectangle(380, 150, 80, 50);
    iSetColor(240, 84, 49);
    // iFilledRectangle(40,430,380,50);
    iFilledRectangle(340, 330, 380, 50);
    iFilledRectangle(340, 230, 380, 50);
    // iFilledRectangle(40,130,380,50);
    iSetColor(0, 0, 0);
    iFilledRectangle(27, 553, 70, 30);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(450, 500, "Task Details", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(350, 400, "Task Name:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(500, 400, tasklist[i].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(350, 350, "Date:", GLUT_BITMAP_TIMES_ROMAN_24);
    char date[20];
    sprintf(date, "%d/%d/%d", tasklist[i].day, tasklist[i].month, tasklist[i].year);
    iText(500, 350, date, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(350, 300, "Time:", GLUT_BITMAP_TIMES_ROMAN_24);
    char time[20];
    sprintf(time, "%02d:%02d", tasklist[i].hour, tasklist[i].minute);
    iText(500, 300, time, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(350, 250, "Description:", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(500, 250, tasklist[i].taskdetails, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(390, 170, "Edit", GLUT_BITMAP_TIMES_ROMAN_24);
}
void showTaskDetails2(int i)
{
    iShowBMP(0, 0, "cop.bmp");
    // iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iFilledRectangle(27, 553, 70, 30);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(55, 65, 75);
    iFilledRectangle(40, 190, 180, 100);
    iFilledRectangle(40, 390, 180, 100);
    // iText(50, 500, "Task Details", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 155);
    iText(50, 450, "Task Name:", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(50, 400, tasklist[i].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 155);
    iText(50, 250, "Description:", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(50, 200, tasklist[i].taskdetails, GLUT_BITMAP_TIMES_ROMAN_24);
    // iText(50, 400, "Date:", GLUT_BITMAP_TIMES_ROMAN_24);
    // char date[20];
    // sprintf(date, "%d/%d/%d", tasklist[i].day, tasklist[i].month, tasklist[i].year);
    // iText(200, 400, date, GLUT_BITMAP_TIMES_ROMAN_24);
    // iText(50, 350, "Time:", GLUT_BITMAP_TIMES_ROMAN_24);
    // char time[20];
    // sprintf(time, "%02d:%02d", tasklist[i].hour, tasklist[i].minute);
    // iText(200, 350, time, GLUT_BITMAP_TIMES_ROMAN_24);
    // iText(50, 250, "Edit", GLUT_BITMAP_TIMES_ROMAN_24);
}

void Task()
{

    iShowBMP(0, 0, "eye.bmp");
    iSetColor(133, 84, 49);
    iFilledRectangle(830, 520, 180, 100);
    iSetColor(0, 0, 0);
    iFilledRectangle(27, 553, 70, 30);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 490, 200, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 440, 200, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 390, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 340, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 290, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 240, 500, 40);
    iSetColor(100, 100, 100);
    iFilledRectangle(195, 190, 500, 40);
    iSetColor(210, 128, 55);
    iFilledRectangle(195, 140, 500, 40);
    // iFilledRectangle(195, 60, 500, 500);
    iSetColor(255, 255, 255);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 0, 0);
    iText(200, 500, "Enter Task Below: ", GLUT_BITMAP_TIMES_ROMAN_24);
    if (i != -1)
    {
        iText(200, 450, tasklist[i].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    iText(200, 400, "Enter Date: (format-dd/mm/yyyy)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 350, tempdate, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 300, "Enter Time: (format(24 hour clock)-hh:mm)", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 250, temptime, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 200, "Enter Description: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 150, tasklist[i].taskdetails, GLUT_BITMAP_TIMES_ROMAN_24);
}

void removeTask()
{
    iShowBMP(0, 0, "add.bmp");
    iSetColor(x, y, z);
    iText(30, 560, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200, 500, "Click the task you want to remove: ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(195, 450, "Title", GLUT_BITMAP_TIMES_ROMAN_24);
    iLine(193, 440, 243, 440);
    iText(400, 450, "Remind at", GLUT_BITMAP_TIMES_ROMAN_24);
    iLine(400, 440, 500, 440);
    iText(700, 450, "Status", GLUT_BITMAP_TIMES_ROMAN_24);
    iLine(700, 440, 760, 440);
    iLine(380, 480, 380, 0);
    iLine(680, 480, 680, 0);

    tasknamelist();
    statusshow();
}
void tasknamelist()
{
    for (int f = 0; f < taskcount; f++)
    {
        char bruh[3];
        itoa(f + 1, bruh, 10);
        iText(100, 460 - 50 * (f + 1), bruh, GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledCircle(120, 463 - 50 * (f + 1), 2);
        iText(130, 460 - 50 * (f + 1), tasklist[f].taskname, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void push()
{

    for (int s = 0; s < (taskcount); s++)
    {
        if (del_ind != -1)
        {
            tasklist[del_ind + s] = tasklist[del_ind + s + 1];
            tasklist[del_ind + s + 1].taskname[0] = '\0';
            tasklist[del_ind + s + 1].taskdetails[0] = '\0';
        }
    }

    fp = fopen("tasks.bin", "wb");
    for (int p = 0; p < taskcount - 1; p++)
    {
        fwrite(&tasklist[p], sizeof(task), 1, fp);
    }

    fclose(fp);
}

void biostimeprint()
{

    iSetColor(0, 0, 0);
    char c[10];
    itoa(pc.dd, c, 10);
    iText(850, 570, c, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(880, 570, "/", GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.mm, c, 10);
    iText(890, 570, c, GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.dd, c, 10);
    iText(920, 570, "/", GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.yy, c, 10);
    iText(930, 570, c, GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.h, c, 10);
    iText(880, 540, c, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(905, 540, ":", GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.mi, c, 10);
    iText(910, 540, c, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(935, 540, ":", GLUT_BITMAP_TIMES_ROMAN_24);
    itoa(pc.sec, c, 10);
    iText(940, 540, c, GLUT_BITMAP_TIMES_ROMAN_24);
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if (st == 0)
        {
            for (int f = 0; f < taskcount; f++)
            {
                if (mx >= 395 && mx <= 595 && my >= 340 - 50 * f && my <= 380 - 50 * f)
                {

                    abcd = f;

                    st = 7;
                    break;
                }
            }
            for (int f = 0; f < taskcount; f++)
            {
                // Check if the click is within the remove area of the task
                if (mx >= 600 && mx <= 700 && my >= 340 - 50 * f && my <= 380 - 50 * f)
                {
                    // If clicked, remove the task
                    del_ind = f;
                    push();
                    taskcount--;
                    i--;

                    break; // Exit loop after removing the task
                }
            }
            for (int f = 0; f < taskcount; f++)
            {
                // printf("TaskCountefws: %d\n", taskcount);
                if (mx >= 710 && mx <= 770 && my >= 360 - 50 * f && my <= 380 - 50 * f)
                {
                    // printf("f: %d, taskcount: %d, taskstate: %d\n", f, taskcount, tasklist[f].taskstate);
                    // Change color to green
                    // iSetColor(0, 255, 0);
                    // Redraw the circle in green
                    // iFilledCircle(760, 363 - 50 * f, 10);

                    tasklist[f].taskstate = !tasklist[f].taskstate;
                    // printf("f: %d, taskcount: %d, taskstate: %d\n", f, taskcount, tasklist[f].taskstate);
                    // printf("my: %d, ll: %d, ul: %d\n", my, 360 - 50 * f, 360 - 50 * f);
                }
            }
            //}
            if (mx >= 380 && mx <= 580 && my >= 450 && my <= 490)
            {
                st = 1;
            }
            // if (mx >= 400 && mx <= 564 && my >= 310 && my <= 331)
            // {
            //     st = 2;
            // }
        }
        if (mx >= 30 && mx <= 80 && my >= 560 && my <= 581 && st != 0)
        {
            st = 0;
        }
    }
    if (st == 9)
    {

        if (mx >= 360 && mx <= 465 && my >= 399 && my <= 424)
        {
            tasklist[ringingtaskindex].minute += 5;
            if (tasklist[ringingtaskindex].minute >= 60)
            {
                tasklist[ringingtaskindex].hour += 1;
                tasklist[ringingtaskindex].minute %= 60;
            }
            PlaySound("No - Sound Effect", NULL, SND_ASYNC);
            tasklist[ringingtaskindex].taskstate = 0;
            st = 0;
        }
        if (mx >= 310 && mx <= 465 && my >= 349 && my <= 374)
        {
            tasklist[ringingtaskindex].minute += 10;
            if (tasklist[ringingtaskindex].minute >= 60)
            {
                tasklist[ringingtaskindex].hour += 1;
                tasklist[ringingtaskindex].minute %= 60;
            }
            PlaySound("No - Sound Effect", NULL, SND_ASYNC);
            tasklist[ringingtaskindex].taskstate = 0;
            st = 0;
        }
        if (mx >= 310 && mx <= 465 && my >= 299 && my <= 324)
        {
            PlaySound("No - Sound Effect", NULL, SND_ASYNC);
            tasklist[ringingtaskindex].taskstate = 1;
            st = 0;
        }
    }
    if (st == 7 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (mx >= 370 && mx <= 420 && my >= 170 && my <= 194)
        {

            st = 10;
        }
    }
}
void ringtone()
{
    if (musicstate)
    {
        PlaySound("hehe.wav", NULL, SND_ASYNC);
    }
}

void iKeyboard(unsigned char key)
{

    if (st == 1)
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tasklist[i].taskname[j] = '\0';
        }
        if (key != '\b')
        {
            tasklist[i].taskname[j] = key;
            tasklist[i].taskname[j + 1] = '\0';
            j++;
        }
        if (key == '\r')
        {
            st = 6;
            j = 0;
            key = ' ';
        }
    }

    if (st == 6 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == '/'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tempdate[j] = '\0';
        }
        if (key != '\b')
        {
            tempdate[j] = key;
            j++;
        }
        if (key == '/' || key == '\r')
        {
            tempdate[j] = '\0';
            tasklist[i].day = atoi(tempdate);
            tasklist[i].month = atoi(tmp + 3);
            tasklist[i].year = atoi(tmp + 6);
            if (key == '\r')
            {
                st = 8;
                j = 0;
                key = ' ';
            }
        }
    }

    if (st == 8 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == ':'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            temptime[j] = '\0';
        }
        if (key != '\b')
        {
            temptime[j] = key;
            j++;
        }
        if ((key == ':' || key == '\r'))
        {
            temptime[j] = '\0';
            tasklist[i].hour = atoi(temptime);
            tasklist[i].minute = atoi(tmt + 3);
            if (key == '\r')
            {
                // for (int k = 0; k < 50; k++) {
                //     tempdate[k] = '\0';
                //     temptime[k] = '\0';
                // }

                st = 12;
                j = 0;
                key = ' ';
            }
        }
    }

    if (st == 12)
    {
        if (key != '\b' && j < 99)
        { // Limit details to 100 characters
            tasklist[i].taskdetails[j] = key;
            tasklist[i].taskdetails[j + 1] = '\0';
            j++;
        }
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tasklist[i].taskdetails[j] = '\0';
        }
        if (key == '\r')
        {
            taskcount++;
            i++;
            for (int k = 0; k < 50; k++)
            {
                tempdate[k] = '\0';
                temptime[k] = '\0';
            }

            j = 0;

            tasklist[i].taskdetails[0] = '\0';
            saveToFile();
            st = 0;
        }
    }
    else if (st == 10)
    {
        i = abcd;
        j = strlen(tasklist[i].taskname);
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tasklist[i].taskname[j] = '\0';
        }
        if (key != '\b')
        {
            tasklist[i].taskname[j] = key;
            tasklist[i].taskname[j + 1] = '\0';
            j++;
        }
        if (key == '\r')
        {
            st = 16;
            j = 0;
            key = ' ';
        }
    }

    if (st == 16 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == '/'))
    {

        j = strlen(tempdate);
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tempdate[j] = '\0';
        }
        if (key != '\b')
        {
            tempdate[j] = key;
            j++;
        }
        if (key == '/' || key == '\r')
        {
            tempdate[j] = '\0';
            tasklist[i].day = atoi(tempdate);
            tasklist[i].month = atoi(tmp + 3);
            tasklist[i].year = atoi(tmp + 6);
            if (key == '\r')
            {
                st = 18;
                j = 0;
                key = ' ';
            }
        }
    }

    if (st == 18 && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '\r' || key == '\b' || key == ':'))
    {
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            temptime[j] = '\0';
        }
        if (key != '\b')
        {
            temptime[j] = key;
            j++;
        }
        if ((key == ':' || key == '\r'))
        {
            temptime[j] = '\0';
            tasklist[i].hour = atoi(temptime);
            tasklist[i].minute = atoi(tmt + 3);
            if (key == '\r')
            {

                st = 112;
                j = 0;
                key = ' ';
            }
        }
    }

    if (st == 112)
    {
        j = strlen(tasklist[i].taskdetails);
        if (key != '\b' && j < 99)
        {
            tasklist[i].taskdetails[j] = key;
            tasklist[i].taskdetails[j + 1] = '\0';
            j++;
        }
        if (key == '\b')
        {
            j--;
            if (j < 0)
                j = 0;
            tasklist[i].taskdetails[j] = '\0';
        }
        if (key == '\r')
        {
            st = 0;
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
}
void biostimefetch()
{
    time_t rawtime;
    tm *t;
    time(&rawtime);
    t = gmtime(&rawtime);
    pc.dd = t->tm_mday;
    pc.mm = t->tm_mon + 1;
    pc.yy = t->tm_year + 1900;
    pc.h = (t->tm_hour + 6) % 24;
    pc.mi = t->tm_min;
    pc.sec = t->tm_sec;
}
void ringtonechk()
{
    if (st == 0)
    {
        musicstate = false;
        PlaySound("No.wav", NULL, SND_ASYNC);
    }
}

int main()
{
    fetchtask();

    iSetTimer(1000, alarm);
    iSetTimer(500, ringtonechk);
    iInitialize(sw, sh, "ToDos");
    return 0;
}