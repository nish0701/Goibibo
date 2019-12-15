#include<bits/stdc++.h>

using namespace std;

class kingdom{

	static int rule_id;
	static int dragon_id;
	map<int, pair<long long int,int > > rules;
	map <int,int> rules_rec;

	map <int,string> dragons;
	map <int, vector <pair < double,int > > > kills;

	public:

		kingdom(){
			cout<<"Welcome to the House Targaryen\n";
		}

		void inputRule(int, int);
		void showRules();
		void deleteRule(int);
		void registerDragon(string);
		void killAnimals(int dragonId, int animals, string timestamp);
		double getHours(string timestamp);
		long long int getDays(int, int, int);
};

int kingdom :: rule_id = 0;

int kingdom :: dragon_id = 0;

// Helper function to calculate the number of hours.
double kingdom :: getHours(string timestamp){
	int year, month, date, hours, minutes;

	int len  = timestamp.length();
	string format = "YYYY-MM-DD-HH:MM";
	if(len != format.length()){
		cout<<"Date is in invalid format.\n";
		return -1;
	}
	string dS = "", yS = "", mS = "", hS = "", minS = "";
	int i =0;
	while(i < len && timestamp[i] != '-'){
		yS += timestamp[i];
		i++;
	}
	i++;

	while(i < len && timestamp[i] != '-'){
		mS += timestamp[i];
		i++;
	}

	i++;

	while(i < len && timestamp[i] != '-')
	{
		dS += timestamp[i];
		i++;
	}
	i++;

	while(i < len && timestamp[i] != ':'){
		hS += timestamp[i];
		i++;
	}
	i++;

	while(i < len){
		minS += timestamp[i];
		i++;
	}

	if(!(yS.length() == 4 && (mS.length() == 2 && dS.length() == 2 && hS.length() == 2 && minS.length() == 2))){
		cout<<"Invalid date format\n";
		// cout<<"ys length is "<<yS.length()<<' '<<mS.length()<<" "<<dS.length()<<" "<<hS.length()<<" "<<minS.length()<<'\n';
		return -1;
	}



	date = (dS[0] - '0')*10 + (dS[1] - '0');
	month = (mS[0] - '0')*10 + (mS[1] - '0');
	year = (yS[0] - '0')*1000 + (yS[1] - '0')*100 + (yS[2] - '0')*10 + (yS[3] - '0');
	hours = (hS[0] - '0') *10 + (hS[1] - '0');
	minutes = (minS[0] - '0') *10 + (minS[1] - '0');

	if(year < 2000 || year > 2010){
		cout<<"Year should be greater than 2000 and less than 2011\n";
		return -1;
	}


	long long int days = getDays(year,month,date);
	if(days < 0 || hours > 24 || minutes > 59){
		cout<<"Invalid Timestamp\n";
		return -1;
	}
	cout<<"days = "<<days<<" hours = "<<hours<<" mins = "<<minutes<<'\n';
	double ans = (days*24) + (hours)+ (minutes/60.0);
	double min = minutes/60.0;
	// cout<<"Minutes obtained are "<<min;
	// cout<<"\nFinal hours being obtained are : "<<ans<<'\n';
	return ans;
}

// Helper function to calculate the number of days between '2000-01-01:00:00' and given time stamp
long long int kingdom :: getDays(int year, int month, int date){
	const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// cout<<"\n year passed is "<<year<<'\n';
	if(month > 12 || date > monthDays[month - 1])
		return -1;
	int yD = year - 2000;
	// cout<<"\nyD is "<<yD<<'\n';
	int mD = month - 1;
	int dD = date - 1;

	long long int days = yD * 365 + dD;

	for(int i=0; i<mD; i++){
		days += monthDays[i];
	}

	return days;
}

// Function to input rule

void kingdom :: inputRule(int hours, int animals){
	if(rules.find(hours) != rules.end()){
		cout<<"Rule for the given hour already exists! Failed to create rule.\n";
		return;
	}

	map<int,pair <long long int, int> > :: iterator it;
	for(it = rules.begin(); it != rules.end(); it++){
		if(it->first < hours && (it->second).first > animals || it->first > hours && (it->second).first < animals){
			cout<<"Given rule is violating with rule number "<<(it->second).second<<"as existing rule states in "<<it->first<<"hours only "<<(it->second).first<<"animals are allowed to be killed."<<'\n';
			return;
		}
	}

	rule_id++;
	rules[hours] = make_pair(animals,rule_id);
	rules_rec[rule_id] = hours;

	cout<<"Rule created with rule ID : "<<rule_id<<'\n';
}

// Function to show already existing rules.

void kingdom :: showRules(){
	cout<<"Format is => RuleID: Hours: Animals\n";
	map<int,pair<long long int,int> > :: iterator it;

	for(it = rules.begin(); it != rules.end(); it++){
		cout<<(it->second).second<<" : "<<it->first<<" : "<<(it->second).first<<'\n';
	}
}

// Function to delete an existing rule.

void kingdom :: deleteRule(int ruleId){
	if(rules_rec.find(ruleId) == rules_rec.end()){
		cout<<"inavlid ruleId\n";
		return;
	}

	int h = rules_rec[ruleId];
	rules_rec.erase(ruleId);
	rules.erase(h);
	cout<<"Rule has been successfuly deleted\n";
}

// Function to register a dragon
void kingdom :: registerDragon(string name){
	dragon_id++;
	dragons[dragon_id] = name;

	cout<<"Dragon Sucessfuly registered with Dragon ID : "<<dragon_id<<'\n';
	return;
}

// function to order killing animals

void kingdom :: killAnimals(int dragonId, int animals, string timestamp){
	if(dragons.find(dragonId) == dragons.end())
	{
		cout<<"Invalid Dragon Id. Couldn't execute!\n";
		return;
	}

	double executionHours = getHours(timestamp);
	// cout<<"\nExecution hours obtained here are "<<executionHours<<'\n';
	if(executionHours < 0){
		return;
	}
	cout<<"Hours obtained are "<<executionHours<<'\n';

	if(kills.find(dragonId) != kills.end()){
		int n = kills[dragonId].size();
		if((kills[dragonId][n-1]).first > executionHours){
			cout<<"TimeStamp must be greater than the last executed killing.\n";
			return;
		}
		else{
			map <int, pair<long long int, int> > :: iterator it;
			bool flag = 1;
			for(it = rules.begin(); it!=rules.end(); it++){
				int tLimit = it->first;
				int allowed = (it->second).first;
				long long int diff = executionHours - tLimit;
				int i = n-1;
				bool flag = 0;
				vector<pair<double, int> > arr = kills[dragonId];
				int count = animals;
				while(i>=0 && arr[i].first > diff){
					flag = 1;
					count += arr[i].second;
					i--;
				}
				if(allowed < count){
					cout<<"Failed as rules are being violated\n";
					return;
				}
			}
			kills[dragonId].push_back(make_pair(executionHours, animals));
			cout<<"Successfuly executed. Animals were killed.\n";
			vector<pair<double, int> > arr = kills[dragonId];
			for(int i=0; i<arr.size(); i++){
				cout<<"\n--"<<arr[i].first<<"-- "<<arr[i].second<<'\n';
			}
			return;
		}
	}

	else{
		if(animals <= (rules.begin()->second).first){
			kills[dragonId].push_back(make_pair(executionHours, animals));
			cout<<"successfuly executed\n";
		}
		else{
			cout<<"Failed as rule: "<<rules.begin()->first<<"are being violated\n";
		}
	}
}

int main(){
	kingdom k;
	int option;
	while(true){
		cout<<"Please select your command\n";
		cout<<"Options Number : Option\n";
		cout<<"1 : Define a new rule\n";
		cout<<"2 : Delete a rule\n";
		cout<<"3 : Register a Dragon\n";
		cout<<"4 : Request to kill an animal\n";
		cout<<"5 : Show existing rules\n";

		cin>>option;

		if(option == 1){
			int hours, animals;
			cout<<"Defining a new rule\n";
			cout<<"Enter Hours : ";
			cin>>hours;
			cout<<'\n';
			cout<<"Enter animals allowed to kill : ";
			cin>>animals;
			cout<<'\n';
			k.inputRule(hours, animals);
		}

		else if(option == 2){
			cout<<"Deleting an existing rule\n";
			cout<<"Please select the rule id for the rule you want to delete\n";
			k.showRules();
			cout<<"Please select the RuleId.\n";
			int choice;
			cin>>choice;
			k.deleteRule(choice);
		}

		else if(option == 3){
			cout<<"Register A Dragon!\n";
			string dragonName;
			cout<<"Enter the Name of the dragon\n";
			cin>>dragonName;
			k.registerDragon(dragonName);
		}

		else if(option == 4){
			 cout<<"Requesting dragon to kill animals\n";
			 int dId, noAnimals;
			 string timestamp;
			 cout<<"Enter dragon's ID: ";
			 cin>>dId;
			 cout<<"\n Enter No. of Animals to be executed : ";
			 cin>>noAnimals;
			 cout<<"\n Enter the timestamp int the format (YYYY-MM-DD-HH:MM). Year should be greater than 1999 and less than 2011\n";
			 cin>>timestamp;
			 k.killAnimals(dId, noAnimals, timestamp);
		}

		else if(option == 5){
			cout<<"Showing existing rules\n";
			k.showRules();
		}
		else{
			cout<<"Invalid option! Try Again.\n";
		}
	}
}
