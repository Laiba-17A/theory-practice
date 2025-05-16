#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){

	string name,line;
	int ch;
	double p,gpa;
	ofstream out("warning.txt");
	if(!out){
		cout<<"error while opening file for writing";
		return 1;
	}
	ifstream in("data.txt");
	if(!in){
		cout<<"error while opening file for reading";
		return 1;
	}
//	while(!in.eof()){
//		in>>name;
//		in>>ch;
//		in>>p;
    while(in>>name>>ch>>p){
		gpa=p/ch;
		if((ch<30 && gpa<1.5) || ((ch>=30 && ch<60) && gpa<1.75) || (ch>=60 && gpa<2)){
			out<<name<<" "<<gpa<<"\n";
		}
	}
	in.close();
	out.close();
}