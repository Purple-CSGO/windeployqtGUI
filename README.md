# Windows平台部署QT应用的GUI 

> windeployqtGUI is A GUI tool that helps improve the speed of win-platform qt program deployment

## 下载方式

- [百度网盘](https://pan.baidu.com/s/1W-mHk5K_8MvWf2Bcla6FIg) 提取码：vv6s

- [微云](https://share.weiyun.com/5NOALOa)

## 使用说明

- 设置`windeployqt.exe`和待部署的QT应用`*.exe`的路径，点击开始即部署，之后返回成功或错误的对话框，并且显示错误信息（调用CMD），自带`-no-angle -no-opengl-sw`参数。

- 可以记录程序的设置，每次打开应用时会显示上次的路径，故每次只用拖拽QT程序，不用多次查找设置`windeployqt.exe`的路径。

## 应用界面

![UI.png](https://upload-images.jianshu.io/upload_images/18819811-06a9ecd91e49602b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 待解决的问题

- 翻译问题
- 加快deploy流程的速度，当前QT应用仍需手动操作移动到单独的目录如`dist`，deploy之后还需要手动添加外部`.dll`，考虑整合`Enigma Virtual Box`的打包功能。

> 添加外部dll还是得手动。
