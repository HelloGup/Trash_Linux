
**该应用可一次删除多个文件/文件夹，且防止回收站重名文件覆盖**

## 安装

- 进入clone目录，执行./install.sh，完成安装，使用 trash 命令即可将被删除文件放入回收站
- 
- 若需要替换rm，自行在.bashrc 中添加 alias rm='/usr/local/bin/trash'

- (可选)列出回收站目录默认使用tree命令，如需要，自行安装

- 回收站默认路径为 $HOME/.trash

- 如需要自定义回收站路径，请在.bashrc中添加如下环境变量 
- export TRASH_PATH='您的回收站绝对路径' 
- 添加完成请记得 source ~/.bashrc

## 使用

- 若添加别名后，使用以下命令请用rm,原rm命令请使用/usr/bin/rm 或 sudo rm
- 请牢记如使用sudo rm，执行的仍然是原系统自带的rm命令，被删除文件无法进入回收站

- 列出回收站文件：trash

- 清空回收站：trash -c

- 删除文件/文件夹：trash file1

- 支持一次删除多个文件：trash file1 file2 file3...

- 回收站目录创建格式为年_月_日
- 被删除文件会添加时_分_秒后缀，以防止同名文件覆盖
