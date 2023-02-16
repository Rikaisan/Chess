
# C++ Chess

This is a work in progress chess game written in C++ using SFML.

## Feature TODO Checklist

 - [x] Blank board render
 - [x] Rendering pieces
 - [x] *Forsyth-Edwards Notation* support to load board states
 - [x] Working Pieces
 - [ ] Per-piece logic
 - [x] Option to enable and disable algebraic notation on the board
 - [ ] Castling
 - [ ] Legal move logic
 - [ ] Customization (piece sets & board colors)
 - [ ] Ability to export games
 - [ ] Ability to import games to review them (No Eval)
 - [ ] Clock
 - [ ] Stockfish integration to play vs the computer
 - [ ] Different AI difficulties

## Dependencies

 - SFML 2.5.1

## Changelog

 ### 15/Feb/2023
 - Separated Board logic into Engine, Renderer and Interface classes
 - Added support to load board states via FEN strings
 - Last position cache is now used
 - BoardRenderer can now draw Text on 5 different positions of a cell (center, top-left, top-right, bottom-left, bottom-right)
 - BoardRenderer now has the option to draw the file and rank coordinates
 - Added App Icon
  ### 16/Feb/2023
 - Pieces are now able to be grabbed and moved
 - Pieces can't take pieces of the same color
 - Renderer can now draw pieces in places not aligned to the grid
 - Implemented methods for the Piece class that allow to check if a piece is empty/null and to reset them
 - Engine now has the option to fetch a piece at a specific square