#include <iostream>
#include<windows.h>
#include<mysql.h>
using namespace std;
int main(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","driving_license",0,NULL,0);
    char* query="CREATE TABLE PERSON_DETAILS( aadhar_num int primary key, name varchar(20), DOB date,mobile int ,  address varchar(20))";
    int qstate= mysql_query(conn, query);
    query=" CREATE TABLE OFFICER_DATA( officer_id  int primary key , name varchar(20) , position varchar(20))";
    qstate= mysql_query(conn, query);
    query="CREATE TABLE OFFICER_ASSIGNED( aadhar_num int,  officer_id int , primary key(aadhar_num , officer_id) , foreign key(officer_id) references officer_data(officer_id), foreign key(aadhar_num) references person_details(aadhar_num) )";
    qstate= mysql_query(conn, query);
    query=" CREATE TABLE LICENSE_DETAILS( license_num int primary key, issue_date date, expiry_date date, state varchar(20), license_type varchar(10)  , aadhar_num int , foreign key(aadhar_num) references person_details( aadhar_num) ) ";
    qstate= mysql_query(conn, query);
    query="INSERT INTO OFFICER_DATA VALUES ( 11, 'RAM', 'high') , ( 12, 'SHYAM' , 'low'), (13 , 'CHANDANLAL', 'intermediate'), (14, 'MANDANLAL', 'intermediate') ";
    qstate= mysql_query(conn,query);
    query="INSERT INTO OFFICER_DATA VALUES (15 , 'CHANDANLAL', 'head') ";
    qstate= mysql_query(conn,query);
    query="CREATE TABLE LICENSE_STAT( license_num int , status varchar(20), primary key(license_num , status),foreign key(license_num) references license_details(license_num)   )";
    qstate= mysql_query(conn,query);
    query= "INSERT INTO PERSON_DETAILS VALUES ( 123, 'ARYAN', '2003-04-23', '992342342', 'STREET-1023' ),( 132, 'ANKIT', '2002-08-14', '953435633', 'STREET-6434' ), ( 432, 'CHAITANYA', '2004-11-11', '995428687', 'STREET-1773' ), ( 843, 'SAKSHAM', '2004-10-30', '343234323', 'STREET-7908' ), ( 664, 'HARSH', '2001-04-01', '977773423', 'STREET-9998' ), ( 983, 'PAVITRA', '2000-12-22', '998876542', 'STREET-0002' )";
    qstate= mysql_query(conn, query);
    query="INSERT INTO PERSON_DETAILS VALUES(223, 'PRASHANT', '2013-09-19', 998376549, 'STREET 420')";
    qstate= mysql_query(conn, query);
    query="INSERT INTO LICENSE_DETAILS VALUES ( 80, '2019-08-24', '2026-09-03', 'DELHI', 'LMV', 132 ), ( 81, '2018-03-14', '2030-09-13', 'DELHI', 'LMV', 123 ), ( 82, '2016-04-29', '2023-01-04', 'MAHARASHTRA', 'HMV', 432 ), ( 83, '2012-08-19', '2027-12-23', 'DELHI', 'MCWG', 123 ), ( 84, '2020-09-09', '2024-11-14', 'KERALA', 'MCWOG', 843 ),( 85, '2017-10-18', '2028-09-06', 'MAHARASHTRA', 'LMV', 664 ), (86, '2018-07-30', '2019-03-31', 'GUJRAT', 'COMMERCIAL', 223)";
    qstate=mysql_query(conn, query);
    query="INSERT INTO LICENSE_STAT VALUES (80, 'APPROVED'), (81, 'APPROVED'), (82, 'PENDING'), (83, 'APPROVED'), (84,'DENIED'), (85, 'APPROVED'), (86, 'PENDING')";
    qstate=mysql_query(conn, query);
    query="INSERT INTO OFFICER_ASSIGNED VALUES( 123, 13 ), (132, 14), (432,12),(843, 11), (664, 13), (223,14)";
    qstate= mysql_query(conn, query);
    cout<< "APPROVED LICENSE AND HOLDER DETAILS: "<<endl;
    query="select person_details.name ,person_details.address,person_details.dob, person_details.mobile, license_details.license_type, license_stat.status from person_details,license_stat,license_details where person_details.aadhar_num=license_details.aadhar_num and license_details.license_num=license_stat.license_num AND license_stat.status='approved';" ;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<< "NAME:"<<row[0]<<"  "<<"ADDRESS:"<< row[1] <<"  "<<"DOB:"<<row[2]<<"  "<<"MOBILE:"<< row[3]<<"  "<<"TYPE:"<<row[4]<<"  "<<"STATUS:"<< row[5] <<endl;    }
    cout<< endl;
    cout<< "PEOPLE WITH PENDING LICENSE: "<< endl;
    query="select name,  address, dob , mobile from person_details where aadhar_num in(select aadhar_num from license_details , license_stat where license_details.license_num=license_stat.license_num AND license_stat.status='PENDING'  )" ;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"NAME:"<< row[0]<<"  "<<"ADDRESS:"<< row[1] << "  "<<"DOB:"<< row[2] <<"  "<<"MOBILE:"<< row[3]<< endl;}
    cout<<endl<< "PEOPLE WITH NO LICENSE: "<< endl;
    query="select name, address ,dob,  mobile from person_details where aadhar_num in(select aadhar_num from license_details , license_stat where license_details.license_num=license_stat.license_num AND license_stat.status='DENIED'  )" ;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    { cout<<"NAME:"<< row[0]<<"  "<<"ADDRESS:"<< row[1]<<"  "<<"DOB:"<< row[2] <<"  "<<"MOBILE:"<< row[3]<< endl;}
    query="select name, address , dob , mobile from person_details where aadhar_num  not in(select aadhar_num from license_details)" ;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"NAME:"<< row[0]<<"  "<<"ADDRESS:"<< row[1]<<"  "<<"DOB:"<< row[2]<< "  "<< "MOBILE:"<< row[3]<<endl;}
    cout<< endl;
    query="select person_details.name , officer_data.name, officer_data.officer_id from person_details,officer_data , officer_assigned where person_details.aadhar_num=officer_assigned.aadhar_num and officer_assigned.officer_id=officer_data.officer_id order by person_details.name" ;
    cout<< "DETAILS OF OFFICER ASSIGNED TO EACH LICENSE HOLDER:"<< endl;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"HOLDER:" <<row[0]<<"     "
            << "OFFICER ASSIGNED:"<<row[1]  <<"     "
            << "OFFICER ID:"<< row[2] <<endl;}
    cout<< endl;
    query="select p.name , license_stat.status from person_details p , license_details l , license_stat  where p.aadhar_num= l.aadhar_num and l.license_num=license_stat.license_num and l.issue_date>'2018-01-01'  ";
    cout<< "LIST OF ALL LICENSE ISSUED AFTER THE YEAR 2018:"<< endl;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    { cout<<"HOLDER:" <<row[0]<<"  "<<"STATUS:"<<row[1]<<endl;}
    cout<< endl;
  query="select p.name ,p.mobile, od.name, od.position from person_details p, officer_data od , officer_assigned oa where p.aadhar_num= oa.aadhar_num and od.officer_id=oa.officer_id and od.name='CHANDANLAL' ";
qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"HOLDER:" <<row[0]<<"  "<<"MOBILE:"<<row[1]<<"  " <<"OFFICER:"<< row[2]<<"  "<<"POSITION:"<<row[3]<<endl;}
    cout<< endl;
    query="select p.name,floor(DATEDIFF(now(), p.dob) /365) from person_details p where (DATEDIFF(now(), p.dob) /365)< 18 ";
    cout<< "LIST OF APPLICANTS YOUNGER THAN 18:" << endl;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    { cout<<"NAME:" <<row[0] <<"  " << "AGE:"<<  row[1]<<endl; }
    cout<< endl;
    query="select p.name, floor(DATEDIFF(now(), p.dob) /365)  from person_details p where (DATEDIFF(now(), p.dob) /365)>18 ";
    cout<< "LIST OF APPLICANTS OLDER THAN 18:" << endl;
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"NAME:" <<row[0] <<"  " << "AGE:"<<  row[1]<<endl;}
    cout<< endl;
   query="update license_details L set L.license_type='MCWOG' where L.license_num=84";
 qstate=mysql_query(conn, query);
  //query="UPDATE license_details L set L.license_type='MCWG' where L.license_type='MCWOG' ";
 //qstate= mysql_query(conn, query);
    cout<< "CHANGE LICENSE TYPE MCWOG TO MCWG FOR ALL-" ;
    query="select count(license_type) from license_details where license_details.license_type='MCWOG' ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<"TOTAL COUNT:" <<row[0] <<endl;}
    cout<< endl;

    cout<< "FUNCTIONAL DEPENDENCY ON LICENSE_NUM AND AADHAR_NUM FOR TABLE- LICENSE DETAILS" << endl;
    query="select * from license_details limit 5 ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
      {cout<<row[0] <<" "<<row[1] <<" "<<row[2] <<" "<<row[3] <<" "<<row[4] <<" "<<row[5] <<" "<<endl;}
    cout<< endl;
    cout<< "FUNCTIONAL DEPENDENCY ON LICENSE_NUM FOR TABLE- LICENSE STAT" << endl;
    query="select * from license_stat limit 5 ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<row[0] <<" "<<row[1] <<" "<<endl;}
    cout<< endl;

    cout<< "FUNCTIONAL DEPENDENCY ON LICENSE_NUM AND AADHAR_NUM FOR TABLE- PERSON DETAILS" << endl;
    query="select * from person_details limit 5 ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<row[0] <<" "<<row[1] <<" "<<row[2] <<" "<<row[3] <<" "<<row[4] <<" "<<endl;}
    cout<< endl;

      cout<< "FUNCTIONAL DEPENDENCY ON OFFICER ID FOR TABLE- OFFICER DATA" << endl;
    query="select * from officer_data limit 5 ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<row[0] <<" "<<row[1] <<" "<<row[2] <<" "<<endl;}
    cout<< endl;
    cout<< "FUNCTIONAL DEPENDENCY ON AADHAR_NUM AND OFFICER ID FOR TABLE- OFFICER ASSIGNED" << endl;
    query="select * from officer_assigned limit 5 ";
    qstate= mysql_query(conn, query);
    res=mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {cout<<row[0] <<" "<<row[1] <<" "<<endl;}
    cout<< endl;
    return 0;
}














