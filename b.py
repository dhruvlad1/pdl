import random

def game():
    random_number = random.randint(1,100)
    guesses=0
    while(True):
        guessed_number=int(input("Guess a number between 1 to 100 "))
        guesses+=1
        if(random_number==guessed_number):
            print(f"You guessed the right number in {guesses} guesses")
            return
        elif(random_number < guessed_number):
            print(f"Guess lower!, guesses : {guesses}")
        else:
            print(f"Guess higher!, guesses : {guesses}")

game()