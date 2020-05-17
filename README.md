# UFFS Professors Asteroids

a simple game developed in C language using Allegro v5 library. This game it's not an Ateroids remake, it's more like a pacman with asteroids coming after the game player.

Since that was my first game and it was developed on 2015, the source code should not be took in consideration :) The repository started on 2020, just at this time I've refatored folder structure and documented it.

The game looks like following:

![game](/docs/img/game.png)

The game runs on any platform, but I don't even know how to make it on Windows platform, since I have just tested it on linux based platforms. 


### How do I get set up? ###

To run this game locally, first of all you need to clone this repository, the project had the following requirements: 

#### Requirements ####

* [Allegro V5](https://liballeg.org/)
* GCC/G++ compiler 

### Running Locally ###

To run the game locally, you need to run the following command to install source dependencies on linux based platform:

```sh
./install-deps.sh
```

after install dependencies you need to build program:

```sh
./build.sh
```

and then, start playing:

```sh
./game.sh
```

## Instructions ##

Use the arrow keys to move player and [F1, F2, F3] keys to change the character.