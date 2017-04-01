#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;


int bolenkalan(int okul_no);
int katlama(int okul_no);
int kareortasi(int okul_no);

void lineer_yoklama(string ozutleme,int retid,int okul_no,string isim,string soyad);
void ayrik_tasma(string ozutleme,int retid,int okul_no,string isim,string soyad);

void yazmalineer(string ozutleme,struct ozutlemebilgi ozutlenmisbilgi[]);
void yazmaayrik(string ozutleme,vector<ozutlemebilgi>  ayrik[]);

int lineer_arama(int arananOkul_no);

int lineerBolenKalanArama(int retid,int okul_no);
int lineerKareOrtasiArama(int retid,int okul_no);
int lineerKatlamaArama(int retid,int okul_no);

int ayrikBolenKalanarama(int retid,int okul_no);
int ayrikKareOrtasiarama(int retid,int okul_no);
int ayrikKatlamaarama(int retid,int okul_no);



struct bilgi{
	int okul_no[9];
	char isim[10];
	char soyad[10];
};

struct ozutlemebilgi{
    int ozutleme;
    int okul_no;
    string isim;
    string soyad;
};

ozutlemebilgi  lineerBolenKalan[500];
ozutlemebilgi  lineerKatlama[500];
ozutlemebilgi  lineerKareOrtasi[500];

vector<ozutlemebilgi>  ayrikBolenKalan[500] ;
vector<ozutlemebilgi>  ayrikKatlama[500] ;
vector<ozutlemebilgi>  ayrikKareOrtasi[500] ;


int main(){

    srand (time(NULL));

    struct bilgi a[500];

    for(int i=0;i<500;i++){
            for(int j=0;j<9;j++){
                if(j==0){
                    a[i].okul_no[j]=1;
                }
                else if(j==1){
                    a[i].okul_no[j]=rand() % 6 ;
                }
                else if(j==2){
                    a[i].okul_no[j]=0;
                }
                else if(j==6){
                    a[i].okul_no[j]=rand() % 5;
                }
                else {
                    a[i].okul_no[j]=rand() % 10 ;
                }

            }

            for(int k=0;k<10;k++){
                a[i].isim[k]='A'+(rand() % 26);
            }
            for(int m=0;m<10;m++){
                a[i].soyad[m]='A'+(rand() % 26);
            }

    }
    FILE *fp;
    fp= fopen("bilgi.txt","w+");

    for(int j=0;j<500;j++){
            for(int i=0;i<9;i++){
                fprintf(fp,"%d",a[j].okul_no[i]);
            }

            fprintf(fp," ");
            for(int k=0;k<10;k++){
                    fprintf(fp,"%c",a[j].isim[k]);
            }

            fprintf(fp," ");
            for(int m=0;m<10;m++){
                    fprintf(fp,"%c",a[j].soyad[m]);
            }
            if(j!=499){
                fprintf(fp,"\n");
            }

    }

    fclose(fp);

    for(int i=0;i<500;i++){
        lineerBolenKalan[i].ozutleme=-1;
        lineerKareOrtasi[i].ozutleme=-1;
        lineerKatlama[i].ozutleme=-1;
    }
    ifstream okuma("bilgi.txt");

    string satir;
    int okul_no;
    string isim;
    string soyad;
    int retid=0;
    string bolen="BolenKalan";
    string katlam="Katlama";
    string kareort="KareOrtasi";

//http://stackoverflow.com/questions/3555715/how-to-read-formatted-data-in-c
    for (string satir; getline(okuma, satir);)
    {
        stringstream iss(satir);
        while(iss>>okul_no>>isim>>soyad)

             {

             retid = bolenkalan(okul_no);
             lineer_yoklama(bolen,retid,okul_no,isim,soyad);
             ayrik_tasma(bolen,retid,okul_no,isim,soyad);

             retid = katlama(okul_no);
             lineer_yoklama(katlam,retid,okul_no,isim,soyad);
             ayrik_tasma(katlam,retid,okul_no,isim,soyad);

             retid= kareortasi(okul_no);
             lineer_yoklama(kareort,retid,okul_no,isim,soyad);
             ayrik_tasma(kareort,retid,okul_no,isim,soyad);

             }

    }




    yazmalineer(bolen,lineerBolenKalan);
    yazmalineer(kareort,lineerKareOrtasi);
    yazmalineer(katlam,lineerKatlama);

    yazmaayrik(bolen,ayrikBolenKalan);
    yazmaayrik(kareort,ayrikKareOrtasi);
    yazmaayrik(katlam,ayrikKatlama);

    string devam="E";

    do{

        int aranacakokulno=0;
    int aranacakretid=0;
    map<string,int> kiyaslama;

    cout<<"Aramak istediginiz ogrenci numarasini giriniz : ";
    cin>>aranacakokulno;
    cout<<"-------------------------------------------------------------------------------"<<endl;

    aranacakretid=bolenkalan(aranacakokulno);
    kiyaslama["Lineer Bolen Kalan"]=lineerBolenKalanArama(aranacakretid,aranacakokulno);

    aranacakretid=kareortasi(aranacakokulno);
    kiyaslama["Lineer Kare Ortasi"]=lineerKareOrtasiArama(aranacakretid,aranacakokulno);

    aranacakretid=katlama(aranacakokulno);
    kiyaslama["Lineer Katlama    "]=lineerKatlamaArama(aranacakretid,aranacakokulno);

    cout<<"-------------------------------------------------------------------------------"<<endl;

    aranacakretid=bolenkalan(aranacakokulno);
    kiyaslama["Ayrik Bolen Kalan "]=ayrikBolenKalanarama(aranacakretid,aranacakokulno);

    aranacakretid=kareortasi(aranacakokulno);
    kiyaslama["Ayrik Kare Ortasi "]=ayrikKareOrtasiarama(aranacakretid,aranacakokulno);

    aranacakretid=katlama(aranacakokulno);
    kiyaslama["Ayrik Katlama     "]=ayrikKatlamaarama(aranacakretid,aranacakokulno);

    cout<<"-------------------------------------------------------------------------------"<<endl;

    kiyaslama["Lineer Arama      "]=lineer_arama(aranacakokulno);

    cout<<"-------------------------------------------------------------------------------"<<endl;

    int enKucuk=kiyaslama.begin()->second;
    string enKucukisim=kiyaslama.begin()->first;
    for(auto eleman:kiyaslama){
        if(eleman.second<enKucuk){
            enKucuk=eleman.second;
            enKucukisim=eleman.first;
        }
    }
    cout<<"                                 *********************"<<endl;
    cout<<"En hizli arama yapilan tablo ==> * "<<enKucukisim<<" *"<<endl;
    cout<<"                                 *********************"<<endl<<endl;

    cout<<"Aramaya devam etmek istiyor musunuz(E/H) : ";
    cin>>devam;

    }while(devam=="E");





    return 0;
}


int lineerBolenKalanArama(int retid,int okul_no){

    int sayac = 0;
    sayac++;

    while(okul_no!=lineerBolenKalan[retid].okul_no){

        retid++;
        retid=(retid)%500;
        sayac++;

    }

    cout<<"Lineer Bolen Kalan "<<sayac<<" islemde buldu. "<<lineerBolenKalan[retid].okul_no<<" "<<lineerBolenKalan[retid].isim<<" "<<lineerBolenKalan[retid].soyad<<endl;
    return sayac;
}
int lineerKareOrtasiArama(int retid,int okul_no){

    int sayac = 0;
    sayac++;

    while(okul_no!=lineerKareOrtasi[retid].okul_no){

        retid++;
        retid=(retid)%500;
        sayac++;

    }

    cout<<"Lineer Kare Ortasi "<<sayac<<" islemde buldu. "<<lineerKareOrtasi[retid].okul_no<<" "<<lineerKareOrtasi[retid].isim<<" "<<lineerKareOrtasi[retid].soyad<<endl;
    return sayac;
}
int lineerKatlamaArama(int retid,int okul_no){

    int sayac = 0;
    sayac++;

    while(okul_no!=lineerKatlama[retid].okul_no){

        retid++;
        retid=(retid)%500;
        sayac++;

    }

    cout<<"Lineer Katlama "<<sayac<<" islemde buldu. "<<lineerKatlama[retid].okul_no<<" "<<lineerKatlama[retid].isim<<" "<<lineerKatlama[retid].soyad<<endl;
    return sayac;
}

int lineer_arama(int arananOkul_no){

    int sayac=0;
    sayac++;
    string satir;
    sayac++;
    int okul_no;
    sayac++;
    string isim;
    sayac++;
    string soyad;
    sayac++;

    ifstream okuma("bilgi.txt");
    sayac++;

    for (string satir; getline(okuma, satir);){
        stringstream iss(satir);
        while(iss>>okul_no>>isim>>soyad){
                 sayac++;

             if( okul_no==arananOkul_no){

                sayac++;
                cout<<"Lineer arama "<<sayac<<" kerede buldu. "<<okul_no<<" "<<isim<<" "<<soyad<<endl;
                return sayac;
             }

        }

    }


}

int ayrikBolenKalanarama(int retid,int okul_no){

    int sayac=0;
    int it=0;
    sayac++;

    while(ayrikBolenKalan[retid][it].okul_no!=okul_no){

        it++;
        sayac++;

    }

    cout<<"Ayrik Bolen Kalan "<<sayac<<" islemde buldu. "<<ayrikBolenKalan[retid][it].okul_no<<" "<<ayrikBolenKalan[retid][it].isim<<" "<<ayrikBolenKalan[retid][it].soyad<<endl;
    return sayac;
}
int ayrikKareOrtasiarama(int retid,int okul_no){

    int sayac=0;
    int it=0;
    sayac++;

    while(ayrikKareOrtasi[retid][it].okul_no!=okul_no){

        it++;
        sayac++;

    }

    cout<<"Ayrik Kare Ortasi "<<sayac<<" islemde buldu. "<<ayrikKareOrtasi[retid][it].okul_no<<" "<<ayrikKareOrtasi[retid][it].isim<<" "<<ayrikKareOrtasi[retid][it].soyad<<endl;
    return sayac;
}
int ayrikKatlamaarama(int retid,int okul_no){

    int sayac=0;
    int it=0;
    sayac++;

    while(ayrikKatlama[retid][it].okul_no!=okul_no){

        it++;
        sayac++;

    }

    cout<<"Ayrik Katlama "<<sayac<<" islemde buldu. "<<ayrikKatlama[retid][it].okul_no<<" "<<ayrikKatlama[retid][it].isim<<" "<<ayrikKatlama[retid][it].soyad<<endl;
    return sayac;
}

int bolenkalan(int okul_no){

    int retid;

    retid=okul_no%500;

    return retid;
}
int katlama(int okul_no){

    int retid=0;
    while(okul_no>0){

        retid+=okul_no%1000;
        okul_no=okul_no/1000;

    }
    return (retid)%500;

}
int kareortasi(int okul_no){


    int retid=0;
    unsigned long long int tmp=0;
    unsigned long long int gecici=okul_no;

    tmp=gecici*gecici;
    tmp=tmp/10000000;
    retid=(tmp%1000)%500;

    return retid;

}

void lineer_yoklama(string ozutleme,int retid,int okul_no,string isim,string soyad ){



    if(ozutleme=="BolenKalan"){

        while(lineerBolenKalan[retid].ozutleme == retid){
        retid++;
        retid = retid % 500;

        }

        lineerBolenKalan[retid].ozutleme=retid;
        lineerBolenKalan[retid].okul_no=okul_no;
        lineerBolenKalan[retid].isim=isim;
        lineerBolenKalan[retid].soyad=soyad;

    }


   else if(ozutleme=="Katlama"){

        while(lineerKatlama[retid].ozutleme == retid){
        retid++;
        retid = retid%500;
        }

        lineerKatlama[retid].ozutleme=retid;
        lineerKatlama[retid].okul_no=okul_no;
        lineerKatlama[retid].isim=isim;
        lineerKatlama[retid].soyad=soyad;

    }
   else if(ozutleme=="KareOrtasi"){

        while(lineerKareOrtasi[retid].ozutleme == retid){
        retid++;
        retid = retid%500;
        }

        lineerKareOrtasi[retid].ozutleme=retid;
        lineerKareOrtasi[retid].okul_no=okul_no;
        lineerKareOrtasi[retid].isim=isim;
        lineerKareOrtasi[retid].soyad=soyad;

    }


}
void ayrik_tasma(string ozutleme,int retid,int okul_no,string isim,string soyad){


    struct ozutlemebilgi gecici;

    gecici.ozutleme=retid;
    gecici.okul_no=okul_no;
    gecici.isim=isim;
    gecici.soyad=soyad;

    if(ozutleme=="BolenKalan"){
        ayrikBolenKalan[retid].push_back(gecici);
    }

    else if(ozutleme=="Katlama"){
        ayrikKatlama[retid].push_back(gecici);
    }

    else if(ozutleme=="KareOrtasi"){
        ayrikKareOrtasi[retid].push_back(gecici);
    }


}

void yazmalineer(string ozutleme,struct ozutlemebilgi ozutlenmisbilgi[]){


    struct ozutlemebilgi gecici;
    string yazmalineer=ozutleme+"lineer.txt";


    ofstream yazma(yazmalineer);

    for(int i=0;i<500;i++){
        yazma<<setw(3)<<ozutlenmisbilgi[i].ozutleme<<" "<<ozutlenmisbilgi[i].okul_no<<" "<<ozutlenmisbilgi[i].isim<<" "<<ozutlenmisbilgi[i].soyad;
        if(i!=499){
            yazma<<endl;
        }
    }


}
void yazmaayrik(string ozutleme,vector<ozutlemebilgi>  ayrik[]){

    string yazmaayrik=ozutleme+"ayrik.txt";
    ofstream yazma(yazmaayrik);

    for(int i=0;i<500;i++){
            yazma<<setw(3)<<i;
        for(int j=0;j<ayrik[i].size();j++){
            yazma<<" "<<ayrik[i][j].okul_no<<" "<<ayrik[i][j].isim<<" "<<ayrik[i][j].soyad<<"--->";

        }
        yazma<<endl;

    }



}
