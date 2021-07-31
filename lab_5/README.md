### Практическая работа №5
---
![Schema](https://user-images.githubusercontent.com/43219252/127753932-09b984fe-9eeb-4e7a-886f-d15337011613.PNG)

Создать распределенное приложение, включающее клиентскую и серверную части, взаимодействующие посредством сетевого обмена сообщениями.

Клиентская часть представляет собой GUI приложение, реализующее интерфейс аналогичный работе №3.
	
Серверная часть представляет собой консольное приложение, предназначенное для вычисления корней, значения и представления полинома 2-ой степени в классической и канонической формах на множествах вещественных и рациональных чисел. Для этого следует модифицировать описание класса  `TPolinom`, представив его в виде параметризованного класса с параметром number, который может принимать значения как `int`, так и `TRational`.

Указания:
1. Заголовочный файл `number.h` из приложения исключить.
2. Содержимое файла реализации `polinom.cpp` перенести в заголовочный файл `polinom.h` (шаблон класса `TPolinom`) и исключить из проекта.