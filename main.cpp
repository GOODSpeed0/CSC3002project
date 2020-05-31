#include "mainwindow.h"
#include "login_page.h"
#include "F_code_library.h"
#include "Process_RAM.h"
#include "snake_widget.h"
#include "taskcontroller.h"
#include <QApplication>
#include "clock.h"
#include <thread>
#include "filesystem.h"
#include "Rom_system.h"
#include "global.h"
#include "File.h"
using namespace std;




int startClock(string& instruct){
    Clock my_clock;
    tm startTime;
    tm endTime;
    cout<<"Start the Clock"<<endl;
    my_clock.start();
    while (instruct!="x"){
        if (instruct=="s"||instruct=="S"){
            instruct="";
            startTime=my_clock.recordCurrentTime();
            cout<<"StartTime:"<<startTime.tm_year<<"-"<<startTime.tm_mon<<"-"<<startTime.tm_mday<<" "<<
                  startTime.tm_hour<<": "<<startTime.tm_min<<": "<<startTime.tm_sec<<endl;
        }
        else if (instruct=="e"||instruct=="E"){
            instruct="";
            endTime=my_clock.recordCurrentTime();
            cout<<"EndTime:"<<endTime.tm_year<<"-"<<endTime.tm_mon<<"-"<<endTime.tm_mday<<" "<<
                  endTime.tm_hour<<": "<<endTime.tm_min<<": "<<endTime.tm_sec<<endl;
            cout<<"Time duration:"<<endTime.tm_min*60+endTime.tm_sec-startTime.tm_min*60-startTime.tm_sec<<"s"<<endl;}

        sleep(1000);
        my_clock.run();
    }
    return 0;
}

int getTime(string& instruct){
    while (true){
        cout<<"Input s/S to record the start time, e/E to record the end time, x to exit"<<endl;
        cin>>instruct;}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // initialize rom:
    ROM rom_C = ana_rom[0];
    ROM rom_D = ana_rom[1];
    ROM rom_E = ana_rom[2];
    // give each disk a path:
    initial_rom(rom_C, "C");
    initial_rom(rom_D, "D");
    initial_rom(rom_E, "E");
    // create folder in disk C:
    createFolder("C:\\","study",rom_C);
    createFolder("C:\\","research",rom_C);
    createFolder("C:\\study\\", "CSC",rom_C);
    File file1;
    file1.setName("Name");
    file1.setTime("1999-02-22");
    file1.setContent("FAKE NEWS");
    createFile("C:\\study\\",file1, ana_rom[0]);
    for (int i = 0; i < 20; i++) {
        ana_ram[i].ram_used = 0;
    } // each time you login the ram of the system should all be set to 0
    LoginPage page;
    page.show();
//    for (int i = 0; i <20; i++) {
//        ana_ram[i].ram_used = 0;
//    }
    cout<< file1.getFilename() << endl;
    cout<< file1.getSize() << endl;
    cout << show_RAM(ana_ram) << endl;

////    system_report(ana_ram);
//    snake_widget snake2;
//    Process_APP snakeProcess = Process_APP(ana_ram);
//    snake2.show();
//    cout << snakeProcess.address << endl;
//    taskcontroller task;
//    task.show();

    return a.exec();
//    return 0;

}

//int main() {

//    ROM rom_C;
//    ROM rom_D;
//    ROM rom_E;

//    rom_C.start_1(0);
//    rom_D.start_1(1);
//    rom_E.start_1(2);

//    initial_rom(rom_C,"C");
//    initial_rom(rom_D,"D");
//    initial_rom(rom_E,"E");

//    createFolder("C:\\","study",rom_C);
//    createFolder("C:\\","research",rom_C);
//    createFolder("C:\\study\\", "CSC",rom_C);
//    createApp("C:\\study\\", "clock",rom_C);

//    File file;
//    createFile("C:\\research\\",file, rom_C);

//    /**************************************/
//    vector<string> vec_name = openFolder("C:\\", rom_C);
//    cout << "first file/folder name: " << vec_name[0] << endl;
//    cout << "second file/folder name: " << vec_name[1] << endl;
//    cout << endl;

//    /**************************************/
//    cout << "folder_pointer: " << rom_to_num(0, rom_C)<<endl;

//    cout << "file_pointer:" << rom_to_num(5,rom_C) << endl;


//    cout << "path name: ";
//    for(int i = 10; i < 39; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40; i < 49; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55, rom_C) << endl;

//    cout << "sub_address1: " << endl;
//    cout << rom_to_num(60,rom_C) << endl;

//    cout << "sub_address2: " << endl;
//    cout << rom_to_num(65,rom_C) << endl;

//    cout << endl;

////    for(int i = 31; i < 41; i++){
////        rom_C.contents[i].show_contents(cout);

////    }
////    cout <<endl;

///***********************************************************/
//    cout << "path name: ";
//    for(int i = 10+60; i < 39+60; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40+60; i < 49+60; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50+60,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55+60, rom_C) << endl;

//    cout << "sub_address1: " << endl;
//    cout << rom_to_num(60+60,rom_C) << endl;

//    cout << "sub_address2: " << endl;
//    cout << rom_to_num(65+60,rom_C) << endl;

//    cout << endl;

////    for(int i = 31+45; i < 41+45; i++){
////        rom_C.contents[i].show_contents(cout);

////    }
////    cout <<endl;

///***********************************************************/
//    cout << "path name: ";
//    for(int i = 10+120; i < 39+120; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40+120; i < 49+120; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50+120,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55+120, rom_C) << endl;

//    cout << "sub_address1: " << endl;
//    cout << rom_to_num(60+120,rom_C) << endl;

//    cout << "sub_address2: " << endl;
//    cout << rom_to_num(65+120,rom_C) << endl;

//    cout << endl;

///***********************************************************/
//    cout << "path name: ";
//    for(int i = 10+180; i < 39+180; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40+180; i < 49+180; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50+180,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55+180, rom_C) << endl;

//    cout << "sub_address1: " << endl;
//    cout << rom_to_num(60+180,rom_C) << endl;

//    cout << "sub_address2: " << endl;
//    cout << rom_to_num(65+180,rom_C) << endl;

//    cout << endl;

///***********************************************************/
//    cout << "path name: ";
//    for(int i = 10+240; i < 39+240; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40+240; i < 49+240; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50+240,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55+240, rom_C) << endl;

//    cout << "sub_address1: " << endl;
//    cout << rom_to_num(60+240,rom_C) << endl;

//    cout << "sub_address2: " << endl;
//    cout << rom_to_num(65+240,rom_C) << endl;

//    cout << endl;
///***********************************************************/
//    cout << "path name: ";
//    for(int i = 10+300; i < 39+300; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout <<endl;

//    cout << "type: ";
//    for(int i = 40+300; i < 49+300; i++){
//        cout << binary_to_char(rom_C.contents[i].contents);
//    }
//    cout << endl;

//    cout << "size: " << endl;
//    cout << rom_to_num(50+300,rom_C) << endl;

//    cout << "super_address: "<< endl;
//    cout << rom_to_num(55+300, rom_C) << endl;

//    cout << "start_address: " << endl;
//    cout << rom_to_num(60+300,rom_C) << endl;

//    cout << "empty: " << endl;
//    cout << rom_to_num(65+300,rom_C) << endl;

//    cout << endl;


//    /***********RAM的部分***********/


//    /*RAM Initialization*/
//    vector<RAM> file_info_ram = build_RAM(10);
//    vector<RAM> ana_ram = build_RAM(1);


//    /*监测内存使用情况*/
//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);


//    ifstream stream;
//    string file1 = "C:\\Users\\lenovo\\Desktop\\reading.txt";
//    string gre = "1234567890In this memo Omega University's dean points out that Omega graduates are less successful in getting jobs thanAlpha University graduates, despite the fact that during the past 15 years the overall grade average of Omega students has risen by 30%.The dean also points out that during the past 15 years Omega has encouraged its students, by way of a particular procedure, to evaluate the effectiveness of their professors.The dean reasons that this procedure explains the gmde-average increase, which in turn has created a perception among employers that Omega graduates are less qualified for jobs. On the basis of this line of reasoning the dean concludes that to enable Omega graduates to find better jobs Omega must terminate its professorevaluation procedure.This argument contains several logical flaws, which render it unconvincing. A threshold problem with the argument involves the voluntary nature of the evaluation procedure.The dean provides no evidence about the number or percentage of Omega students who participate in the procedure. Lacking such evidence it is entirely possible that those numbers are insignificant, in which case terminating the procedure is unlikely to have any effect on the grade average of Omega students or their success in getting jobs after graduation. The argument also assumes unfairly that the grade-average increase is the result of the evaluation procedure-rather than some other phenomenon.The dean ignores a host of other possible explanations for the increase-such as a trend at Omega toward higher admission standards, or higher quality instruction or faci1ities.Without ruling out all other possible explanations for the grade-average increase, the dean cannot convince me that by terminating the evaluation procedure Omega would curb its perceived grade inflation-let alone help its graduates get jobs. Even if the evaluation procedure has resulted in grade inflation at Omega, the dean's claim that grade inflation explains why Omega graduates are less successful than Alpha graduates in getting jobs is unjustified.The dean overlooks a myriad of other possible reasons for Omega's comparatively poor job-placement record. Perhaps Omega's career services are inadequate; or perhaps Omega's curriculum does not prepare students for the job market as effectively as Alpha's. In short, without www.petersons.com/arco ARC0 GRE CAT-Answers to Although some skeptics points to Arctic places such as the high latitudes of Greenland, where temperatures seem to have fallen, a recent scientific report concludes that in recent decades average temperatures have increased faster in the Arctic than elsewhere. Scientists have long suspected that several factors lead to greater temperature swings at Earths polar regions than elsewhere. First, most of the Arctic is covered in snow and ice, which are highly reflective; if snow and ice melt, the exposed soil, which absorbs heat, serves to accelerate warming. Second, the polar atmosphere is thin, so little energy is required to warm it. My name is Tianshi Wang,I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student. My name is Tianshi Wang, I'm a year 3 Data Science student.";
//    string gre5 = gre+gre+gre+gre+gre;
//    string s = "My name is Tianshi Wang, I'm a year 3 Data Science student.";
//    string filename1 = "SkyWang";
//    string filename2 = "Group37";



////    /*基于当前系统的当前日期&时间*/
////    time_t now = time(0);

////    /*把 now 转换为字符串形式*/
////    string dt = ctime(&now);



//    try{
//    /*Class方法读取文件*/
//    file.setContent(gre5);
//    Process_File file_ram(file,0,file_info_ram);

//    checkRamSize(file.getSize()/1024+1, ana_ram);

//    file_ram.readin_file(file,memory_allocation(file.getSize()/1024+1, ana_ram),ana_ram);
//    file_ram.readout_file(ana_ram);


//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);
//    }
//    catch(ramFullException & e){
//        cout << e.what();
//        cout << "Would like to select an App to close?" << endl;
//    }



//    File file2 = File();
//    file2.setContent(gre);
//    Process_File file2_ram(file2,1,file_info_ram);
//    file2_ram.readin_file(file2,memory_allocation(file2.getSize()/1024+1, ana_ram),ana_ram);
//    file2_ram.readout_file(ana_ram);

//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);

////    file_ram.delete_file(ana_ram);

//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);


//    File file3 = File();
//    file3.setContent(gre);
//    Process_File file3_ram(file3,1,file_info_ram);
//    file3_ram.readin_file(file3,memory_allocation(file3.getSize()/1024+1, ana_ram),ana_ram);
//    file3_ram.readout_file(ana_ram);

//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);


//    file2_ram.delete_file(ana_ram);

//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);


//    Process_APP a = Process_APP(ana_ram);
//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);

//    a.kill_Process_APP(ana_ram);
//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);

//    Process_APP b = Process_APP(ana_ram);
//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);

//    b.kill_Process_APP(ana_ram);
//    cout << "RAM Visualization:" << endl << show_RAM(ana_ram) << endl;
//    system_report(ana_ram);

//    return 0;
//}



