#include <iostream>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;
    do
    {
        cout << "How many questions do you want to solve? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions>10);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel >4);

    return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType;
    do
    {
        cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix : ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;

}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PLayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[10];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

int SimpleCalculator(int Num1, int Num2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Num1 + Num2;
    case enOperationType::Sub:
        return Num1 - Num2;
    case enOperationType::Mul:
        return Num1 * Num2;
    case enOperationType::Div:
        return Num1 / Num2;
    default:
        return Num1 + Num2;
    }
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel , enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    }

    return Question;

}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_________" << endl;
}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult)
        system("color 2F");
    else
        system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz &Quizz , short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PLayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-(\n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-) \n";

    }
    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz &Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PLayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool isPass)
{
    SetScreenColor(isPass);

    if (isPass)
        return "PASS :-)";
    else
        return "FAIL :-(";
}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionLevelText[4] = { "Easy" , "Med" , "Hard" , "Mix" };
    return arrQuestionLevelText[QuestionsLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "___________________________\n\n";
    cout << "Final Result is : " << GetFinalResultText(Quizz.isPass);
    cout << "\n__________________________\n\n";

    cout << "Number of questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions level     : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType              : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of right answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of wrong answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "___________________________\n";

}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again? Y/N ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}
