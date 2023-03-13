
# C++ Chess

This is a work in progress chess game written in C++ using SFML.

## Feature TODO Checklist

- [x] Blank board render
- [x] Rendering pieces
- [x] *Forsyth-Edwards Notation* support to load board states
- [x] Working Pieces
- [x] Pseudolegal movement
- [x] Option to enable and disable algebraic notation on the board
- [ ] Special moves (castling & en pessant)
- [ ] Legal move logic
- [ ] Auto flip board option for local games
- [ ] Customization (piece sets & board colors)
- [ ] Ability to export games
- [ ] Ability to import games to review them (No Eval)
- [ ] Clock
- [ ] Simple online multiplayer (p2p)
- [ ] Stockfish integration to play vs the computer
- [ ] Different AI difficulties

## Dependencies

- SFML 2.5.1 (Included)
- Premake 5 (For project setup only - Included)

## Changelog

### 15/Feb/2023

- Separated Board logic into `BoardEngine`, `BoardRenderer` and `BoardInterface`
- Added support to load board states via FEN strings
- Last position cache is now used
- `BoardRenderer` can now draw text on 5 different positions of a cell (center, top-left, top-right, bottom-left, bottom-right)
- `BoardRenderer` now has the option to draw the file and rank coordinates
- Added App Icon

### 16/Feb/2023

- Pieces are now able to be grabbed and moved
- Pieces can't take pieces of the same color
- `BoardRenderer` can now draw pieces in places not aligned to the grid
- Implemented methods for `Piece` that allow to check if a piece is empty/null and to reset them
- `BoardEngine` now has the option to fetch a piece at a specific square

### v0.1.0

- Introducing Semantic Versioning! From now on, all updates will be labeled using semantic versioning instead of dates
- Pieces now move using pseudo-legal moves (this doesn't include any special moves)
- `BoardEngine` now has two ways of representing the board: the original 64 piece array and a 2D piece array
- `BoardRenderer` now has the ability to hide pieces, this was added so that `BoardInterface` hides the piece instead of deleting it while holding a piece
- `BoardEngine` now uses `int8_t` instead of `uint8_t` for piece indices

### v0.2.0

- Reworked the whole project structure
- Repository now includes a premake file instead of Visual Studio files
- All dependencies are now included under /vendor
- `.gitignore` now ignores Visual Studio files
