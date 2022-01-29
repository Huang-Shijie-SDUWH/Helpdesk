# Python 与 Linux 基础教学项目

本项目旨在基于ESP32开发一个独居老人按键求助的家庭求助机，家人可通过企业微信收到求助消息，并可直接通过企业微信进行回复。

## 项目框架

![image-20220128213530297](https://s2.loli.net/2022/01/28/rkAmadftC2Ljb7c.png)

本项目采用一个 `Websocket` 服务器与单片机通信，一个 `HTTP` 服务器与企业微信端通信，服务器之间提供 `redis` 通信的方法来建立单片机与企业微信之间的双端通信。

## 服务器端

### Quick Start

```shell
git clone https://github.com/Huang-Shijie-SDUWH/Helpdesk.git
cd Helpdesk/Server
docker-compose up
```

记得修改认证信息，域名信息等。

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

其中， `corpid` 为企业ID， `corpsecret` 为自定义应用Secret， `receive_token` 和 `AESKey` 分别为定义接收消息API时定义的 `Token` 和 `EncodingAESKey` 

### 技术栈：

* ❤️ HTTP服务 —— Flask，文档见 [Flask Documentation (2.0.x)](https://flask.palletsprojects.com/en/2.0.x/) 
* ❤️ WebSocket服务 —— Websocket-Server，文档见 [Pithikos/python-websocket-server](https://github.com/Pithikos/python-websocket-server) 
* ❤️ 部署 —— Docker-Compose 部署，文档见 [Docker Documentation](https://docs.docker.com/compose/) 

### 效果图：

![image-20220128212043303](https://s2.loli.net/2022/01/28/Xun6hHbdAM49yW2.png)

## 硬件端

已实现蜂鸣器以任意频率响任意声，显示屏显示任意消息，按键检测/防抖，websocket收发消息。用到的库和接口见接口定义，所有代码都已通过测试，IDE采用 [PlatformIO](https://platformio.org/) ，可直接在图形化界面里进行对应库的安装，可自行进行样例测试。

![image-20220128212006638](https://s2.loli.net/2022/01/28/mtEs1r8ePdIu3GF.png)

此项目基于Arduino实现，较为简单，建议使用VScode作为IDE复现代码，若想使用此代码，在购买硬件时，注意是否支持Arduino库。



## RoadMap

🚀 表示已经实现的功能，👷 表示进行中的功能，⏳ 表示规划中的功能，🏹 表示技术方案设计中的功能。

| 功能                                 | 状态     |
| ------------------------------------ | -------- |
| 服务器代理企业微信应用与用户双向通信 | 🚀 已实现 |
| 更详细的代码注释                     | 🚀 已实现 |
| 在单片机上实现老人求助功能           | 🚀 已实现 |
| 一些更进一步的功能                   | ⏳ 规划中 |

## 使用到的硬件淘宝链接（仅供参考）

| 硬件                                | 页面链接                            |
| ----------------------------------- | ----------------------------------- |
| NodeMCU-32S CH340(强烈推荐，3个GND) | https://m.tb.cn/h.fjLwS3o?sm=dd01d0 |
| OLED 2.4寸白色 SSD1309/128x64       | https://m.tb.cn/h.f8MxQ2X?sm=b33ce6 |
| 有源蜂鸣器，高电平触发              | https://m.tb.cn/h.fjLDt5d?sm=0cd854 |
| 4位独立按键模块                     | https://m.tb.cn/h.fRJ2sJ5?sm=85a4ba |

## 关于：

本项目为课程教学项目，若有它用，请遵循开源许可证。

