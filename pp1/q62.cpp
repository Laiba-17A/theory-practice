#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class vehicle{
	private:
		string model;
	public:
		vehicle(string m):model(m){
			
		}
		
	    string getm(){
	    	return model;
		}
};

class funtype:virtual public vehicle{
	private:
		string func;
	public:
		funtype(string m,const string& f):vehicle(m),func(f){
			
		}
	    string getf(){
	    	return func;
		}
};

class engtype:virtual public vehicle{
	private:
		string eng;
	public:
		engtype(string m,const string& e):vehicle(m),eng(e){
			
		}
		string gete(){
	    	return eng;
		}
};

class combine:public funtype,public engtype{
	public:
		combine(string m,string f,string e):vehicle(m),funtype(m,f),engtype(m,e){
		}
		void display(){
			cout<<"model "<<vehicle::getm()<<endl;
			cout<<"function "<<getf()<<endl;
			cout<<"engine "<<gete()<<endl;
		}
};

int main(){
	combine c("2018","car","automatic");
	c.display();
	return 0;
}


