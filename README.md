# 🎮 cub3D — 42 Raycasting Project

> A first-person 3D game engine built from scratch in C, inspired by the legendary **Wolfenstein 3D**.  
> Developed as part of the **42 School** curriculum.

---

## 📖 Table of Contents

- [About](#about)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Installation & Build](#installation--build)
- [Usage](#usage)
- [Map File Format (.cub)](#map-file-format-cub)
- [Controls](#controls)
- [Bonus Features](#bonus-features)
- [Authors](#authors)

---

## About

**cub3D** is a raycasting-based 3D renderer that simulates a first-person perspective inside a maze defined by a 2D map. Using the **DDA (Digital Differential Analysis)** algorithm to cast rays across the field of view, the engine projects walls, floors, and ceilings with directional textures in real time.

The project is split into two parts:
- **Mandatory** — core raycasting engine with textured walls, floor/ceiling colors, movement, and collision detection.
- **Bonus** — extended version featuring a minimap, animated sprites, openable doors, and mouse-look support.

---

## Features

### Mandatory
- ✅ Real-time raycasting rendering at **1920×1080**
- ✅ Directional wall textures (North, South, East, West) loaded from PNG files
- ✅ Configurable floor and ceiling RGB colors
- ✅ Player movement with **WASD** keys and rotation with **arrow keys**
- ✅ Collision detection against walls
- ✅ Strict `.cub` map file parsing with error reporting

### Bonus
- ✅ **Minimap** overlay (160×160 px) rendered live in the corner
- ✅ **Animated sprite** rendered in the center of the screen (10 frames, toggled with `Y`)
- ✅ **Door tiles** (`D`) that block movement and raycasting
- ✅ **Mouse-look** (camera rotation following cursor, toggled with `Left Alt`)
- ✅ Window close via the **✕** button

---

## Project Structure

```
cub3d/
├── Makefile
├── MLX42/                         # MLX42 graphics library (submodule)
├── mandatory/
│   ├── cub3d.h                    # Main header — structs & prototypes
│   ├── cub3d.c                    # Game init, texture loading, loop hook
│   ├── raycasting.c               # Ray casting loop
│   ├── horz_inter.c               # Horizontal ray intersections
│   ├── vert_inter.c               # Vertical ray intersections
│   ├── textures.c                 # Wall texture rendering
│   ├── collision.c                # Player collision logic
│   └── parsing/
│       ├── gnl.c                  # get_next_line implementation
│       ├── map.cub                # Example map file
│       ├── textures/              # Wall texture PNG files
│       ├── main/                  # Map parsing & validation logic
│       └── utils/                 # String and utility helpers
└── bonus/
    ├── cub3d_bonus.h              # Bonus header — extended structs & prototypes
    ├── cub3d_bonus.c              # Game init & main loop (bonus)
    ├── raycasting_bonus.c         # Extended raycasting with door & minimap support
    ├── horz_inter_bonus.c         # Horizontal intersections (bonus)
    ├── vert_inter_bonus.c         # Vertical intersections (bonus)
    ├── textures_bonus.c           # Wall texture rendering (bonus)
    ├── render.c                   # Floor & ceiling rendering
    ├── init_mlx.c                 # MLX42 initialization (bonus)
    ├── loop_hook.c                # Loop hook, key/mouse handlers
    ├── sprites.c                  # Animated sprite system (10-frame)
    └── parsing_bonus/
        ├── gnl_bonus.c            # get_next_line (bonus)
        ├── map_bonus.cub          # Example map with doors
        ├── textures_bonus/        # Wall/sprite texture PNGs and frames/
        ├── main_bonus/            # Bonus parsing & validation
        └── utils_bonus/           # Utility helpers (bonus)
```

---

## Dependencies

| Dependency | Description |
|------------|-------------|
| **GCC** | C compiler (`-Wall -Wextra -Werror`) |
| **CMake ≥ 3.18** | Required to build MLX42 |
| **GLFW3** | OpenGL windowing library (required by MLX42) |
| **MLX42** | 42 graphics library (included as a subdirectory) |

### Installing dependencies (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install gcc cmake libglfw3-dev
```

### Installing dependencies (macOS with Homebrew)

```bash
brew install cmake glfw
```

---

## Installation & Build

### 1. Clone the repository

```bash
git clone https://github.com/<your-username>/cub3d.git
cd cub3d
```

> Make sure the `MLX42/` directory is present. If it was added as a submodule, run:
> ```bash
> git submodule update --init --recursive
> ```

### 2. Build the mandatory version

```bash
make
```

This produces the `cub3D` executable.

### 3. Build the bonus version

```bash
make bonus
```

This produces the `cub3D_bonus` executable.

### 4. Clean build artifacts

```bash
make clean    # Remove object files
make fclean   # Remove object files + executables + MLX42 build
make re       # Full rebuild from scratch
```

---

## Usage

```bash
# Mandatory
./cub3D <path/to/map.cub>

# Bonus
./cub3D_bonus <path/to/map_bonus.cub>
```

### Example

```bash
./cub3D mandatory/parsing/map.cub
./cub3D_bonus bonus/parsing_bonus/map_bonus.cub
```

---

## Map File Format (`.cub`)

A `.cub` file has two sections: a **header** defining textures and colors, followed by the **map grid**.

### Header

```
NO <path/to/north_texture.png>
SO <path/to/south_texture.png>
WE <path/to/west_texture.png>
EA <path/to/east_texture.png>

F <R>,<G>,<B>     # Floor color
C <R>,<G>,<B>     # Ceiling color
```

### Map Grid

```
111111
100001
1000N1
100001
111111
```

#### Map Characters

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty / walkable floor |
| `N` | Player spawn, facing **North** |
| `S` | Player spawn, facing **South** |
| `E` | Player spawn, facing **East** |
| `W` | Player spawn, facing **West** |
| `D` | Door tile *(bonus only)* |

#### Map Rules
- The map **must be fully enclosed** by walls (`1`).
- Exactly **one** player spawn character must be present.
- The map must appear **last** in the file, after all header identifiers.
- Empty lines are **not allowed** inside the map.

### Example `.cub` file

```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 189,183,107
C 51,51,0

111111111
100000001
10000N001
100000001
111111111
```

---

## Controls

| Key / Action | Effect |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `← / →` Arrow keys | Rotate left / right |
| `ESC` | Quit the game |
| **Window ✕ button** | Quit the game |
| `Y` *(bonus)* | Toggle animated sprite on/off |
| `Left Alt` *(bonus)* | Toggle mouse-look (cursor lock) on/off |
| Mouse movement *(bonus)* | Rotate camera (when mouse-look is active) |

---

## Bonus Features

The bonus version (`cub3D_bonus`) extends the mandatory version with:

### 🗺️ Minimap
A 160×160 pixel top-down minimap is rendered live in the corner of the screen, showing walls (`1`), open space (`0`), and doors (`D`) color-coded in gray, white, and blue respectively.

### 🚪 Doors
Door tiles (`D` in the map) are treated as solid walls — they block raycasting and player movement. They are visually distinct in the minimap.

### 🎞️ Animated Sprite
A 10-frame animated sprite can be toggled on/off with the `Y` key. The sprite plays its animation automatically when active, cycling through frames every 3 render ticks. Sprite frames must be placed at:
```
bonus/parsing_bonus/textures_bonus/frames/frame1.png
bonus/parsing_bonus/textures_bonus/frames/frame2.png
...
bonus/parsing_bonus/textures_bonus/frames/frame10.png
```

### 🖱️ Mouse Look
Toggle mouse-look mode with `Left Alt`. When active, moving the mouse horizontally rotates the player's view (the cursor is hidden and locked to the window).

---

## Authors

| Name | Login | School |
|------|-------|--------|
| **Adil Mabrouk** | `amabrouk` | 1337 |
| **Ismail** | `isrkik` | 1337 |

---

<p align="center">Made with ❤️ at <strong>1337 Coding School</strong></p>
