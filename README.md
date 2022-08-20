# MCS51 CircleMN

#### 介绍
本软件是面向51单片机的，寄存器自动配置、代码自动生成工具，功能设计主要参考STM32CubeMX。希望这一软件能够帮助喜欢用51的朋友们简化一些开发流程，加快开发速度。

#### 软件运行环境要求
建议Windows7及以上，32 / 64位 系统均可运行。

#### 使用方法

1.  下载项目zip包到本地，并解压
2.  进入Release文件夹，运行MCS51CircleMN.exe
3.  在“功能模块配置”页面对需要使用的硬件功能进行配置，输入必要的参数，并对需要启用的模块勾选“启用该模块”；如果需要使用对应的中断，则勾选“开启中断”。
4.  完成后，切换到“项目生成设置”页面，输入项目名称（建议使用英文），点击“浏览”选择项目路径，然后点击“生成项目！”按钮，即可生成相应的Keil工程。
5.  打开Keil工程，编写必要的应用逻辑，并进行编译，烧录至单片机。

#### 函数库说明

  由软件生成的工程文件中，对必要的硬件操作已经封装为函数，无须操作寄存器。（但直接操作寄存器也可以控制硬件，两种方法并不冲突）
1.  串口硬件：在软件中完成配置后即可直接使用。uart.c为串口相关代码。调用print()函数发送字符串，InterruptUART()为中断函数，可在其中处理接收操作。
2.  定时器硬件：在软件中完成配置后即可直接使用。tim.c为定时器相关代码。调用StartT0() / StartT1()启动定时器，调用StopT0() / StopT1()停止定时器。InterruptT0() / InterruptT1()为中断函数。
3.  外部中断硬件：在软件中完成配置后即可直接使用。exti.c为外部中断相关代码。InterruptExti0() / InterruptExti1()为中断函数。


#### 注意事项

1.  本软件仅适用标准型8051/8052单片机，以及机器周期与标准型相一致的增强型51。
2.  本软件仅提供自动化配置结果，不保证生成的代码一定正确无误；此外，对因使用本软件而可能造成的任何形式的损失不予赔偿，敬请留意。软件生成的代码可用于学习，如用于工程请再三检查代码，确保无误！

#### 致谢

本软件使用到了如下的开源工具/库：
1.  QT 5.12
2.  TinyXML

衷心向以上项目作者表示感谢。没有好用的工具/库，本软件的制作将非常困难，甚至无法实现。
