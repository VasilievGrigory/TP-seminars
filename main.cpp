#include "lib.h"

int main(){
	initscr();
	//Game g;
	//g.New_Game();
	Unite* u = new Human;
	Unite* mg_h = new Mage(u);
	Unite* u1 = new Human;
	Unite* wr_h = new Warrior(u1);
	Unite* u2 = new Elf;
	Unite* a = new Archer(u2);
	Composite_Humans* crowd;
	crowd->add(mg_h);
	crowd->add(wr_h);
	printw("%d\n", a->current_hp());
	crowd->HUMANS_POWER(a);
	printw("%d\n", a->current_hp());
	endwin();
	return 0;
}
