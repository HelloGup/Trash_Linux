### 安装
- 进入clone目录，执行./install.sh

- 回收站默认路径为 $HOME/.trash
- 如需要自定义回收站路径，请在.bashrc中添加如下环境变量
  export TRASH_PATH='您的回收站绝对路径'
  添加完成请记得 source ~/.bashrc

### 使用
- 安装后默认替换rm命令为trash,原rm命令请使用/usr/bin/rm

- 查看回收站:rm
- 清空回收站:rm -c
- 删除文件/文件夹:rm file1
- 支持一次删除多个文件:rm file1 file2 file3...
- 若设置不生效，请重新打开终端
