# CommunicationMonitor
现场不同设备经常容易掉线，做一个通讯检测小软件，定位问题是由于接线还是仪器自身问题
![图片](https://github.com/zhangjiechina001/CommunicationMonitor/assets/49397821/5b6f8605-138e-4df2-b901-9666fd75036f)
# 主要原理：
通过绑定连接客户端tcp端口后隔一段时间发送一次测试指令，看看指令有没有返回，这里的指令是每个设备自己的指令，建议是读取状态之类的。
下面是配置通讯的文件
```json
{
    "Interval": 2,
    "Items": {
        "激光器":{
                "CommunicationParam":"127.0.0.1:508",
                "SendCommand": "12345678",    
                "ReceiveCommand": "23456789"
        },
        "光谱仪":{
                "CommunicationParam":"127.0.0.1:508",  
                "SendCommand": "12345678",
                "ReceiveCommand": "23456789"
        }
    }
}
```
