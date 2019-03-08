#include <iostream>
#include <exception>
#include <string>
#include <sstream>
using namespace std;

string AskTimeServer() {
    /* ��� ������������ ������������ ���� ���, ����������� ��������� ��������� ���� ������:
       * ���������� ������� ���������� ��������
       * ������ ���������� system_error
       * ������ ������� ���������� � ����������.
    */
	//throw system_error(error_code());
	//throw domain_error("hui");
	//throw exception();
	//return "01:01:01";
}

class TimeServer {
public:
    string GetCurrentTime() {
        /* ���������� ���� �����:
            * ���� AskTimeServer() ������� ��������, �������� ��� � LastFetchedTime � �������
            * ���� AskTimeServer() ������� ���������� system_error, ������� ������� ��������
            ���� LastFetchedTime
            * ���� AskTimeServer() ������� ������ ����������, ���������� ��� ������.
        */
    	try {
    		LastFetchedTime = AskTimeServer();
    		return LastFetchedTime;
    	}
    	catch (system_error& e) {
    			return LastFetchedTime;
    	}
    	catch (exception& e) {
    		throw runtime_error(e.what());
    	}
    }

private:
    string LastFetchedTime = "00:00:00";
};

/*int main() {
    // ����� ���������� ������� AskTimeServer, ���������, ��� ���� ��� �������� ���������
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}*/
