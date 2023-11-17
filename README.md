# 轮腿平衡车
北极熊的轮腿平衡车车验证项目，打造一款萌宠小平衡。

doc文件夹中为说明文档，请阅读

更多功能正在开发中。

## 电机标号

![motor_id](./doc/.pic/motor_id.svg)<br>

本项目中前方方向为电池开关方向。

关节电机选用小米电机，接入CAN1，各电机id如图所示。

驱动轮电机选用2006，接入CAN2，各电机id如图所示。


## 操作说明
鉴于小米电机的控制反馈问题，目前打算先用几何解算来使用位置模式达到控制效果。
1. 准备模式，遥控器左端拨杆置于`OFF`档，初始化收腿（此时将右拨杆置于`ATII`裆重新标定电机零点）
2. 腿部伸长，遥控器左端拨杆置于`CL`档，此时腿部伸长到指定位置
3. 将机器人竖直放置
4. 开始平衡，遥控器左端拨杆置于`HL`档，此时差不多能平衡了。

如何控制这只小平衡：
- 右摇杆控制速度和旋转。
- 左摇杆控制腿长和roll角。

## 参考
- [RoboMaster平衡步兵机器人控制系统设计](https://zhuanlan.zhihu.com/p/563048952)
- [无刷轮腿平衡机器人开源GitHub仓库](https://github.com/Skythinker616/foc-wheel-legged-robot/tree/master)
- [2023 EC basic-framework](https://gitee.com/hnuyuelurm/balance_chassis)

详见 [reference](./doc/reference.md)

## 开发方向
- 添加离地检测和打滑检测