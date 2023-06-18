#include "Automata.h"

bool isLetter(char ch){
    return ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'));
}

bool isNumber(char ch){
    return (ch>='0'&& ch<='9');
}

MyString reversPolishNotation(const MyString& str){


    MyString result;
    MyVector<char> operators;
    size_t len = str.length();

    for(int i=0;i<len;i++){
        char temp =  str[i];

        if(isLetter(temp)||isNumber(temp)){
            result+=temp;
        }else if(temp =='('){
            operators.push(temp);
        }else if(temp==')'){
            while (operators.back()!='('){
                result+=operators.back();
                operators.popBack();
            }
        }else if(temp=='*'){
            result+='*';
        }else if(temp=='+'){
            while (!operators.isEmpty()&&(operators.back()=='.'||operators.back()=='+')){
                result+=operators.back();
                operators.popBack();
            }
            operators.push(temp);
        }
        if(i != str.length()-1){
            char next=str[i+1];
            if ((isLetter(temp) && (isLetter(next) || next == '(')) || (temp == ')' &&
            (isLetter(next) || next == '(')) ||( temp == '*' && (next == '(' || isLetter(next))))
            {
                while (!operators.isEmpty() && (operators.back() == '.' || operators.back() == '*'))
                {
                    result += operators.back();
                    operators.popBack();
                }

                operators.push('.');
            }
        }


    }

//    for(int i=0;i<len;i++){
//        char temp=str[i];
//        if(isLetter(temp)){
//            result+=temp;
//        }else if(temp=='('){
//            operators.push('(');
//        }else if(temp==')'){
//            while (!operators.isEmpty() && operators.back()!='('){
//                result+=operators.back();
//                operators.popBack();
//            }
//            if(!operators.isEmpty()&& operators.back()=='('){
//
//                operators.popBack();
//            }
//        }  else if (temp == '*') {
//            result += '*';
//
//        } else if (temp == '+') {
//            while (operators.isEmpty() && (operators.back() == '.' || operators.back() == '+')) {
//                result += operators.back();
//                operators.popBack();
//            }
//            operators.push('+');
//        }
//
//        if(i!= len-1){
//            char beforeLast = str[i];
//            char last = str[i+1];
//
//            std::cout<<last<<" "<<temp<<std::endl;
//
//            if ((isLetter(last) && (isLetter(beforeLast) || beforeLast == '('))
//            || (last == ')' && (isLetter(beforeLast) || beforeLast == '('))
//            || (last == '*' && (beforeLast == '(' || isLetter(beforeLast)))){
//                while (!operators.isEmpty()&&
//                (operators.back()=='.'||operators.back()=='*')){
//                    result+=operators.back();
//                    operators.popBack();
//                }
//                operators.push('.');
//            }
//        }
//
//    }
    while (! operators.isEmpty()){
        result+= operators.back();
        operators.popBack();
    }

    return result;
}


Automata::Automata(): Automata(1) {}

Automata::Automata(size_t statesCount) {
    startState=0;

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
    return *this;
}

Automata &Automata::addTransition(size_t from, size_t dest, char key) {
    states[from].addTransition(dest,key);
    alphabet.push(key);
    return *this;
}

Automata& Automata::addLetter(char ch) {
    alphabet.push(ch);
    return *this;
}

Automata &Automata::makeLastStateStarting() {
    size_t index = states.getSize();

    states[index]=states[startState];
    startState=states.getSize()-1;

    return *this;

}

void Automata::makeStateFinal(size_t ind) {
    finalStates.push(ind);
}

Automata Automata::build(const MyString &str)const{
    MyString rpn= reversPolishNotation(str);

    size_t len = rpn.length();
    MyVector<Automata> allAutomats;
    //using the building configs;

    for(int i=0;i<len;i++){
        char temp = rpn[i];

        if(isLetter(temp)|| isNumber(temp)){
            allAutomats.push(buildSmallAutomata(temp));
        }else if(temp=='*'){
            Automata autToReturn = allAutomats.back();
            allAutomats.popBack();
            allAutomats.push((KleeneStar(autToReturn)));
        }else if(temp=='+'){
            Automata lhs = allAutomats.back();
            allAutomats.popBack();
            Automata rhs = allAutomats.back();
            allAutomats.popBack();
            allAutomats.push(Union(lhs,rhs));

        }else if(temp=='.'){
            Automata rhs = allAutomats.back();
            allAutomats.popBack();
            Automata lhs = allAutomats.back();
            allAutomats.popBack();
            allAutomats.push(Concat(lhs,rhs));

        }
    }

    return allAutomats.back();
}

Automata Automata::buildSmallAutomata(char ch) const {
    Automata temp;

    if(ch == '$'){
        temp.makeStateFinal(0);
        return temp;
    }

    temp.addLetter(ch);
    temp.addState();
    temp.addTransition(0,1,ch);
    temp.makeStateFinal(1);
    //temp.debug();
    //std::cout<<"_________________________"<<std::endl;
    return temp;
}

void Automata::copyTransitions(int lhs, int rhs) {
    int limit= states[rhs].getCountOfTransitions();

    for(int i=0;i<limit;i++){
        states[lhs].addTransition(states[rhs][i]);
    }
}

MySet<int> Automata::getTransitions(int start, char ch) const {
    MySet<int> result;

    for(int i=0;i<states[start].getCountOfTransitions();i++){
        if(states[start][i].key==ch){
            result.push(states[start][i].destination);
        }
    }
    return result;
}

bool Automata::reachableStates(int state,const MyString &str) const {

    if(str.length()==0&& isFinal(state)){
        return true;
    }
    //std::cout<<"length-"<<str.length()<<std::endl;
    if(str.length()==0){
        return false;
    }

    char firstLetter= str[0];
    MyString remaining=str.substr(1,str.length()-1);

    //std::cout<<states[state].getCountOfTransitions()<<std::endl;


    for(int i=0;i<states[state].getCountOfTransitions();i++){
        if(states[state].transitionsFromState[i].key==firstLetter){
            if(reachableStates(states[state].transitionsFromState[i].destination,remaining)){
                return true;
            }
        }
    }
    return false;
}

bool Automata::accept(const MyString &str) const {
    return    reachableStates(startState,str);
}

bool Automata::isFinal(int n) const {
    for(int i=0;i<finalStates.getSize();i++){
        if(finalStates[i]==n){
            return true;
        }
    }
    return false;
}
bool Automata::isDeterminized() const {
    for(int i=0;i<states.getSize();i++){
        for(int j=0;j<states[i].getCountOfTransitions();j++){
            for(int l=j+1;l<states[i].getCountOfTransitions();l++){
                if(states[i][j].key==states[i][l].key){
                    return false;
                }
            }
        }
    }
    return true;
}
bool Automata::isStateValid(size_t n) const {
    return n<states.getSize();
}
void Automata::changeStartingState(size_t n) {
    if(! isStateValid(n)){
        return;
    }
    startState=n;
    return;
}
void Automata::makeToOneAutomata(const Automata &other) {
    int size =states.getSize();
    int otherSize=other.states.getSize();

    for(int i=0;i<otherSize;i++){
        states.push(other.states[i]);

            for(int j=0;j<other.states[i].getCountOfTransitions();j++){
                states[i+size][j].changeDest(size+states[i+size][j].destination);
            }
        if(other.finalStates.contains(i)){
            finalStates.push(size+i);
        }
    }
    return;
}

void Automata::reverse() {
    Automata result(states.getSize());
    result.alphabet=alphabet;

    for(int i=0;i<states.getSize();i++){
        for(int j=0;j<states[i].getCountOfTransitions();j++){
            Transition temp = states[i][j];
            //std::cout<<states[i].getCountOfTransitions()<<std::endl;
            //result.addTransition(states[i][j].destination,i,states[i][j].key);
            result.addTransition(temp.destination,i,temp.key);
        }
    }
    result.makeStateFinal(startState);

    MySet<int> newFinalStates= finalStates;
    result.startingStates=finalStates;
    if(finalStates.contains(startState)){
        result.isStartingFinal= true;
    }
    *this=result;
}

void Automata::makeTotal() {
    this->addState();
    int junkStateIndex=states.getSize();

    //making the junkState point to itself
    for(int i=0;i<alphabet.getSize();i++){
        states[junkStateIndex].addTransition(junkStateIndex,alphabet[i]);
    }

    for(int i=0;i<states.getSize();i++){
        for(int j=0;j<alphabet.getSize();j++){
            if(!states[i].hasTransition(alphabet[j])){
                states[i].addTransition(junkStateIndex,alphabet[j]);
            }
        }
    }
}

void Automata::makeDeterminized() {
    if(isDeterminized()){
        return;
    }
    Automata result;

    MyQueue<MySet<int>> newStates;
    MyVector<MySet<int>> stateSets;
    MyVector<int> stateIndexes;
    MySet<int> newStartState;
    result.alphabet=alphabet;

    if(isFinal(startState)){
        result.makeStateFinal(0);
    }

    stateSets.push(newStartState);
    newStates.push(newStartState);
    stateIndexes.push(0);

    int statesCount =1;

    while (!newStates.isEmpty()){
        MySet<int> currentState= newStates.peek();
        newStates.pop();

        int currentStateIndex= stateIndexes.peek(0);
        stateIndexes.remove(stateIndexes[0]);
        stateSets.remove(0);

        bool stateExist= false;
        int destStateIndex=-1;
        destStateIndex=stateSets.find(currentState);
        if(destStateIndex!=-1){
            stateExist= true;
        }
        for(int i=0;i<alphabet.getSize();i++){
            MySet<int> currentStateSet= getTransitions(currentStateIndex,alphabet[i]);

            if(currentStateSet.getSize()==0){
                continue;
            }

            if(stateExist){
                result.addTransition(currentStateIndex,destStateIndex,alphabet[i]);
            }else{
                result.addState();
                stateSets.push(currentStateSet);
                stateIndexes.push(statesCount);
                newStates.push(currentStateSet);

                if(Intersection(currentStateSet,finalStates).getSize()!=0){
                    result.makeStateFinal((statesCount));
                }

                result.addTransition(currentStateIndex,statesCount,alphabet[i]);
                statesCount++;
            }
        }
    }

    *this=result;
}

void Automata::makeMinimal() {
    makeDeterminized();
    reverse();
    makeDeterminized();
    reverse();
    makeDeterminized();
    isMinimal= true;
}

MyString Automata::getRegularExpression() const {
    MyString result;

    bool firstFinalState= false;
    for(int i=0;i<states.getSize();i++){
        if(!firstFinalState){
            result+='+';
        }else{
            firstFinalState= false;
        }
        int finalStateInd=finalStates[i];
        result+=""
    }
}

Automata Union(const Automata& lhs, const Automata& rhs){
    // drawing the both automats
    //adding new starting state
    Automata result;
    result.makeToOneAutomata(rhs);
    result.addState();
    size_t newStartingStateIndex=result.states.getSize()-1;
    result.changeStartingState(newStartingStateIndex);

    size_t finalStatesCount = lhs.finalStates.getSize();
    MyVector<State> tempFinalStates;
    for(int i=0;i<finalStatesCount;i++){
        State temp;
        temp.transitionsFromState=rhs.states[0].transitionsFromState;
        //tempFinalStates.push(temp);
        result.states.push(temp);
    }

    if(lhs.finalStates.contains(lhs.startState)||rhs.finalStates.contains(rhs.startState)){
        result.makeStateFinal(result.startState);
    }
    result.alphabet= lhs.alphabet+rhs.alphabet;

    return result;
}


Automata Concat(const Automata& lhs, const Automata& rhs){
    //Zinoviev methods
    //the
    Automata result=lhs;
    result.makeToOneAutomata(rhs);

    size_t finalStatesCount = lhs.finalStates.getSize();
    MySet<int> tempFinalStates;
//    for(int i=0;i<finalStatesCount;i++){
//        State temp;
//        temp.transitionsFromState=rhs.states[0].transitionsFromState;
//        //tempFinalStates.push(temp);
//        result.states.push(temp);
//    }
    for(int i=0;i<finalStatesCount;i++){
        result.copyTransitions(lhs.finalStates[i],rhs.startState+lhs.states.getSize());
    }

    result.alphabet=lhs.alphabet+rhs.alphabet;
    for(int i=1;i<rhs.states.getSize();i++) {
        result.states.push(rhs.states[i]);
    }

    result.finalStates.clear();
    for(int i=0;i<rhs.finalStates.getSize();i++){
        result.finalStates.push(rhs.finalStates[i]+lhs.states.getSize());
    }

    return result;
}
Automata KleeneStar(const Automata& source){
    //Zinoviev methods
    //adding new starting State and making it final

    Automata result= source;
    result.addState();
    result.makeLastStateStarting();
    //make the new starting State do the the same as the old one
    result.copyTransitions(result.startState,source.startState);
    result.makeStateFinal(result.startState);
    for(int i=0;i<result.finalStates.getSize();i++){
        result.copyTransitions(i,result.startState);
    }


    return result;
}

Automata Intersect(const Automata&lhs, const Automata& rhs){
    return Complement(Union(Complement(lhs), Complement(rhs)));
}

Automata Complement(const Automata& source){
    Automata result= source;

    MySet<int> newFinals;
    for(int i=0;i<source.states.getSize();i++){
        if(!result.finalStates.contains(i)){
            newFinals.push(i);
        }
    }
    result.finalStates=newFinals;
    return result;
}

void Automata::debug() const {
    std::cout<<"starting state-"<<startState<<std::endl;
    for(int i=0;i<states.getSize();i++){
        std::cout<<"State - "<<i<<" - "<<std::endl;
        for(int j=0;j<states[i].getCountOfTransitions();j++){
            std::cout<<states[i][j].key<<"  -  "<<states[i][j].destination<<std::endl;
        }
    }
    for(int i=0;i<finalStates.getSize();i++){
        std::cout<<"final state- "<<finalStates[i]<<" ";
    }
    std::cout<<std::endl;
}

