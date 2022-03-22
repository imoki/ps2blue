# ps2blue

#### 介绍
esp32蓝牙摇杆鼠标


#### 安装教程

1.先安装ESP32蓝牙鼠标模拟库
```
https://github.com/T-vK/ESP32-BLE-Mouse
或
https://gitee.com/onlykeri/ESP32-BLE-Keyboard.git
```

2.电路接线
![输入图片说明](15.PS2%E6%93%8D%E7%BA%B5%E6%9D%86%E5%AE%9E%E9%AA%8C_bb.jpg)
图片来源：创乐博 《基于ESP32物联网IOT开发套件学习Arduino IDE C/C++编程》

#### 使用说明

可能不同ps2静止时实际测得的x和y值有细微差别，只需要根据自己的ps2修改如下变量的值即可​。xCentre为ps2静止时实际测得x值/10,yCentre为ps2静止时实际测得y值/10,xDeviationMin和yDeviationMin是对实际测得的值进行细微修正，可看我下面的说明。

```
const float xCentre = 46.0; // x中心
const float yCentre = 47.0; // y中心
const int xDeviationMin = 3;  // x细微偏差值
const int yDeviationMin = 3;  // y细微偏差值
```

ps2的x和y轴数据范围为0-1023，当ps2静止时，实际测得x值为458-462，y值为478-482。
变量解释及代码思路：
1.首先对ps2获取的x和y值做处理：将0-1023缩短为0-102（即测量值除以10），但是ps2静止时,x值为45-46，y值为47-48。为了使静止时x和y恒定不变，因此对实际测得x值加上一个细微偏差值xDeviationMin（这里为3），对实际测得y值减去一个细微偏差值yDeviationMin（这里为3）。从而使得实际值x和y除以10后恒定不变。
2.编写鼠标移动逻辑，首先发现ps2静止时，在x轴方向，x处于中心时左右侧的长度不等（左侧102~46，右侧46~0），因此需要让左右两侧等长，只需要对右侧的数都乘以一个值xDeviation即可，xDeviation = (102- 46)/46;同理y轴方向也一样。最后就直接用个循环，里面包含x轴方向移动多久，y轴方向移动多久即可
3.点击，按下ps2时相当于点击鼠标左键

最后将代码烧录到esp32中，电脑连接名为ps2blue的蓝牙，即可用ps2控制鼠标

