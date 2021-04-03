# redsquare-bluesquare
A tool for broadcasting combat robot events using Challonge and OBS

This tool will allow you to create a countdown timer file to be consumed by OBS. It will also pull down any number of brackets from Challonge and provide a list of fights that are "active", meaning there are two participants matched and results have not been submitted. These are all fights that could happen now. Click on "vs" in any row of fights will generate text files red.txt and blue.txt with the participants' names for consumption by OBS for the competitors names. My arena has a red square and a blue square for fighters to place their bots, hence the repo name.

Test it yourself by creating and initializing a bracet in Challonge. Add your username and API key in __main__ and add the tournament(s) you would like to query. Point OBS to timer.txt, red.txt and blue.txt in the folder and execute the program.

This code does NOT upload any data to challonge, but it could be modified to submit results. 

Requires pychallonge (https://github.com/ZEDGR/pychallonge) and Kivy (https://kivy.org/#home)

Definitely alpha. Like most of my bots...
