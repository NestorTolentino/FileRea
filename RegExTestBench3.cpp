#include<iostream>
#include<stdlib.h>
#include<string>
#include<regex>
#include<fstream>
using namespace std;

int main(){
    //read .sv file
    ifstream file;
    std::ofstream o("testbench.sv");
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
    //Extraction of the module's name

    regex moduleNameRegEx("module\\s+(\\w+)");
    smatch moduleNameMatch;
    //regex_search(completeFile, moduleNameMatch, moduleNameRegEx);
        
    //cout << '1' << ": '" << moduleNameMatch.str() << "'\n";
    //cout <<completeFile << "'\n";
      
    while(regex_search(completeFile, moduleNameMatch, moduleNameRegEx)){
        moduleName += moduleNameMatch.str();
        completeFile= moduleNameMatch.suffix();
    }
    //****************************************************
    //Extraction of the inputs

    regex inputsRegEx("input\\s*(.*)");
    smatch inputsMatch;
    string inputschange[10];
     int a = 0;

    while(regex_search(completeFile, inputsMatch, inputsRegEx)){
        
        inputschange[a] = "reg "+inputsMatch[1].str();
            
        inputs += inputsMatch.str()+ "\n";
        completeFile= inputsMatch.suffix();
        a = a+1;
    }
    //*****************************************************
    //Extraction of the outputs

    regex outputsRegEx("output\\s*(.*)");
    smatch outputsMatch;
    string outputschange[10];
    int b=0;

    while(regex_search(completeFile, outputsMatch, outputsRegEx)){
        outputschange[b] = "wire "+outputsMatch[1].str();

        outputs += outputsMatch.str() + "\n";
        completeFile= outputsMatch.suffix();
        b =b+1;
    }
    //*****************************************************
    o<<moduleName + "_TB;"<<endl;
     int k = 0;
    
    while (inputschange[k] != ""){
        o<<inputschange[k]<<endl;
        k = k+1;
    }

    k = 0;
    
    while (outputschange[k] != ""){
        o<<outputschange[k]<<endl;
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
        pch = strtok (NULL, " ,;\n\r");
        r += 1;
    }
//*********************************************************

  /*  int  i = 0;

    while(splitInputs[i] != ""){
        cout<<splitInputs[i]<<endl;
        i += 1;
    }

    i = 0;

    while(splitOutputs[i] != ""){
        cout<<splitOutputs[i]<<endl;
        i += 1;
    }

    string justInputs [20];
    string justOutputs[20];
    string valueVectors[20];

    r =0;
    int v = 0;

    int numVectors = 0;
    int numFirstVector = 0;
    int numSecondVector = 0;
    int numThirdVector = 0;
    int offset = 0;
    int flag2 = 0;

    for (int j = 0; j<20; j++){
        if(splitInputs[j].compare("input") == 0){
            splitInputs[j].append("Holi");
            flag2 += 1;
        }
        else if(splitInputs[j].compare(0,1,"[") == 0){
            valueVectors[v].append(splitInputs[j]);
            v += 1;
            numVectors += 1;
        }
        else
        {
            if(numVectors == 1 && flag2 == 1){
                numFirstVector += 1;
            }
            else if(numVectors == 2 && flag2 == 2){
                numSecondVector += 1;
            }
            else
            {
                numThirdVector += 1;
            }
            justInputs[r].append(splitInputs[j]);
            r += 1;
            offset +=1;
        }
    }

     for (int j = 0; j<20; j++){
        if(splitOutputs[j].compare("input") == 0){
            splitOutputs[j].append("Holi");
            flag2 += 1;
        }
        else if(splitOutputs[j].compare(0,1,"[") == 0){
            valueVectors[v].append(splitOutputs[j]);
            v += 1;
            numVectors += 1;
        }
        else
        {
            if(numVectors == 1 && flag2 == 1){
                numFirstVector += 1;
            }
            else if(numVectors == 2 && flag2 == 2){
                numSecondVector += 1;
            }
            else
            {
                numThirdVector += 1;
            }
            justInputs[r].append(splitInputs[j]);
            r += 1;
            offset +=1;
        }
    }


    for(int y = 0; y <numFirstVector; y++){
        cout<<"reg "+valueVectors[0]+" "+justInputs[y]+";"<<endl;
    }
    for(int y = 0; y <numSecondVector; y++){
        cout<<"reg "+valueVectors[1]+" "+justInputs[y+numFirstVector]+";"<<endl;
    }

    //o<<moduleName<<endl;
    k = 0;
    
    while (justInputs[k] != ""){
        o<<justInputs[k]<<endl;
        k = k+1;
    }
    k = 0;
    
    while (splitOutputs[k] != ""){
        o<<splitOutputs[k]<<endl;
        k = k+1;
    }
    return 0;*/
    string justInputs [20];
    string justOutputs[20];
    //string vector1[20];


    r =0;
    int j = 0;

    while(splitInputs[j] != ""){
        if(splitInputs[j].compare("input") == 0){
            j +=1;
        }
        else if(splitInputs[j].compare(0,1,"[") == 0){
            //vector1.append(splitInputs[j]);
            j +=1;
        }
        else
        {
            justInputs[r].append(splitInputs[j]);
            r +=1;
            j +=1;
        }
    }
       
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

    //o<<moduleName<<endl;
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
    
    
    regex moduleNameRegEx2("module\\s");
    string moduleName2;

    regex_search(moduleName, moduleNameMatch, moduleNameRegEx2);
    moduleName2= moduleNameMatch.suffix();

    o<<"\ninitial"<<endl<<"\tbegin"<<endl<<"\t\t$dumpfile(\""<<moduleName2<<".vcd\");";
    o<<"\n\t\t$dumpvars(1,"<<moduleName2<<"_TB);";
    string token[20];
    int ite=0;
    //cout<<inputs.find("\n")<<endl;
   
    //std::string s = "scott>=tiger>=mushroom";
    string delimiter = "\n";
    size_t pos = 0;
    //std::string token;
    while ((pos = inputs.find(delimiter)) != string::npos) {
    token[ite] = inputs.substr(0, pos);
    inputs.erase(0, pos + delimiter.length());
    ite++;
    }
    delimiter = ",";
        int ite2=0;
        while ((pos = token[0].find(delimiter)) != string::npos) {
        token[0].erase(0, pos + delimiter.length());
        ite2++;
        }
    //ite2 se debe de sumar 1
    cout<<ite2;
    //cout << token[2] <<endl;

    return 0;
}