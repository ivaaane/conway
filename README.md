# Conway's Game of Life

Matrix greenrain screensavers are getting old!

This is a fairly simple implementation of Conway's celular automaton *The Game of Life*, directly available from the terminal. Now there is a tiny living world in your workspace :3

Right now the only initial configuration is *The R-pentomino* (this one):

```
 #
##
 ##
```

## Usage

Execute:

```sh
conway
```

Options:

| flag      | description                              |
|-----------|------------------------------------------|
|`-c [char]`| The character representing a living cell |
|`-d [int]` | The delay time between ticks             |
|`-r`       | Randomizes the initial generation        |
|`-l [int]` | Limits the number of generations         |
|`-h`       | Show help                                |

Other example:

```sh
conway -c 8 -d 25
```

## Install

```sh
git clone https://github.com/ivaaane/conway.git
cd conway
sudo make install
```

## Roadmap

- [x] Thing works.

- [ ] More default configurations.

- [ ] Option to input custom configuration.

- [x] Option to limit the number of generations.

- [x] Option to randomize the initial configuration.

- [ ] Color options.
