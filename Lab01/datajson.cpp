#include "datajson.h"

DataJson::DataJson()
{
    this->name = nullptr;
    this->age = 0;
    this->phoneNumber = nullptr;
}

QString DataJson::GetName() const
{
    return this->name;
}

int DataJson::GetAge() const
{
    return this->age;
}

QString DataJson::GetPhoneNumber() const
{
    return this->phoneNumber;
}

void DataJson::SetName(const QString name)
{
    this->name = name;
}

void DataJson::SetAge(const int age)
{
    this->age = age;
}

void DataJson::SetPhoneNumber(const QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}
