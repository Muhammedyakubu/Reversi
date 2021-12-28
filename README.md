# Reversi

## Reversi Rules
Reversi (also known as Othello) consists of a 8x8 square board, and pieces with one black and one white side. Each player has a color, and the aim of the game is to get more of your pieces on the board than the opponent's pieces.

### Gameplay
At the start of the game there are four pieces on the board, two white and two black. You must try to capture opponent pieces and flip them over so they turn into your color. You do this by making a horizontal, vertical or diagonal line of pieces, where your pieces surround the other player's pieces. The surrounded opponent pieces are then captured and will be flipped over to your color, increasing the number of your pieces on the board.

https://user-images.githubusercontent.com/72368510/147362669-aa1a0cc1-1e49-4bf7-a079-95e93d2796ac.mp4

**definition credit** - https://cardgames.io/reversi/ ,
**video credit** - https://gfycat.com/creepymagnificentamericanmarten-patrick-chiang-gaming

## Implementation
In Part1, I developed a basic *greedy* AI to which aimed to flip the hihgest number of the player's pieces. 

However, in part2 the AI utilized a MiniMax Algorithm to "look into the future" and scored potential moves based on:
  1. Number of player pieces flipped
  2. Whether or not a corner is captured
  3. The number of future player moves if that move is made (lower is better).

Both parts support board sizes of 4 - 26.

Developed as a course assignment for the 2021 Winter Computer Fundamentals course at the University of Toronto.
