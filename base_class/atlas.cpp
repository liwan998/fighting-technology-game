#include "atlas.h"
#include<QString>
#include<QImage>
#include<QDebug>


Atlas::~Atlas()
{
    qDeleteAll(img_list);
    img_list.clear();
}

void Atlas::load_from_file(QString str, int num)
{
    clear();
    for (int i = 0; i < num; ++i) {
        QString file_name = str.arg(i); // str是一个包含文件名模式的字符串，例如 "image_%1.png"
        QImage *img = new QImage(file_name);
        if (img->isNull()) {
            qDebug() << "文件加载失败：" << file_name;
            delete img; // 加载失败时释放内存
        } else {
            img_list.append(img);
        }
    }
}

void Atlas::load_from_file(QString str, int num_w, int num_h, float zoom=1)
{
    clear();
    QImage img(str);
    QTransform transform;
    transform.scale(zoom, zoom); // 将图像缩放到原来的zoom倍
    QImage img_1=img.transformed(transform,Qt::SmoothTransformation);
    for(int i=0;i<num_h;i++){
        for(int j=0;j<num_w;j++){
            QImage temp=img_1.copy(img_1.width()/num_w*j,img_1.height()/num_h*i,
                                     img_1.width()/num_w*(j+1),img_1.height()/num_h*(i+1));
            QImage* dst_img=new QImage(temp);
            if (dst_img->isNull()) {
                qDebug() << "文件加载失败：" << str<<"该图片第"<<i*num_h+j+1;
                delete dst_img; // 加载失败时释放内存
            } else {
                img_list.append(dst_img);
            }
        }
    }
}

void Atlas::clear()
{
    qDeleteAll(img_list); // 使用 qDeleteAll 安全删除所有 QImage 对象
    img_list.clear(); // 清空 QVector
}

int Atlas::get_size()
{
    return img_list.size();
}

void Atlas::add_image(QImage*image)
{
    if (image) {
        img_list.append(image);
    }
}

QImage *Atlas::get_image(int idx)
{
    if(idx<0||idx>img_list.size())
        return nullptr;
    return img_list[idx];
}

