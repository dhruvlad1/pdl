import random;

def scramble_word(word):
    letters=list(word)
    random.shuffle(letters)
    return "".join(letters)

def game():
    words = [
    "python", "developer", "computer", "science", "program", "keyboard", "laptop", "internet",
    "elephant", "mountain", "galaxy", "sunshine", "whisper", "avocado", "castle", "breeze",
    "horizon", "chocolate", "umbrella", "festival", "puzzle", "diamond", "volcano", "island",
    "forest", "journey", "legend", "mystery", "river", "snowflake", "thunder", "ocean",
    "candle", "adventure", "happiness", "butterfly", "piano", "mirror", "shadow", "treasure",
    "kangaroo", "courage", "fantasy", "gravity", "secret", "rainbow", "pepper", "magic"
    ]
    score = 0
    print("Welcomt to the word scramble game")
    print("Type 'quit' anytime to exit")
    while(True):
        original_word=random.choice(words)
        scramble=scramble_word(original_word)
        print(f'scrambled word : **{scramble}**')

        while(True):
            guess=input("Your guess ").lower()
            if(guess=="quit"):
                print(f'Game over! Your final score is {score}')
                return
            if(guess==original_word):
                score+=1
                print("Correct!, score:",score,"\n")
                break
            else:
                print("Incorrect! try again!")

game() 