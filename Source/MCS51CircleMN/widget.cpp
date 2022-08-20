#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <TinyXML/tinystr.h>
#include <TinyXML/tinyxml.h>
#include <t1canceldialog.h>
#include <uartcanceldialog.h>
#include <baudwrongdialog.h>
#include <timwrongdialog.h>
#include <genfinishdialog.h>
#include <fileexistdialog.h>
#include <timewrongdialog.h>
#include <timecopieddialog.h>
#include <aboutauthordialog.h>
#include <aboutsoftwaredialog.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

TiXmlElement* FindInDepth(TiXmlElement* element,const char* targetValue)//xml纵深查询
{
    while(strcmp(element->Value(),targetValue)!=0)
    {
        element=element->FirstChildElement();
    }
    return element;
}

TiXmlElement* FindInSameLevel(TiXmlElement* element,const char* targetValue)//xml同级查询
{
    while(strcmp(element->Value(),targetValue)!=0)
    {
        element=element->NextSiblingElement();
    }
    return element;
}

void AddIncludePath(QString fileName_proj,QString includePaths)
{
    //
    TiXmlDocument doc;
    if(doc.LoadFile(fileName_proj.toStdString().c_str()))
    {
        qDebug()<<"XML Load Success"<<endl;
    }
    else
    {
        qDebug()<<"XML Load Failed"<<endl;
    }

    TiXmlElement* element=doc.RootElement();
    element=element->FirstChildElement();

    element=FindInSameLevel(element,"Targets");
    element=FindInDepth(element,"TargetName");
    element=FindInSameLevel(element,"TargetOption");
    element=element->FirstChildElement();
    element=FindInSameLevel(element,"Target51");
    element=element->FirstChildElement();
    element=FindInSameLevel(element,"C51");
    element=element->FirstChildElement();
    element=FindInSameLevel(element,"VariousControls");
    element=element->FirstChildElement();
    element=FindInSameLevel(element,"IncludePath");

    TiXmlText* text=new TiXmlText(includePaths.toStdString().c_str());
    element->LinkEndChild(text);
    qDebug()<<"element value:"<<element->Value()<<endl;

    doc.SaveFile(fileName_proj.toStdString().c_str());
    qDebug()<<"IncludePath Add Complete!"<<endl;
}

void AddSourceFile(QString fileName_proj,QString fileName,QString filePath_source)
{
    //
    TiXmlDocument doc;
    if(doc.LoadFile(fileName_proj.toStdString().c_str()))
    {
        qDebug()<<"Load Success"<<endl;
    }
    else
    {
        qDebug()<<"Load Failed"<<endl;
    }

    TiXmlElement* element=doc.RootElement();
    //cout<<"root value:"<<element->Value()<<endl;
    element=element->FirstChildElement();
    element=element->NextSiblingElement();
    element=element->NextSiblingElement();
    element=element->FirstChildElement();
    element=element->FirstChildElement();

    element=FindInSameLevel(element,"Groups");
    /*while(strcmp(element->Value(),"Groups")!=0)//寻找Groups节点
    {
        cout<<"Element value:"<<element->Value()<<endl;
        element=element->NextSiblingElement();
    }*/
    element=element->FirstChildElement();
    element=element->FirstChildElement();
    element=element->NextSiblingElement();
    //cout<<"Element value:"<<element->Value()<<endl;

    TiXmlElement* element2=new TiXmlElement("File");

    TiXmlElement* element2_1=new TiXmlElement("FileName");
    TiXmlText* text2_1=new TiXmlText(fileName.toStdString().c_str());
    element2_1->LinkEndChild(text2_1);

    TiXmlElement* element2_2=new TiXmlElement("FileType");
    TiXmlText* text2_2=new TiXmlText("1");
    element2_2->LinkEndChild(text2_2);

    TiXmlElement* element2_3=new TiXmlElement("FilePath");


    TiXmlText* text2_3=new TiXmlText(filePath_source.toStdString().c_str());
    element2_3->LinkEndChild(text2_3);

    element2->LinkEndChild(element2_1);
    element2->LinkEndChild(element2_2);
    element2->LinkEndChild(element2_3);

    element->LinkEndChild(element2);

    doc.SaveFile(fileName_proj.toStdString().c_str());

    qDebug()<<"Souce Add Complete!"<<endl;
}

void Widget::ChangeProjectName(QString fileName_proj)
{
    TiXmlDocument doc;
    if(doc.LoadFile(fileName_proj.toStdString().c_str()))
    {
        qDebug()<<"Load Success"<<endl;
    }
    else
    {
        qDebug()<<"Load Failed"<<endl;
    }

    TiXmlElement* element=doc.RootElement();
    element=FindInDepth(element,"SchemaVersion");
    element=FindInSameLevel(element,"Targets");
    element=FindInDepth(element,"TargetName");
    element=FindInSameLevel(element,"TargetOption");
    element=FindInDepth(element,"Device");
    element=FindInSameLevel(element,"OutputName");

    TiXmlText* text=new TiXmlText(ui->lineEdit_projName->text().toStdString().c_str());
    element->LinkEndChild(text);

    doc.SaveFile(fileName_proj.toStdString().c_str());
    qDebug()<<"Project Name Change Complete!"<<endl;
}

bool CreateFolder(QString targetDirectory)
{
    QDir dir;
    if(dir.mkdir(targetDirectory))//创建项目文件夹
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isPureNumber(QString strInput)
{
    bool isNumber=true;
    const char* strConverted=strInput.toStdString().c_str();
    int length=strlen(strConverted);
    for(int cnt=0;cnt<length;cnt++)
    {
        if(*strConverted>='0' && *strConverted<='9')
        {
            strConverted++;
        }
        else
        {
            isNumber=false;
            break;
        }
    }
    return isNumber;
}

bool isLegalHex(QString strInput)
{
    const char* strConverted=strInput.toStdString().c_str();
    int length=strlen(strConverted);
    bool isHex=true;
    if(strConverted[0]=='0' && (strConverted[1]=='x' || strConverted[1]=='X'))
    {
        strConverted+=2;
        for(int cnt=2;cnt<length;cnt++)
        {
            if((*strConverted>='0' && *strConverted<='9') || (*strConverted>='A' && *strConverted<='F') || (*strConverted>='a' && *strConverted<='f'))
            {
                strConverted++;
            }
            else
            {
                isHex=false;
                break;
            }
        }
    }
    else
    {
        isHex=false;
    }
    return isHex;
}

bool isPureFloat(QString strInput)
{
    bool isFloat=true;
    const char* strConverted=strInput.toStdString().c_str();
    int length=strlen(strConverted);
    for(int cnt=0;cnt<length;cnt++)
    {
        if((*strConverted>='0' && *strConverted<='9') || *strConverted=='.')
        {
            strConverted++;
        }
        else
        {
            isFloat=false;
            break;
        }
    }
    return isFloat;
}

void Widget::GenerateAll()
{
    QString fileName_template=QApplication::applicationDirPath()+"/template/template.uvproj";
    QString fileName_proj=fileDirectory+"/"+ui->lineEdit_projName->text()+"/"+ui->lineEdit_projName->text()+".uvproj";//工程文件所在文件夹

    if(CreateFolder(fileDirectory+"/"+ui->lineEdit_projName->text()))//创建项目文件夹
    {
        qDebug()<<"Project Folder create successful"<<endl;
    }
    else
    {
        qDebug()<<"Project Folder create failed"<<endl;
    }

    QFile file_template(fileName_template);//模板工程文件所在位置
    file_template.copy(fileName_template,fileName_proj);
    file_template.close();
    qDebug()<<"Project file created!"<<endl;
    //经过实测，项目文件生成成功！
    //复制startup.a51文件
    QString filepath_startup=QApplication::applicationDirPath()+"/template/STARTUP.A51";
    QString targetPath_startup=fileDirectory+"/"+ui->lineEdit_projName->text()+"/STARTUP.A51";
    QFile file_startup(filepath_startup);
    file_startup.copy(filepath_startup,targetPath_startup);
    qDebug()<<"startup file copy successful"<<endl;

    //工程文件编辑操作
    //修改项目名称
    ChangeProjectName(fileName_proj);
    //添加项目头文件
    QString includePath;
    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        includePath=".\\TIM;";
    }
    if(ui->checkBox_uart_en->isChecked())
    {
        includePath+=".\\UART;";
    }
    if(ui->checkBox_ex0_en->isChecked() || ui->checkBox_ex1_en->isChecked())
    {
        includePath+=".\\EXTI;";
    }
    AddIncludePath(fileName_proj,includePath);
    //添加项目代码文件
    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        AddSourceFile(fileName_proj,"tim.c",".\\TIM\\tim.c");
    }
    if(ui->checkBox_uart_en->isChecked())
    {
        AddSourceFile(fileName_proj,"uart.c",".\\UART\\uart.c");
    }
    if(ui->checkBox_ex0_en->isChecked() || ui->checkBox_ex1_en->isChecked())
    {
        AddSourceFile(fileName_proj,"exti.c",".\\EXTI\\exti.c");
    }


    //代码文件编辑操作
    //定时器代码操作
    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        if(CreateFolder(fileDirectory+"/"+ui->lineEdit_projName->text()+"/TIM"))//创建模块代码文件夹
        {
            qDebug()<<"TIM Folder create successful"<<endl;
        }
        else
        {
            qDebug()<<"TIM Folder create failed"<<endl;
        }
        TimInclude();//定时器代码内头文件添加
        TimHeader();//定时器头文件编写
    }
    if(ui->checkBox_t0_en->isChecked())//如果定时器0被启用
    {
        ConfigureT0();
    }
    if(ui->checkBox_t1_en->isChecked())//如果定时器1被启用
    {
        ConfigureT1();
    }

    //串口代码操作
    if(ui->checkBox_uart_en->isChecked())
    {
        if(CreateFolder(fileDirectory+"/"+ui->lineEdit_projName->text()+"/UART"))//创建模块代码文件夹
        {
            qDebug()<<"UART Folder create successful"<<endl;
        }
        else
        {
            qDebug()<<"UART Folder create failed"<<endl;
        }
        UartInclude();//定时器代码内头文件添加
        UartHeader();//定时器头文件编写
        ConfigUart();
    }

    //外部中断代码操作
    if(ui->checkBox_ex0_en->isChecked() || ui->checkBox_ex1_en->isChecked())
    {
        if(CreateFolder(fileDirectory+"/"+ui->lineEdit_projName->text()+"/EXTI"))//创建模块代码文件夹
        {
            qDebug()<<"EXTI Folder create successful"<<endl;
        }
        else
        {
            qDebug()<<"EXTI Folder create failed"<<endl;
        }
        ExtiInclude();//外部中断代码内头文件引用
        ExtiHeader();//外部中断头文件编写
    }
    if(ui->checkBox_ex0_en->isChecked())
    {
        ConfigureExti0();
    }
    if(ui->checkBox_ex1_en->isChecked())
    {
        ConfigureExti1();
    }

    ConfigureMain();
}

void Widget::TimInclude()//定时器代码引用头文件
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/TIM/tim.c";
    QFile code_tim(temp);
    code_tim.open(QFile::WriteOnly);
    code_tim.write("#include \"reg52.h\"\n#include \"tim.h\"\n");//包含头文件
    code_tim.write("void PreProcessTMOD()\n{\n\tTMOD=0x00;\n}\n");
    code_tim.close();
}

void Widget::ConfigureT0()//定时器0配置
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/TIM/tim.c";
    QString temp2="TH0="+ui->lineEdit_t0h->text()+";\n\tTL0="+ui->lineEdit_t0l->text()+";\n\t";
    QString temp3="void LoadT0()\n{\n\tTH0="+ui->lineEdit_t0h->text()+";\n\tTL0="+ui->lineEdit_t0l->text()+";\n}\n";
    QFile code_tim(temp);
    code_tim.open(QFile::Append);
    code_tim.write("void StartT0()\n{\n\tTR0=1;\n}\n");
    code_tim.write("void StopT0()\n{\n\tTR0=0;\n}\n");
    code_tim.write("void ConfigT0()\n{\n\tEA=1;\n\t");
    switch (ui->comboBox_t0mode->currentIndex())
    {
        case 0://16位手动重装
            code_tim.write("TMOD|=0x01;\n\t");
            break;
        case 1://8位自动重装
            code_tim.write("TMOD|=0x02;\n\t");
            break;
    }
    code_tim.write(temp2.toStdString().c_str());
    if(ui->checkBox_t0it->isChecked())
    {
        code_tim.write("ET0=1;\n}\n");
        code_tim.write(temp3.toStdString().c_str());
        code_tim.write("void InterruptT0() interrupt 1\n{\n\t\n}\n");
    }
    else
    {
        code_tim.write("\n}\n");
        code_tim.write(temp3.toStdString().c_str());
    }
    code_tim.close();
    qDebug()<<"TIM0 config completed!"<<endl;
}

void Widget::ConfigureT1()//定时器1配置
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/TIM/tim.c";
    QString temp2="TH1="+ui->lineEdit_t1h->text()+";\n\tTL1="+ui->lineEdit_t1l->text()+";\n\t";
    QString temp3="void LoadT1()\n{\n\tTH1="+ui->lineEdit_t1h->text()+";\n\tTL1="+ui->lineEdit_t1l->text()+";\n}\n";
    QFile code_tim(temp);
    code_tim.open(QFile::Append);
    code_tim.write("void StartT1()\n{\n\tTR1=1;\n}\n");
    code_tim.write("void StopT1()\n{\n\tTR1=0;\n}\n");
    code_tim.write("void ConfigT1()\n{\n\tEA=1;\n\t");
    switch(ui->comboBox_t1mode->currentIndex())
    {
        case 0://16位手动重装
            code_tim.write("TMOD|=0x10;\n\t");
            break;
        case 1://8位自动重装
            code_tim.write("TMOD|=0x20;\n\t");
            break;
    }

    code_tim.write(temp2.toStdString().c_str());
    if(ui->checkBox_t1it->isChecked())
    {
        code_tim.write("ET1=1;\n}\n");
        code_tim.write(temp3.toStdString().c_str());
        code_tim.write("void InterruptT1() interrupt 3\n{\n\t\n}\n");
    }
    else
    {
        code_tim.write("\n}\n");
        code_tim.write(temp3.toStdString().c_str());
    }
    //code_tim.write("void LoadT1()\n{\n\tTH1=0xfc;\n\tTL1=0x66;\n}\n");
    code_tim.close();
    qDebug()<<"TIM1 config completed!"<<endl;
}

void Widget::TimHeader()//定时器头文件编写
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/TIM/tim.h";
    QFile code_tim_header(temp);
    code_tim_header.open(QFile::Append);
    code_tim_header.write("#include \"reg52.h\"\n");
    code_tim_header.write("#ifndef __TIM_H\n#define __TIM_H\n");
    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        code_tim_header.write("void PreProcessTMOD();\n");
    }
    if(ui->checkBox_t0_en->isChecked())
    {
        code_tim_header.write("void StartT0();\n");
        code_tim_header.write("void StopT0();\n");
        code_tim_header.write("void ConfigT0();\n");
        code_tim_header.write("void LoadT0();\n");
        if(ui->checkBox_t0it->isChecked())
        {
            code_tim_header.write("void InterruptT0();\n");
        }
    }
    if(ui->checkBox_t1_en->isChecked())
    {
        code_tim_header.write("void StartT1();\n");
        code_tim_header.write("void StopT1();\n");
        code_tim_header.write("void ConfigT1();\n");
        code_tim_header.write("void LoadT1();\n");
        if(ui->checkBox_t1it->isChecked())
        {
            code_tim_header.write("void InterruptT1();\n");
        }
    }
    code_tim_header.write("#endif\n");
    code_tim_header.close();
}

void Widget::UartInclude()//串口代码引用头文件
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/UART/uart.c";
    QFile code_uart(temp);
    code_uart.open(QFile::WriteOnly);
    code_uart.write("#include \"reg52.h\"\n#include \"uart.h\"\n#include \"string.h\"\n");//包含头文件
    code_uart.close();
}

void Widget::ConfigUart()//串口配置
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/UART/uart.c";
    QString temp2="TH1=256-(11059200/12/16)/baud;\n\t";
    QFile code_uart(temp);
    code_uart.open(QFile::Append);
    code_uart.write("void ConfigUART(unsigned int baud)\n{\n\tPCON|=0x80;\n\tSCON=0x50;\n\t");
    code_uart.write("TMOD|=0x20;\n\t");
    code_uart.write(temp2.toStdString().c_str());
    code_uart.write("TL1=TH1;\n\tET1=0;\n\t");

    if(ui->checkBox_uart_it->isChecked())
    {
        code_uart.write("ES=1;\n\tEA=1;\n\tTR1=1;\n}\n");
        code_uart.write("void InterruptUART() interrupt 4\n");
        //code_uart.write("{\n\tif(TI)\n\t{\n\t\tTI=0;\n\t}\n\t");
        code_uart.write("{\n\tif(RI)\n\t{\n\t\tRI=0;\n\t}\n}\n");
    }
    else
    {
        code_uart.write("TR1=1;\n}\n");
    }

    code_uart.write("void print(unsigned char* str)\n{\n\t");
    code_uart.write("unsigned int cnt=0;\n\t");
    code_uart.write("while(*str)\n\t{\n\t\t");
    code_uart.write("SBUF=*str++;\n\t\twhile(!TI);\n\t\tTI=0;\n\t}\n}\n");

    code_uart.close();
    qDebug()<<"UART config completed!"<<endl;
}

void Widget::UartHeader()
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/UART/uart.h";
    QFile code_uart_header(temp);
    code_uart_header.open(QFile::Append);
    code_uart_header.write("#include \"reg52.h\"\n");
    code_uart_header.write("#ifndef __UART_H\n#define __UART_H\n");

    code_uart_header.write("void ConfigUART(unsigned int baud);\n");
    if(ui->checkBox_uart_it->isChecked())
    {
        code_uart_header.write("void InterruptUART();\n");
    }
    code_uart_header.write("void print(unsigned char* str);\n");

    code_uart_header.write("#endif\n");
    code_uart_header.close();
}

void Widget::ExtiInclude()
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/EXTI/exti.c";
    QFile code_exti(temp);
    code_exti.open(QFile::WriteOnly);
    code_exti.write("#include \"reg52.h\"\n#include \"exti.h\"\n");//包含头文件
    code_exti.close();
}

void Widget::ConfigureExti0()
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/EXTI/exti.c";
    QFile code_exti(temp);
    code_exti.open(QFile::Append);
    code_exti.write("void ConfigExti0()\n{\n\t");

    switch(ui->comboBox_ex0_trigmode->currentIndex())//配置触发模式
    {
        case 0://下降沿触发
            code_exti.write("IT0=1;\n\t");
            break;
        case 1://低电平触发
            code_exti.write("IT0=0;\n\t");
            break;
    }

    if(ui->checkBox_ex0it->isChecked())//已开启中断
    {
        code_exti.write("EX0=1;\n\tEA=1;\n}\n");
        code_exti.write("void InterruptExti0() interrupt 0\n{\n\t");
        code_exti.write("\n}\n");
    }
    else
    {
        code_exti.write("\n}\n");
    }


    code_exti.close();
    qDebug()<<"Exti0 config completed!"<<endl;
}

void Widget::ConfigureExti1()
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/EXTI/exti.c";
    QFile code_exti(temp);
    code_exti.open(QFile::Append);
    code_exti.write("void ConfigExti1()\n{\n\t");

    switch(ui->comboBox_ex1_trigmode->currentIndex())//配置触发模式
    {
        case 0://下降沿触发
            code_exti.write("IT1=1;\n\t");
            break;
        case 1://低电平触发
            code_exti.write("IT1=0;\n\t");
            break;
    }

    if(ui->checkBox_ex1it->isChecked())//已开启中断
    {
        code_exti.write("EX1=1;\n\tEA=1;\n}\n");
        code_exti.write("void InterruptExti1() interrupt 2\n{\n\t");
        code_exti.write("\n}\n");
    }
    else
    {
        code_exti.write("\n}\n");
    }


    code_exti.close();
    qDebug()<<"Exti1 config completed!"<<endl;
}

void Widget::ExtiHeader()
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/EXTI/exti.h";
    QFile code_exti_header(temp);
    code_exti_header.open(QFile::Append);
    code_exti_header.write("#include \"reg52.h\"\n");
    code_exti_header.write("#ifndef __EXTI_H\n#define __EXTI_H\n");
    if(ui->checkBox_ex0_en->isChecked())//如果外部中断0已启用
    {
        code_exti_header.write("void ConfigExti0();\n");
        if(ui->checkBox_ex0it->isChecked())
        {
            code_exti_header.write("void InterruptExti0();\n");
        }
    }
    if(ui->checkBox_ex1_en->isChecked())//如果外部中断1已启用
    {
        code_exti_header.write("void ConfigExti1();\n");
        if(ui->checkBox_ex1it->isChecked())
        {
            code_exti_header.write("void InterruptExti1();\n");
        }
    }
    code_exti_header.write("#endif\n");
    code_exti_header.close();
}

void Widget::ConfigureMain()//配置主函数代码
{
    QString temp=fileDirectory+"/"+ui->lineEdit_projName->text()+"/main.c";
    QFile code_main(temp);
    code_main.open(QFile::WriteOnly);
    code_main.write("#include \"reg52.h\"\n");

    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        code_main.write("#include \"tim.h\"\n");
    }
    if(ui->checkBox_uart_en->isChecked())
    {
        code_main.write("#include \"uart.h\"\n");
    }
    if(ui->checkBox_ex0_en->isChecked() || ui->checkBox_ex1_en->isChecked())
    {
        code_main.write("#include \"exti.h\"\n");
    }

    code_main.write("void main()\n{\n\t");
    if(ui->checkBox_t0_en->isChecked() || ui->checkBox_t1_en->isChecked())
    {
        //
        code_main.write("PreProcessTMOD();\n\t");
        if(ui->checkBox_t0_en->isChecked())
        {
            code_main.write("ConfigT0();\n\t");
        }
        if(ui->checkBox_t1_en->isChecked())
        {
            code_main.write("ConfigT1();\n\t");
        }
    }
    if(ui->checkBox_uart_en->isChecked())
    {
        QString Baud="ConfigUART("+ui->lineEdit_baud->text()+");\n\t";
        code_main.write(Baud.toStdString().c_str());
    }
    if(ui->checkBox_ex0_en->isChecked() || ui->checkBox_ex1_en->isChecked())
    {
        if(ui->checkBox_ex0_en->isChecked())
        {
            code_main.write("ConfigExti0();\n\t");
        }
        if(ui->checkBox_ex1_en->isChecked())
        {
            code_main.write("ConfigExti1();\n\t");
        }
    }


    code_main.write("while(1);\n}\n");
    code_main.close();
    qDebug()<<"main.c created!"<<endl;
}

void Widget::PulseToRegT0()//t0脉冲数转寄存器值
{
    if(isPureNumber(ui->lineEdit_t0_pulse->text()))
    {
        int temp=ui->lineEdit_t0_pulse->text().toInt();
        char str_temp[30];
        switch(ui->comboBox_t0mode_pulse->currentIndex())
        {
        case 0://16位手动模式
            temp=65536-temp;
            sprintf(str_temp,"0x%02x",temp/256);
            ui->lineEdit_t0h->setText(str_temp);
            memset(str_temp,0,30);

            sprintf(str_temp,"0x%02x",temp%256);
            ui->lineEdit_t0l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        case 1://8位自动模式
            temp=256-temp;
            sprintf(str_temp,"0x%02x",temp%256);
            ui->lineEdit_t0h->setText(str_temp);
            ui->lineEdit_t0l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        }
    }
}

void Widget::PulseToRegT1()//t1脉冲数转寄存器值
{
    if(isPureNumber(ui->lineEdit_t1_pulse->text()))
    {
        int temp=ui->lineEdit_t1_pulse->text().toInt();
        char str_temp[30];
        switch(ui->comboBox_t1mode_pulse->currentIndex())
        {
        case 0://16位手动模式
            temp=65536-temp;
            sprintf(str_temp,"0x%02x",temp/256);
            ui->lineEdit_t1h->setText(str_temp);
            memset(str_temp,0,30);

            sprintf(str_temp,"0x%02x",temp%256);
            ui->lineEdit_t1l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        case 1://8位自动模式
            temp=256-temp;
            sprintf(str_temp,"0x%02x",temp%256);
            ui->lineEdit_t1h->setText(str_temp);
            ui->lineEdit_t1l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        }
    }
}

void Widget::on_pushButton_clicked()//顶栏按钮1
{
    ui->tabWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_2_clicked()//顶栏按钮2
{
    ui->tabWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_3_clicked()//顶栏按钮3
{
    ui->tabWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_5_clicked()//项目路径选择
{
    QString temp;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly,true);

    temp=dialog.getExistingDirectory(this,"请选择路径","C:\\");
    if(temp!=NULL)
    {
        fileDirectory=temp;
    }

    ui->lineEdit_3->setText(fileDirectory);
}

int HexToInt(QString strInput)
{
    const char* strConverted=strInput.toStdString().c_str();
    int result=0;
    if(strConverted[1]=='x')
    {
        sscanf(strConverted,"0x%02x",&result);
    }
    else if(strConverted[1]=='X')
    {
        sscanf(strConverted,"0X%02x",&result);
    }
    return result;
}



void Widget::on_listWidget_currentRowChanged(int currentRow)
{
    qDebug()<<currentRow<<" Selected"<<endl;
    ui->tabWidget_2->setCurrentIndex(currentRow+1);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    ui->tab_t0->setCurrentIndex(index);
}

void Widget::on_comboBox_4_currentIndexChanged(int index)
{
    ui->tab_t1->setCurrentIndex(index);
}

void Widget::on_pushButton_6_clicked()//生成项目按钮
{
    QDir dir;
    dir.setPath(fileDirectory+"/"+ui->lineEdit_projName->text());
    if(dir.exists())
    {
        fileExistDialog* existDialog=new fileExistDialog;
        existDialog->setWindowTitle("提示信息");
        existDialog->show();
    }
    else
    {
        GenerateAll();
        GenFinishDialog* finishDialog=new GenFinishDialog;
        finishDialog->setWindowTitle("提示信息");
        finishDialog->show();
    }
}



void Widget::on_checkBox_uart_en_toggled(bool checked)//串口勾选框
{
    if(checked)
    {
        QString BaudInput=ui->lineEdit_baud->text();
        if(!isPureNumber(BaudInput) && !isLegalHex(BaudInput))//波特率输入错误提示
        {
            BaudWrongDialog* baudDialog=new BaudWrongDialog;
            baudDialog->setWindowTitle("提示信息");
            baudDialog->show();
        }
        else if(ui->checkBox_t1_en->isChecked())//与定时器1相冲突，弹窗提示
        {
            t1CancelDialog* t1Dialog=new t1CancelDialog;
            t1Dialog->setWindowTitle("提示信息");
            t1Dialog->show();
            ui->checkBox_t1_en->setCheckState(Qt::Unchecked);
        }
    }
}

void Widget::on_checkBox_t1_en_toggled(bool checked)//t1勾选框
{
    if(checked)
    {
        QString ThInput=ui->lineEdit_t1h->text();
        QString TlInput=ui->lineEdit_t1l->text();
        if((!isPureNumber(ThInput) && !isLegalHex(ThInput)) || (!isPureNumber(TlInput) && !isLegalHex(TlInput)))
        {
            TimWrongDialog* timDialog=new TimWrongDialog;
            timDialog->setWindowTitle("提示信息");
            timDialog->show();
        }
        else if(ui->checkBox_uart_en->isChecked())
        {
            uartcanceldialog* uartDialog=new uartcanceldialog;
            uartDialog->setWindowTitle("提示信息");
            uartDialog->show();
            ui->checkBox_uart_en->setCheckState(Qt::Unchecked);
        }
    }
}

void Widget::on_checkBox_t0_en_toggled(bool checked)
{
    if(checked)
    {
        QString ThInput=ui->lineEdit_t0h->text();
        QString TlInput=ui->lineEdit_t0l->text();
        if((!isPureNumber(ThInput) && !isLegalHex(ThInput)) || (!isPureNumber(TlInput) && !isLegalHex(TlInput)))
        {
            TimWrongDialog* timDialog=new TimWrongDialog;
            timDialog->setWindowTitle("提示信息");
            timDialog->show();
        }
    }
}



void Widget::on_checkBox_t0it_2_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBox_t0it->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_t0it->setCheckState(Qt::Unchecked);
    }
}

void Widget::on_checkBox_t0_pulse_en_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBox_t0_en->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_t0_en->setCheckState(Qt::Unchecked);
    }
}

void Widget::on_comboBox_t0mode_pulse_currentIndexChanged(int index)
{
    ui->comboBox_t0mode->setCurrentIndex(index);
    PulseToRegT0();
}

void Widget::on_lineEdit_t0_pulse_editingFinished()//输入完成后，进行进制换算
{
    /*if(isPureNumber(ui->lineEdit_t0_pulse->text()))
    {
        int temp=ui->lineEdit_t0_pulse->text().toInt();
        char str_temp[30];
        switch(ui->comboBox_t0mode_pulse->currentIndex())
        {
        case 0://16位手动模式
            sprintf(str_temp,"0x%x",temp/256);
            ui->lineEdit_t0h->setText(str_temp);
            memset(str_temp,0,30);

            sprintf(str_temp,"0x%x",temp%256);
            ui->lineEdit_t0l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        case 1://8位自动模式
            sprintf(str_temp,"0x%x",temp%256);
            ui->lineEdit_t0h->setText(str_temp);
            ui->lineEdit_t0l->setText(str_temp);
            memset(str_temp,0,30);
            break;
        }
    }*/
    PulseToRegT0();
}

void Widget::on_checkBox_t1it_2_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBox_t1it->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_t1it->setCheckState(Qt::Unchecked);
    }
}

void Widget::on_checkBox_t1_pulse_en_toggled(bool checked)
{
    if(checked)
    {
        ui->checkBox_t1_en->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_t1_en->setCheckState(Qt::Unchecked);
    }
}

void Widget::on_lineEdit_t1_pulse_editingFinished()
{
    /*int temp=ui->lineEdit_t1_pulse->text().toInt();
    char str_temp[30];
    switch(ui->comboBox_t1mode_pulse->currentIndex())
    {
    case 0://16位手动模式
        sprintf(str_temp,"0x%x",temp/256);
        ui->lineEdit_t1h->setText(str_temp);
        memset(str_temp,0,30);

        sprintf(str_temp,"0x%x",temp%256);
        ui->lineEdit_t1l->setText(str_temp);
        memset(str_temp,0,30);
        break;
    case 1://8位自动模式
        sprintf(str_temp,"0x%x",temp%256);
        ui->lineEdit_t1h->setText(str_temp);
        ui->lineEdit_t1l->setText(str_temp);
        memset(str_temp,0,30);
        break;
    }*/
    PulseToRegT1();
}

void Widget::on_comboBox_t1mode_pulse_currentIndexChanged(int index)
{
    ui->comboBox_t1mode->setCurrentIndex(index);
    PulseToRegT1();
}

void Widget::on_pushButton_calculate_clicked()//计算时长
{
    if(ui->comboBox_cal_mode->currentIndex()==0)//从寄存器值算时长
    {
        QString thx=ui->lineEdit_thx->text();
        QString tlx=ui->lineEdit_tlx->text();
        QString xtal_input=ui->lineEdit_xtal->text();
        float xtal=11.0592f;
        int th,tl;
        float result;
        if(isPureFloat(xtal_input) || isPureNumber(xtal_input))
        {
            xtal=xtal_input.toFloat()*1000000;//计算晶振数值，单位为hz
        }


        if(isPureNumber(thx) || isLegalHex(thx))//处理高8位
        {
            if(isPureNumber(thx))
            {
                th=thx.toInt();
            }
            else
            {
                th=HexToInt(thx);
            }
            if(isPureNumber(tlx) || isLegalHex(tlx))//处理低8位
            {
                if(isPureNumber(tlx))
                {
                    tl=tlx.toInt();
                }
                else
                {
                    tl=HexToInt(tlx);
                }
                //按模式分别处理
                if(ui->comboBox_txmode_reg->currentIndex()==0)//16位手动模式
                {
                    th=th*256+tl;
                    th=65536-th;//th为脉冲个数
                }
                else//8位自动模式
                {
                    th=256-th;//th为脉冲个数
                }
                result=th*12/xtal*1000;
                char result_out[30];
                sprintf(result_out,"%.4f",result);
                ui->lineEdit_corrsponding_time->setText(result_out);
            }
            else//低8位输入错误
            {
                TimWrongDialog* timDialog=new TimWrongDialog;
                timDialog->setWindowTitle("提示信息");
                timDialog->show();
            }
        }
        else//高8位输入错误
        {
            TimWrongDialog* timDialog=new TimWrongDialog;
            timDialog->setWindowTitle("提示信息");
            timDialog->show();
        }
    }
    else//从时长算寄存器值
    {
        QString xtal_input=ui->lineEdit_xtal->text();
        float xtal=11.0592f;
        QString targetTime_input=ui->lineEdit_target_time->text();
        float targetTime;
        int th,tl;
        char strOutput[30];
        float error;
        if(isPureFloat(xtal_input) || isPureNumber(xtal_input))
        {
            xtal=xtal_input.toFloat()*1000000;//计算晶振数值，单位为hz
        }
        if(isPureFloat(targetTime_input))//如果输入正常，则转换为数字型
        {
            targetTime=targetTime_input.toFloat();
            error=targetTime-(int)(targetTime*xtal/12/1000)/xtal*12*1000;

            sprintf(strOutput,"%.4f",error);
            ui->lineEdit_corresponding_error->setText(strOutput);
            memset(strOutput,0,30);

            th=(int)(targetTime*xtal/12/1000);
            if(ui->comboBox_txmode_toreg->currentIndex()==0)//16位手动模式
            {
                th=65536-th;
                tl=th%256;
                th=th/256;
            }
            else//8位自动模式
            {
                th=256-th;
                tl=th;
            }
            sprintf(strOutput,"0x%02x",th);
            ui->lineEdit_corresponding_thx->setText(strOutput);
            memset(strOutput,0,30);

            sprintf(strOutput,"0x%02x",tl);
            ui->lineEdit_corresponding_tlx->setText(strOutput);
            memset(strOutput,0,30);


        }
        else//如果输入非数字，则弹窗提示
        {
            timeWrongDialog* timeDialog=new timeWrongDialog;
            timeDialog->setWindowTitle("提示信息");
            timeDialog->show();
        }
    }
}

void Widget::on_comboBox_cal_mode_currentIndexChanged(int index)
{
    ui->tab_cal_mode->setCurrentIndex(index);
}

void Widget::on_pushButton_fromt0_clicked()//从t0导入
{
    ui->lineEdit_thx->setText(ui->lineEdit_t0h->text());
    ui->lineEdit_tlx->setText(ui->lineEdit_t0l->text());
    ui->comboBox_txmode_reg->setCurrentIndex(ui->comboBox_t0mode->currentIndex());
}

void Widget::on_pushButton_fromt1_clicked()//从t1导入
{
    ui->lineEdit_thx->setText(ui->lineEdit_t1h->text());
    ui->lineEdit_tlx->setText(ui->lineEdit_t1l->text());
    ui->comboBox_txmode_reg->setCurrentIndex(ui->comboBox_t1mode->currentIndex());
}

void Widget::on_lineEdit_xtal_editingFinished()//更改晶振频率后，自动计算最大允许时长
{
    QString xtal_input=ui->lineEdit_xtal->text();
    float xtal=11.0592f;
    float maxTime=1.0f;
    if(isPureFloat(xtal_input))
    {
        xtal=xtal_input.toFloat()*1000000;//将输入晶振值转换为数字型
    }

    switch(ui->comboBox_txmode_toreg->currentIndex())//据不同定时器模式计算最大时长
    {
    case 0://16位手动模式
        maxTime=(float)65536*12/(float)xtal*1000;
        break;
    case 1://8位自动模式
        maxTime=(float)256*12/(float)xtal*1000;
        break;
    }
    char temp[30];
    sprintf(temp,"%.4f",maxTime);
    ui->lineEdit_maxTime->setText(temp);
}

void Widget::on_comboBox_txmode_toreg_currentIndexChanged(int index)
{
    QString xtal_input=ui->lineEdit_xtal->text();
    float xtal=11.0592f;
    float maxTime=1.0f;
    if(isPureFloat(xtal_input))
    {
        xtal=xtal_input.toFloat()*1000000;//将输入晶振值转换为数字型
    }

    switch(index)//据不同定时器模式计算最大时长
    {
    case 0://16位手动模式
        maxTime=(float)65536*12/(float)xtal*1000;
        break;
    case 1://8位自动模式
        maxTime=(float)256*12/(float)xtal*1000;
        break;
    }
    char temp[30];
    sprintf(temp,"%.4f",maxTime);
    ui->lineEdit_maxTime->setText(temp);
}

void Widget::on_pushButton_tot0_clicked()
{
    ui->lineEdit_t0h->setText(ui->lineEdit_corresponding_thx->text());
    ui->lineEdit_t0l->setText(ui->lineEdit_corresponding_tlx->text());
    ui->comboBox_t0mode->setCurrentIndex(ui->comboBox_txmode_toreg->currentIndex());
    TimeCopiedDialog* timeDialog=new TimeCopiedDialog;
    timeDialog->setWindowTitle("提示信息");
    timeDialog->show();
}

void Widget::on_pushButton_tot1_clicked()
{
    ui->lineEdit_t1h->setText(ui->lineEdit_corresponding_thx->text());
    ui->lineEdit_t1l->setText(ui->lineEdit_corresponding_tlx->text());
    ui->comboBox_t1mode->setCurrentIndex(ui->comboBox_txmode_toreg->currentIndex());
    TimeCopiedDialog* timeDialog=new TimeCopiedDialog;
    timeDialog->setWindowTitle("提示信息");
    timeDialog->show();
}

void Widget::on_pushButton_7_clicked()
{
    AboutSoftwareDialog* softwareDialog=new AboutSoftwareDialog;
    softwareDialog->setWindowTitle("关于软件");
    softwareDialog->show();
}

void Widget::on_pushButton_8_clicked()
{
    AboutAuthorDialog* authorDialog=new AboutAuthorDialog;
    authorDialog->setWindowTitle("关于作者");
    authorDialog->show();
}
