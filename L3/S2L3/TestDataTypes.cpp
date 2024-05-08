#include "../../../../L2/S2L2/Exception.hpp"
#include <cassert>
#include "Person.hpp"
#include "Student.hpp"
#include "Teacher.hpp"
#include "String.hpp"

void TestDataTypes() {
	String f_name1 = *(new String("Ivan"));
	String m_name1 = *(new String("Ivanovich"));
	String l_name1 = *(new String("Ivanov"));
	String date1 = *(new String("01-01-2000"));
	String universityName1 = *(new String("MEPhI"));

	String f_name2 = *(new String("Alexei"));
	String m_name2 = *(new String("Alexeevich"));
	String l_name2 = *(new String("Alexeev"));
	String date2 = *(new String("01-01-1980"));
	String universityName2 = *(new String("MSU"));

	String f_name3 = *(new String("Sergei"));
	String m_name3 = *(new String("Sergeevich"));
	String l_name3 = *(new String("Sergeev"));
	String date3 = *(new String("01-012000"));

	String f_name4 = *(new String("Anna_"));
	String m_name4 = *(new String("Vitalievna"));
	String l_name4 = *(new String("Sorokina"));

	// Дописать (!)
}