#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <unordered_set>

using namespace std;

class Weapon {
public:
	string name;
	int type;
	int atk;

	Weapon(const char* s, int t, int n) :name(s), type(t), atk(n) {};
	virtual void use() = 0;
	virtual bool empty() = 0;
	virtual int getCnt() { return 0; }
	virtual ~Weapon() {};
};

class sword : public Weapon {
public:
	sword(int n) :Weapon("sword", 0, n) {};
	void use() {};
	bool empty() {
		return false;
	}
};

class bomb : public Weapon {
public:
	bool used = false;

	bomb(int n) :Weapon("bomb", 1, n) {};
	void use() override {
		used = true;
	}
	bool empty() override {
		return used;
	}
};

class arrow : public Weapon {
public:
	int cnt = 2;

	arrow(int n) :Weapon("arrow", 2, n), cnt(2) {};
	int getCnt() override { return cnt; }
	void use() override {
		cnt--;
	}
	bool empty() override {
		return !cnt;
	}
};

Weapon* makeWeapon(int t, int ATK) {
	if (t == 0) return new sword(ATK * 2 / 10);
	else if (t == 1) return new bomb(ATK * 4 / 10);
	else return new arrow(ATK * 3 / 10);
}

class Warrior {
public:
	int id;
	int hp;
	int atk;
	int city = 0;
	int tmp = 0;

	string type;
	string faction;

	vector<Weapon*> weapons;
	unordered_set<Weapon*> taken;

	Warrior(int id, int hp, int atk, string f, string t) :id(id), hp(hp), atk(atk),
		faction(f), type(t) {
	};
	/*virtual void move();*/
	/*virtual void battle();*/
	virtual void reportWeapon() {};
	virtual void printBornExtra() {};
	virtual bool runaway() { return false; }
	virtual void weaponSort();
	bool hasWeapon() {
		for (auto w : weapons) {
			if (w && !w->empty()) return true;
		}
		return false;
	}
	Weapon* nextWeapon(int& p) {
		int n = weapons.size();
		if (n == 0) return nullptr;
		for (int i = 0; i < n; i++) {
			int idx = (p + i) % n;
			if (weapons[idx] && !weapons[idx]->empty()) {
				p = (idx + 1) % n;
				return weapons[idx];
			}
		}
		return nullptr;
	}
	bool use_weapon(Warrior* attacker, Warrior* defender, Weapon* w) {
		if (!w || w->empty()) return false;
		int pre_ahp = attacker->hp, pre_dhp = defender->hp;
		bool state_changed = false;

		if (w->name == "sword") {
			defender->hp -= attacker->atk * 2 / 10;
		}
		else if (w->name == "bomb") {
			int dmg = attacker->atk * 4 / 10;
			defender->hp -= dmg;
			if (attacker->type != "ninja") attacker->hp -= dmg / 2;
			w->use();
			state_changed = true;
		}
		else {
			defender->hp -= attacker->atk * 3 / 10;
			w->use();
			state_changed = true;
		}

		if (pre_ahp != attacker->hp || pre_dhp != defender->hp) state_changed = true;
		return state_changed;
	}
	void removeWeapon() {
		for (auto& w : weapons) {
			if (!w) continue;
			if (w->empty()) {
				delete w;
				w = nullptr;
			}
		}
		weapons.erase(
			remove(weapons.begin(), weapons.end(), nullptr),
			weapons.end()
		);
	}
	void disarm(Warrior* other);
	virtual int& getLoyalty() { return tmp; }
	virtual void wolfRob(Warrior* other) {};

	virtual ~Warrior() {};
};

class Dragon : public Warrior {
public:
	/*double morale;*/

	Dragon(int id, int hp, int atk, string f) :Warrior(id, hp, atk, f, "dragon") {
		weapons.push_back(makeWeapon(id % 3, atk));
	}

	void reportWeapon() override {};
};

class Ninja : public Warrior {
public:
	Ninja(int id, int hp, int atk, string f) :Warrior(id, hp, atk, f, "ninja") {
		weapons.push_back(makeWeapon(id % 3, atk));
		weapons.push_back(makeWeapon((id + 1) % 3, atk));
	}
};

class Iceman : public Warrior {
public:
	Iceman(int id, int hp, int atk, string f) : Warrior(id, hp, atk, f, "iceman") {
		weapons.push_back(makeWeapon(id % 3, atk));
	}
};

class Lion : public Warrior {
public:
	int loyalty;

	Lion(int id, int hp, int atk, string f, int l) :Warrior(id, hp, atk, f, "lion"), loyalty(l) {
		weapons.push_back(makeWeapon(id % 3, atk));
	}
	void printBornExtra() {
		printf("Its loyalty is %d\n", loyalty);
	}
	void reportWeapon() override {

	}
	int& getLoyalty() override { return loyalty; }
	bool runaway() {
		return (loyalty <= 0);
	}
};

class Wolf :public Warrior {
public:
	Wolf(int id, int hp, int atk, string f) :Warrior(id, hp, atk, f, "wolf") {};
	virtual void wolfRob(Warrior* other) {
		if (!other->hasWeapon()) return;
		vector<Weapon*> loot;
		for (auto w : other->weapons) {
			if (w && !w->empty()) loot.push_back(w);
		}

		sort(loot.begin(), loot.end(),
			[](Weapon* a, Weapon* b) {
				if (a->type != b->type) return a->type < b->type;
				if (a->type == 2) return a->getCnt() > b->getCnt();
				return false;
			});

		taken.clear();
		if (loot.empty()) return;
		int minT = loot[0]->type;
		for (auto w : loot) {
			if (w->type == minT && weapons.size() < 10) {
				weapons.push_back(w);
				taken.insert(w);
			}
			else break;
		}

		vector<Weapon*> remain;
		for (auto w : other->weapons) {
			if (!taken.count(w)) remain.push_back(w);
		}
		other->weapons = remain;
	}
};

enum class WarriorType { Dragon, Ninja, Iceman, Lion, Wolf };

class City {
public:
	int id;

	Warrior* red = nullptr;
	Warrior* blue = nullptr;
};

class Headquarter {
public:
	string name;
	int total_hp;

	int cur_id = 0;
	bool stopped = false;

	WarriorType order[5];

	Warrior* produce();

	int total_num = 0;
	map<string, int> count;

	Headquarter(string s, int m) :name(s), total_hp(m) {
		if (s == "red") {
			order[0] = WarriorType::Iceman, order[1] = WarriorType::Lion, order[2] = WarriorType::Wolf,
				order[3] = WarriorType::Ninja, order[4] = WarriorType::Dragon;
		}
		else {
			order[0] = WarriorType::Lion, order[1] = WarriorType::Dragon, order[2] = WarriorType::Ninja,
				order[3] = WarriorType::Iceman, order[4] = WarriorType::Wolf;
		}
	}
};

class World {
public:
	void produce();
	void escape();
	void march();
	void rob();
	void battle();
	void report_HP();
	void report_weapon();
	void report_end(int t, Headquarter* h);
	void report_born(int t, Headquarter* h, Warrior* w) {
		printf("%03d:%02d %s %s %d born\n", t / 60, t % 60, h->name.c_str(), w->type.c_str(), w->id);
	}
	void report_march(int t, Headquarter* h, Warrior* w);
	void report_rob(Warrior* attacker, Warrior* defender);
	void battle_in_city(int i);

	int Time = 0;
	int N, K, T;
	bool is_end = false;

	Headquarter red, blue;
	vector<City> cities;

	World(int m, int n, int k, int t) :red("red", m), blue("blue", m), N(n), K(k), T(t) {
		cities.resize(N + 2);
	}
	void run();
};

void World::run() {
	while (Time <= T) {
		if (is_end) break;
		int minute = (Time) % 60;

		if (minute == 0) produce();
		else if (minute == 5) escape();
		else if (minute == 10) march();
		else if (minute == 35) rob();
		else if (minute == 40) battle();
		else if (minute == 50) report_HP();
		else if (minute == 55) report_weapon();

		Time += 5;
	}
}

struct WarriorSpec
{
	int init_hp;
	int atk;
	string type;
}spec[5];

Warrior* Headquarter::produce() {
	if (stopped) return nullptr;
	WarriorType T = order[cur_id % 5];
	int cost = spec[(int)T].init_hp;
	if (total_hp >= cost) {
		cur_id++;
		total_hp -= cost;
		switch (T) {
		case WarriorType::Dragon: return new Dragon(cur_id, cost, spec[(int)T].atk, name);
		case WarriorType::Ninja: return new Ninja(cur_id, cost, spec[(int)T].atk, name);
		case WarriorType::Iceman: return new Iceman(cur_id, cost, spec[(int)T].atk, name);
		case WarriorType::Lion: return new Lion(cur_id, cost, spec[(int)T].atk, name, total_hp);
		case WarriorType::Wolf: return new Wolf(cur_id, cost, spec[(int)T].atk, name);
		}
	}
	else {
		stopped = true;
		return nullptr;
	}
}

void World::report_end(int t, Headquarter* h) {
	printf("%03d:%02d %s headquarter was taken\n",
		Time / 60, Time % 60, h->name.c_str());
	is_end = true;
}

void World::report_march(int t, Headquarter* h, Warrior* w) {
	printf("%03d:%02d %s %s %d marched to city %d with %d elements and force %d\n",
		t / 60, t % 60, h->name.c_str(), w->type.c_str(), w->id, w->city, w->hp, w->atk);
}

void World::produce() {
	Warrior* rw = red.produce();
	Warrior* bw = blue.produce();

	if (rw) {
		cities[0].red = rw;
		report_born(Time, &red, rw);
		if (rw->type == "lion") {
			rw->printBornExtra();
		}
	}
	if (bw) {
		cities[N + 1].blue = bw;
		report_born(Time, &blue, bw);
		if (bw->type == "lion") {
			bw->printBornExtra();
		}
	}
}

void World::escape() {
	for (int i = 0; i <= N + 1; i++) {
		if (cities[i].red) {
			Warrior* w = cities[i].red;
			if (w->type == "lion" && w->runaway()) {
				if (i != N + 1) {
					printf("%03d:%02d red lion %d ran away\n", Time / 60, Time % 60, w->id);
					delete cities[i].red;
					cities[i].red = nullptr;
				}
			}
		}
		if (cities[i].blue) {
			Warrior* w = cities[i].blue;
			if (w->type == "lion" && w->runaway()) {
				if (i != 0) {
					printf("%03d:%02d blue lion %d ran away\n", Time / 60, Time % 60, w->id);
					delete cities[i].blue;
					cities[i].blue = nullptr;
				}
			}
		}
	}
}

void World::march() {
	vector<City> newCities(N + 2);
	for (int i = 1; i <= N + 1; i++) {
		if (cities[i].blue) {
			Warrior* w = cities[i].blue;
			w->city = i - 1;
			newCities[i - 1].blue = w;
			if (w->type == "lion") w->getLoyalty() -= K;
			else if (w->type == "iceman") w->hp -= w->hp * 1 / 10;
		}
	}
	for (int i = N; i >= 0; i--) {
		if (cities[i].red) {
			Warrior* w = cities[i].red;
			w->city = i + 1;
			newCities[i + 1].red = w;
			if (w->type == "lion") w->getLoyalty() -= K;
			else if (w->type == "iceman") w->hp -= w->hp * 1 / 10;
		}
	}
	cities = newCities;

	if (cities[0].blue) {
		Warrior* w = cities[0].blue;
		printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n",
			Time / 60, Time % 60, w->type.c_str(), w->id, w->hp, w->atk);
		report_end(Time, &red);
	}
	for (int i = 1; i <= N; i++) {
		if (cities[i].red) {
			report_march(Time, &red, cities[i].red);
		}
		if (cities[i].blue) {
			report_march(Time, &blue, cities[i].blue);
		}
	}
	if (cities[N + 1].red) {
		Warrior* w = cities[N + 1].red;
		printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n",
			Time / 60, Time % 60, w->type.c_str(), w->id, w->hp, w->atk);
		report_end(Time, &blue);
	}
}

void World::report_weapon() {
	for (int i = 0; i <= N + 1; i++) {
		if (cities[i].red) {
			Warrior* W = cities[i].red;
			int s_sum = 0, b_sum = 0, a_sum = 0;
			for (auto w : W->weapons) {
				if (w->name == "sword") s_sum++;
				else if (w->name == "bomb") b_sum++;
				else if (w->name == "arrow" && !w->empty()) a_sum++;
			}

			printf("%03d:%02d red %s %d has %d sword %d bomb %d arrow and %d elements\n",
				Time / 60, Time % 60, W->type.c_str(), W->id, s_sum, b_sum, a_sum, W->hp);
		}

		if (cities[i].blue) {
			Warrior* W = cities[i].blue;
			int s_sum = 0, b_sum = 0, a_sum = 0;
			for (auto w : W->weapons) {
				if (w->name == "sword") s_sum++;
				else if (w->name == "bomb") b_sum++;
				else if (w->name == "arrow" && !w->empty()) a_sum++;
			}

			printf("%03d:%02d blue %s %d has %d sword %d bomb %d arrow and %d elements\n",
				Time / 60, Time % 60, W->type.c_str(), W->id, s_sum, b_sum, a_sum, W->hp);
		}
	}
}

void World::report_HP() {
	printf("%03d:%02d %d elements in red headquarter\n", Time / 60, Time % 60, red.total_hp);
	printf("%03d:%02d %d elements in blue headquarter\n", Time / 60, Time % 60, blue.total_hp);
}

void Warrior::weaponSort() {
	sort(weapons.begin(), weapons.end(),
		[](Weapon* a, Weapon* b) {
			if (a->type != b->type) return a->type < b->type;
			if (a->type == 2) {
				return a->getCnt() < b->getCnt();
			}
			return false;
		});
}

void World::report_rob(Warrior* attacker, Warrior* defender) {
	int s_cnt = 0, b_cnt = 0, a_cnt = 0;
	for (auto w : attacker->taken) {
		if (w->type == 0) s_cnt++;
		else if (w->type == 1)  b_cnt++;
		else a_cnt++;
	}
	if (s_cnt || b_cnt || a_cnt) {
		printf("%03d:%02d %s wolf %d took ", Time / 60, Time % 60,
			attacker->faction.c_str(), attacker->id);
		if (s_cnt) printf("%d sword ", s_cnt);
		if (b_cnt) printf("%d bomb ", b_cnt);
		if (a_cnt) printf("%d arrow ", a_cnt);
		printf("from %s %s %d in city %d\n", defender->faction.c_str(), defender->type.c_str(),
			defender->id, defender->city);
	}
}

void Warrior::disarm(Warrior* other) {
	if (!other->hasWeapon()) return;
	vector<Weapon*> loot;
	for (auto w : other->weapons) {
		if (w && !w->empty()) loot.push_back(w);
	}

	if (loot.empty()) return;
	sort(loot.begin(), loot.end(),
		[](Weapon* a, Weapon* b) {
			if (a->type != b->type) return a->type < b->type;
			if (a->type == 2) return a->getCnt() > b->getCnt();
			return false;
		});

	taken.clear();
	for (auto w : loot) {
		if (weapons.size() < 10) {
			weapons.push_back(w);
			taken.insert(w);
		}
		else break;
	}

	vector<Weapon*> remain;
	for (auto w : other->weapons) {
		if (!taken.count(w)) remain.push_back(w);
	}
	other->weapons = remain;
}

void World::battle_in_city(int i) {
	Warrior* r = cities[i].red;
	Warrior* b = cities[i].blue;
	if (!r || !b) return;

	r->weaponSort(), b->weaponSort();
	int pr = 0, pb = 0;
	bool red_turn = (i % 2 == 1);
	int no_change = 0;

	while (true) {
		if (!r->hasWeapon() && !b->hasWeapon()) break;

		Warrior* attacker = (red_turn ? r : b);
		Warrior* defender = (red_turn ? b : r);
		int& p = red_turn ? pr : pb;

		bool changed = false;
		if (attacker->hasWeapon()) {
			Weapon* w = attacker->nextWeapon(p);
			if (w) {
				changed = attacker->use_weapon(attacker, defender, w);
				if (!changed) no_change++;
				else no_change = 0;
			}
		}

		if (r->hp <= 0 || b->hp <= 0) break;
		if (no_change >= 100) break;

		red_turn = !red_turn;
	}

	r->removeWeapon();
	b->removeWeapon();

	bool red_dead = (r->hp <= 0), blue_dead(b->hp <= 0);
	if (red_dead && blue_dead) {
		printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n",
			Time / 60, Time % 60, cities[i].red->type.c_str(), cities[i].red->id,
			cities[i].blue->type.c_str(), cities[i].blue->id, i);
		delete cities[i].red;
		delete cities[i].blue;
		cities[i].red = cities[i].blue = nullptr;
	}
	else if (red_dead) {
		printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n",
			Time / 60, Time % 60, cities[i].blue->type.c_str(), cities[i].blue->id,
			cities[i].red->type.c_str(), cities[i].red->id, i, cities[i].blue->hp);
		cities[i].blue->disarm(cities[i].red);
		if (cities[i].blue->type == "dragon") printf("%03d:%02d blue dragon %d yelled in city %d\n",
			Time / 60, Time % 60, cities[i].blue->id, i);
		delete cities[i].red;
		cities[i].red = nullptr;
	}
	else if (blue_dead) {
		printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n",
			Time / 60, Time % 60, cities[i].red->type.c_str(), cities[i].red->id,
			cities[i].blue->type.c_str(), cities[i].blue->id, i, cities[i].red->hp);
		if (cities[i].red->type == "dragon") printf("%03d:%02d red dragon %d yelled in city %d\n",
			Time / 60, Time % 60, cities[i].red->id, i);
		cities[i].red->disarm(cities[i].blue);
		delete cities[i].blue;
		cities[i].blue = nullptr;
	}
	else {
		printf("%03d:%02d both red %s %d and blue %s %d were alive in city %d\n",
			Time / 60, Time % 60, cities[i].red->type.c_str(), cities[i].red->id,
			cities[i].blue->type.c_str(), cities[i].blue->id, i);
		if (cities[i].red->type == "dragon") printf("%03d:%02d red dragon %d yelled in city %d\n",
			Time / 60, Time % 60, cities[i].red->id, i);
		if (cities[i].blue->type == "dragon") printf("%03d:%02d blue dragon %d yelled in city %d\n",
			Time / 60, Time % 60, cities[i].blue->id, i);
	}
}

void World::rob() {
	for (int i = 1; i <= N; i++) {
		if (cities[i].red && cities[i].red->type == "wolf"
			&& cities[i].blue && cities[i].blue->type != "wolf") {
			cities[i].red->wolfRob(cities[i].blue);
			report_rob(cities[i].red, cities[i].blue);
		}
		if (cities[i].blue && cities[i].blue->type == "wolf"
			&& cities[i].red && cities[i].red->type != "wolf") {
			cities[i].blue->wolfRob(cities[i].red);
			report_rob(cities[i].blue, cities[i].red);
		}
	}
}

void World::battle() {
	for (int i = 1; i <= N; i++) {
		battle_in_city(i);
	}
}

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		int M, N, K, T;
		cin >> M >> N >> K >> T;
		World world(M, N, K, T);
		printf("Case %d:\n", i);
		for (int i = 0; i < 5; i++) cin >> spec[i].init_hp;
		for (int i = 0; i < 5; i++) cin >> spec[i].atk;

		world.run();
	}
	return 0;
}