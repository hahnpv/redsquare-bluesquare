import threading
import challonge
import math
from time import sleep
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.properties import NumericProperty

class Thread(BoxLayout):
    duration = NumericProperty(180)             # seconds
    counter = NumericProperty(180)
    pause = True                                # toggle play/pause

    def timestr(self):
        minutes = math.floor(self.counter/60.)
        seconds = self.counter - 60*minutes
        timestamp = str(minutes) + ":" + str("{:02d}".format(seconds))
        return timestamp

    def Counter_function(self):
        for i in range(self.duration):
            timestamp = self.timestr()
            self.ids.lbl.text = "{}".format(timestamp)
            open('timer.txt', 'w').write(timestamp)
            sleep(1)
            if self.counter == 0:
                print('breaking, self.counter == 0')
                break
            if self.pause is True:
                print('breaking, self.pause is True')
                break
            self.counter -= 1 

    def toggle_thread(self, instance):
        if self.pause is True:
            self.pause = False
            print("kicking off new thread")
            threading.Thread(target = self.Counter_function, daemon=True).start()
            instance.text = "Pause"
            # note this code will allow starting multiple threads
        else:
            instance.text = "Resume"
            self.pause = True

    def reset_thread(self, instance):
        self.pause = True
        self.counter = self.duration
        timestamp = self.timestr()
        print(self.counter)
        print(timestamp)
        instance.parent.parent.ids.lbl.text = "{}".format(timestamp)
        instance.parent.parent.ids.start.text = "{}".format("Start")

    def redsquare_bluesquare(self, instance):
        print(instance.player1 + " vs " + instance.player2)
        open('red.txt', 'w').write(instance.player1)
        open('blue.txt', 'w').write(instance.player2)

    def refresh_combatants(self, instance):
        gl = instance.parent.parent.ids.gridlayout
        gl.clear_widgets()

        # fixme tournament is global... ok?
        for t in tournament:
            if t["started_at"] is None:
                print("Tournament has not been started!")
            else:
                # fetch all tournament participants
                participants = challonge.participants.index(t["id"])

                gl.add_widget(Button(text = t["name"], size_hint_y=None, height=40))
                print(t["name"])
                # fetch all matches
                matches = challonge.matches.index(t["id"])

                # print combatants for each open match
                open_matches = (m for m in matches if m["state"]=="open")
                for m in open_matches:
                    p1 = m["player1_id"]
                    p2 = m["player2_id"]
                    player1 = next(p for p in participants if p["id"]==p1)
                    player2 = next(p for p in participants if p["id"]==p2)

                    layout = GridLayout(cols=3, spacing=10, height=40, size_hint_x=1.0)
                    btn = Button(text = player1["name"], size_hint_y=1.0, height=40, background_color=(1,0,0,1.0))
                    layout.add_widget(btn)
                    btn = Button(text = "vs", size_hint_x=1.0, height=40)
                    btn.player1 = player1["name"]
                    btn.player2 = player2["name"]
                    btn.bind(on_release=self.redsquare_bluesquare)
                    layout.add_widget(btn)
                    btn = Button(text = player2["name"], size_hint_y=1.0, height=40, background_color=(0,0,1,1.0))
                    layout.add_widget(btn)
                    gl.add_widget(layout)

        # Make sure the height is such that there is something to scroll.
        gl.bind(minimum_height=gl.setter('height'))

class MyApp(App):
    def build(self):
        self.load_kv('redsquare-bluesquar.kv')
        return Thread() 

if __name__ == "__main__":

    challonge.set_credentials("user", "apikey")
    tournament = [challonge.tournaments.show("arrtestfairy"),
                challonge.tournaments.show("arrtestant"),
                challonge.tournaments.show("arrtestplastic"),
                challonge.tournaments.show("arrtestbeetle")
                ]

    app = MyApp()
    app.run()