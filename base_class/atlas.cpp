#include "atlas.h"
#include<QString>
#include<QImage>
#include<QDebug>


Atlas::~Atlas()
{
    clear();
}

void Atlas::load_from_file(QString filePath, int num)
{
    clear();
    for (int i = 0; i < num; ++i) {
        QString file_name = filePath.arg(i); // str是一个包含文件名模式的字符串，例如 "image_%1.png"
        QImage *img = new QImage(file_name);
        if (img->isNull()) {
            qDebug() << "文件加载失败：" << file_name;
            delete img; // 加载失败时释放内存
        } else {
            img_list.append(img);
        }
    }
}

void Atlas::load_from_file(QString filePath, int num_w, int num_h, float zoom)
{
    clear();// 清空之前的图像列表

    QImage img(filePath);// 加载大图
    if (img.isNull()) {
        qWarning() << "加载图片失败:" << filePath;
        return;
    }
    // 缩放图像
    QTransform transform;
    transform.scale(zoom, zoom);
    QImage scaledImg = img.transformed(transform, Qt::SmoothTransformation);
    // 检查缩放后的图像尺寸是否满足分割要求
    if (scaledImg.width() % num_w != 0 || scaledImg.height() % num_h != 0) {
        qWarning() << "缩放后的图像尺寸不能被 num_w 或 num_h 整除:" << filePath;
        return;
    }
    // 计算每个小图的宽度和高度
    int subImgWidth = scaledImg.width() / num_w;
    int subImgHeight = scaledImg.height() / num_h;
    // 分割图像
    for (int i = 0; i < num_h; i++) {
        for (int j = 0; j < num_w; j++) {
            // 计算小图的区域
            QRect subImgRect(j * subImgWidth, i * subImgHeight, subImgWidth, subImgHeight);
            // 复制小图
            QImage* subImg = new QImage(scaledImg.copy(subImgRect));
            if (subImg->isNull()) {// 检查小图是否有效
                qWarning() << "复制子图像失败:" << filePath << "在位置 (" << i << "," << j << ")";
                delete subImg; // 释放无效的小图
                continue;
            }
            img_list.append(subImg);// 将小图添加到列表中
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

