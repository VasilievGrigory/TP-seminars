#include <iostream>
class Unite {
public:
	virtual void common_hit(Unite&) = 0;
	virtual int max_health() = 0;
	virtual bool is_dead() = 0;
	virtual int current_hp() = 0;
	virtual int current_act_points() = 0;
	virtual void decrease_hp(int) = 0;
	virtual void decrease_act_points(int) = 0;
	virtual ~Unite() = 0;
};
Unite::~Unite() {};
class Mage :public Unite {
public:
	int health = 60;
	int action_points = 3;
	int initiative = 8;
	Mage() = default;
	int max_health() {
		return 60;
	}
	int  current_hp(){
		return this->health;
	}
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
		this->health -= damage;
	}
	void decrease_act_points(int damage_points){
		this->action_points -= damage_points;
	}
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(15);
		this->action_points--;
	}
	void fireball(Unite& u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(35);
		this->action_points -= 2;
	}
	void heal(Unite& u) {
		if (this->action_points < 2 || u.max_health()==u.current_hp()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(-10);
		this->action_points -= 2;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Mage() = default;
};
 
class Warrior :public Unite {
public:
	int health = 100;
	int action_points = 3;
	int initiative = 4;
	Warrior() = default;
	int max_health() {
		return 100;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "I can't do this!\n";
			return;
		}
		u.decrease_hp(10);
		this->action_points--;
	}
	void hit_with_stun(Unite& u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "I can't do this!\n";
			return;
		}
		u.decrease_hp(30);
		u.decrease_act_points(u.current_act_points());
		this->action_points -= 2;
	}
	void strong_hit(Unite& u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "I can't do this!\n";
			return;
		}
		u.decrease_hp(30);
		this->action_points -= 2;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Warrior() = default;
};
 
class Archer :public Unite {
public:
	int health = 70;
	int action_points = 4;
	int initiative = 6;
	Archer() = default;
	int max_health() {
		return 70;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite & u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "It can't be done!\n";
			return;
		}
		u.decrease_hp(10);
		this->action_points--;
	}
	void deadly_arrow(Unite & u) {
		if (this->action_points < 3 || u.is_dead()) {
			std::cout << "It can't be done!\n";
			return;
		}
		u.decrease_hp(10);
		if (u.current_hp() <= 20) {
			u.decrease_hp(u.current_hp());
		}
		this->action_points -= 3;
	}
	void drag_arrow(Unite & u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "It can't be done!\n";
			return;
		}
		u.decrease_hp(30);
		this->action_points -= 2;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Archer() = default;
};

class Rogue :public Unite {
public:
	int health = 60;
	int action_points = 4;
	Rogue() = default;
	int max_health() {
		return 60;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(15);
		this->action_points--;
	}
	void blade_of_shadow(Unite& u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(10);
		if (u.current_hp()<=0){
			this->action_points++;
			this->health+=10;
		}
		this->action_points -= 2;
	}
	void irrepressibility(Unite& u) {
		if (u.is_dead()){
			std::cout<<"This is silly...\n";
			return;
		}
		if(this->action_points<3){
			std::cout<<"I can't do this!\n";
			return;
		}
		u.decrease_act_points(-3);
		this->action_points-=2;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Rogue() = default;
};

class Paladin :public Unite {
public:
	int health = 85;
	int action_points = 3;
	Paladin() = default;
	int max_health() {
		return 85;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(15);
		this->action_points--;
	}
	void hit_with_blind(Unite& u) {
		if (this->action_points < 2 || u.is_dead()) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(20);
		u.decrease_act_points(3);
		this->action_points -= 2;
	}
	void blessing(Unite& u) {
		if (this->action_points < 3) {
			std::cout << "It's impossible!\n";
			return;
		}
		u.decrease_hp(-10);
		u.decrease_act_points(-2);
		this->action_points -= 3;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Paladin() = default;
};

class Easy_enemy :public Unite {
public:
	int health = 50;
	int action_points = 3;
	int initiative = 3;
	Easy_enemy() = default;
	int max_health() {
		return 50;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "NO!\n";
			return;
		}
		u.decrease_hp(10);
		this->action_points--;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Easy_enemy() = default;
};
 
class Medium_enemy :public Unite {
public:
	int health = 70;
	int action_points = 3;
	int initiative = 5;
	Medium_enemy() = default;
	int max_health() {
		return 70;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "NO!\n";
			return;
		}
		u.decrease_hp(15);
		this->action_points--;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Medium_enemy() = default;
};
 
class Hard_enemy :public Unite {
public:
	int health = 80;
	int action_points = 4;
	int initiative = 7;
	Hard_enemy() = default;
	int max_health() {
		return 80;
	}
	int  current_hp(){
                return this->health;
        }
	int  current_act_points(){
                return this->action_points;
        }
	void decrease_hp(int damage){
                this->health -= damage;
        }
        void decrease_act_points(int damage_points){
                this->action_points -= damage_points;
        }
	void common_hit(Unite& u) {
		if (this->action_points < 1 || u.is_dead()) {
			std::cout << "NO!\n";
			return;
		}
		u.decrease_hp(20);
		this->action_points--;
	}
	bool is_dead() {
		if (this->health <= 0) {
			return true;
		}
		return false;
	}
	~Hard_enemy() = default;
};

int main(){
	Paladin p;
	Mage m;
	Hard_enemy h;
	std::cout<<m.health<<' '<<m.action_points<<std::endl;
	std::cout<<p.health<<' '<<p.action_points<<std::endl;
	std::cout<<h.health<<' '<<h.action_points<<std::endl;
	p.blessing(m);
	m.common_hit(h);
	std::cout<<m.health<<' '<<m.action_points<<std::endl;
        std::cout<<p.health<<' '<<p.action_points<<std::endl;
	std::cout<<h.health<<' '<<h.action_points<<std::endl;
	return 0;
}
