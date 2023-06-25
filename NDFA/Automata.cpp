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

bool Automata::isReachable(int state) const {
    MySet<int> visited;
    MyVector<int> temp;
    temp.push(startState);

    while (!temp.isEmpty()){
        int currentState= temp.back();
        temp.popBack();

        if(visited.contains(currentState)){
            continue;
        }
        visited.push(currentState);

        if(currentState==state){
            return true;
        }

        for(int i=0;i<alphabet.getSize();i++ ){
            MySet<int> nextState= getTransitions(currentState,alphabet[i]);
            for(int j=0;j<nextState.getSize();j++){
                temp.push(nextState[i]);
            }
        }
    }
    return false;
}

bool Automata::isEmptyLanguage() const {
    MyVector<bool> visited ;
    for(int i=0;i<visited.getSize();i++){
        visited[i]= false;
    }
    visited[startState]= true;
    MyQueue<int> rest;
    rest.push(startState);

    while (!rest.isEmpty()){
        int currentState=rest.peek();
        rest.pop();

        if(finalStates.contains(currentState)){
            return false;
        }
        for(int i=0;i<states[currentState].getCountOfTransitions();i++){
            int next = states[currentState][i].destination;
            if(!visited[next]){
                visited[next]= true;
                rest.push(next);
            }
        }
    }
    return true;
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
    if(str.length()==0){
        return false;
    }

    char firstLetter= str[0];
    MyString remaining=str.substr(1,str.length()-1);



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

    for(int i=0;i<other.states.getSize();i++){
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

    this->print();

    for(int i=0;i<states.getSize();i++){
        for(int j=0;j<states[i].getCountOfTransitions();j++){
            result.addTransition(states[i][j].destination,i,states[i][j].key);
        }
    }
    result.makeStateFinal(startState);

    MySet<int> newFinalStates= finalStates;
    result.startingStates=finalStates;
    if(finalStates.contains(startState)){
        result.isStartFinal= true;
    }
    result.makingMinimal= true;
    *this=result;
    return;
}

void Automata::makeTotal() {
    this->addState();
    int junkStateIndex=states.getSize()-1;

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

    if(isDeterminized())
        return;

    Automata result;
    result.makingMinimal= makingMinimal;
    result.isStartFinal=isStartFinal;

    MyQueue<MySet<int>> newStates;
    MyVector<MySet<int>> stateSets;
    MyVector<int> stateIndexes;
    MySet<int> newStartStates;
    result.alphabet=alphabet;


    if(makingMinimal){
        newStartStates=startingStates;
        if(isStartFinal){
            result.makeStateFinal(0);
        }
    }else{
        newStartStates.push(startState);
        if(isFinal(startState)){
            result.makeStateFinal(0);
        }
    }

    stateSets.push(newStartStates);
    newStates.push(newStartStates);
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
    makingMinimal= true;
    reverse();
    makeDeterminized();
    reverse();
    makeDeterminized();
    makingMinimal = false;
}


MyString Automata::getRegularExpression() const {
    MyString result ="";
    int counterEpsilon=0;
    for(int i=0;i<states.getSize();i++){
        MyString temp=getRegularExpression(startState, finalStates[i], states.getSize(), true);
        if(temp==""){
            continue;
        }
        if(temp=="$"){
            counterEpsilon++;
        }
        if(counterEpsilon>1&&temp=="$"){
            continue;
        }
        if(i!=0){
            result+='+';
        }
        result += "[" + temp + "]";
    }

    return result;
}

//MyString Automata::getRegularExpression() const {
//    MyVector<MyVector<MyString>> regex(states.getSize());
//
//    for(int i=0;i<states.getSize();i++){
//        MyVector<MyString> temp(states.getSize());
//        for(int j=0;j<states.getSize();j++){
//            temp.push("");
//        }
//        regex.push(temp);
//    }
//
//    int transitionIndex=0;
//    for(int i=0;i<states.getSize();i++){
//        for(int j=0;j<states[i].getCountOfTransitions();j++){
//            int dest= states[i][j].destination;
//            char symb= states[i][j].key;
//            if(i==transitionIndex){
//                if(regex[i][dest]==""){
//                    regex[i][dest]+=symb;
//                }else{
//                    regex[i][dest]+="+"+symb;
//                }
//                transitionIndex++;
//            }else{
//                break;
//            }
//        }
//    }
//
//        for(int k=0;k<states.getSize();k++){
//            for(int i=0;i<states.getSize();i++){
//                for(int j=0;j<states.getSize();j++){
//                    if(regex[i][k]!=""&& regex[k][j]!=""){
//                        MyString newReg=("("+regex[i][k]+")("+regex[k][j]+")");
//                        if(regex[i][j]==""){
//                            regex[i][j]=newReg;
//                        }else{
//                            regex[i][j]+="+"+newReg;
//                        }
//                    }
//                }
//            }
//        }
//    MyString finalRegex=regex[startState][finalStates[0]];
//
//        if(finalStates.getSize()>1){
//            for(int i=1;i<finalStates.getSize();i++){
//                MyString currentFinalStateREX= regex[startState][finalStates[i]];
//                finalRegex=("("+finalRegex+" )+( "+currentFinalStateREX+")");
//            }
//        }
//
//    return finalRegex;
//}

bool needBrackets(const MyString& regex)
{
    if (regex.length() == 0)
        return false;
    if (regex[0] == '(' && regex[regex.length() - 1] == ')')
        return false;

    for (int i = 0; i < regex.length(); ++i)
    {
        if (regex[i] == '+')
            return true;
    }
    return regex[regex.length() - 1] == '*';
}
MyString Automata::getRegularExpression(int start, int end, int bound, bool epsilon) const {
    // From Angeld55
    // Ne sme vzimali kak se izvejda regulqren izraz ot avtomat,
    // opitah nqkolko varianta i se chupeha v nqkoi sluchai
    // ostaveni sa zakomentirani po gore
    if(bound==0){
        MySet<char> temp;

        if(start==end&& epsilon){
            temp.push('$');
        }
        for(int i=0;i<states[start].getCountOfTransitions();i++){
            if(states[start][i].destination==end){
                temp.push(states[start][i].key);
            }
        }

        MyString str="";
        for(int i=0;i<temp.getSize();i++){
            if(i!=0){
                str+=" + ";
            }
            str+= temp[i];
        }
        return str;
    }

    MyString leftL= getRegularExpression(start,end,bound-1,epsilon);
    MyString beforeBound= getRegularExpression(start,bound-1,bound-1,epsilon);
    MyString boundState = getRegularExpression(bound-1,bound-1,bound-1, false);
    MyString afterBound= getRegularExpression(bound-1,end,bound-1,epsilon);
    MyString right;

    if(beforeBound!="$"){
        if(needBrackets(beforeBound)){
            right+=" ( "+beforeBound+")";
        }else{
            right+=beforeBound;
        }
    }

    if(boundState!= "$"&& boundState !=""){
        right+= " ( "+boundState+ ")*";
    }

    if(afterBound!= "$"){
        if(needBrackets(afterBound)){
            right+= " ( "+ afterBound+ " ) ";
        }else{
            right+= afterBound;
        }
    }
    if (beforeBound == "$" && (boundState == "$" || boundState == "") && afterBound == "$")
        right = "$";
    if (beforeBound == "" || afterBound == "")
        right = "";

    if (leftL == "" && right == "")
        return "";
    if (leftL == "")
        return right;
    if (right == "")
        return leftL;
    if (leftL == right)
        return leftL;

    MyString regex= leftL;
    if (needBrackets(right))
        regex = regex + " + " + "(" + right + ")";
    else
        regex += " + " + right;
    return regex;
}


Automata Union(const Automata& lhs, const Automata& rhs){
    // drawing the both automats
    //adding new starting state

    Automata result=lhs;
    result.makeToOneAutomata(rhs);
    result.addState();
    result.changeStartingState(result.states.getSize()-1);
    result.copyTransitions(result.states.getSize()-1,lhs.startState);
    result.copyTransitions(result.states.getSize()-1,lhs.states.getSize()+rhs.startState);



    if(lhs.finalStates.contains(lhs.startState)||rhs.finalStates.contains(rhs.startState)){
        result.makeStateFinal(result.startState);
    }
    result.alphabet= lhs.alphabet+rhs.alphabet;

    return result;
}


Automata Concat(const Automata& lhs, const Automata& rhs){
    //Zinoviev methods

    Automata result=lhs;
    result.makeToOneAutomata(rhs);

    size_t finalStatesCount = lhs.finalStates.getSize();
    MySet<int> tempFinalStates;

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
    result.copyTransitions(result.states.getSize()-1,source.startState);
    for(int i=0;i<result.finalStates.getSize();i++){
        result.copyTransitions(result.finalStates[i],result.startState);
    }
    result.makeStateFinal(result.startState);

    return result;
}

Automata Intersect(const Automata&lhs, const Automata& rhs){
    return Complement(Union(Complement(lhs), Complement(rhs)));
}

Automata Difference(const Automata& lhs,const Automata&rhs){
    return Intersect(lhs, Complement(rhs));
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

void Automata::print() const {
    std::cout<<"starting state-"<<startState<<std::endl;
    for(int i=0;i<states.getSize();i++){
        std::cout<<"State - "<<i<<" - "<<std::endl;
        for(int j=0;j<states[i].getCountOfTransitions();j++){
            std::cout<<states[i][j].key<<"  ->  "<<states[i][j].destination<<std::endl;
        }
    }
    for(int i=0;i<finalStates.getSize();i++){
        std::cout<<"final state- "<<finalStates[i]<<" ";
    }
    std::cout<<std::endl;
}

void Automata::writeToFile(const MyString &name) const {
    std::ofstream ofs(name.c_str(),std::ios::binary);

    if(!ofs.is_open()){
        throw std::runtime_error("file not opened");
    }
    ofs.write((const char*)& startState, sizeof(startState));

    int alphabetSize = alphabet.getSize();
    ofs.write((const char*)&alphabetSize, sizeof(int));
    for(int i=0;i<alphabetSize;i++){
        ofs.write((const char*)&alphabet[i], sizeof(alphabet[i]));
    }

    int finalStatesSize = finalStates.getSize();
    ofs.write((const char*)&finalStatesSize, sizeof(int));
    for(int i=0;i<finalStatesSize;i++){
        ofs.write((const char*)&finalStates[i], sizeof(int ));
    }

    int statesSize= states.getSize();
    ofs.write((const char*)&statesSize, sizeof(int));
    for(int i=0;i<statesSize;i++){
        states[i].writeToFile(ofs);
    }

    ofs.write((const char*)&isStartFinal, sizeof(bool ));
    ofs.close();
}
void Automata::readFromFile(const MyString &name) {
    std::ifstream ifs(name.c_str(),std::ios::binary);

    if(!ifs.is_open()){
        throw std::runtime_error("file not opened");
    }
    ifs.read((char*)& startState, sizeof(startState));

    int alphabetSize = 0;
    ifs.read(( char*)&alphabetSize, sizeof(int));
    for(int i=0;i<alphabetSize;i++){
        ifs.read((char*)&alphabet[i], sizeof(char));
    }

    int finalStatesSize = 0;
    ifs.read((char*)&finalStatesSize, sizeof(int));
    for(int i=0;i<finalStatesSize;i++){
        ifs.read((char*)&finalStates[i], sizeof(int ));
    }

    int statesSize= 0;
    ifs.read(( char*)&statesSize, sizeof(int));
    for(int i=0;i<statesSize;i++){
        states[i].readFromFile(ifs);
    }
    ifs.read((char*) &isStartFinal, sizeof(bool ));
    ifs.close();
}