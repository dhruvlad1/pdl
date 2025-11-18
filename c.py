import random

def game():
    ships = set(random.sample(range(1, 10), 3))
    attempts = 0
    guessed_positions = set()

    print("Welcome to the 1D Battleship Game!")
    print("Guess positions from 1 to 9. Find all 3 ships!\n")

    while ships:  
        try:
            guess = int(input("Guess a number from 1 to 9: "))
        except ValueError:
            print("Invalid input! Enter a number 1–9.")
            continue

        if guess < 1 or guess > 9:
            print("Number out of range! Enter 1–9 only.")
            continue

        if guess in guessed_positions:
            print("You've already guessed that position! Try another.")
            continue

        guessed_positions.add(guess)
        attempts += 1

        if guess in ships:
            print("HIT!")
            ships.remove(guess)
        else:
            print("MISS!")

        print(f"Ships remaining: {len(ships)}\n")

    print(f"Congratulations! You found all ships in {attempts} attempts!")

game()
