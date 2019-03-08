#include <iostream>
#include <exception>
#include <string>
#include <sstream>
using namespace std;

string AskTimeServer() {
    /* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии:
       * нормальный возврат строкового значени€
       * выброс исключени€ system_error
       * выброс другого исключени€ с сообщением.
    */
	//throw system_error(error_code());
	//throw domain_error("hui");
	//throw exception();
	//return "01:01:01";
}

class TimeServer {
public:
    string GetCurrentTime() {
        /* –еализуйте этот метод:
            * если AskTimeServer() вернула значение, запишите его в LastFetchedTime и верните
            * если AskTimeServer() бросила исключение system_error, верните текущее значение
            пол€ LastFetchedTime
            * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
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
    // ћен€€ реализацию функции AskTimeServer, убедитесь, что этот код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}*/
