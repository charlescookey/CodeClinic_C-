#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int returnYear(string date){
    std::replace(date.begin(), date.end(), '_', ' ');

    stringstream yearS(date);
    int year;
    yearS>>year;
    
    return year - 2012;

    return 0;
}

double barPressure(istream & file , string date , string time){
    string tempDate ,  tempTime , line;
    double tempBm , AT , DP , RH , WD , WG , WS;
    while(getline(file , line)){
        istringstream fileStream(line);
        while(fileStream>>tempDate>>tempTime>>AT>>tempBm>>DP>>RH>>WD>>WG>>WS){
            if(tempDate == date && tempTime == time){
                cout<<tempDate<<" "<<tempTime<<" "<<AT<<" "<<tempBm<<" "<<DP<<" "<<RH<<" "<<WD<<" "<<WG<<" "<<WS<<"\n";
                return tempBm;
            }    
        }
    }
    return 0;
};

double time(string begind, string begint , string endd , string endt){
    std::replace(begind.begin(), begind.end(), '_', ' ');
    std::replace(begint.begin(), begint.end(), ':', ' ');

    std::replace(endd.begin(), endd.end(), '_', ' ');
    std::replace(endt.begin(), endt.end(), ':', ' ');

    double year , year2 , month , month2 , day ,day2 , hour ,hour2 , minute ,minute2 ,second , second2;

    stringstream a(begind);
    a>>year>>month>>day;

    stringstream b(endd);
    b>>year2>>month2>>day2;

    stringstream c(begint);
    c>>hour>>minute>>second;

    stringstream d(endt);
    d>>hour2>>minute2>>second2;

    double answer = (second2 -second)/(24*60*60);


    answer+= (minute2 - minute)/(24*60);
   
    answer+= (hour2 - hour)/24;
 
    answer+= day2-day;

    answer+= (month2-month)*12;

    answer+= (year2-year)*365;
    
    return answer;
};

int main(){
    ifstream file[4];
    file[0] = ifstream("./Environmental_Data_Deep_Moor_2012.txt");
    file[1] = ifstream("./Environmental_Data_Deep_Moor_2013.txt");
    file[2] = ifstream("./Environmental_Data_Deep_Moor_2014.txt");
    file[3] = ifstream("./Environmental_Data_Deep_Moor_2015.txt");    

    string begindate{"2012_01_01"};
    string begintime{"00:21:00"};

    string endDate{"2014_01_01"};
    string endTime{"00:21:24"};

    
    cout<<"Enter the start date in the format yyyy_mm_dd"<<endl;
    cin>>begindate;
    cout<<"Enter the start time in the format hh:mm:ss(24 hour format)"<<endl;
    cin>>begintime;
    cout<<"Enter the end date in the format yyyy_mm_dd"<<endl;
    cin>>endDate;
    cout<<"Enter the end time in the format hh:mm:ss(24 hour format)"<<endl;
    cin>>endTime;

    int year1 = returnYear(begindate);
    int year2 = returnYear(endDate);

    double timeDiff = time(begindate , begintime ,  endDate , endTime );
    
    double bar1 = barPressure(file[year1] , begindate ,begintime);
    double bar2 = barPressure(file[year2] , endDate ,endTime);

    double answer = (bar2 - bar1)/timeDiff;
    cout<<"the barometric pressure slope is: "<<answer<<endl;
    
};