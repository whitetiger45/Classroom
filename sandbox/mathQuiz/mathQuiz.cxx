#include "mathQuiz.hxx"

using namespace std;

auto addition = [](unsigned int x, unsigned int y) -> unsigned int {return x  + y;};

int main()
{
    showTitle();
    Quizzer quizApp;

    getQuestion:
    srand(time(NULL));

    quizApp.setXAndY(rand() % 9999, rand() % 9999);

    quizApp.getProblem();
    unsigned int userResponse;
    cin >> userResponse;

    if(userResponse == addition(quizApp.getX(), quizApp.getY()))
    {
        cout << "\nCorrect!\n";
        goto getQuestion;
    }
    else
        cout << "\nIncorrect...the correct answer is: " <<  addition(quizApp.getX(), quizApp.getY()) << "\n\nGame Over\n\n";

    return 0;
}