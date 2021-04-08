#include <ncurses.h>
#include <vector>
#include <string>
class Unite {
public:
	virtual void common_hit(Unite*) = 0;
	virtual int max_health() = 0;
	virtual bool is_dead() = 0;
	virtual int current_pos() = 0;
	virtual int current_hp() = 0;
	virtual int current_act_points() = 0;
	virtual void decrease_hp(int) = 0;
	virtual void decrease_act_points(int) = 0;
	virtual ~Unite() = 0;
};
Unite::~Unite()=default;
class Profession_Decorate:public Unite{
protected:
	Unite* unite_;
public:
	int health = 0;
	int mx_hp = 0;
        int action_points = 0;
        int initiative = 0;
        int position = 0;
        Profession_Decorate (Unite* unite): unite_(unite){
        }
	int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                        return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
	bool is_dead() {
		if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
       

};
class Ork : public Unite{
public:
	int health = 100;
        int action_points = 3;
        int initiative = 4;
        int position = 0;
        Ork (int pos){
                health = 100;
                action_points = 3;
                initiative = 4;
                position = pos;
        }
        Ork() = default;
	int current_pos(){
                return this->position;
        }
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
        void common_hit(Unite* u) {
                if (this->action_points < 1 || u->is_dead()) {
                        printw("I can't do this!\n");
                        return;
                }
                u->decrease_hp(10);
                this->action_points--;
        }
        bool is_dead() {
                if (this->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
};
class Elf : public Unite{
public:
        int health = 60;
        int action_points = 3;
        int initiative = 8;
        int position = 0;
        Elf (int pos){
                health = 60;
                action_points = 3;
                initiative = 8;
                position = pos;
        }
	int current_pos(){
                return this->position;
        }
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
        void common_hit(Unite* u) {
                if (this->action_points < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                        return;
                }
                u->decrease_hp(15);
                this->action_points--;
        }
};
class Human : public Unite{
public:
        int health = 85;
        int action_points = 3;
        int initiative = 7;
        int position = 0;
        Human (int pos){
                health = 85;
                action_points = 3;
                initiative = 7;
                position = pos;
        }
        int current_pos(){
                return this->position;
        }
        Human() = default;
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
        void common_hit(Unite* u) {
                if (this->action_points < 1 || u->is_dead()) {
                        printw("It's impossible!\n");
                        return;
                }
                u->decrease_hp(15);
                this->action_points--;
        }
        bool is_dead() {
                if (this->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
};

class Mage :public Profession_Decorate {
public:
	int health = 0;
	int action_points = 0;
	int initiative = 0;
	int position = 0;
	Mage (Unite* unite): Profession_Decorate(unite){
	}
	int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                       return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
        bool is_dead() {
                if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
	void fireball(Unite* u){
		if(this->unite_->current_act_points() < 2 || u->is_dead()){
			printw( "It's impossible!\n");
			return;
		}
		u->decrease_hp(35);
		this->unite_->decrease_act_points(2);
	}
	void heal(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->max_health()==u->current_hp()) {
			printw( "It's impossible!\n");
			return;
		}
		u->decrease_hp(-10);
		this->unite_->decrease_act_points(2);
	}
	~Mage() = default;
};

class Warrior :public Profession_Decorate {
public:
	int health = 0;
        int action_points = 0;
        int initiative = 0;
        int position = 0;
        Warrior (Unite* unite): Profession_Decorate(unite){
        }
        int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                       return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
        bool is_dead() {
                if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
	void hit_with_stun(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->is_dead()) {
			printw("I can't do this!\n");
			return;
		}
		u->decrease_hp(30);
		u->decrease_act_points(u->current_act_points());
		this->unite_->decrease_act_points(3);
	}
	void strong_hit(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->is_dead()) {
			printw("I can't do this!\n");
			return;
		}
		u->decrease_hp(30);
		this->unite_->decrease_act_points(2);
	}
	~Warrior() = default;
};

class Archer :public Profession_Decorate {
public:
	int health = 0;
        int action_points = 0;
        int initiative = 0;
        int position = 0;
        Archer (Unite* unite): Profession_Decorate(unite){
        }
        int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                       return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
        bool is_dead() {
                if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
	void deadly_arrow(Unite* u){
		if (this->unite_->current_act_points() < 3 || u->is_dead()) {
			printw("It can't be done!\n");
			return;
		}
		u->decrease_hp(10);
		if (u->current_hp() <= 20) {
			u->decrease_hp(u->current_hp());
		}
		this->unite_->decrease_act_points(3);
	}
	void drag_arrow(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->is_dead()) {
			printw("It can't be done!\n");
			return;
		}
		u->decrease_hp(30);
		this->unite_->decrease_act_points(2);
	}
	~Archer() = default;
};

class Rogue :public Profession_Decorate {
public:
	int health = 0;
        int action_points = 0;
        int initiative = 0;
        int position = 0;
        Rogue (Unite* unite): Profession_Decorate(unite){
        }
        int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                       return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
        bool is_dead() {
                if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
	void blade_of_shadow(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->is_dead()) {
			printw("It's impossible!\n");
			return;
		}
		u->decrease_hp(10);
		if (u->current_hp()<=0){
			this->unite_->decrease_act_points(-1);
			this->unite_->decrease_hp(-10);
		}
		this->unite_->decrease_act_points(2);
	}
	void irrepressibility(Unite* u) {
		if (u->is_dead()){
			printw("This is silly...\n");
			return;
		}
		if(this->unite_->current_act_points()<3){
			printw("It's impossible!\n");
			return;
		}
		u->decrease_act_points(-3);
		this->unite_->decrease_act_points(2);
	}
	~Rogue() = default;
};

class Paladin :public Profession_Decorate {
public:
	int health = 0;
        int action_points = 0;
        int initiative = 0;
        int position = 0;
        Paladin (Unite* unite): Profession_Decorate(unite){
        }
        int current_pos(){
                return this->unite_->current_pos();
        }
        int max_health() {
                return this->unite_->max_health();
        }
        int  current_hp(){
                return this->unite_->current_hp();
        }
        int  current_act_points(){
                return this->unite_->current_act_points();
        }
        void decrease_hp(int damage){
                this->unite_->decrease_hp(damage);
        }
        void decrease_act_points(int damage_points){
                this->unite_->decrease_act_points(damage_points);
        }
        void common_hit(Unite* u) {
                if (this->unite_->current_act_points() < 1 || u->is_dead()) {
                        printw( "It's impossible!\n");
                       return;
                }
                u->decrease_hp(15);
                this->unite_->decrease_act_points(1);
        }
        bool is_dead() {
                if (this->unite_->current_hp() <= 0) {
                        return true;
                }
                return false;
        }
	void hit_with_blind(Unite* u) {
		if (this->unite_->current_act_points() < 2 || u->is_dead()) {
			printw("It's impossible!\n");
			return;
		}
		u->decrease_hp(20);
		u->decrease_act_points(3);
		this->unite_->decrease_act_points(2);
	}
	void blessing(Unite* u) {
		if (this->unite_->current_act_points() < 3) {
			printw("It's impossible!\n");
			return;
		}
		u->decrease_hp(-10);
		u->decrease_act_points(-2);
		this->unite_->decrease_act_points(3);
	}
	~Paladin() = default;
};

class Easy_enemy :public Unite {
public:
	int health = 50;
	int action_points = 3;
	int initiative = 3;
	int position = 0;
	int current_pos(){
		return this->position;
	}
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
			printw("NO!\n");
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
	int position = 0;
        int current_pos(){
                return this->position;
        }
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
			printw("NO!\n");
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
	int position = 0;
        int current_pos(){
                return this->position;
        }
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
			printw("NO!\n");
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

class Game{
	public:
		bool is_ready = false;
		bool currect_state(){
			return this->is_ready;
		}
		void New_Game(){
			this->is_ready = true;
			std::vector<std::string> army;
			std::vector<Mage> mages;
			std::vector<Warrior> warriors;
			std::vector<Archer> archers;
			std::vector<Rogue> rogues;
			std::vector<Paladin> paladins;
			for (int i=1;i<=3;i++){
				int pick_un = pick_unite(4-i);
				int pick_pr = pick_profession();
				if (pick_un == 0){
					Mage m(i);
					mages.push_back(m);
					army.push_back("Mage");
				}
				else if(pick_un == 1){
					Warrior w(i);
					warriors.push_back(w);
					army.push_back("Warrior");
				}
				else if(pick_un == 2){
					Archer a(i);
					archers.push_back(a);
					army.push_back("Archer");
				}
				else if(pick_un == 3){
					Rogue r(i);
					rogues.push_back(r);
					army.push_back("Rogue");
				}
				else{
					Paladin p(i);
					paladins.push_back(p);
					army.push_back("Paladin");
				}
			}
			clear();
			printw("You have made your choice!\n");
			printw("Your army is:\n");
			printw("%s\n",army[0].c_str());
			printw("%s\n",army[1].c_str());
			printw("%s\n",army[2].c_str());
			printw("It's all for now!\nPress any key to leave...");
			getch();
		}
		int pick_unite(int i){
			const char items[3][6]={
                        	        "Elf",
                                	"Ork",
                               		 "Human"};
			bool exit = false;
                	int choice = 0;
                	curs_set(0);
                        keypad(stdscr,true);
                        while(!exit){
				clear();
				printw("Welcome to the unites constructor!\n");
                                printw("Here and always: dm = damage, gap = give action points, 
						ca = cost of action, h = heal, # = ALL, I = initiative\n");
                                printw("Check out all the unites:\n\n");
                                printw("Elf:\nHP = 60\nAP = 3\nI = 8\nCommon_hit = 15dm1ca\n\n");
                                printw("Ork:\nHP = 100\nAP = 3\nI = 4\nCommon_hit = 10dm1ca\n\n");
                                printw("Human:\nHP = 60\nAP = 3\nI = 7\nCommon_hit = 15dm1ca\n\n");
				printw("Now, choose your unites!\n");
				printw("Pick ");
				printw("%d ",i);
				printw("more:\n");
                                for(int i=0;i<3;i++){
                                        if(i==choice){
                                                addch('>');
                                        }
                                        else addch(' ');
                                        printw("%s",items[i]);
                                }
				printw("\n(To iterate use: KEY_LEFT and KEY_RIGHT)");
				printw("\n(To pick click KEY_UP)");
                                switch(getch()){
                                        case KEY_LEFT:
                                                if(choice) choice--;
                                                break;
                                        case KEY_RIGHT:
                                                if(choice!=2) choice++;
                                                break;
                                        case KEY_UP:
						exit = true;
                                                break;

				}
			}
			return choice;
		}
		int pick_profession(){
			const char items[5][8]={
                        	        "Mage",
                                	"Warrior",
                               		 "Archer",
                               		 "Rogue",
                               		 "Paladin"};
			bool exit = false;
                	int choice = 0;
                	curs_set(0);
                        keypad(stdscr,true);
                        while(!exit){
				clear();
				printw("\n\nYou pick your unite! Now pick his profession:");
				printw("Mage:\nAbilities:\n1) fireball = 35dm2ca\n2) heal = 10h2ca\n\n");
                        	printw("Warrior:\nAbilities:\n1) hit_with_stan = 30dm#apdm3ca\n2) strong_hit = 30dm2ca\n\n");
                        	printw("Archer:\nAbilities:\n1) drag_arrow = 30dm2ca\n2) deadly_arrow = (10 + 20*)dm2ca
				       	(*if less 20 hp after first hit)\n\n");
                        	printw("Rogue:\nAbilities:\n1) blade_of_shadow = 10*dm2ca (if enemy died after hit, 
					rogue gets 1ap and 10hp)\n2) irrepressibility  = 2ap (target unite gets 3ap)\n\n");
                        	printw("Paladin:\nAbilities:\n1) hit_with_blind = 20dm3ap2ca\n2) blessing = 10h2gap2ca\n\n");
				printw("Now, choose your unites!\n");
				for(int i=0;i<5;i++){
                                        if(i==choice){
                                                addch('>');
                                        }
                                        else addch(' ');
                                        printw("%s",items[i]);
                                }
				printw("\n(To iterate use: KEY_LEFT and KEY_RIGHT)");
				printw("\n(To pick click KEY_UP)");
                                switch(getch()){
                                        case KEY_LEFT:
                                                if(choice) choice--;
                                                break;
                                        case KEY_RIGHT:
                                                if(choice!=4) choice++;
                                                break;
                                        case KEY_UP:
						exit = true;
                                                break;
				}
			}
			return choice;
		}
};
