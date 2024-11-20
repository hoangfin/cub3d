# cub3d
42 curriculum project on a raycaster written in C. Implements DDA algorithm for raycasting.

### Requirements
[MLX42](https://github.com/codam-coding-college/MLX42) graphics library

### How to install
`git clone` && `cd` into desired repository. Run `git submodule init` and `git submodule update` in the same directory and then `make`.

### Gameplay
Run executable `cub3D` with any of the maps found in the maps folder within the same repository `assets/maps/good/` like:
```./cub3D assets/maps/good/tunnel.cub```
Use `AWSD` keys to move left, right, forwards and backwards. Use arrow keys and/or mouse to rotate player view. Doors can be opened by running the player front-first towards the door which will launch its opening. Open doorways can be closed by casting a spell with a left mouse click and aiming the magic wand towards the door.
