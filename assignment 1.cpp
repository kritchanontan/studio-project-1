#include <ctype.h>
#include <iostream>
#include <string>


using namespace std;

int NoOfOptr(string expr) {
    int count = 0;
    for (unsigned int i = 0; i < expr.length(); i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == 'x' || expr[i] == '/') {
            count++;
        }

    } return count;
}


char optrIdentify(string expr, int pos) {
    char optr = '+';

    if (expr[pos] == '+') {
        optr = '+';
    }
    else if (expr[pos] == '-') {
        optr = '-';
    }
    else if (expr[pos] == 'x') {
        optr = '*';
    }
    else if (expr[pos] == '/') {
        optr = '/';
    }
    return optr;
}

int OptrPos(string expr, int prev) {
    int pos = 0;
    for (unsigned int i = 1 + prev; i < expr.length(); i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == 'x' || expr[i] == '/') {
            pos = i;
            break;
        }
    }
    return pos;
}

float solver1(string eqn, char op1, int optr1pos) {
    float fresult = 0;
    float result1 = 0;
    float result2 = 0;
    string operand1str = eqn.substr(0, optr1pos);
    float operand1 = stof(operand1str);
    string operand2str = eqn.substr(optr1pos + 1);
    float operand2 = stof(operand2str);

    switch (op1) {
    case '+':
        fresult = operand1 + operand2;
        break;
    case '-':
        fresult = operand1 - operand2;
        break;
    case '*':
        fresult = operand1 * operand2;
        break;
    case '/':
        fresult = operand1 / operand2;
        break;
    }
    return fresult;
}

float solver2(string eqn, char op1, int optr1pos, char op2, int optr2pos) {
    float fresult = 0;
    float result1 = 0;
    float result2 = 0;
    string operand1str = eqn.substr(0, optr1pos);
    float operand1 = stof(operand1str);
    string operand2str = eqn.substr(optr1pos + 1, optr2pos);
    float operand2 = stof(operand2str);
    string operand3str = eqn.substr(optr2pos + 1);
    float operand3 = stof(operand3str);
    if (((op2 == '*') || (op2 == '/')) &&
        ((op1 == '+') || (op1 == '-'))) {
        switch (op2) {
        case '*':
            result1 = operand2 * operand3;
            break;
        case '/':
            result1 = operand2 / operand3;
            break;
        }

        switch (op1) {
        case '+':
            fresult = operand1 + result1;
            break;
        case '-':
            fresult = operand1 - result1;
            break;
        }
        return fresult;
    }
    else {
        switch (op1) {
        case '+':
            result1 = operand1 + operand2;
            break;
        case '-':
            result1 = operand1 - operand2;
            break;
        case '*':
            result1 = operand1 * operand2;
            break;
        case '/':
            result1 = operand1 / operand2;
            break;
        }
        switch (op2) {
        case '+':
            fresult = result1 + operand3;
            break;
        case '-':
            fresult = result1 - operand3;
            break;
        case '*':
            fresult = result1 * operand3;
            break;
        case '/':
            fresult = result1 / operand3;
            break;
        }


        return fresult;
    }
}

int openBPos(string expr) {
    int pos = 0;
    int length = expr.length();
    unsigned int L2 = length;
    for (unsigned int i = 0; unsigned(i) < unsigned(expr.length()); i++) {
        if (expr[i] == '(') {
            pos = i;
            break;
        }
    }
    return pos;
}

int closeBPos(string expr) {
    int pos = 0;
    for (unsigned int i = 0; i < expr.length(); i++) {
        if (expr[i] == ')') {
            pos = i;
            break;
        }
    }
    return pos;
}

bool bValidCheck(string expr, int openBPosi, int closeBPosi) {
    char openBFront = expr[openBPosi - 1];
    char openBBack = expr[openBPosi + 1];
    char closeBFront = expr[closeBPosi - 1];
    char closeBBack = expr[closeBPosi + 1];
    bool opencheck = false;
    bool closecheck = false;
    if ((isdigit(openBFront)) || (isdigit(closeBBack)) ){
        return false;

   }

    return true;
}


int main() {
    int usetimes = 0;
    while (true) {
        int openBPosi = 0;
        int closeBPosi = 0;
        int optr1pos = 0;
        int optr2pos = 0;
        char operator1 = 0;
        char operator2 = 0;
        bool start = false;
        string eqn;
        string beqn, beqn2;

        float result = 0;

        cout << "enter equation: ";
        cin >> eqn;

        if (eqn == "quit") {
            cout << "You have used me " << usetimes << " times";
            break;
        }

        bool bcheck = false;

        int bracketcheck = eqn.find('(');

        if (bracketcheck >= 0) {
            bcheck = true;
        }
        else{
            bcheck = false;
        }
        if (bcheck == true) {
            int openBPosi = openBPos(eqn);
            int closeBPosi = closeBPos(eqn);
            start = true;
            
            
        }
        if (bcheck == false) {
            start = true;
        }


        if (start == true) {
            int count = NoOfOptr(eqn);
            switch (count) {
            case 0:
                if (bcheck == true) {
                    beqn = eqn.erase(0, 1);
                    beqn2 = beqn.erase(beqn.length() - 1, 1);
                    cout << "result: " << beqn << endl << endl;
                    break;
                }
                else {
                    cout << "result: " << eqn << endl << endl;
                    break;
                }

            case 1:
                if (bcheck == true) {
                    beqn = eqn.erase(0, 1);
                    beqn2 = beqn.erase(beqn.length() - 1, 1);
                    eqn = beqn2;
                }
                optr1pos = OptrPos(eqn, 0);
                operator1 = optrIdentify(eqn, optr1pos);
                result = solver1(eqn, operator1, optr1pos);
                
                cout << "result: " << result << endl << endl;
                break;

            case 2:
                if (bcheck == true) {
                    
                    if ((openBPosi == 0) && (closeBPosi == eqn.length() - 1)) {
                        beqn = eqn.erase(0, 1);
                        beqn2 = beqn.erase(beqn.length() - 1, 1);
                        eqn = beqn;
                    }
                    
                   
                }
                optr1pos = OptrPos(eqn, 0);
                operator1 = optrIdentify(eqn, optr1pos);
                optr2pos = OptrPos(eqn, optr1pos + 1);
                operator2 = optrIdentify(eqn, optr2pos);
               
                result = solver2(eqn, operator1, optr1pos, operator2, optr2pos);
                
                cout << "result: " << result << endl << endl;
                break;

            default:
                cout << "error, too much operators" << endl << endl;


            }
            usetimes++;
        }
    }
}
