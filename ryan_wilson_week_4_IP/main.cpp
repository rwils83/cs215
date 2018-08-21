/*  Created by Ryan J. Wilson
    For CS215/ Intermediate C++ Programming
    Program Description: A simple program to load exams, take the exam, and then score the exam.
    Date of last Modification: August 8, 2018*/

#include <iostream>

#include <string>

#include <stdexcept>

#include <limits>

#include <cctype>

#include <fstream>

using namespace std;
ifstream infile;
class Question
{
private:
	string question, answer;
	int value;
public:

	string getQuestion()
	{return question;}

	int getValue()
	{return value;}

	virtual void setQuestion(string answer, int value)
	{}

	virtual void printOptions()
	{}

	virtual string getAnswer()
	{return answer;}
};

class QuestionTF: public Question
{
private:
	string question;
	string answer;
	int points;
	string options;
public:
	void setQuestion(string theQuestion, int pointValue)
	{
        string theAnswer;
		question = theQuestion;
		points = pointValue;
		options = "true/false";
		getline(infile,theAnswer);
		answer = theAnswer;
	}
	void printOptions()
	{
		cout<<question<<endl;
		}
	string getAnswer()
	{
		return answer;
	}
};

class QuestionMC: public Question
{
private:
	int value, numberOfOptions;
	string question, answer;
	string options[6];
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string line;
		getline(infile,line);//
		numberOfOptions = stoi(line);
		question = theQuestion;
		value = pointValue;
		for (int count = 0; count<numberOfOptions;count++){
			getline(infile,line);
			options[count] = line;
		}
		getline(infile, line);
		answer = line;
	}
	void printOptions()
	{
		char first = 'A';
		cout<<question<<endl;
		for(int count = 0; count<numberOfOptions;count++){
			cout<<first++ <<".  "<<options[count]<<endl;
		}
		cout<<"Answer:  "<< answer << endl;
	}
	string getAnswer()
	{
		return answer;
	}
};

void loadExam(string examName);

void takeExam(string examName);

int gradeExam(double pointsEarned, double pointsPossible, int& menuChoice);

void createTestFile();



int main()

{

    createTestFile();

    int  menuChoice;

    while(menuChoice != 4){

        cout << "\nPlease choose an option 1-4\n";

        cout << "1. Load an Exam" << endl;

        cout << "2. Take an Exam" << endl;

        cout << "3. View your results" << endl;

        cout << "4. Quit" << endl;

        cin>>menuChoice;



        if (!cin){

            cout << "Please Enter a number 1-4\n"<<endl;

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

            switch (menuChoice){

                case 1:

                {string examFile;

                cout<< "What is the name of your exam file?"<<endl;

                cin.ignore();

                getline(cin, examFile);

                loadExam(examFile);}

                    break;

                case 2:
                    {
                    string examFile;
                    cout << "What is the name of the exam file you need to take?"<<endl;
                    cin.ignore();
                    getline(cin, examFile);
                    takeExam(examFile);}
                    break;

                case 3:

                    int examPoints;

                    int yourPoints;

                    cout << "What were your points?"<< endl;

                    cin >> yourPoints;

                    cout << "How Many points was the exam worth?" << endl;

                    cin >> examPoints;

                    gradeExam(yourPoints, examPoints, menuChoice);

                    break;

                case 4:

                break;

                default:



                    break;}





    }return 0;}

    void loadExam(string examName){

        string stringFromFile;

        ifstream infile;

        infile.open(examName);

        if(infile.fail()){

            cout<<"Exam File failed to open"<< endl;}

            else{

                getline(infile, stringFromFile);}

                cout << stringFromFile<<endl;
                cout << "You Successfully Loaded: "<< examName << endl;}

    int gradeExam(double pointsEarned, double pointsPossible, int& menuChoice){

        string backToMenu;

        cout << pointsEarned << endl;

        cout <<pointsPossible<< endl;

        double gradePercentage = pointsEarned/pointsPossible*100;

        cout << "You scored: " <<gradePercentage<<"%"<<endl;

        cout << "Would you like to continue?" <<endl;

        cin.ignore();

        getline(cin, backToMenu);

        backToMenu[0] = toupper(backToMenu[0]);

        cout <<backToMenu<<endl;

        if (backToMenu == "Y" || backToMenu == "Yes"){

            menuChoice = 0;}

        if (backToMenu == "N" || backToMenu == "No"){

            menuChoice = 4;}}
void takeExam(string examName){
    string line, questiontype, questiontxt, typeOfQuestion, questionAnswer, theQuestion, theAnswer;
    string answertxt, optiontxt;
    int numberOfQuestions,questionvalue ,userScore;
    infile.open(examName);
    userScore = 0;
    getline(infile, line);
    numberOfQuestions = stoi(line);
    Question *myQuestions[numberOfQuestions];
    cout << "This quiz has "<< numberOfQuestions << " questions"<<endl;
    //cout << examName <<endl;
    for(int count = 0; count<numberOfQuestions;count++){
		getline(infile,line);
		int npos = line.size();
		int prev_pos = 0;
		int pos = 0;
		while( line[pos]!=' ')
			pos++;
		questiontype = line.substr(prev_pos, pos-prev_pos);
		prev_pos = ++pos;
        questionvalue = stoi(line.substr(prev_pos, npos-prev_pos));

	   if (questiontype == "TF")
		{

			myQuestions[count] = new QuestionTF;
			getline(infile,theQuestion);

			myQuestions[count]->setQuestion(theQuestion,questionvalue);

		}
		if (questiontype =="MC")
		{
			myQuestions[count] =new QuestionMC;
			getline(infile,theQuestion);
			myQuestions[count]->setQuestion(theQuestion,questionvalue);
		}
		for(int count = 0; count<numberOfQuestions;count++)
	{
		//cout <<"Worked to here"<<endl;
		cout << "Question #" << count +1 <<endl;
		myQuestions[count]->printOptions();
		cout << "What is your answer?" << endl;
		getline(cin,  questionAnswer);
		if (questiontype == "TF"){
            theAnswer = myQuestions[count]->getAnswer();
            questionAnswer[0]= toupper(questionAnswer[0]);
            //questionAnswer[0] = true;
            if (questionAnswer[0] == toupper(theAnswer[0])){
                cout << "Good Job" << endl;
                userScore = userScore + questionvalue;
                }
            else {
             cout << "Sorry, that is not correct"<<endl;
             }}
		//cout<<endl;
	}
	getchar();

}}


void createTestFile(){

        ofstream outputFile;

        outputFile.open("test.txt");

        if(!outputFile){

            cout<<"Cannot Open Output file"<<endl;}

        else{
            outputFile << "1\n";
            outputFile << "TF 2\n";
            outputFile << "Programming is fun?\n";
            outputFile << "true\n";
            outputFile << "MC 4\n";
            outputFile << "QUESTION 2\n";
            outputFile << "4\n";
            outputFile << "option 1\n";
            outputFile << "option 2\n";
            outputFile << "option 3\n";
            outputFile << "option 4\n";
            outputFile << "d\n";

    }}

