#ifndef ITEMINFO_H
#define ITEMINFO_H


class ItemInfo
{
    Q_OBJECT

public:
    ItemInfo(bool isDir, QString path, qint64 size);
    ~ItemInfo();
private:
    bool isDir;
    QString path;
    qint64 size;
};


#endif // ITEMINFO_H
