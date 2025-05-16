#include <iostream>
#include <stdexcept>
using namespace std;

class car{
	public:
		int speed;
		double regprice;
		string color;
		
		car(int s,double rp,string c):speed(s),regprice(rp),color(c){
		}
		
		virtual double getsaleP(){
			return regprice;
		}
		
};

class truck:public car{
	public:
		int weight;
		
		truck(int s,double rp,string c,int w):car(s,rp,c),weight(w){
		}
		
		double getsaleP() override {
        if (weight > 2000)
            return regprice - (regprice * 0.1);
        else
            return regprice - (regprice * 0.2); 
    }
};

class ford:public car{
	public:
		int yr;
		int mdis;
		
		ford(int s,double rp,string c,int y,int md):car(s,rp,c),yr(y),mdis(md){
		}
		
		double getsaleP() override {
        return regprice - mdis;
    }
};

class sedan:public car{
	public:
		int length;
		
		sedan(int s,double rp,string c,int l):car(s,rp,c),length(l){
		}
		
	double getsaleP() override {
        if (length > 20)
            return regprice - (regprice * 0.05);
        else
            return regprice - (regprice * 0.10);
    }
};

class myownautoshop{
	sedan s;
    ford f;
    car c1;
    ford f2;

public:
    myownautoshop() :
        s(25, 60000, "black", 30),
        f(30, 60000, "black", 2015, 1000),
        c1(25, 70000, "blue"),
		f2(35, 55000, "red", 2018, 1500) {}

	void display(){
		cout<<"sedan: "<<s.getsaleP()<<endl;
		cout<<"ford: "<<f.getsaleP()<<endl;
		cout<<"car: "<<c1.getsaleP()<<endl;
		cout << "Second Ford: " << f2.getsaleP() << endl;
	}
};

int main(){
	myownautoshop a;
	a.display();
	return 0;
}
