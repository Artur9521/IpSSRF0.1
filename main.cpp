//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <string>
#include <sys/stat.h> 
#include <vector>

using namespace std;
/*
input дляфайлов чекать оба варика
newip для файлов чекнутьо

*/

string fi(string a,int i){
            for (int j=0;j<3;j++){
                if(('0' <= a[i+j+1]and a[i+j+1] <='9')or '.'==a[i+j+1]){
                    if ('.' == a[i+j+1]){
                        if('0' <= a[i+j+2] and a[i+j+2] <='9'){
                            char b = a[i+j+2];
                            return to_string(j+1) + fi(a,i+j+2);
                                                }
                            else
                            return to_string(j+1);
                    }
                }
                else 
                return to_string(j+1); 
            }
    return "000000" + to_string(3)+fi(a, i+3);

}

int* chooseip(string a,string b){
    int* ans= new int[6];
    int n [5]= {0, 0, 0 ,0 ,0},k = 0;

    string buf="";
    for (int i = 0;i<b.size();i++){
        if (b[i] == '-' ){
            n [k]= stoi (buf);
            int i1=i;
            for (k = 1;k<5;k++)
            {
                buf = b[i + k];
                n[k] = stoi (  buf );
                i1++;
            }
            i = i + i1;
        }
        else buf = buf + b[i];

    }
    ans[0] = n[0];
    ans[1] = n[0];
    buf ="";
    for(int i= 2;i<6;i++)
    ans[i] = 0;
    for (int i = 0;i<4;i++){
        for (int j=0;j<n[i+1];j++){    
            buf = buf+ a[i + j + ans[1]]; 
        }
        ans[1] = ans[1] + n[i+1];
        ans[2 + i] = stoi(buf);
        buf = "";
    }

    return ans;


}

string findnomb(string a,int start){// "--"- нет в строке ip ;12-3213 - 12 номер начала ip 3,2,1,3 -количество символов в октете "
    string answer;
    for (int i = start;i<a.size();i++){
        if (('0' <= a[i] and a[i] <='9' )and('0' >= a[i-1]or a[i-1] >='9' )){
            string buf = fi(a,i);
            if (buf.size()==4)
                return to_string(i)+"-"+buf;
            else if (buf.size() >4)
                {
                    int u = stoi (buf),add = 0;
                    while(u != 0)
                    {
                        add = add + u % 10;
                        u = u/10;
                    }
                    i = i+add;
                }
        }      
    }
    return "--";
}

char ss16(int a)
{   char b;
    if ((0<=a) and(a<=9))
        return 48 + a;
        else  return 55 + a;    
}

string ss(int number,int sis){
    int numberl = number;
    if (sis ==10)
        return to_string(number);
    string ans = "";
    while(numberl != 0)
    {
        ans =ss16(numberl%sis) + ans;
        numberl = numberl / sis;

    }
    return ans;
}



void creatipnew(string dir, int* ip,string* key, bool bo){
    fstream ans;
    string prip = "";
    ans.open(dir +"/OnlyIp.txt",ios::app);
    int sis;
    if (bo){
    for (int i=0;i<4;i++){
        if (key[i] == "a16"){
            sis = 16;
            prip = prip +"0x";
            }
            else if (key[i] == "a8"){
                sis = 8;
                prip= prip +"0";
                }
                else sis =10;
        prip = prip+ ss(ip[2+i],sis);
        if (i!=3)
        prip = prip+'.';
        }}
        else{
            if (key[0] == "a16"){
                sis = 16;
                prip = prip + "0x";
            }
            else if (key[0] == "a8"){
                sis = 8;
                prip = prip + "0";

            }
            else 
            sis = 10;
            int p;
            for (int i=0;i<4;i++)
                p = p * 256 + ip[2+i];
            prip = prip + ss(p,sis);
            }
    ans<<prip<<endl; 
    ans.close();
}

void changeip(int* ipis,string nameofdir){
    fstream keyfile;    
    keyfile.open("key.txt",ios::in);
    string key,bufr;
    string* buf = new string[4];
    while(getline(keyfile,key)){
        int count = 0;
        bool qe;
        if ((key != "a10*;") and (key != "a16*;") and (key != "a8*;")){
        qe = true;
        for (int i = 0;i <key.size();i++)
            {
                //дописать  3 иначе
                if ((key[i] != '.') and (key[i] != ';'))
                    bufr = bufr+ key[i];
                else
                    {
                        buf[count]= bufr;
                        bufr = "";
                        count++;
                    }

            //сам перевод ipis-> 1 символ;длина;новый ip;
            //string a[4];
            //for (int i=0;i<4;i++)
            //a[i]= buf[i];
            }
            creatipnew(nameofdir,ipis, buf,qe);
            //for (int i = 0;i <key.size();i++){ }
            }
            else{
                qe = false;
                if (key == "a10*;")
                buf[0] = "a10";
                else if (key == "a16*;")
                buf[0] = "a16";
                else buf[0] = "a8";
            creatipnew(nameofdir,ipis, buf,qe);
            


            }
    }



}//остановился тут внизу финкция не готова сверху start новым поиском
void newip(string buffil, string nameofdir, bool ch, int count){
    ifstream buf,fil;
    string bufst,numb,ip;
    if (!ch){
    buf.open(buffil,ios::in);
    while(getline(buf,bufst)){
        int* a = new int[6];//
        numb = findnomb(bufst,count);
        if (numb !="--"){
        a = chooseip(bufst,numb);///
        changeip(a,nameofdir);
        string nimb = numb.substr(0 ,numb.find('-'));
        numb.erase(0 , nimb.size()+1);
        int numbi = stoi(nimb), u = stoi(numb);
        while(u != 0)
        {
            numbi += u % 10 + 1;
            u = u / 10 ;
        }
        newip(buffil, nameofdir, ch, numbi-1);
        }
            /*for(int i= 0;i<6;i++)
    cout << a[0]<<'.';
    cout << endl;
    cout<<numb<<endl;*/
    }}
    else{
        buf.open(buffil,ios::in);
        while(getline(buf,bufst)){
            fil.open(bufst,ios::in);
            if (fil){
            cout<<"+";
            newip(bufst,nameofdir,0,0);}
            else 
            cout <<"-";
            fil.close();            
        }
    }
}

string namefiloftime(){
    string ot= "";
    time_t now = time(0);
    struct tm tstruct;
    char pr[16];
    tstruct = *localtime(&now);
    strftime (pr, sizeof(pr), "%d%m%Y%H%M%S" , &tstruct);
    for (int i= 0; i<sizeof(pr)-2;i++)
        ot = ot+pr[i];
   // ot=ot+".txt";
    return ot;
}

void gofile (string infile, string ourfile, bool ans){
    ofstream ourfil;
    if (infile != ourfile){
    ourfil.open(ourfile,ios::app );
    if (ourfil.is_open())
    if (ans){
        ifstream infil;
        string buf;
        infil.open(infile,ios::in);
        while(getline(infil,buf)){
                ourfil << buf << endl;
                
            }
        infil.close();
    }
    else{
        ourfil << infile << endl;
    }
    ourfil.close();
}
 else
            cout<< "ссылка на буферный файл";}


void delfile (string B){
    int a = remove(B.c_str());
     if (a==0)
            cout << "Удаление прошло" <<endl;
        else 
            cout << "Удаление не прошло код ошибки:" << a <<endl;    
}

bool qesfordel(string a){
    cout << "Введите N чтобы не удалять буфурный файл" <<endl;
    string buf="";
    getline(cin, buf);
    if (!( (buf == "n") or (buf == "N"))){
        delfile(a);
        return 0;
    }
    return 1;
}

void ressi(string a,string b){
    fstream buffil,y;
    buffil.open(a,ios::in);
    y.open("bufr.txt",ios::out);
    int count = 0;
    string s="";
    while (getline(buffil,s))
        y<< b+"/"+s<<endl;
    buffil.close();
    y.close();
    y.open("bufr.txt",ios::in);
    buffil.open(a,ios::out);
    while(getline(y,s))
        buffil << s <<endl;
    y.close();
    buffil.close();
    remove("bufr.txt");
}

bool input(string nameofbuffile)
{while(true){
        string buf1,namefile = "";
        const char buf = '"';
        cout << " Нажмите "<< buf <<"Enter" << buf <<",чтобы ввести файл. Введите IP или " <<buf <<"-z"<< buf <<" чтобы остановить ввод"<<endl;
        getline (cin,buf1);
        int inbuf = buf1.size();
        if (inbuf == 0){
            cout << "Введите"<<buf<<"+"<<buf<<" для перехода к наиписанию директории"<<endl<<"Или введите любой иной символ для перехода к вводу пути к файлу"<<endl; 
            getline(cin,namefile);
            if (namefile != "+"){
            cout << "Введите имя файла(включая обсолютный путь)"<<endl;
            getline(cin, namefile);
            if (namefile != nameofbuffile)
            gofile(namefile,nameofbuffile,true);
           
            }
            else{
            cout << "Введите дирикторию (включая обсолютный путь или относительный)"<<endl;
            getline(cin, namefile);

            cout << "Введите дирикторию "<<buf<<"Y"<<buf<<"чтобы перенести излишние данные в файл с ответом"<<endl;// сюда
            cout<<"Или любой иной символ для чтобы просто пропустить все что не IP"<<endl;
            string bla;
            //getline(cin, bla);
            if (bla == "Y" or bla == "y"){
                string a= "ls "+ namefile +" >"+nameofbuffile;
                system(a.c_str());
                ressi(nameofbuffile,namefile);
                return 1;
                }
            else {
                string a1 = "buf.txt";
                fstream a2;
                a2.open(a1,ios::out);
                a2.close();
                string a= "ls "+ namefile +" >"+a1;
                system(a.c_str());
                ressi(a1,namefile);
                a2.close();
                a2.open(a1,ios::in);
                while(getline(a2,bla)){{
                    gofile(bla,nameofbuffile,true);}
                    
                }
                a2.close();
                delfile(a1);
                }
            }
        }
        else if (buf1 == "-z")
            return 0;
        else 
        gofile(buf1,nameofbuffile,false);
}}

bool createdir(string name){
    bool a = mkdir(name.c_str() ,0740);
    if (!a) {
        cout << "Директория для итоговых файлов создана" <<endl;
        cout << "Дириктория с конечным файлом/ами: "<<name<<endl;
        ofstream filans;
        filans.open(name+"/OnlyIp.txt");
    }
    else{ 
        cout << "Дириктрия для итоговых файлов не создана.:"<<endl;
        cout << "Введите Y, если вы уверены,что хотите продолжить выполнение команды" <<endl;
        string f;
        getline(cin,f);
        if (!(f == "Y" or f == "y")) 
            return 1;
    }
        return 0;
}
int main(){
    setlocale(LC_ALL, "Russian");
    bool chek, check1;
    string nameofdir="",nameofbuffile  = "";
    nameofbuffile = namefiloftime();
    nameofdir =""+nameofbuffile;
    chek = createdir(nameofdir);

    nameofbuffile = nameofbuffile + ".txt";
    if (chek) return -1;
    nameofbuffile = "buffile_"+nameofbuffile;
    cout <<"Буферный файл"<<nameofbuffile<<endl;
    chek = input(nameofbuffile);
    
    //cout<<typeid(system("ls")).name();
    newip(nameofbuffile,nameofdir,chek,0);


    if(qesfordel (nameofbuffile))
        cout<<"Буферный файл"<<nameofbuffile<<endl;
    cout <<"Дириктрия для итоговых файлов"<<nameofdir<<endl;
    return 0;
    }
