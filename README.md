
# C++ Chess

This is a work in progress chess game written in C++ using SFML.

## Feature TODO Checklist

 - [x] Blank board render
 - [x] Rendering pieces
 - [x] *Forsyth-Edwards Notation* support to load board states
 - [ ] Working Pieces
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
