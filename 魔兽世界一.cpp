#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

int t;
int total_resource;

class Servant
{
private:
	string name;
public:
	int strength;
	Servant(string s, int n) :name(s), strength(n) {};
	string get_name() {
		return name;
	}
	virtual ~Servant() {};
};

class Dragon : public Servant {
public:
	static int base_strength;
	Dragon() :Servant("dragon", base_strength) {};
};

class Ninja : public Servant {
public:
	static int base_strength;
	Ninja() :Servant("ninja", base_strength) {};
};

class Iceman : public Servant {
public:
	static int base_strength;
	Iceman() : Servant("iceman", base_strength) {};
};

class Lion : public Servant {
public:
	static int base_strength;
	Lion() : Servant("lion", base_strength) {};
};

class Wolf :public Servant {
public:
	static int base_strength;
	Wolf() :Servant("wolf", base_strength) {};
};

int warriors_cost[5];
int Dragon::base_strength = 0;
int Ninja::base_strength = 0;
int Iceman::base_strength = 0;
int Lion::base_strength = 0;
int Wolf::base_strength = 0;


class Faction {
private:
	string faction_name;
	int total_num;
	map<string, int> unit_num;

public:
	int total_resource;
	int cur_idx = 0;

	Faction(string s, int n) : faction_name(s), total_resource(n), total_num(0) {};

	string get_faction_name() {
		return faction_name;
	}

	Servant* make_warrior(int id) {
		switch (id) {
		case 0: return new Dragon();
		case 1: return new Ninja();
		case 2: return new Iceman();
		case 3: return new Lion();
		case 4: return new Wolf();
		}
	}


	void recruit(Servant* s) {
		total_num++;
		unit_num[s->get_name()]++;

		int tmp_n = unit_num[s->get_name()];

		printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
			t, faction_name.c_str(), s->get_name().c_str(), total_num, s->strength,
			tmp_n, s->get_name().c_str(), faction_name.c_str());
	}
};

int red_order[] = { 2,3,4,1,0 };
int blue_order[] = { 3,0,1,2,4 };

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> total_resource;
		cin >> Dragon::base_strength >> Ninja::base_strength >> Iceman::base_strength >>
			Lion::base_strength >> Wolf::base_strength;
		warriors_cost[0] = Dragon::base_strength,warriors_cost[1] = Ninja::base_strength;
		warriors_cost[2] = Iceman::base_strength;
		warriors_cost[3] = Lion::base_strength;
		warriors_cost[4] = Wolf::base_strength;

		cout << "Case:" << i << endl;
		// 红方阵营
		Faction redFaction("red", total_resource);

		// 蓝方阵营
		Faction blueFaction("blue", total_resource);

		//初始化状态
		bool red_end = false;
		bool blue_end = false;
		// 初始化时间
		t = 0;
		while (true) {
			// 红方
			if (!red_end) {
				bool red_exhausted = true;
				for (int count = 0; count < 5; count++) {
					int current_id = red_order[redFaction.cur_idx];
					if (redFaction.total_resource >= warriors_cost[current_id]) {
						redFaction.total_resource -= warriors_cost[current_id];
						redFaction.recruit(redFaction.make_warrior(current_id));

						redFaction.cur_idx = (redFaction.cur_idx + 1) % 5;
						red_exhausted = false;
						break;
					}
					else {
						redFaction.cur_idx = (redFaction.cur_idx + 1) % 5;
					}
				}

				// 判断红方有无余力
				if (red_exhausted) {
					red_end = true;
					printf("%03d %s headquarter stops making warriors\n",
						t, redFaction.get_faction_name().c_str());
				}
			}

			// 蓝方
			if (!blue_end) {
				bool blue_exhausted = true;
				for (int count = 0; count < 5; count++) {
					int current_id = blue_order[blueFaction.cur_idx];
					if (blueFaction.total_resource >= warriors_cost[current_id]) {
						blueFaction.total_resource -= warriors_cost[current_id];
						blueFaction.recruit(blueFaction.make_warrior(current_id));

						blueFaction.cur_idx = (blueFaction.cur_idx + 1) % 5;
						blue_exhausted = false;
						break;
					}
					else {
						blueFaction.cur_idx = (blueFaction.cur_idx + 1) % 5;
					}
				}

				// 判断蓝方有无余力
				if (blue_exhausted) {
					blue_end = true;
					printf("%03d %s headquarter stops making warriors\n",
						t, blueFaction.get_faction_name().c_str());
				}
			}

			// 终判定
			if (red_end && blue_end) break;

			//更新
			t++;
		}

		cout << endl;
	}

	return 0;
}