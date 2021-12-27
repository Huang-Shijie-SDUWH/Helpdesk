# Python 与 Linux 基础教学项目

本项目旨在通过51单片机开发一个独居老人按键求助的家庭求助机，家人可通过企业微信收到求助消息，并可直接通过企业微信进行回复。

## 服务器端

### 页面间调用关系

在`/`中，有以下文件（仅展示部分）

```
|-README.md 说明文档
|-WXBizMsgCrypt.py 适用于企业微信的加解密库，来自企业微信文档
|-api.py 自定义的函数库
|-ierror.py 错误码解释文件，来自企业微信文档
|-main.py Flask代码文件，编写主要逻辑
|-config.yaml 企业微信的个人配置文件，数据绑定企业微信（并未上传）
```

其中，由于`config.yaml` 涉及个人信息，并未上传，其结构如下：

![image-20211028001024147](https://i.loli.net/2021/10/28/AmKpVQfvU2SNdOB.png)

其中，`corpid`为企业ID，`corpsecret`为自定义应用Secret，`receive_token`和`AESKey`分别为定义接收消息API时定义的`Token`和`EncodingAESKey`

此代码由纯小白复现起来可能有难度，感到困难的同学可以先听我讲。

### 技术栈：

* ❤️ 服务 —— Flask，文档见 [Welcome to Flask — Flask Documentation (2.0.x) (palletsprojects.com)](https://flask.palletsprojects.com/en/2.0.x/)
* ❤️ 部署 —— 基于 screen 部署，文档见 [Screen User’s Manual: Top (gnu.org)](https://www.gnu.org/software/screen/manual/html_node/index.html)

### 效果图：

<img src="https://i.loli.net/2021/10/27/8YrXAjFcivwudVf.png" alt="image-20211027230020087" style="zoom:50%;" />



## 硬件端

目前已上传需要用到的esp32操控蜂鸣器，4个按钮分别检测按下，12864液晶显示自定义文字示例代码，用到的库和接口见接口定义，所有代码都已通过测试，IDE采用 [PlatformIO](https://platformio.org/) ，可直接在图形化界面里进行对应库的安装，可自行进行样例测试。

![IMG_20211227_210158](https://s2.loli.net/2021/12/27/vMeRJAktQ6pmy83.jpg)



此项目基于Arduino实现，较为简单，建议使用VScode作为IDE复现代码，同学们若想使用此代码，在购买硬件时，注意是否支持Arduino库。



## RoadMap

🚀 表示已经实现的功能，👷 表示进行中的功能，⏳ 表示规划中的功能，🏹 表示技术方案设计中的功能。

| 功能                                 | 状态      |
| ------------------------------------ | --------- |
| 服务器代理企业微信应用与用户双向通信 | 🚀 已实现  |
| 更详细的代码注释                     | 🚀 已实现  |
| 在单片机上实现老人求助功能           | ⏳  规划中 |
| 一些更进一步的功能                   | 🏹 设计中  |

## 使用到的硬件淘宝链接（仅供参考）

| 硬件                                | 页面链接                            |
| ----------------------------------- | ----------------------------------- |
| NodeMCU-32S CH340(强烈推荐，3个GND) | https://m.tb.cn/h.fjLwS3o?sm=dd01d0 |
| OLED 2.4寸白色 SSD1309/128x64       | https://m.tb.cn/h.f8MxQ2X?sm=b33ce6 |
| 有源蜂鸣器，高电平触发              | https://m.tb.cn/h.fjLDt5d?sm=0cd854 |
| 4位独立按键模块                     | https://m.tb.cn/h.fRJ2sJ5?sm=85a4ba |

## 关于：

本项目为课程教学项目，仅供教学使用。

