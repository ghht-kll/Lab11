#ifndef DATAJSON_H
#define DATAJSON_H

#include <QString>

class DataJson
{
public:
    DataJson();
    QString GetName() const ;
    int GetAge() const;
    QString GetPhoneNumber() const;
    void SetName(const QString name);
    void SetAge(const int age);
    void SetPhoneNumber(const QString phoneNumber);
private:
    QString name;
    int age;
    QString phoneNumber;
};

#endif // DATAJSON_H
