#include <iostream>
#include <string>
#include <fstream>

#include "Member.h"
#include "House.h"
#include "Admin.h"
#include "System.h"
#include "Request.h"

using std::string;
using std::cout;
using std::cin;
// g++ Schiesser.cpp Admin.cpp Function.cpp House.cpp Member.cpp System.cpp Request.cpp; ./a
//.exe
int main() {
    System sys;

    Member ownerR;
    House huserR;

    vector<Member> vtmb; // I need it because otherwise we cannot modify the sys.getMemberList()
    vector<string> phonePacks; // each must be sent to each member in vtmb
     <%	// Mission : initialize phonePacks
		string line;
     	 std::ifstream myfile("requests.txt");
     	 if(myfile.is_open()){
     		 while(getline(myfile,line)){ // Important: getline won't get empty line
     			 phonePacks.push_back(line);
     		 }
     		 myfile.close();
     	 }


	 %>
    if(!sys.loadData()) {
        cout << "Fail to load data from database.";
        return -1;
    }
    for(Member m : sys.getMemberList()){
        	vtmb.push_back(m);
        }
    for(int i = 0; i < (int)vtmb.size(); i++){
    	vtmb[i].rq.requests = phonePacks[i];
    }

    while(1) { // String is concatnated using translation unit
        cout << "EEET2482/COSC2082 ASSIGNMENT\n"
                "VACATION HOUSE EXCHANGE APPLICATION\n\n"
                "Instructors: Mr. Linh Tran & Phong Ngo\n"
                "Group: Group Name\n"
                "s3916884, Kang Junsik\n"
                "s3864235, Lee Seungmin\n"
                "s3926977, Di Doan\n"
                "s3836278, Mai Le Anh Huy\n"
                "------------------------\n";
        cout << "Use the app as: \n";
        cout << "1. Guest    2. Member   3. Admin\n";
        cout << "Enter your choice: ";

        string choice;
        do {
            getline(cin, choice);
        } while (choice == "");

        if(choice == "1") { // customer chooses 'Guest'
            while(1) {
                cout << "------------------------\n"
                     << "This is guest menu: \n";
                cout << "0. Exit\n"
                     << "1. Registration\n"
                     << "2. View information of all houses\n";
                cout << "Enter your choice: ";

                string guestChoice;
                do {
                    getline(cin, guestChoice);
                } while (guestChoice == "");

                if(guestChoice == "0") { // Guest chooses 0. exit
                    cout << "GOODBYE!";
                    break;
                } else if(guestChoice == "1") {  // Guest chooses 1. Registration
                    Member doRegister;
                    Member newMember = doRegister.registration(sys.getMemberList()); // After registration,
                    sys.pushMemberList(newMember);
                    vtmb.push_back(newMember);
                    sys.pushHouseList(newMember.getHouse());
                    bool checkNewMember = true;
                    while(1) {
                        cout << "------------------------\n"   // go to member menu autonatically by system
                             << "This is member menu: \n";
                        cout << "0. Exit\n"
                                                  << "1. View the user information\n"
                                                  << "2. View all house information\n"
                                                  << "3. List / Unlist a house to be occupied\n"
                                                  << "4. Search for all available suitable houses for a particular city\n";

                                             cout << "Enter your choice: ";

                        string memberChoice;
                        do {
                            getline(cin, memberChoice);
                        } while (memberChoice == "");

                        if(memberChoice == "0") {
                            sys.saveAllData(checkNewMember, sys.getMemberList(), newMember);
                            <%
                             std::ofstream myfile;
                    	myfile.open("requests.txt");
                    	string res = "";


                    		for(Member m : vtmb){
                    			myfile << m.rq.requests;
                    			myfile << "\n";
                    		}



                    	myfile.close();
                            %>
                            cout << "GOODBYE!\n";
                            break;
                        } else if (memberChoice == "1") {
                            sys.showMyInfo(newMember);
                        } else if(memberChoice == "2") { // Member chooses 2. View all house information
                            sys.showAllHouseByMember(newMember, sys.getHouseList());
                        } else if(memberChoice == "3") { // Member chooses 3. List / Unlist a house to be occupied
                            newMember = sys.listHouseAvailable(newMember, sys.getHouseList());
                        } else if(memberChoice == "4") { // Member chooses 4. Search for all available suitable houses for a particular city
                            sys.searchAllAvailableHouses(newMember, sys.getHouseList());
                        }
                    }
                    break;
                } else if(guestChoice == "2") { // Guest chooses 2. View information of all houses
                    sys.showAllHouseByGuest(sys.getHouseList());
                } else { // Member chooses invalid option
                    cout << "You've choosen wrong option!\n"
                        << "------------------------\n";
                }
            }
            break;
        } else if(choice == "2") { // customer chooses 'Member'

            cout << "------------------------\n";
            Member loggedInMember = sys.loginByMember(sys.getMemberList(), sys.getHouseList());
            bool checkNewMember = false;
            for(Member m : vtmb){
            	if(m.rq.requests.find(loggedInMember.getphoneNumber()) != -1 and m.getHouse().getOccupied() == true){
            		printf("###Enjoy spending time with the house###\n");
            	}
            }
            menu:
            while(1) {
                cout << "------------------------\n"   // go to member menu after logged in successfully
                     << "This is member menu: \n";
                cout << "0. Exit\n"
                		"1. View the user information\n"
                		"2. View all house information\n"
                		"3. List / Unlist a house to be occupied\n"
                		"4. Search for all available suitable houses for a particular city\n"
                		//Huy
                		 "5. Request to occupy a house\n"
                		 "6. View and accept a request\n"
                		 "7. Check out the house you are occupying" "\n";
                cout << "Enter your choice: ";

                string memberChoice;
                do {
                    getline(cin, memberChoice);
                } while (memberChoice == "");

                if(memberChoice == "0") { // Member chooses 0. Exit

                    sys.saveAllData(checkNewMember, sys.getMemberList(), loggedInMember);
                    //Will save data of requestes (My convention <% %> is important)
                    <%

						std::ofstream myfile;
                    	myfile.open("requests.txt");
                    	string res = "";


                    		for(Member m : vtmb){
                    			myfile << m.rq.requests;
                    			myfile << "\n";
                    		}



                    	myfile.close();
					%>
                    cout << "GOODBYE!\n";
                    break;
                } else if(memberChoice == "1") { // Member chooses 1. View the user information
                    sys.showMyInfo(loggedInMember);
                } else if(memberChoice == "2") { // Member chooses 2. View all house information
                    sys.showAllHouseByMember(loggedInMember, sys.getHouseList());
                } else if(memberChoice == "3") { // Member chooses 3. List / Unlist a house to be occupied
                    loggedInMember = sys.listHouseAvailable(loggedInMember, sys.getHouseList());
                } else if(memberChoice == "4") { // Member chooses 4. Search for all available suitable houses for a particular city
                    sys.searchAllAvailableHouses(loggedInMember, sys.getHouseList());
                }
                //Huy works
                else if(memberChoice == "5"){
                	// Show all houses first then let the user choose
                	int i = 0;
                	vector<House> hvt = sys.getHouseList();
                	vector<House> res = {}; //
                	vector<Member> ownerlist = sys.getMemberList();
                	vector<Member> owner = {};
                	int iterations = 0;
                	// We need to see if this member is recorded on phonePacks
                	for(string s : phonePacks){
                		if(s.find(loggedInMember.getphoneNumber()) != -1){
                			cout<< "You have requested a house or have been occupying a house already and you cannot cancel that request!\n";
                			goto menu;
                		}
                	}
                	 for (House s: sys.getHouseList()){

                		 if(!s.getListed() ||
                	 loggedInMember.getHouse().getDescription() == s.getDescription()||
					(s.getOccupied())||
					(loggedInMember.getcredit()<s.getRequiredCredit())||
					(loggedInMember.getAvg()<s.getRequiredRating()))	// Filtered by requirements
                		 <%
						 	 iterations++;
                			 continue;
                		 %>

                	   	   cout <<  i + 1 << ": "<<s.getLocation() << ": "
                	   							   <<s.getDescription()<< std::endl
												   << "Requirements: " << "Required Credits: "<<s.getRequiredCredit()
												   << " Required Rating: "<<s.getRequiredRating()
												   << " Trial: "<<s.getStartPoint()<<'-'<<s.getEndPoint()<<'\n';
                		 res.push_back(s);
                		 owner.push_back(ownerlist[iterations]);
                		   iterations++;
                	   	   i++;

                	     }
                	 if(i==0){
                		 cout<<"There is no house suitable for you based on your credit and rating! \n";
                		 goto menu; // Bad practice but fine anyway
                	 }
                	 int pick = 0;
                	 House huser;
                	 again:
                	 cout<<"Choose a house to request base on the number: \n";
                	 cin>>pick;
                	 if(!(pick >= 1 && pick <= i)){
                		 goto again; // Bad practice but we will use it
                	 }
                	 // House is chosen
                	 huser = res[pick-1];
                     huserR = huser;
                     ownerR = owner[pick-1];
                	 //corresponding owner is owner[pick-1]


                	 // Show inner information of this house
                	 int sizeInfo = huser.getComment().size();
                	 int ratingInfo = huser.getRating().size();
                	 <%
					 if(sizeInfo==0){
						 cout<<"There is no comment just yet:\n";
					 }
                	 if(ratingInfo==0){
                		 cout<<"There is no rating just yet:\n";
                	 }
					 %>
                	  vector<int> ratehuser = huser.getRating();
                	 vector<string> commenthuser = huser.getComment();
                	 for(int i = 0; i<sizeInfo; i++){
                		 	cout<<"Rate: " << ratehuser[i] << " Comment: " << commenthuser[i] << std::endl;
                	 }
                	 ilikecheesetoast:
                	 char ans = ' ';
                	 cout<<"Do you want to occupy this house ? Y/N/M (menu): \n";
                	 cin>>ans;

                	 switch(ans){
                	 case 'Y' : case 'y' :

                	//	 cout<<owner[pick-1].rq.requests.at(0);
                		 owner[pick-1].setcredit(
                				 owner[pick-1].getcredit()+huser.getRequiredCredit());
                		// cout<<owner[pick-1].getusername();
                		 sys.phoneOwner = owner[pick-1].getphoneNumber();

                		 for(int i = 0; i < (int)sys.getMemberList().size(); i++){
                			 if(sys.getMemberList().at(i).getphoneNumber() == owner[pick-1].getphoneNumber()){
                				 vtmb.at(i).rq.requests += loggedInMember.getphoneNumber() + " ";
                				 //loggedInMember.getphoneNumber()

                				// cout<<vtmb.at(i).rq.requests.at(0);

                			 }
                		 }
                        // Wrong Because this will add and subtract credit BEFORE user is accepted, the fix is below
                		//  sys.requiredCreOwner = owner[pick-1].getHouse().getRequiredCredit();
                		//  loggedInMember.setcredit(
                		// 		 loggedInMember.getcredit()-huser.getRequiredCredit());
                        cout<<"Successfully occupy the house\n";

                	 break;
                	 case 'N' : case 'n' : {goto again;}
                	 case 'M' : case 'm' : break;
                	 default: goto ilikecheesetoast;
                	 }


                }
                else if (memberChoice == "6"){
                	loggedInMember.acceptRequest(vtmb);
                    sys.requiredCreOwner = ownerR.getHouse().getRequiredCredit();
                		 loggedInMember.setcredit(
                				 loggedInMember.getcredit()-huserR.getRequiredCredit());
                }
                else if(memberChoice == "7"){
                    for(Member m : vtmb){
                        if(m.rq.requests.find(loggedInMember.getphoneNumber()) != -1 and m.getHouse().getOccupied()){
                            sys.phoneOwner = m.getphoneNumber();
                        }
                    }
                	if(sys.phoneOwner == ""){
                        printf("You are not occupying any house yet\n");
                        goto menu;
                    }
                    for(Member &m : vtmb){
                        if(m.getphoneNumber() == sys.phoneOwner){
                            // m is now an owner
                            m.rq.requests = "";
                            m.getHouse().changeOccupied();
                            printf("Successfully check out the current house, Please leave rating and comment to the house:"); // Di part
                            goto menu;
                        }
                    }
                }

            }
            break;
        } else if(choice == "3") { // customer chooses 'Admin'
            sys.loginByAdmin();
            while(1) {
                cout << "------------------------\n"
                     << "This is admin menu: \n";
                cout << "0. Exit\n"
                     << "1. View all user/house information\n";
                cout << "Enter your choice: ";

                string adminChoice;
                do {
                    getline(cin, adminChoice);
                } while (adminChoice == "");

                if(adminChoice == "0") { // Member chooses 0. Exit
                    cout << "GOODBYE!";
                    break;
                } else if(adminChoice == "1") { // Member chooses 1. View all user/house information
                    sys.showAllInfo(sys.getMemberList());
                } else { // Member chooses invalid option
                    cout << "You've choosen wrong option!\n"
                         << "------------------------\n";
                }
            }
            break;
        } else { // customer chooses invalid option
            cout << "You've choosen wrong option!\n"
                 << "------------------------\n";
        }
    }
}
