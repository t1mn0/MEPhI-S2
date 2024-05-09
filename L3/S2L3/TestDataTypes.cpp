#include "../../../../L2/S2L2/Exception.hpp"
#include <cassert>
#include "Student.hpp"
#include "Teacher.hpp"

int PersonID::nextID = 0;

void TestDataTypes() {
    // Test struct "Person"
    String f_name1("Ivan");
    String m_name1("Ivanovich");
    String l_name1("Ivanov");
    String bdate1("01-01-2000");
    
    Person person1(f_name1, m_name1, l_name1, bdate1);
    assert(person1.getFirstName() == f_name1);
    assert(person1.getMiddleName() == m_name1);
    assert(person1.getLastName() == l_name1);
    assert(person1.getBirthDate() == bdate1);
    
    String f_name2("Ivan10");
    try {
        Person person2(f_name2, m_name1, l_name1, bdate1);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String m_name2("Ivanovich_!");
    try {
        Person person3(f_name1, m_name2, l_name1, bdate1);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String l_name2("R3_D3");
    try {
        Person person4(f_name1, m_name1, l_name2, bdate1);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String f_name3("T0lya");
    try {
        Person person5(f_name3, m_name1, l_name1, bdate1);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String l_name3("Titov.");
    try {
        Person person6(f_name1, m_name1, l_name3, bdate1);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String bdate2("01-01-1800");
    try {
        Person person7(f_name1, m_name1, l_name1, bdate2);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String bdate3("0101-1800");
    try {
        Person person8(f_name1, m_name1, l_name1, bdate3);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    String bdate4("29-02-2023");
    try {
        Person person7(f_name1, m_name1, l_name1, bdate4);
        assert(false);
    }
    catch (const Exception& e) {
        assert(true);
    }

    // Test struct "Student"
    String f_name10("Anna");
    String m_name10("Viktorovna");
    String l_name10("Sorokina");
    String bdate10("25-06-2004");
    String universityName10("MSU");

    Student student1(f_name10, m_name10, l_name10, bdate10, universityName10, 2);
    assert(student1.getFirstName() == f_name10);
    assert(student1.getMiddleName() == m_name10);
    assert(student1.getLastName() == l_name10);
    assert(student1.getBirthDate() == bdate10);

    // Test struct "Teacher"
    String f_name11("Alexander");
    String m_name11("Andreevich");
    String l_name11("H");
    String bdate11("20-02-1998");
    String universityName11("MEPhI");

    Teacher teacher1(f_name11, m_name11, l_name11, bdate11, universityName11, 20);
    assert(teacher1.getFirstName() == f_name11);
    assert(teacher1.getMiddleName() == m_name11);
    assert(teacher1.getLastName() == l_name11);
    assert(teacher1.getBirthDate() == bdate11);
}
