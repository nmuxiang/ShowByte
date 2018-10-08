#include <iostream>
#include <sstream>
#include <cstring>

#include <typeinfo>
#include <bitset>
#ifdef __GNUC__
#include <cxxabi.h>
#endif // __GNUC__

using namespace std;

struct typedata
{
	const void * p;
	unsigned int d;

};

template<class T>
void showbyte(const T & typecharacter) {

	int len = sizeof(typecharacter);
	const char * real_name;
#	if defined(__GNUC__)
        real_name=abi::__cxa_demangle(typeid(typecharacter).name(),nullptr, nullptr, nullptr);
#    else
        real_name=typeid(typecharacter).name();
#    endif
	cout <<"The type of " << typecharacter <<" is " << real_name <<endl;
	cout <<"Use " <<len << " bytes" << endl;
	unsigned char * p;
	p = (unsigned char *)&typecharacter;
	for (int i = 0; i < len; i++) {
		typedata bytedata;
		bytedata.p = static_cast<const void *>(p + i);
        bytedata.d=*(p+i);
		cout <<hex<<bytedata.d << " in address " << bytedata.p << " The binary is " << bitset<8>(bytedata.d)<<endl;
	}
    cout << "======================================================================" << endl;
}
template <class T>
T convert(const char * &p){
    stringstream sstream;
    T output;
    sstream<<p;
    sstream>>output;
    sstream.clear();
    return output;
}

char * inputdata(){
    cout << "Please input character: " << endl;
    string acharacter;
    cin >> acharacter;

    char *data=new char;
    strcpy_s(data,acharacter.size()+1,acharacter.c_str());
    return data;
}

void inputtype(const char * & pcharacter) {
    cout << "Please choose a type you want: " << endl;
    cout << "1.  character		2.int		3.float(double)		4.exit" << endl;
    char choose;
    cin >> choose;
    cout << "================================output================================" << endl;
    switch (choose)
    {
    case '1':
        showbyte(convert<char>(pcharacter));
        break;
    case '2':
        showbyte(convert<int>(pcharacter));
        break;
    case '3':
        showbyte(convert<float>(pcharacter));
        break;
    case '4':
        exit(0);
    default:
        cout <<"Input choose is not right! Please check and input again. " <<endl;
        break;
    }
    delete pcharacter;
}

void process(){
    while(true){
        const char * p;
        p=inputdata();
        inputtype(p);
    }
    }

int main() {
	process();
	system("pause");
	return 0;
}
