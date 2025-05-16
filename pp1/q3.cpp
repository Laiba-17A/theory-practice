#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class file{
	public:
		double size;
		string loc,crdate,modDate;
		
		virtual void open(){
			cout<<"file is open"<<endl;
			
		}
		
	    virtual void print()=0;
	    virtual ~File() {}
};

class pdf:public file{
	public:
		void print(){
			cout<<"pdf file"<<endl;
		}
};

class asc:public file{
	public:
		void print(){
			cout<<"ASCII file"<<endl;
		}
};

class pS:public file{
	public:
		void print(){
			cout<<"pS file"<<endl;
		}
};

int main(){
	file *f1,*f2,*f3;
	pdf pf;
	asc a;
	pS p;
	f1=&pf;
	f2=&a;
	f3=&p;
	f1->print();
	f2->print();
	f3->print();
	return 0;
}