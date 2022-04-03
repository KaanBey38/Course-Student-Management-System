#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class StudentNode
{
private:
	string id, name;
	StudentNode* next;

public:

	StudentNode(string id, string name) :id{ id }, name{ name }, next{ NULL }{};

	string getName() { return name; }
	string getId() { return id; }
	StudentNode* getNext() { return next; }
	void setNext(StudentNode* ptr) { next = ptr; }

};


class CourseNode
{
private:

	CourseNode* next;
	StudentNode* stHead;

public:
	string code;
	CourseNode(string name) :stHead{ NULL }, next{ NULL }, code{ name } {};

	CourseNode* getNext() { return next; }
	void setNext(CourseNode* ptr) { next = ptr; }

	void addStudent(StudentNode* student)
	{
		if (stHead == NULL)
		{
			stHead = student;
			return;
		}

		//StudentNode* curr = new StudentNode();
		StudentNode* curr = stHead;


		while (curr->getNext() != NULL)
			curr = (curr->getNext());

		curr->setNext(student);

	}

	bool print()
	{

		if (this != NULL)
		{
			cout << code << endl;

			if (stHead == NULL)
			{
				cout << "Course is empty" << endl;
				return false;
			}

			StudentNode* curr = stHead;
			int i = 1;
			while (curr != NULL)
			{
				cout << i << ".";
				cout << curr->getName() << " " << curr->getId() << endl;
				curr = (curr->getNext());
				i++;
			}

			cout << endl;
			//cout << "End of " << code << endl << endl;
			return true;
		}
		return false;
	}

	void deleteStudent(int studentCode)
	{
		StudentNode* curr = stHead;
		StudentNode* prev = NULL;
		if (studentCode == 1)
		{
			stHead = curr->getNext();

			delete curr;
			return;
		}

		for (int i = 1; i < studentCode; i++)
		{
			prev = curr;
			curr = curr->getNext();
		}
		prev->setNext(curr->getNext());

		delete curr;
	}

	bool searchStudent(string name)
	{
		StudentNode* curr = stHead;

		if (stHead == NULL)
			return false;

		while (curr != NULL)
		{
			if (curr->getName() == name)
				return true;

			curr = curr->getNext();
		}


		return false;


	}

	void StudentWrite(fstream& text)
	{
		StudentNode* curr = stHead;

		if (stHead == NULL)
			return;

		while (curr != NULL)
		{
			text << curr->getName() << " " << curr->getId();
			text << endl;
			curr = curr->getNext();
		}
		text << "END" << endl;
	}

	void deleteStudentMemory()
	{
		StudentNode* curr = stHead;
		StudentNode* prev = NULL;

		while (curr != NULL)
		{
			prev = curr;
			curr = curr->getNext();
			delete prev;
		}
	}
};

class List {

private:
	CourseNode* cHead;
public:

	List() :cHead{ NULL } {};

	void addCourse(string name)
	{
		if (cHead == NULL)
		{
			cHead = new CourseNode(name);
			return;

		}

		CourseNode* curr = cHead;


		while (curr->getNext() != NULL)
			curr = (curr->getNext());

		CourseNode* temp = new CourseNode(name);

		curr->setNext(temp);

	}

	void addStudent(string code, StudentNode* student)
	{
		if (cHead == NULL)
			return;

		CourseNode* curr = cHead;
		while (curr != NULL)
		{
			if (curr->code == code)
				break;
			curr = curr->getNext();
		}

		curr->addStudent(student);
	}


	void print()
	{
		if (cHead == NULL)
		{
			//cout << "List is empty"<<endl;
			return;
		}


		CourseNode* curr = cHead;

		while (curr != NULL)
		{

			curr->print();
			curr = curr->getNext();
		}



	}

	void printCourses()
	{
		if (cHead == NULL)
		{
			cout << "List empty";
			return;
		}

		CourseNode* curr = cHead;
		int i = 1;
		while (curr != NULL)
		{
			cout << i << "." << curr->code << endl;
			curr = curr->getNext();
			i++;
		}

	}


	bool printOneCourse(int code)
	{
		CourseNode* curr = cHead;
		int i = 1;

		while (curr != NULL)
		{
			if (i == code)
				break;

			i++;
			curr = curr->getNext();
		}

		return(curr->print());

	}


	void deleteCourse(string code)
	{
		CourseNode* curr = cHead;
		CourseNode* prev = NULL;

		int place = stoi(code);

		if (curr == NULL)
			return;
		if (place == 1)
		{
			cHead = curr->getNext();

			curr->deleteStudentMemory();
			delete curr;///memory leak 
			return;
		}

		for (int i = 1; i < place; i++)
		{
			prev = curr;
			curr = curr->getNext();
		}

		prev->setNext(curr->getNext());


		///memory leak 
		curr->deleteStudentMemory();

		delete curr;


	}

	void deleteStudent(int code, int studentCode)
	{
		CourseNode* curr = cHead;
		int i = 1;

		while (curr != NULL)
		{
			if (i == code)
				break;

			i++;
			curr = curr->getNext();
		}

		curr->deleteStudent(studentCode);


	}

	string searchStudent(string name)
	{
		CourseNode* curr = cHead;
		string courseName{};

		if (cHead == NULL)
			return 0;

		while (curr != NULL)
		{
			if (curr->searchStudent(name))
			{
				courseName = curr->code;
				return courseName;
			}

			curr = curr->getNext();
		}

		return "No courses";
	}

	void deleteLastCourse()
	{
		CourseNode* curr = cHead;
		CourseNode* prev = NULL;
		while (curr->getNext() != NULL)
		{
			prev = curr;
			curr = curr->getNext();
		}

		prev->setNext(NULL);
		delete curr;
	}


	void save()
	{
		ofstream{ "list.txt" };
		fstream text;
		text.open("list.txt");
		CourseNode* curr = cHead;

		while (curr != NULL)
		{
			text << curr->code;
			text << endl;

			curr->StudentWrite(text);

			curr = curr->getNext();
		}
		text.close();
	}
};


int main()
{
	List list;
	int choice{};

	fstream text;
	string course, name, id;

	text.open("list1.txt");

	while (!text.eof())
	{
		text >> course;
		list.addCourse(course);

		for (int i = 0; i < 3; i++)
		{
			text >> name;
			if (name == "END")
				break;
			text >> id;
			StudentNode* temp = new StudentNode(id, name);
			list.addStudent(course, temp);
		}


	}

	cout << "1. Display courses" << endl
		<< "2. Add new course" << endl
		<< "3. Delete existing course" << endl
		<< "4. Enroll student" << endl
		<< "5. Unenrol student" << endl
		<< "6. Search student" << endl
		<< "7. Save and exit" << endl << endl;

	do {
		cout << "Your choice:";
		cin >> choice;

		if (choice == 1)
			list.print();

		else if (choice == 2)
		{
			string temp_name;
			cout << "Enter course name: ";
			cin >> temp_name;

			list.addCourse(temp_name);
		}

		else if (choice == 3)//////////////////////////memory leak 
		{
			string name;
			cout << "Avabile courses:" << endl;
			list.printCourses();
			cout << "Which course:";
			cin >> name;
			list.deleteCourse(name);

		}

		else if (choice == 4)
		{
			string code, id, name;

			cout << "Enter course code, student id and name:";
			cin >> code >> id >> name;
			StudentNode* temp = new StudentNode(id, name);
			list.addStudent(code, temp);


		}

		else if (choice == 5)
		{
			int code{}, studentCode{};
			bool flag;
			cout << "Avabile courses:" << endl;
			list.printCourses();
			cout << "Which Course:";
			cin >> code;
			cout << "Avabile students:" << endl;
			flag = list.printOneCourse(code);
			if (flag)
			{
				cout << "Which Student:";
				cin >> studentCode;
				list.deleteStudent(code, studentCode);
			}



		}


		else if (choice == 6)
		{
			string name;
			string course;
			cout << "Enter student name:";
			cin >> name;
			course = list.searchStudent(name);
			cout << name << " is enrolled to " << course << endl;


		}


		else if (choice == 7)
		{
			list.save();
		}

		cout << endl;

	} while (choice != 7);


	text.close();

	return 0;
}