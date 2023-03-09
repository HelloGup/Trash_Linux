
**该程序可一次删除多个文件/文件夹，并防止回收站重名文件覆盖**

## 安装

- 进入clone目录，执行./install.sh，即完成安装，使用rm命令即可删除
- 若设置不生效，请重新打开终端
- 查看回收站默认使用tree命令，若终端未安装该命令，
- 请使用sudo yum install tree -y 或 sudo apt-get install tree -y 安装tree命令

- 回收站默认路径为 $HOME/.trash

- 如需要自定义回收站路径，请在.bashrc中添加如下环境变量 
- export TRASH_PATH='您的回收站绝对路径' 
- 添加完成请记得 source ~/.bashrc

## 使用

- 安装后默认替换rm命令,原rm命令请使用/usr/bin/rm 或 sudo rm
- 请牢记如使用sudo rm，执行的仍然是原系统自带的rm命令，被删除文件无法进入回收站

- 查看回收站：rm

- 清空回收站：rm -c

- 删除文件/文件夹：rm file1

- 支持一次删除多个文件：rm file1 file2 file3...

- 回收站目录格式为年_月_日
- 被删除文件会添加时_分_秒后缀，防止同名文件覆盖
