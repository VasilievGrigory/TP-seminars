import curses
from curses.textpad import Textbox, rectangle

class Game():
    level = 0
    l = ["Easy", "Medium", "Hard"]
    player = ""
    time = 0
    mistakes = 0
    def start_game(self, main):
        curses.noecho()
        main.addstr("Hi! How are you? Ready to start? ")
        main.getch()
        main.clear()
        main.addstr(0, 0, "Enter IM message: (hit Ctrl-G to send)")
        editwin = curses.newwin(5,30, 2,1)
        rectangle(main, 1,0, 1+5+1, 1+30+1)
        main.refresh()
        box = Textbox(editwin)
        box.edit()
        name = box.gather()
        main.clear()
        self.player = name
        self.level = self.pick_mod(main)
        main.clear()
        main.addstr("Your pick is ")
        main.addstr(self.l[self.level])
        main.addstr("\nNow, we are ready to start!")

        
    def pick_mod(self, main):
        curses.noecho()
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
                main.addstr(self.l[i])
            main.addstr("\n(To iterate use: KEY_LEFT and KEY_RIGHT)")
            main.addstr("\n(To pick click KEY_UP)")
            ans = main.getch()
            if ans == ord('D'):
                if choice >= 1:
                    choice -= 1
            elif ans == ord('C'):
                if choice != 4:
                    choice += 1
            elif ans == ord('A'):
                exit = True
        return choice
    def easy_mode(self, main):
        f = open('easy_mode.txt', 'r')
        s = f.read()
        s_const = s
        start = time.time()
        while len(s) != 0:
            main.clear()
            main.addstr(s_const)
            main.addstr('\n')
            s_curr = s[:s.find(' ') + 1]
            s = s[s.find(' ') + 1:]
            main.addstr('\n')
            main.addstr(s)
            main.addstr('\n')
            main.addstr(s_curr)
            main.addstr('\n')
            temp = 0
            while temp != len(s_curr):
                ans = main.getch()
                if ord(s_curr[temp]) == ans:
                    main.addstr(s_curr[temp])
                    temp += 1
                else:
                    self.mistakes += 1
        self.time = time.time() - start
        main.addstr('\n')
        main.addstr("Your results:\n")
        main.addstr("Time: ")
        main.addstr(str(self.time))
        main.addstr('\n')
        main.addstr("Mistakes: ")
        main.addstr(str(self.mistakes))
        main.addstr('\n')







main = curses.initscr()
g = Game()
g.start_game(main)
main = curses.endwin()
