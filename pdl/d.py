def is_valid_sudoku(board):
    for row in board:
        nums = [x for x in row if x != 0]
        if len(nums) != len(set(nums)):
            return False


    for col in range(9):
        nums = []
        for row in range(9):
            if board[row][col] != 0:
                nums.append(board[row][col])
        if len(nums) != len(set(nums)):
            return False

    
    for start_row in range(0, 9, 3):
        for start_col in range(0, 9, 3):
            nums = []
            for r in range(start_row, start_row + 3):
                for c in range(start_col, start_col + 3):
                    if board[r][c] != 0:
                        nums.append(board[r][c])
            if len(nums) != len(set(nums)):
                return False

    return True



sudoku_grid = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]


if is_valid_sudoku(sudoku_grid):
    print("Valid Sudoku configuration")
else:
    print("Invalid Sudoku configuration")
