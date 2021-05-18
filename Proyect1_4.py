#######################################################################
#Descripción:   Generador de TestBench para modulos de SystemVerilog
#               utilizando expresiones regulares en python.
#Limitaciones:  
#               El reloj debe llamarse clk o clock, solo debe haber 1
#               el reset debe ser positivo, debe llamarse rst o reset (solo 1)
#               no deben haber instanciaciones en el modulo
#
#Autores:   Alejandro Ramirez
#           Emmanuel Vera
#           Ivar Ramírez
#           Nestor Tolentino
#######################################################################

import re
import random
import time

s=time.time()
#~~~~~~~~~~~~~~~~~~~~funciones~~~~~~~~~~~~~~~~~~~~#
def StringOfFile(NameOfFile):
    with open(File, 'r') as OpenedFile:
        if (OpenedFile.mode != 'r'): print("no file open")
        else: print("Archivo", NameOfFile, "abierto")
        text = OpenedFile.read()
    return text

#~~~~~~~~~~~~Abrir archivo
#File = input("File name: ")
#File = input("Texto a examinar: ")
File = "design2.sv"
#regex = input("Ingresa una expresion regular: ")
#x=input("if sequential write 's', if combinational write 'c': ")
text = StringOfFile(File)

#~~~~~~~~~~~~~~~~~~~~remover comentarios~~~~~~~~~~~~~~~~~~~~#
regexComments = r"\/\/[^\n]*\n"
matches = re.finditer(regexComments, text)
for match in matches:
    text = text.replace(match.group(),"")
#~~~~~~~~~~~~~Encontrar nombre de modulo
regexNameModule= r"module\s*([\w]*)\s*\("
matches = re.search(regexNameModule, text)
if matches:
    ModuleName = matches.group(1)
    print("Matches: ", ModuleName)

#~~~~~~~~~~~~~Encontrar entradas
#regexclk = r"clk|clock"
#matches = re.finditer(regexclk, text, re.MULTILINE | re.IGNORECASE)

#regexrst = r"rst|reset"
#matches = re.finditer(regexrst, text, re.MULTILINE | re.IGNORECASE)

regexInputs = r"input\s*(\[*.*)[,|\s|;]"
matches = re.finditer(regexInputs, text)
Inputs=[]

for match in matches:
    for groupNum in range(0, len(match.groups())):
         Inputs.append(match.group(groupNum+1))

# Elimina , al final de cada input por ;
for i in range(len(Inputs)):
    a_str = Inputs[i]
    index = a_str.rfind(';')     # rfind encuntra el ultimo elemento del string con ';'
    index2 = a_str.rfind(',')    # rfind encuntra el ultimo el  emento del string con ','
    if index != -1:           
        Inputs[i]= a_str[:index]  # Si encuentra ';' la quita de la string 
    elif index2 != -1:  
        Inputs[i]= a_str[:index2] # Si no hay ';' encuntra ',' la quita del string

#~~~~~~~~~~~~~Encontrar salidas
regexOutputs = r"output\s*[reg\s*]*(\[*.*)[,|\s|;]"#r"output\s*(reg)*(\[*.*)[,|\s|;]"
matches = re.finditer(regexOutputs, text)
Outputs=[]
for match in matches:   
    for groupNum in range(0, len(match.groups())):
         Outputs.append(match.group(groupNum+1))

# Elimina "," al final de cada input y elimina "reg" de Outputs en en el caso de output reg
a = []
for i in range(len(Outputs)):
    a_str = Outputs[i]         # Guarda en auxiliar el valor de cada elemento de la lista
    index = a_str.find('reg')  # Busca el indice de la primera cocncidencia con reg
    if index > -1:
       a.append(i)           # Si hay coincidencia guarda en una lisa a los indices de los elemntos con reg
    else:    
       index = a_str.rfind(';')  # rfind encuntra el ultimo elemento del string con ';'
       index2 = a_str.rfind(',') # rfind encuntra el ultimo elemento del string con ','
       if index != -1:
           Outputs[i]= a_str[:index]  # Si encuentra ';' la quita de la string 
       elif index2 != -1:
            Outputs[i]= a_str[:index2] # Si no hay ';' encuntra ',' la quita del string
for i in a:
    Outputs.pop(i)  # Saca de la lista las elementos con "reg" en base a los indices de a


#~~~~~~~~~~~~~Declara el modulo del test bench y las señales reg wire a usar
OutFile = "Testbenc.sv"
with open(OutFile, 'w') as OpenedFile:
   if (OpenedFile.mode != 'w'): print("Not ready to write")
   else:
        OpenedFile.write    (   "`timescale 1ns/1ns \n"
                            +   "module " + ModuleName + "_TB;\n"
                            )
        for i in Outputs:
            OpenedFile.write(   "\twire " + i +";\n")
                            
        for i in Inputs:
            OpenedFile.write(   "\treg " + i + ";\n")

#~~~~~~~~~~~~~Crea una lista donde cada elemento es un input y su tamño en bits
list1=[]                      
for i in range(len(Inputs)):       # En este for creamos una lista de cada entrada por seprado
    ind1=Inputs[i].find('[')
    if Inputs[i].find('[') !=-1:   # En este if se separa las entrdas delcaradas en la misma linea con
        ind2=Inputs[i].find(']')   # el mismo tamño de mas de 1 bit
        str1=Inputs[i][ind1:ind2+1]     # Primero en la condicion de if vemos si hay '['
        str2=Inputs[i][ind2+1:].split(',') # Despues buscamos ']' y guradmos lo que hay de '['-']' en str1
                                           # en str2 guardamos una lista de los elementos restantes del string
                                           # separados en base a ','
        for j in range(len(str2)):         # En el for combinamos str2 y str1 y cremos strings con 
            str3=str1+str2[j]              # el tamño bits "[...]" mas el nombre de cada entrada
            list1.append(str3)             # como cada string es un solo elemnto de lista usamos append
        
    else:                               # En este else se separa los inputs en una linea que estan juntos en string 
        Inputs[i]=Inputs[i].split(',')  # Esto da una lista de los elemnetos del string sperados en base a ','
        list1.extend(Inputs[i])         # Ya que queremos agregra a la lista otra lista usamos extend 
                                        # append agregaria toda la lista como un solo elemento
# List 1 tiene una lista de strings con cada entrada
list2=[]
for i in range(len(list1)):      # En este for agregamos el tamaño en bits de cada elemento
    ind1=list1[i].find('[')      # Idetificamos si hay '[' para detminar si el tamño de mas de 1 bit
    if list1[i].find('[') !=-1:
        ind2=list1[i].find(']')
        x1=list1[i]            # Guardamos en auxiliar el string de la lista que estamos examinando
        x=x1[ind1+1:ind2]      # Tomamos solo lo que hay entre "[...]" 
        y=x.split(':')         # Separmos el strin en base a ':'
        y1=int(y[0])           # Convertimos cada elemneto seprado a entero
        y2=int(y[1])
        size=abs(y2-y1)+1      # Con la resta abosluta calculamos en tamaño total en bits
        list2.append([list1[i][ind2+1:],size])  # Agregamos el tamño del elemento de la lista
    else:
        list2.append([list1[i],1]) # Agregamos el tamño de 1 al elemnto de 1 bit 
#design5.svprint(list2)
#list 2 tiene todas las entradas y sus dimensiones


# ~~~~~~~~~~~~~Crea un lista donde cada elemento es un Output
list3=[]
for i in range(len(Outputs)):
    ind1=Outputs[i].find(']') # Identificamos si hay o no ']' es decir si el tamño es de mas de 1 bit
    if Outputs[i].find(']') !=-1:
        list3.extend(Outputs[i][ind1+1:].split(',')) # Si idetificamos ']' no codiseramos este caracter y todo
    else:                                            # lo que esta antes y creamos lista de salidas que estan en una
        list3.extend(Outputs[i].split(','))          # sola linea saparadas en base a ','
                                                     # Si no identificamos ']' solo cremos la lista
#list 3 tiene todas las salidas


#~~~~~~~~~~~~~Instancia el modulo a probar
OutFile = "Testbenc.sv"
with open(OutFile, 'a') as OpenedFile:
   if (OpenedFile.mode != 'a'): print("Not ready to write")
   else:
        Inputstring=""
        Outputstring =""
        
        for i in range(len(list2)): # Con este for eliminamos los espacios de los string de la lista de entradas
            list2[i][0]=list2[i][0].replace(" ","")                       # Cremos un string con la declaracion directa
            Inputstring=Inputstring +"."+list2[i][0]+"("+list2[i][0]+")," # de las entrdas del DUT/UUT
        for i in range(len(list3)-1): # Con este for eliminamos los espacios de los string de la lista de salidas
            list3[i]=list3[i].replace(" ","")                         # Cremos un string con la declaracion directa
            Outputstring=Outputstring+"."+list3[i]+"("+list3[i]+"),"  # de las salidas del DUT/UUT 
        OpenedFile.write(ModuleName+" UUT("+Inputstring+Outputstring+"."+list3[-1].replace(" ","")+"("+list3[-1].replace(" ","")+"));\n")
        OpenedFile.write("\ninitial\n\tbegin\n\t\t$dumpfile(\""+ModuleName+'.vcd");\n\t\t$dumpvars(1,'+ModuleName+"_TB);\n")

#~~~~~~~~~~~~~Removes clock
inputclck = "" 
for i in list2:
    if (i[0].lower() == "clk") or (i[0].lower() == "clock"):
        inputclck=i[0]
        list2.remove(i)

#~~~~~~~~~~~~~Removes reset
inputrst = "" 
for i in list2:
    if (i[0].lower() == "rst") or (i[0].lower() == "reset"):
        inputrst=i[0]
        list2.remove(i)

#~~~~~~~~~~~~~Creacion de las señales de prueba
numbits=0
for i in range(len(list2)): # Con este for determinamos la suma total del tamño de bits todas las entradas 
    numbits+=list2[i][1]

inps=""

OutFile = "Testbenc.sv"
if len(list2)==0:
    with open(OutFile, 'a') as OpenedFile:
        if (OpenedFile.mode != 'a'): print("Not ready to write")
        else: 
            if inputclck!="":
                OpenedFile.write("\t\t\t"+inputclck+"=1'b0; #1\n")
            if inputrst!="":
                OpenedFile.write("\t\t\t"+inputrst+"=1'b1; #1 \n" + "\t\t\t" + inputrst +"=1'b0; #1\n")
            OpenedFile.write("\n\t\t$finish;\n\tend\n")
            if inputclck!="":
                OpenedFile.write("\talways #1 " + inputclck + "=~" + inputclck + ";")
            OpenedFile.write("\nendmodule")
            
else:
    with open(OutFile, 'a') as OpenedFile:
        if (OpenedFile.mode != 'a'): print("Not ready to write")
        else:
            if inputclck!="":
                OpenedFile.write("\t\t\t"+inputclck+"=1'b0; #1\n")
            if inputrst!="":
                OpenedFile.write("\t\t\t"+inputrst+"=1'b1; #1 \n" + "\t\t\t" + inputrst +"=1'b0; #1\n")
            
            if 2**numbits <25:
                random_signals=random.sample(range(1,2**numbits-1),2**numbits-2)
            elif 2**numbits >100:
                random_signals=random.sample(range(1,2**numbits-1),100)
            else:
                v=round(2**numbits/2)
                random_signals=random.sample(range(1,2**numbits-1),v)   # Four samples without replacement
        
            random_signals.extend([0,2**numbits-1])
            random_signals.sort()
        #print(random_signals)

            for i in random_signals: # Con este for cremos cada combiacion de bits de las entrdas
                #if 1 == random_signals.co:
                    if i in random_signals:
                        inps+="\t\t\t{"
                        for j in range(len(list2)-1): # Aqui pndemos entre '{}' cada entrada excepto la ultima
                            inps += list2[j][0]+","
                
                        inps+=list2[-1][0]+"}="+(str(bin(i)).replace("0b",str(numbits)+"'b")+";#1\n") # Aqui gurdamos en una string
                                        #da en binario       Sutituye 0b                      # la declaracion de cada 
            OpenedFile.write(inps)      #la combinacion      por N'b                            señal de prueba
            OpenedFile.write("\n\t\t$finish;\n\tend\n")
            if inputclck!="":
                OpenedFile.write("\talways #1 " + inputclck + "=~" + inputclck + ";")
            OpenedFile.write("\nendmodule")

print("Time take", time.time()-s)