### Практическая работа №3
---
![Схема](https://user-images.githubusercontent.com/43219252/127753706-2af0bac1-2e90-4a45-b091-e78fc4272e12.PNG)

Создать GUI приложение, реализующее функции перечисленные в описании работы №1 (вычисление корней, вычисление значения, представление полинома в классической и канонических формах) на множестве рациональных чисел. Приложение должно включать основной модуль, модуль `interface`, модуль `polinom` и модуль `rational`.

Основной модуль main.cpp GUI приложения может иметь вид:

```c++
#include <QApplication>
#include "interface.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TInterface interface;
    interface.show();
    return a.exec();
}
```
