#include "Automata.h"

bool isLetter(char ch){
    return ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'));
}

MyString reversPolishNotation(const MyString& str){
    //from tutorialspoint.com
    MyString result;
    MyVector<char> operators;
    size_t len = str.length();
    for(int i=0;i<len;i++){
        char temp=str[i];
        if(isLetter(temp)){
            result+=temp;
        }else if(temp=='('){
            operators.push('(');
        }else if(temp==')'){
            while (! (operators.isEmpty()&&operators.back()!='(')){
                result+=operators.back();
                operators.remove(operators.getSize()-1);
                //operators.popBack();
                //????
            }
            if(!(operators.isEmpty()&& operators.back()=='(')){

                operators.remove(operators.getSize()-1);
                //operators.popBack();
            }
        }  else if (temp == '*') {
            result += '*';
        } else if (temp == '+') {
            while (!(operators.isEmpty() && (operators.back() == '.' || operators.back() == '+'))) {
                result += operators.back();
                //operators.popBack();
                operators.remove(operators.getSize()-1);
            }
            operators.push('+');
        }

        if(i!= len-1){
            char ch
        }

    }

}


Automata::Automata(): Automata(1) {}

Automata::Automata(size_t statesCount) {

    for(int i=0;i<statesCount;i++){
        State st;
        states.push(st);
    }
}

Automata::Automata(const MyString &str) {
    *this=build(str);
}
Automata& Automata::addState() {
    State st;
    states.push(st);
}

Automata &Automata::addTransition(size_t from, size_t dest, char key) {
    states[from].addTransition(dest,key);
}

Automata& Automata::addLetter(char ch) {
    alphabet.push(ch);
}

Automata Automata::build(const MyString &str) {
    size_t len = str.length();

    for(int i=0;i<len;i++){
        char temp = str[i];
        switch (temp) {
            case '*':
                break;
            case '+':
                break;
            case '/':
                break;
            default:

        }
    }
}

void Automata::makeTotal() {

}

void Automata::makeDeterminized() {

}

void Automata::makeMinimal() {

}

MyString Automata::getRegularExpression() const {

}

Automata U(const Automata& lhs, const Automata& rhs){

}


Automata operator/(const Automata& lhs, const Automata& rhs){

}
Automata operator*(const Automata& source){

}