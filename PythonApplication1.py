import curses
class Game():
    level = 0
    l = ["Easy", "Medium", "Hard"]
    player = ""
    time = 0
    mistakes = 0
    def start_game(self, name, main):
        main.addstr("Hi! How are you? Ready to start? ")
        main.getch()
        main.clear()
        main.addstr(0, 0, "Enter IM message: (hit Ctrl-G to send)")
        editwin = curses.newwin(5,30, 2,1)
        rectangle(stdscr, 1,0, 1+5+1, 1+30+1)
        main.refresh()
        box = Textbox(editwin)
        box.edit()
        name = box.gather()
        main.clear()
        self.player = name
        self.level = self.pick_mod(main)
        main.getch()
        
    def pick_mod(self, main):
        exit = False
        choice = 0
        while(not exit):
            main.clear()
            main.addstr("Now time to pick mode:\n")
            for i in range(3):
                if i == choice:
                    main.addstr('>')
                else:
                    main.addstr(' ')
                main.addstr(l[i])
            main.addstr("\n(To iterate use: KEY_LEFT and KEY_RIGHT)")
            main.addstr("\n(To pick click KEY_UP)")
            ans = main.getch()
            if ans == 'D':
                if choice >= 1:
                    choice -= 1
            elif ans == 'C':
                if choice != 4:
                    choice += 1
            elif ans == 'A':
                exit = True
        return choice





main = curses.initscr()

main = curses.endscr()
