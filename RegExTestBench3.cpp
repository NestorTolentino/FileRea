#include<iostream>
#include<stdlib.h>
#include<string>
#include<regex>
#include<fstream>
using namespace std;

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
    //Extraction of the module's name

    regex moduleNameRegEx("module\\s+(\\w+)");
    smatch moduleNameMatch;
    //regex_search(completeFile, moduleNameMatch, moduleNameRegEx);
        
    //cout << '1' << ": '" << moduleNameMatch.str() << "'\n";
    //cout <<completeFile << "'\n";
      
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

    //regex outputsRegEx("output\\s*(.*)\\b");
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
    o<<"module "<<moduleName + "_TB;"<<endl;
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
//*******************************************************************************************************************************************
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

    //o<<moduleName<<endl;
    k = 0;
    o<<moduleName<<" UUT(";
    while (justInputs[k] != ""){
       o<<"."<<justInputs[k]<<"("<<justInputs[k]<<"),";
        k = k+1;
       // cout<<justInputs[k]<<endl;
    }
    //o<<"."<<justInputs[k]<<"("<<justInputs[k]<<")";
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
    
    /* delimiter = ",";
        int ite2=0;
        while ((pos = token[0].find(delimiter)) != string::npos) {
        token[0].erase(0, pos + delimiter.length());
        ite2++;
        } */
    //ite2 se debe de sumar 1
    //cout<< ite2 <<endl;
    //cout<<token

    regex sizeRegEx("\\[(\\d*):(\\d*)\\]");
    smatch sizeMatch;
    string digit1[10];
    string digit2[10];
    int dig1, dig2, result;
    for (size_t j = 0; j < ite; j++)
    {
        regex_search(token[j], sizeMatch, sizeRegEx);
        //sizeI[b] = "wire "+sizeMatch[1].str();
        if(!sizeMatch.empty()){
            digit1[j] += sizeMatch[1].str();
            digit2[j] += sizeMatch[2].str();
            dig1 = stoi(digit1[j]);
            //cout<<dig1<<" ";
            dig2 = stoi(digit2[j]);
            result=abs(dig1-dig2)+1;
            cout<<result<<"  "; 
        }
      /* code */
    }
  
    
    

    return 0;
}