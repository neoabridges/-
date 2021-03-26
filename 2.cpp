#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Student
{
    int id;
    char name[11];
    int age;
    char birthplace[11];
    double score;
};
void convert_file(const char *src, const char *dst)
{
    fstream stream_src;
    stream_src.open(src, ios::in);
    fstream stream_dst;
    stream_dst.open(dst, ios::out|ios::binary);
    if (!stream_src.is_open() || !stream_dst.is_open()){
        cout << "open failed\n";
        exit(-1);
    }
    while(stream_src.good()){
        Student* stu = new Student;
        stream_src >> stu->id; 
        stream_src >> stu->name; 
        stream_src >> stu->age;
        stream_src >> stu->birthplace;
        stream_src >> stu->score;
        if (stream_src.good())
            stream_dst.write((char*)stu, sizeof(Student));
    } 
    stream_src.close();
    stream_dst.close();
}
bool compare(Student* stu1, Student* stu2)
{
    if (stu1->score > stu2->score){
        return true;
    }
    return stu1->id < stu2->id && stu1->score == stu2->score; 
}
void modify_file(const char *src, const char *dst)
{
    fstream stream_src, stream_dst;
    stream_src.open(src, ios::in|ios::binary);
    if (!stream_src.is_open()){
        cout << "open failed\n";
        exit(-1);
    }
    Student* students[120];
    int count = 0;
    Student* stu = new Student;
    stream_src.read((char*)stu, sizeof(Student));
    while(stream_src.good()){
        if(!strcmp("Nanjing", stu->birthplace)){
            stu->id = 170000000 + stu->id % 10000000;
        }
        students[count] = stu;
        count++;
        stu = new Student;
        if (stream_src.good())
            stream_src.read((char*)stu, sizeof(Student));
    }
    stream_src.close();
    stream_dst.open(dst, ios::out|ios::binary);
    sort(students, students + count, compare);
    for(int i = 0; i < count; i++){
        stream_dst.write((char*)students[i], sizeof(Student));
    }
    stream_dst.close();
}
void print_file(const char *src)
{
    fstream stream;
    stream.open(src, ios::in|ios::binary);
    if (!stream.is_open()){
        cout << "shit\n";
        exit(-1);
    }
    Student *stu = new Student;
    stream.read((char*)stu, sizeof(Student));
    while(stream.good()){
        cout << stu->id << ' ';
        cout << stu->name << ' ';
        cout << stu->age << ' ';
        cout << stu->birthplace << ' ';
        printf("%.1f\n", stu->score);
        stream.read((char*)stu, sizeof(Student));
    }
    stream.close();
}
#include"test.hpp"
int main()
{
    test();
    /*
    convert_file("file_io\\student.txt", "file_io\\chainsaw.dat");
    print_file("file_io\\chainsaw.dat");
    modify_file("file_io\\chainsaw.dat", "file_io\\chainsaw.dat");
    modify_file("file_io\\b.dat", "file\\io_chainsaw.dat");
    print_file("file_io\\chainsaw.dat");
    */
    return 0;
}