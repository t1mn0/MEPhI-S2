#include "Student.hpp"
#include "Teacher.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Deque.hpp"

#include <iostream>

void TestCompatibility() {
	Stack<Student> debtors;
	Queue<Teacher> professors;
	Deque<String> cities;

    Student student_1(String("Ivan"), String("Ivanov"), String("Ivanovich"), String("21-12-2000"), String("MEPhI"), 3);
	Student student_2(String("Dmitrii"), String("Dmitriev"), String("Dmitrievich"), String("12-01-2001"), String("HSE"), 3);
	Student student_3(String("Vasilii"), String("Valisievich"), String("Sidorov"), String("21-12-1999"), String("MSU"), 3);
	Student student_4(String("Petr"), String("Petrov"), String("Petrovich"), String("06-06-2004"), String("MIT"), 3);
	
	debtors.push(student_1);
	debtors.push(student_2);
	debtors.push(student_3);
	debtors.push(student_4);
	
	std::cout << debtors.top().getFullName().c_str() << '\n';

	std::cout << debtors.pop().getFullName().c_str() << '\n';

	std::cout << debtors.pop().getFullName().c_str() << '\n';

	Teacher teacher_1(String("Maria"), String("Marieva"), String("Ivanovna"), String("15-03-1982"), String("SPbU"), 10);
	Teacher teacher_2(String("Anna"), String("Anatolievna"), String("Sergeevna"), String("25-07-1980"), String("BMSTU"), 12);
	Teacher teacher_3(String("Alexander"), String("Alexandrov"), String("Alexeevich"), String("02-02-1975"), String("MGU"), 20);
	Teacher teacher_4(String("Olga"), String("Olgova"), String("Andreevna"), String("09-11-1983"), String("ITMO"), 9);
	Teacher teacher_5(String("Nikita"), String("Nikitin"), String("Mikhailovich"), String("30-08-1985"), String("UrFU"), 8);
	Teacher teacher_6(String("Elena"), String("Elenova"), String("Petrovna"), String("14-05-1978"), String("TSU"), 15);
	Teacher teacher_7(String("Sergey"), String("Sergeev"), String("Sergeevich"), String("07-04-1976"), String("NSU"), 18);
	Teacher teacher_8(String("Irina"), String("Irinova"), String("Ivanovna"), String("18-10-1981"), String("KFU"), 10);
	Teacher teacher_9(String("Maxim"), String("Maximov"), String("Maximovich"), String("23-01-1979"), String("HSE"), 13);
	Teacher teacher_10(String("Tatiana"), String("Tatianova"), String("Alexandrovna"), String("05-02-1977"), String("SPbPU"), 17);
	Teacher teacher_11(String("Alexei"), String("Alexeev"), String("Nikitovich"), String("16-06-1975"), String("RUDN"), 22);
	Teacher teacher_12(String("Natalia"), String("Natalieva"), String("Vladimirovna"), String("12-12-1980"), String("MSU"), 14);
	Teacher teacher_13(String("Dmitriy"), String("Dmitriev"), String("Dmitrievich"), String("17-07-1984"), String("MIPT"), 7);
	Teacher teacher_14(String("Yulia"), String("Yulieva"), String("Sergeevna"), String("28-09-1985"), String("SMTU"), 8);
	Teacher teacher_15(String("Anton"), String("Antonov"), String("Antonovich"), String("19-03-1982"), String("VGU"), 11);
	Teacher teacher_16(String("Ksenia"), String("Ksenieva"), String("Andreevna"), String("22-08-1983"), String("MAI"), 9);
	Teacher teacher_17(String("Boris"), String("Borisov"), String("Borisovich"), String("11-11-1976"), String("MSLU"), 21);
	Teacher teacher_18(String("Svetlana"), String("Svetlanova"), String("Igorevna"), String("06-10-1980"), String("HSE"), 14);
	Teacher teacher_19(String("Mikhail"), String("Mikhailov"), String("Mikhailovich"), String("03-03-1978"), String("MTU"), 16);
	Teacher teacher_20(String("Ludmila"), String("Ludmilova"), String("Nikolaevna"), String("29-02-1980"), String("SPbU"), 14);
	
	professors.push(teacher_1);
	professors.push(teacher_2);
	professors.push(teacher_3);
	professors.push(teacher_4);
	professors.push(teacher_5);
	professors.push(teacher_6);
	professors.push(teacher_7);
	professors.push(teacher_8);
	professors.push(teacher_9);
	professors.push(teacher_10);
	professors.push(teacher_11);
	professors.push(teacher_12);
	professors.push(teacher_13);
	professors.push(teacher_14);
	professors.push(teacher_15);
	professors.push(teacher_16);
	professors.push(teacher_17);
	professors.push(teacher_18);
	professors.push(teacher_19);
	professors.push(teacher_20);

	std::cout << professors.pop().getFullName().c_str() << '\n';
	std::cout << professors.pop().getFullName().c_str() << '\n';
	std::cout << professors.pop().getFullName().c_str() << '\n';

	String string_1("Moscow");
	String string_2("Saint Petersburg");
	String string_3("Novosibirsk");
	String string_4("Ekaterinburg");
	String string_5("Nizhny Novgorod");
	String string_6("Kazan");
	String string_7("Chelyabinsk");
	String string_8("Omsk");
	String string_9("Samara");
	String string_10("Rostov-on-Don");

	cities.push_front(string_5);
	cities.push_front(string_1);
	cities.push_front(string_6);
	cities.push_front(string_4);
	cities.push_front(string_7);
	cities.push_back(string_3);
	cities.push_back(string_8);
	cities.push_back(string_10);
	cities.push_back(string_2);
	cities.push_back(string_9);

	std::cout << '\n';

	std::cout << cities.pop_front().c_str() << '\n';
	std::cout << cities.pop_front().c_str() << '\n';
	std::cout << cities.pop_back().c_str() << '\n';
	std::cout << cities.pop_back().c_str() << '\n';
	std::cout << cities.pop_back().c_str() << '\n';
}