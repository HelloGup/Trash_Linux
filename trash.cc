#include <cstdlib>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Trash {
    private:
        string trash_path;
        vector<string> files;

    public:
        Trash() { Init(); }

        void Init() {
            //获取自定义回收站路径
            char *custom = getenv("TRASH_PATH");
            if (custom) {
                trash_path = custom;
                cout << trash_path << endl;
            }

            else {
                string home_path = getenv("HOME");
                trash_path += home_path;
                trash_path += "/.trash";
            }
        }

        void trash_list() {
            string command = "tree ";
            command += trash_path;

            int status = system(command.c_str());
        }

        void trash_delete(string &file) {
            if (file.empty()) {
                return;
            }

            // 去掉尾部‘/’
            if (file[file.size() - 1] == '/') {
                file.erase(file.end() - 1);
            }

            time_t timer = time(nullptr);
            struct tm *ss;
            ss = gmtime(&timer);

            // tm结构体中的变量值
            // 年份从1900开始算起，要+1900;
            // 月份是0-11，要+1;
            // 小时是西方时间，相差8小时，要+8 会超过24 取余一下;
            string date = to_string(ss->tm_year + 1900) + "_" +
                to_string(ss->tm_mon + 1) + "_" + to_string(ss->tm_mday);
            string time = to_string((ss->tm_hour + 8) % 24) + "_" +
                to_string(ss->tm_min) + "_" + to_string(ss->tm_sec);

            // 创建回收站目录 以当日日期创建目录
            string command = "mkdir -p ";
            command += trash_path;
            command += "/";
            command += date;
            system(command.c_str());

            // 防止同名文件覆盖，以当前时间重命名后再移动
            string newFile = file + "_" + time;
            command = "mv ";
            command += file;
            command += " ";
            command += newFile;
            int status = system(command.c_str());
            if (status != 0) {
                return;
            }

            // 移动文件
            command = "mv ";
            command += newFile;
            command += " ";
            command += trash_path;
            command += "/";
            command += date;
            status = system(command.c_str());
            if (status == 0) {
                cout << "Deleted " << file << "; ";
            } else {
                cerr << "Delete Error";
            }
        }

        //清空回收站
        int trash_clean() {
            string command = "/usr/bin/rm -rf ";
            command += trash_path;
            command += "/*";

            int status = system(command.c_str());

            //TODO

            return status;
        }

        //调用原rm命令删除文件
        void trash_rm(string &file) {

            string command = "/usr/bin/rm -rf ";
            command += file;
            system(command.c_str());
        }

        ~Trash() {}
};

int main(int argc, char *argv[], char *env[]) {

    Trash *tr = new Trash();

    // trash list
    if (argc == 1) {
        tr->trash_list();
        delete tr;
        return 0;
    }

    set<string> files;
    //除命令外其他参数全放set里
    int i = 1;
    while (i < argc) {
        files.insert(argv[i++]);
    }

    set<string>::iterator it = files.find("-c");
    if (it != files.end()) {
        char c;
        cout << "Cleaning Trash? [y/n]:";
        cin >> c;

        if (c == 'y' || c == 'Y') {
            int status = tr->trash_clean();
            if (status == 0) {
                cout << "Finsh" << endl;
            }

            else {
                cout << "Clean Error" << endl;
            }
        }

        else {
            cout << "Cancel Clean." << endl;
        }

        delete tr;
        return 0;
    }

    // 彻底删除 不使用(背离修改原rm命令的初衷)
    // it = files.find("-d");
    // if (it != files.end()) {
    //     files.erase(it);
    //     
    //     for(string file : files){
    //         tr->trash_rm(file); 
    //     }
    //     
    //     delete tr;
    //     return 0;
    // }

    //删除文件 放入回收站
    for(string file : files){
        tr->trash_delete(file);
    }

    cout << endl;

    delete tr;
    return 0;
}
