#ifndef ATLAS_H
#define ATLAS_H
#include<QVector>
class QString;
class QImage;

class Atlas
{
public:
    Atlas()=default;
    ~Atlas();
    void load_from_file(QString filePath,int num);
    void load_from_file(QString filePath,int num_w,int num_h,float zoom=1);
    void clear();
    int get_size();
    void add_image(QImage*image);
    QImage *get_image(int idx);
private:
    QVector<QImage*> img_list;
};

#endif // ATLAS_H
