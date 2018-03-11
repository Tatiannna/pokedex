#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

//Reads pokemon and descriptions from file pokedex.txt and allows user to enter a pokemon name and have description and stats displayed until 
//user enters "done"

class Pokemon;
class Type
{
public:
	Type (string& name): name(name) {}
	string getName() const {return name;}
	void addPokemon (Pokemon& poke){pokemon.push_back(&poke);}
	void display() const;
	
private:
	string name;
	vector<Pokemon*> pokemon;
};


class Pokemon
{
public:
	Pokemon(string& number, string& name, string& description, string& stats, string& preEvo, string& postEvo, string& otherForms) :
		pokeNum(number), name(name), description(description), stats(stats), preEvo(preEvo), postEvo(postEvo), otherForms (otherForms),
		type1(NULL), type2(NULL) {}
	string getName () {return name;}
	void SetType1(Type* t) {type1 = t;}
	void SetType2(Type* t) {type2 = t;}
	void display() const
	{
		cout << "\n\n-----------------\n" << pokeNum << endl << name << endl << "The " << description << " pokemon\n\nType: " << type1->getName();
		if (type2)
			cout << "/" << type2->getName();

		istringstream iss(stats);
		string temp;
		vector<string> allStats;

		while (iss >> temp)
		{
			allStats.push_back(temp);
		}
		cout << "\n\nMaximum Stats:\n\nHP: " << allStats[0] << "\nAttack: "<< allStats[1] << "\nDefense: " << allStats[2] << "\nSp. Atk: " 
			 << allStats[3] << "\nSp.Def: " << allStats[4] << "\nSpeed: " << allStats[5] << endl << endl;

		cout << "Pre-evolution: " << preEvo << endl << "Post-Evolution: " << postEvo << endl << "Alternate Forms: " << otherForms << "\n-----------------\n\n";
	}
private:
	string pokeNum;
	string name;
	string description;	
	string stats;

	string preEvo;
	string postEvo;
	string otherForms;
	Type* type1;
	Type* type2;
};

void Type::display() const
{
	for (size_t i = 0; i < pokemon.size(); i++)
		cout << pokemon[i]->getName() << endl;
}

void openFileAndFillVector (ifstream& ifs, ifstream& ifs2, vector<Pokemon>& pokemon, vector<Type>& types)
{
	string number;
	string name;
	string description;
	string type;
	string pre;
	string post;
	string otherForms;
	string stats;
	string junk;

	ifs2.open("types.txt");
	
	if(ifs2.fail())
	{
		cout << "error opening types file!\n\n";
		exit (1);
	}
	
	string aType;
	while (ifs2 >> aType)
	{
		Type t(aType);
		types.push_back(t);
	}


	ifs.open("pokedex.txt");
	if(ifs.fail())
	{
		cout << "error opening pokedex file!\n\n";
		exit (1);
	}

	while ( getline(ifs, number) )
	{
		getline(ifs,name);
		getline(ifs, description);
		getline(ifs, type);
		getline(ifs, stats);
		getline(ifs, pre);
		getline(ifs, post);
		getline(ifs, otherForms);
		getline(ifs, junk);

		Pokemon poke (number, name, description, stats, pre, post, otherForms);
		pokemon.push_back(poke);

		istringstream iss(type);
		string tempType;

		unsigned count(0);
		while (iss >> tempType)
		{
			count++;
			for(size_t i = 0; i< types.size() ; i++)
			{
					if(tempType == types[i].getName())
					{
						types[i].addPokemon(pokemon[pokemon.size()-1]);
						if (count == 1)
						{ 
							pokemon[pokemon.size()-1].SetType1(&types[i]);
						}
						else 
						{
							pokemon[pokemon.size()-1].SetType2(&types[i]);
						}
					}
			}
		}
		
	}
}


void getUsersRequest( vector<Pokemon> & pokemon, vector<Type>& types)
{
	string name;

	cout << "Pokemon: ";
	cin >> name;

	if (name == "done")
	{
		cout << "\n\n* * * Thanks for using the program! * * * \n\n\n\n\n";
		exit (0);
	}
	
	unsigned count(0);

	for (size_t i = 0; i < types.size(); i++)
	{
		if (types[i].getName() == name)
		{
			count++;
			cout << "Here are all the pokemon of the " << name << " type:\n\n";
			types[i].display();
		}
	}
	if (count == 0)
	{
		for (size_t i = 0; i < pokemon.size() ; i++)
		{
			if (name == pokemon[i].getName())
			{
				pokemon[i].display();
				cout << endl;
				break;
			}
		}	
		cout << "\nError: pokemon not found\n\n\n";
	}
}


int main()
{
	ifstream ifs, ifs2;
	vector<Pokemon> pokemon;
	vector<Type> types;
	//string poke;
	//int tempCount(0);

	openFileAndFillVector( ifs, ifs2, pokemon, types);

	while(true)
	{
		getUsersRequest(pokemon, types);
	}
}