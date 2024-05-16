#include "Student.hpp"
#include "Teacher.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Deque.hpp"

#include <cassert>
#include <iostream>

int reduceFunc1(const int& accumulator, const Student& student) {
	return accumulator + student.getYearsOfStudy();
}

bool whereFunc1(const Teacher& t) {
	return t.getYearsOfWork() >= 12;
}

void TestCompatibility() {
	Stack<Student> debtors;
	Queue<Teacher> professors;
	Deque<String> cities;

    Student student_1(String("Ivan"), String("Ivanov"), String("Ivanovich"), String("21-12-2000"), String("MEPhI"), 3);
	Student student_2(String("Dmitrii"), String("Dmitriev"), String("Dmitrievich"), String("12-01-2001"), String("HSE"), 4);
	Student student_3(String("Vasilii"), String("Valisievich"), String("Sidorov"), String("21-12-1999"), String("MSU"), 3);
	Student student_4(String("Petr"), String("Petrov"), String("Petrovich"), String("06-06-2004"), String("MIT"), 2);
	Student student_5(String("Anastasiya"), String("Starova"), String("Olegovna"), String("25-09-2006"), String("MEPhI"), 1);
	
	String name_student_1 = student_1.getFullName();
	String name_student_2 = student_2.getFullName();
	String name_student_3 = student_3.getFullName();
	String name_student_4 = student_4.getFullName();
	String name_student_5 = student_5.getFullName();

	int id_student_1 = student_1.getID();
	int id_student_2 = student_1.getID();
	int id_student_3 = student_1.getID();
	int id_student_4 = student_1.getID();
	int id_student_5 = student_1.getID();

	debtors.push(student_1);
	debtors.push(student_2);
	debtors.push(student_3);
	debtors.push(student_4);
	debtors.push(student_5);
	
	assert(debtors.pop().getFullName() == name_student_5);
	assert(debtors.top().getID() == student_4.getID());
	assert(debtors.pop().getFullName() == name_student_4);
	assert(debtors.top().getID() == student_3.getID());
	assert(debtors.pop().getFullName() == name_student_3);
	assert(debtors.top().getID() == student_2.getID());
	assert(debtors.pop().getFullName() == name_student_2);
	assert(debtors.top().getID() == student_1.getID());
	assert(debtors.pop().getFullName() == name_student_1);

	try {
		debtors.pop();
		assert(false);
	}
	catch (Exception& e) {
		assert(true);
	}

	debtors.push(student_1);
	debtors.push(student_2);
	debtors.push(student_3);
	debtors.push(student_4);
	debtors.push(student_5);

	assert(debtors.reduce(0, reduceFunc1) == 13);

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

	assert(professors.pop().getFullName() == teacher_1.getFullName());
	assert(professors.pop().getFullName() == teacher_2.getFullName());
	assert(professors.pop().getFullName() == teacher_3.getFullName());
	assert(professors.pop().getFullName() == teacher_4.getFullName());
	assert(professors.pop().getFullName() == teacher_5.getFullName());
	assert(professors.pop().getFullName() == teacher_6.getFullName());
	assert(professors.pop().getFullName() == teacher_7.getFullName());
	assert(professors.pop().getFullName() == teacher_8.getFullName());
	assert(professors.pop().getFullName() == teacher_9.getFullName());
	assert(professors.pop().getFullName() == teacher_10.getFullName());

	try {
		professors.pop();
		assert(false);
	}
	catch (Exception& e) {
		assert(true);
	}

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

	Queue<Teacher> new_q = professors.where(&whereFunc1);
	int s = new_q.size();
	for (int i = 0; i < s; ++i) {
		assert(new_q.pop().getYearsOfWork() >= 12);
	}

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

	assert(cities.pop_front() == String("Chelyabinsk"));
	assert(cities.pop_front() == String("Ekaterinburg"));
	assert(cities.pop_back() == String("Samara"));
	assert(cities.pop_back() == String("Saint Petersburg"));
	assert(cities.pop_back() == String("Rostov-on-Don"));
}