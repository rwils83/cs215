#include <iostream>
using namespace std;
class student{
	private:
		string studentFirstName;
		string studentLastName;
		float studentGPA;
	public:
		void setStudentFirstName(string);
		string  getStudentFirstName();
		void setStudentLastName(string);
		string getStudentLastName();
		void setStudentGPA(float);
		float getStudentGPA();
		student();
};
void student:: setStudentFirstName(string name){
	name[0]= toupper(name[0]);
	studentFirstName = name;
};
void student:: setStudentLastName(string name){
	name[0]= toupper(name[0]);
	studentLastName = name;
};
void student:: setStudentGPA(float GPA){
	studentGPA = GPA;};
string student:: getStudentFirstName(){return studentFirstName;};
string student:: getStudentLastName(){return studentLastName;};
float student:: getStudentGPA(){return studentGPA;};
student:: student(){
	studentFirstName = "";
	studentLastName = "";
	studentGPA = 0;}
void displayStudents(student *stud);
int main(){
	string studentFirst = " ";
	string studentLast = " ";
	float studentGPA = 0;
	string voidedVar = " ";
	cout << "Please enter the Student's First Name: " << endl;
	cin >> studentFirst;
	cout << "Please enter the Student's Last Name: " << endl;
	cin >> studentLast;
	cout << "Please enter the Student's GPA: " << endl;
	cin >> studentGPA;
	student student1;
	student1.setStudentFirstName(studentFirst);
	student1.setStudentLastName(studentLast);
	student1.setStudentGPA(studentGPA);
	//cout << getStudentFirstName() << endl;
	//cout <<  getStudentLastName() << endl;
	//cout << getStudentGPA() << endl;
	//cin >> voidedVar;
	displayStudents(&student1);
}

void displayStudents(student *stud){
	cout << "First Name: " << stud->getStudentFirstName()<<endl;
	cout <<  "Last Name: " << stud->getStudentLastName()<<endl;
	cout << "GPA: " << stud->getStudentGPA()<< endl;
}
