#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <string.h>

using namespace std;

class Trash {
    private:
        string trash_path;
        vector<string> files;

    public:
        Trash() { Init(); }
        void Init() {
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

            time_t timer = time(nullptr);
            struct tm *ss;
            ss = gmtime(&timer);

            // 年份从1900开始算起，要+1900;
            // 月份是0-11，要+1;
            // 小时是西方时间，相差8小时，要+8 会超过24 取余一下;
            string date = to_string(ss->tm_year + 1900) + "_" +
                to_string(ss->tm_mon + 1) + "_" + to_string(ss->tm_mday);
            string time = to_string((ss->tm_hour + 8) % 24) + "_" +
                to_string(ss->tm_min) + "_" + to_string(ss->tm_sec);

            // 创建回收站目录 以当前日期创建目录
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

        int trash_clean() {
            string command = "/usr/bin/rm -rf ";
            command += trash_path;
            command += "/*";

            int status = system(command.c_str());
            return status;
        }

        ~Trash() {}
};

int main(int argc, char *argv[], char *env[]) {
    // trash list
    Trash *tr = new Trash();

    if (argc == 1) {
        tr->trash_list();
        delete tr;
        return 0;
    }

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i++], "-c") == 0) {
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
    }

    i = 1;
    while (i < argc) {
        string file = argv[i++];
        tr->trash_delete(file);
    }

    cout << endl;

    delete tr;
    return 0;
}
