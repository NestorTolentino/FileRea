#include<iostream>
#include<stdlib.h>
#include<string>
#include<regex>
#include<fstream>
#include<math.h>
#include<set>
#include<iterator>
using namespace std;


string toBinary(unsigned long long int);

int main(){
    //read .sv file
    ifstream file;
    std::ofstream o("testbonc.sv");
    string lineFile;
    string completeFile;
    string moduleName;
    string inputs;
    string outputs;

    file.open("design2.sv",ios::in);

    if(file.fail()){
        cout<<"It was impossible to read the file"<<endl;
        exit(1);
    } 

    while (!file.eof()){
        getline(file,lineFile);
        completeFile += lineFile + "\n";
    }
    //****************************************************
    //Remove Comments
    regex CommentsRegEx("\\/\\/[^\n]*\n");
    completeFile = regex_replace(completeFile,CommentsRegEx,"\n");
    //****************************************************
    //Extraction of the module's name

    regex moduleNameRegEx("module\\s+(\\w+)");
    smatch moduleNameMatch;
      
    while(regex_search(completeFile, moduleNameMatch, moduleNameRegEx)){
        moduleName += moduleNameMatch[1].str();
        completeFile= moduleNameMatch.suffix();
    }
    //****************************************************
    //Extraction of the inputs

    regex inputsRegEx("input\\s*(.*)\\b");
    smatch inputsMatch;
    string inputschange[10];
     int a = 0;

    while(regex_search(completeFile, inputsMatch, inputsRegEx)){
        
        inputschange[a] = "reg "+inputsMatch[1].str();
       
        inputs += inputsMatch[1].str()+ "\n";
        completeFile= inputsMatch.suffix();
        a = a+1;
    }
    //*****************************************************
    //Extraction of the outputs

    regex outputsRegEx("output\\s*(?:reg)*\\s*(.*)\\b");
    smatch outputsMatch;
    string outputschange[10];
    int b=0;

    while(regex_search(completeFile, outputsMatch, outputsRegEx)){
        outputschange[b] = "wire "+outputsMatch[1].str();
        outputs += outputsMatch[1].str() + "\n";
        completeFile= outputsMatch.suffix();
        b =b+1;
    }
    //*****************************************************
    o<<"`timescale 1ns/1ns\nmodule "<<moduleName + "_TB;"<<endl;
     int k = 0;
    
    while (inputschange[k] != ""){
        o<<inputschange[k]<<";"<<endl;
        k = k+1;
    }

    k = 0;
    
    while (outputschange[k] != ""){
        o<<outputschange[k]<<";"<<endl;
        k = k+1;
    }

//*********Spliting the inputs and outputs***************** 
    string splitInputs[20];
    string splitOutputs[20];
    int r =0;
 // Converting the inputs to char []***********************
    char instr[inputs.size() + 1];
    strcpy(instr, inputs.c_str());
  
//*********************************************************
//**********Spliting the inputs ***************************
    char * pch;
    pch = strtok (instr," ,;\n\r");

    while (pch != NULL)
    {
        splitInputs[r].append(pch);
        pch = strtok (NULL, " ,;\n\r");
        r = r +1;
    }
//**********************************************************
//Converting outputs to a char []
    char outstr[outputs.size() + 1];
    strcpy(outstr, outputs.c_str());  
//*********************************************************
//Spliting the outputs ************************************
    r = 0;
    pch = strtok (outstr," ,;\n\r");
    while (pch != NULL)
    {
        splitOutputs[r].append(pch);
        pch = strtok (NULL, "re ,;\n\r");
        r += 1;
    }
//****************************************************
    //Celning of "[..]" and  and keyword "output" and "inputs" from lits of inputs
    //and outputs   
    string justInputs [20];
    string justOutputs[20];

    r =0;
    int j = 0;

    while(splitInputs[j] != ""){
        if(splitInputs[j].compare("input") == 0){
            j +=1;
        }
        else if(splitInputs[j].compare(0,1,"[") == 0){
            j +=1;
        }
        else
        {
            justInputs[r].append(splitInputs[j]);
            r +=1;
            j +=1;
            
        }
    }
    //*****************************************************************************************************
       
    r = 0;
    j = 0;

    while(splitOutputs[j] != ""){
        if(splitOutputs[j].compare("output") == 0 ){
            j += 1;
        }
        else if(splitOutputs[j].compare(0,1,"[") == 0){
            j += 1;
        }
        else{
            justOutputs[r].append(splitOutputs[j]);
            r += 1;
            j += 1;
        }
    }
//****************************************************
    // Instatation of the module to test and declaration of commads to
    // strat the simulation  
    k = 0;
    o<<moduleName<<" UUT(";
    while (justInputs[k] != ""){
       o<<"."<<justInputs[k]<<"("<<justInputs[k]<<"),";
        k = k+1;
    }

    k = 0;
    
    while (justOutputs[k] != ""){
        if(justOutputs[k+1] != "")
        {
          o<<"."<<justOutputs[k]<<"("<<justOutputs[k]<<"),";  
        }

        k = k+1;
    }
    o<<"."<<justOutputs[k-1]<<"("<<justOutputs[k-1]<<"));"; 
    
    o<<"\ninitial"<<endl<<"\tbegin"<<endl<<"\t\t$dumpfile(\""<<moduleName<<".vcd\");";
    o<<"\n\t\t$dumpvars(1,"<<moduleName<<"_TB);\n";

//****************************************************
    //Identification of RST and CLK
    k =0;
    r =0;
    string cl="";
    string rt="";
    string secInputs[20];
    while(justInputs[k] != ""){
        if(justInputs[k].compare("rst") == 0|| justInputs[k].compare("reset") == 0){
            rt = justInputs[k];
            justInputs[k]="";
            k++;
        }
        else if (justInputs[k].compare("clk") == 0|| justInputs[k].compare("clock") == 0){
            cl = justInputs[k];
            justInputs[k]="";
            k++;
        }
        else
        {
            secInputs[r].append(justInputs[k]); 
            justInputs[k]="";
            r ++;
            k ++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        justInputs[i]=secInputs[i];
    }
//****************************************************
    //Clock initialization   
    if (cl!=""){
        o<<"\t\t"<<cl<<"=1'b0;#1\n";
    }
//****************************************************
    //RST initialization  
    if (rt!=""){
        o<<"\t\t"<<rt<<"=1'b1;#1\n\t\t"<<rt<<"=1'b0;#1\n";
    }

//****************************************************
    //Number of lines with "input", stored in ite
    string token[20];
    int ite=0;
    string delimiter = "\n";
    size_t pos = 0;
    while ((pos = inputs.find(delimiter)) != string::npos) {
    token[ite] = inputs.substr(0, pos);
    inputs.erase(0, pos + delimiter.length());
    ite++;
    }
//****************************************************
    //Identification of "[.:.]" to get the total number of bits of all the inputs
    regex sizeRegEx("\\[(\\d*):(\\d*)\\]");
    smatch sizeMatch;
    string digit1[10];
    string digit2[10];
    regex groupRegEx("([^,]+)");
    smatch groupMatch;
    int n=0;
    string aux;
    int dig1, dig2, result;
    int size;
    for (size_t j = 0; j < ite; j++)
    {
        regex_search(token[j], sizeMatch, sizeRegEx);
        size = 0;
        aux = token[j];
        while(regex_search(aux, groupMatch, groupRegEx)){
            size++;
            aux= groupMatch.suffix();
        }
        if(!sizeMatch.empty()){
            digit1[j] += sizeMatch[1].str();
            digit2[j] += sizeMatch[2].str();
            dig1 = stoi(digit1[j]);
            dig2 = stoi(digit2[j]);
            result=abs(dig1-dig2)+1;
            n=n+result*size;         
        }
        else
        {
           n = n+size;
        }    
    }
//****************************************************
    //Generation of random cobinations of the total number of bits
    unsigned long long int  v = pow(2,n);
    std::set <unsigned long long int> randSet = {0};
    std::set <unsigned long long int>::iterator itr;
    int m;

    if(v>100){
      m = 100;
    }
    else if (v<25){
        m = v;
    }
    else{
        m =round(v/2);
    }
    k=0;
    for (int i;i<=m;i++){
        if (i!=m){
        randSet.insert(rand()%v);}
        else{
        randSet.insert(v-1);}
    }
//****************************************************
    //Generation string with each input to assaign to this the generated combinations    
    //ex. {A,B,C,...}=
    string allinputs="{";
    while(justInputs[k]!=""){  
        if(justInputs[k+1] != ""){
        allinputs += justInputs[k]+",";
        }
        k ++;
    }
    allinputs += justInputs[k-1]+"}=";
//****************************************************
    //Writing of each combination transform in binary
    for (itr = randSet.begin(); itr != randSet.end(); itr++)
    {

       o <<"\t\t"<<allinputs<<n<<"'b"<<toBinary(*itr)<<";#1"<<endl;
    }
//****************************************************
    //Closing of the declaration of the simulates signals
    o<<"\t\t$finish;\n\tend\n";
//****************************************************
    //Definition of the clock
    if (cl!=""){
        o<<"\t"<<"always #1 "<<cl<<"=~"<<cl<<";\n";
    }
//****************************************************
    //Closing of the module
    o<<"endmodule"<<endl;
    
    randSet.clear();    
    return 0;
}

//****************************************************
    //Function that trasfroms to binary integers
string toBinary(unsigned long long int n)
{
    string r;
    if(n!=0){
        while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    }
    else{
        r = "0";
    }
    return r;
}
